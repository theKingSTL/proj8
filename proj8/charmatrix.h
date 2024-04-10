#include <vector>
#include <iostream>
#include <cstring>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

#ifndef charmatrix_h
#define charmatrix_h


class CharMatrix
{
protected:
    vector<string> chars;

public:
    CharMatrix();
    virtual ~CharMatrix();
    void resize(int width, int height);
    int width();
    int height();
    char get(int x, int y);
    void put(int x, int y, char c);
};

#endif

