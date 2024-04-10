#include "dataset.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string strip(const string value)
{
    string s = value;
    while (s.size() > 0 && std::isspace(s[s.size() - 1]))
        s.erase(s.end() - 1);
    while (s.size() > 0 && std::isspace(s[0]))
        s.erase(s.begin());
    return s;
}

int smart_compare(std::string& a, std::string& b);

void dataset::load_csv(string& filename)
{
    // Clear any existing data
    this->data.clear();

    // Open the file
    std::ifstream stream;
    stream.open(filename);
    if (!stream.is_open()) {
        throw std::system_error(errno, std::generic_category(), filename);
    }

    // Read the file
    while (!stream.eof())
    {
        // Read a line
        string s;
        if (!std::getline(stream, s))
            break;
        vector<string> empty;
        this->data.push_back(empty);
        vector<string>& current_row = this->data.back();

        // Break up the line into cells
        while (true)
        {
            // Find the next comma
            size_t pos = s.find(",");
            if (pos == string::npos)
            {
                // This is the last cell in the row
                current_row.push_back(s);
                break;
            }
            else
            {
                // This is not the last cell in the row
                current_row.push_back(s.substr(0, pos));
                s.erase(0, pos + 1); // erase the cell and the comma
            }
        }

        // Ensure all rows have the same size
        if (current_row.size() < 1)
        {
            // This row is empty, so just drop it
            this->data.pop_back();
        }
        else if (current_row.size() != this->data[0].size())
        {
            // Uh oh, the row is the wrong size!
            string s = "Error, row " + this->data.size();
            s += " has " + current_row.size();
            s += " elements. Expected " + this->data[0].size();
            throw std::runtime_error(s);
        }
    }

    // Move the first row into this->col_names
    this->col_names = this->data[0];
    this->data.erase(this->data.begin());
}

int dataset::num_cols(){
 return this->col_names.size();
}
int dataset::num_rows(){
    if(num_cols()==0){
        return 0;
    }
    return this->data.size();
}

void dataset::index_data()
{
    // Index the data
    indices.clear();
    indices.resize(this->num_cols());
    for (int i = 0; i < this->num_cols(); i++)
    {
        // Build an index for column i
        //right here is very important because the index is a reference to indices
        //[col num ] and that changes the values in the indicies for you
        vector< vector<string>* >& index = indices[i];
        for (int j = 0; j < this->num_rows(); j++)
            index.push_back(&this->data[j]);

    // sort the vector using the custom comp func
    std::sort(index.begin(), index.end(), [i](vector<string>* a, vector<string>* b){
            return smart_compare((*a)[i], (*b)[i]) < 0;
        });
}
}

vector<string>& dataset::get_row(int i){
    if (i>this->num_rows()||i<0){
        throw std::runtime_error("This row does not exist");
    }
    return this->data[i];
}

void dataset::print_index(int col_num)
{
    cout << "Sorted by column " << col_num << ":" << endl;
    cout << "-------------------" << endl;
    vector< vector<string>*> index = this->indices[col_num];
    for (size_t i = 0; i < index.size(); i++)
    {
        vector<string>& row = *index[i];
        for (size_t j = 0; j < row.size(); j++)
        {
            if (j > 0)
                cout << ", ";
            cout << row[j];
        }
        cout << endl;
    }
}

int dataset::bi_search(int i, string start){
// Quickly find the approximate row_num
int floor = 0;
vector< vector<string>*> index = this->indices[i];
int ceil = num_rows();
int row_num,cmp;

while(true){
    row_num = (floor + ceil) / 2;
    if (row_num == floor)
        break;
    cmp = smart_compare((*index[row_num])[i], start);
    if (cmp < 0)
        floor = row_num;
    else
        ceil = row_num;
}
// fine-tune the row_num
while (row_num > 0 && smart_compare((*index[row_num])[i], start) >= 0 ){
    row_num--;
}
while(row_num < num_rows() && smart_compare((*index[row_num])[i], start) < 0 ){
    row_num++;
}
return row_num;
}

void dataset::query(string start, string end, int column){
    int row_start = bi_search(column, start);
    cout << "Printing your Query :" << endl;
    cout << "-------------------" << endl;
    vector< vector<string>*> index = this->indices[column];
     for (size_t i = row_start;strip((*index[i])[column]) != end; i++)
    {
        vector<string>& row = *index[i];
        for (size_t j = 0; j < row.size(); j++)
        {
            if (j > 0)
                cout << ", ";
            cout << row[j];
        }
        cout << endl;
    }
    cout << "-------------------" << endl;
}

