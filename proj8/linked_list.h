#ifndef linked_list
#define linked_list
#include <string>

// Represents a single node in a linked list
extern int g_count;

class LinkedListNode
{

public:
    std::string value;
    LinkedListNode* next;
    LinkedListNode(std::string& val);
    virtual ~LinkedListNode();
};



// A data structure that holds a list of strings
class LinkedList
{
protected:
    int length;
    LinkedListNode* first;
    LinkedListNode* last;

public:
    LinkedList();
    virtual ~LinkedList();
    void push_back(std::string& s);
    void push_front(std::string& s);
    void pop_front(bool all_of_it);
    int size();
    std::string get_first();
    std::string get_last();
    void two_list(int index,LinkedList& second);
    void set_size(int val);
    LinkedList sort(LinkedList& a);
    LinkedList merge(LinkedList& a, LinkedList& b);
};

#endif