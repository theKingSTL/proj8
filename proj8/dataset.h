#include <vector>
#include <iostream>
#include <cstring>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

#ifndef dataset_h
#define dataset_h

class dataset
{
   
public:
//   col     name
    vector< string > col_names;

//  matrix   row     cell
    vector< vector< string > > data;

//  indxes  col-idx  pointer-to-row
    vector< vector< vector<string>* > > indices;

    void load_csv(string& filename);
    int num_cols();
    int num_rows();
    void index_data();
    vector<string>& get_row(int i);
    void print_index(int col_num);
    int bi_search(int i, string start);
    void query(string start, string end, int column);
};


#endif