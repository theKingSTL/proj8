#include "config.h"
#include "charmatrix.h"
#include "linked_list.h"
#include "dataset.h"
#include <vector>
#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<string> g_lex;
CharMatrix g_grid;
LinkedList g_link_list;
dataset g_dataset;

void load_csv()
{
    cout << "Please enter a filename of a .csv file:" << endl;
    cout << "> ";
    string filename;
    getline(std::cin, filename);
    g_dataset.load_csv(filename);
    g_dataset.index_data();
    //for(int i=0;i<g_dataset.num_cols();i++){
    //g_dataset.print_index(i);}
}

void find_letter(string word, int depth, int x, int y, int size, bool& found){
    if (depth==size){
        char lc = g_grid.get(x,y);
               if(word[depth-1]==lc){
                found=true;
    }
    }
    else if(depth==0){
        int c_width=g_grid.width();
        int c_height=g_grid.height();
        for(int width=0;width<c_width;width++){
            for(int height=0;height<c_height;height++){
               char letter_compare=g_grid.get(width,height);
               if(word[depth]==letter_compare){
                    find_letter(word, depth+1,width,height, size, found);
               } 
            }
        }
    }

    else if(depth>0){
    int c_width=g_grid.width();
    int c_height=g_grid.height();
    if (x > 0){
            char letter_compare=g_grid.get(x-1,y);
            char replace=g_grid.get(x,y);
            if(word[depth]==letter_compare){
                    g_grid.put(x, y, '@');
                    find_letter(word, depth+1,x-1,y, size, found);
                    g_grid.put(x, y, replace);
               } 
    }
    if (y > 0){
            char letter_compare=g_grid.get(x,y-1);
            char replace=g_grid.get(x,y);
            if(word[depth]==letter_compare){
                    g_grid.put(x, y, '@');
                    find_letter(word, depth+1,x,y-1, size, found);
                    g_grid.put(x, y, replace);
               } 
    }
    if (x < c_width-1){
            char letter_compare=g_grid.get(x+1,y);
            char replace=g_grid.get(x,y);
            if(word[depth]==letter_compare){
                    g_grid.put(x, y, '@');
                    find_letter(word, depth+1,x+1,y, size, found);
                    g_grid.put(x, y, replace);
               } 
    }
    if (y < c_height-1){
            char letter_compare=g_grid.get(x,y+1);
            char replace=g_grid.get(x,y);
            if(word[depth]==letter_compare){
                    g_grid.put(x, y, '@');
                    find_letter(word, depth+1,x,y+1, size, found);
                    g_grid.put(x, y, replace);
               } 
    }
    if (x > 0 && y>0){
            char letter_compare=g_grid.get(x-1,y-1);
            char replace=g_grid.get(x,y);
            if(word[depth]==letter_compare){
                    g_grid.put(x, y, '@');
                    find_letter(word, depth+1,x-1,y-1, size, found);
                    g_grid.put(x, y, replace);
               } 
    }
    if (x > 0 && y<c_height-1){
            char letter_compare=g_grid.get(x-1,y+1);
            char replace=g_grid.get(x,y);
            if(word[depth]==letter_compare){
                    g_grid.put(x, y, '@');
                    find_letter(word, depth+1,x-1,y+1, size, found);
                    g_grid.put(x, y, replace);
               } 
    }
    if (x < c_width-1 && y<c_height-1){
            char letter_compare=g_grid.get(x+1,y+1);
            char replace=g_grid.get(x,y);
            if(word[depth]==letter_compare){
                    g_grid.put(x, y, '@');
                    find_letter(word, depth+1,x+1,y+1, size, found);
                    g_grid.put(x, y, replace);
               } 
    }
    if (x < c_width-1 && y>0){
            char letter_compare=g_grid.get(x+1,y-1);
            char replace=g_grid.get(x,y);
            if(word[depth]==letter_compare){
                    g_grid.put(x, y, '@');
                    find_letter(word, depth+1,x+1,y-1, size, found);
                    g_grid.put(x, y, replace);
               } 
    }
    }

    else {
        cout<<"error your depth is not in the bounds"<<endl;
    }
}

void boogle(){
    for(unsigned int i=0; i<g_lex.size(); i++){
        int depth=0;
        int word_size=g_lex[i].size();
        bool found=false;
        int x=0;
        int y=0;
        find_letter(g_lex[i],depth,x,y,word_size,found);
            if (found==true){
                cout << g_lex[i]<<endl;}
    }
}

void print_char_matrix()
{
    for (int y = 0; y < g_grid.height(); y++)
    {
        for (int x = 0; x < g_grid.width(); x++)
        {
            cout << g_grid.get(x, y);
        }
        cout << endl;
    }
}

void fill(int x, int y, char c, int max_depth){
if (max_depth==0){
    return;}

    if (config.debug)
{
    usleep(100000);
    for (int i = 0; i < 20; i++)
        cout << endl;
    print_char_matrix();
    cout.flush();
}
    char bef = g_grid.get(x, y);
    if (bef == c)
        return;
    g_grid.put(x, y, c);
    if (x > 0 && g_grid.get(x - 1, y) == bef)
        fill (x - 1, y, c, max_depth - 1);
    if (y > 0 && g_grid.get(x, y - 1) == bef)
        fill (x, y - 1, c, max_depth - 1);
    if (x + 1 < g_grid.width() && g_grid.get(x + 1, y) == bef)
        fill (x + 1, y, c, max_depth - 1);
    if (y + 1 < g_grid.height() && g_grid.get(x, y + 1) == bef)
        fill (x, y + 1, c, max_depth - 1);
}

void flood_fill()
{
    string word;
    cout << "Please enter a starting column:" << endl;
    cout << "> ";
    getline(cin, word);
    int x = stoi(word);
    cout << "Please enter a starting row:" << endl;
    cout << "> ";
    getline(cin, word);
    int y = stoi(word);
    cout << "Please enter a fill character:" << endl;
    cout << "> ";
    getline(cin, word);
    int c = word[0];
    cout << "Please enter the max fill depth:" << endl;
    cout << "> ";
    getline(cin, word);
    int max_depth = stoi(word);
    fill(x, y, c, max_depth);
}

void load_char_matrix()
{
    if (!config.quiet)
    {
        cout << "Please enter a grid of characters." << endl;
        cout << "All rows should have the same length." << endl;
        cout << "When you are done, just press Enter." << endl;
    }
    vector<string> grid;
    while(true)
    {
        string row;
        getline(cin, row);
        if (row.compare("") == 0)
            break;
        else if (grid.size() > 0 && row.size() != grid[0].size())
            throw std::runtime_error("Rows in a CharMatrix must all have the same size!");
        else
            grid.push_back(row);
    }
    int height = grid.size();
    int width = 0;
    if (height > 0)
        width = grid[0].size();
    g_grid.resize(width, height);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            g_grid.put(x, y, grid[y][x]);
        }
    }
}
void destroy_lexicon(vector<string>& lex)
{
    int word_capacity=lex.size();
    string popped_word;
    for (int i=word_capacity;i>0;i--){
        popped_word=lex.back();
        cout << popped_word << endl;
        lex.pop_back();
    }
}

void test_linked_list(LinkedList link){
    bool pass_test=true;
    int counter=0;
    string compare="1";

    //tests the push back method 
    for(int i=1;i<5;i++){
    int a=i;
    string str = std::to_string(a);
    link.push_back(str);
    if(link.get_first()!=compare)
        pass_test=false;
    if(link.get_last()!=str)
        pass_test=false;
    if(link.size()!=i)
        pass_test=false;
    }

    if(pass_test==false){
        counter=counter+1;
        cout<<"You failed test one (push back method)"<<endl;
    }
    pass_test=true;

    //tests the pop front with false method 
    for(int i=4;i>0;i--){
        link.pop_front(false);
        if ((i==1)&&(link.size()!=0)){
            pass_test=false;}
    }

    if(pass_test==false){
    counter=counter+1;
    cout<<"You failed test two (pop front when false method)"<<endl;
    }
    pass_test=true;

    //tests the push front method
    for(int i=1;i<5;i++){
    int a=i;
    string str = std::to_string(a);
    link.push_front(str);
    if(link.get_first()!=str)
        pass_test=false;
    if(link.get_last()!=compare)
        pass_test=false;
    if(link.size()!=i)
        pass_test=false;
    }

    if(pass_test==false){
    counter=counter+1;
    cout<<"You failed test three (push front method)"<<endl;
    }
    pass_test=true;

    //tests the pop front with true method 
    for(int i=1;i>0;i--){
        link.pop_front(true);
        if ((i==1)&&(link.size()!=0)){
            pass_test=false;}
    }

    if(pass_test==false){
    counter=counter+1;
    cout<<"You failed test four (pop front when true method)"<<endl;
    }
    pass_test=true;

    //test for split in two link list method
    LinkedList second;
    string str1="1";
    string str2="2";
    string str3="3";
    string str4="4";
    int index=2;

    link.push_back(str1);
    link.push_back(str2);
    link.push_back(str3);
    link.push_back(str4);
    link.two_list(index,second);
    
    if(link.get_first()!=str3)
        pass_test=false;
    if(link.get_last()!=str4)
        pass_test=false;
    if(link.size()!=index)
        pass_test=false;
    
    if(second.get_first()!=str1)
        pass_test=false;
    if(second.get_last()!=str2)
        pass_test=false;
    if(second.size()!=index)
        pass_test=false;

    if(pass_test==false){
    counter=counter+1;
    cout<<"You failed test five (split list mehtod 2)"<<endl;
    }
    pass_test=true;

    if(counter==0)
        cout<<"You Passed All Tests!!"<<endl;

  
}

void fill_lexicon(vector<string>& lex) {
while(true)
{

    quiet("\n");
    quiet("Please enter another word\n");
    quiet("> ");
    string word;
    getline(cin,word);

    if (word.size() == 0)
    {
        break;
    }  
    else if (word.compare("-") == 0){
        lex.pop_back();
    }
    else{
        lex.push_back(word);
    }
    

    quiet( "So far, the words you have entered are:\n");
if(config.quiet==false){
    for (unsigned int i = 0; i < lex.size(); i++)
    {
        cout << i << ". " << lex[i] << endl;
    }
}
}}

void merg_lexicon()
{
    LinkedList lex_link;
    unsigned int i=0;
    unsigned int link_size2 =g_lex.size();
    g_count=0;
    if (g_lex.size()<=0){
        throw std::runtime_error("Lex is to small to merge");
        }
    while (i < link_size2)
        {
            string lex_value=g_lex[i];
            lex_link.push_back(lex_value);
            i++;
        }
    i=0;
    while (i < link_size2)
    {
        g_lex.pop_back();
        i++;
    }
    lex_link=lex_link.sort(lex_link);
    unsigned int link_size =lex_link.size();

    for(unsigned int in = 0; in < link_size; in++){
        string word=lex_link.get_first();
        g_lex.push_back(word);
        lex_link.pop_front(false);
    }
    cout << "comparisons: " << g_count << endl;

}

void query()
{
    // Ask for query parameters
    cout << "Please enter a column index:" << endl;
    cout << "> ";
    string column_str;
    getline(std::cin, column_str);
    int column = stoi(column_str);
    cout << "Please enter a starting value:" << endl;
    cout << "> ";
    string start;
    getline(std::cin, start);
    cout << "Please enter an ending value:" << endl;
    cout << "> ";
    string end;
    getline(std::cin, end);

    // Perform the query
    g_dataset.query(start, end, column); // (you will write this method)
}

int main(int argc, char** argv)
{
config.parse_flags(argc, argv);
log("---Running in debug mode---");
string option;

while (true)
{
    cout << "Dylan Stroud PF2 projects" << endl;
    cout << "Lexicon size: " << g_lex.size() << endl << endl;
    cout << "0. Quit" << endl;
    cout << "1. Fill lexicon" << endl;
    cout << "2. Tear Down Lexicon" << endl;
    cout << "3. Load char matrix" << endl;
    cout << "4. Print char matrix" << endl;
    cout << "5. Flood fill" << endl;
    cout << "6. Boggle" << endl;
    cout << "7. Linked List unit test" << endl;
    cout << "8. Merge Sort" << endl;
    cout << "9. Load CSV file" << endl;
    cout << "10. Query" << endl;
    cout << "> ";
    getline(cin,option);
    
    if (option.compare("0") == 0) {
        break;
    } else if ((option.compare("1") == 0)){
        fill_lexicon(g_lex);
    }
     else if (option.compare("2") == 0){
        destroy_lexicon(g_lex);
    } 
     else if (option.compare("3") == 0){
        load_char_matrix();
    } 
     else if (option.compare("4") == 0){
        print_char_matrix();
    } 
     else if (option.compare("5") == 0){
        flood_fill();
    } 
     else if (option.compare("6") == 0){
        boogle();
    } 
    else if (option.compare("7") == 0){
        test_linked_list(g_link_list);
    } 
     else if (option.compare("8") == 0){
        merg_lexicon();
    } 
     else if (option.compare("9") == 0){
        load_csv();
    } 
      else if (option.compare("10") == 0){
        query();
    } 
    else {
        cout << option << " Was not one of the options. Quitting." << endl;
        break;
    }
}
}


