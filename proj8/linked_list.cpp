#include "linked_list.h"
#include <iostream>
#include <string.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
int g_count= 0;

string strip(const string value);

int smart_compare(std::string& a, std::string& b) {
    // Skip the parts that are the same
    a = strip(a);
    b = strip(b);
    long unsigned int i = 0;
    while(i < a.size() && i < b.size() && a[i] == b[i]) {
        i++;
    }
    if (i >= a.size()) {
        if (i >= b.size()) {
            return 0;
        } else {
            return -1;
        }
    } else if (i >= b.size()) {
        return 1;
    }

    // Skip zeros
    long unsigned int a_start = i;
    long unsigned int b_start = i;
    while (a_start < a.size() && a[a_start] == '0')
        a_start++;
    while (b_start < b.size() && b[b_start] == '0')
        b_start++;

    // Count digits
    long unsigned int a_digits = a_start;
    while (a_digits < a.size() && a[a_digits] >= '0' && a[a_digits] <= '9')
        a_digits++;
    long unsigned int b_digits = b_start;
    while (b_digits < b.size() && b[b_digits] >= '0' && b[b_digits] <= '9')
        b_digits++;
    if (a_digits > 0 && a_digits < b_digits) {
        return -1; // a comes first because its number is shorter
    } else if (b_digits > 0 && b_digits < a_digits) {
        return 1; // b comes first because its number is shorter
    } else {
        // The numbers are the same length, so compare alphabetically
        return strcmp(a.c_str() + a_start, b.c_str() + b_start);
    }
}

LinkedListNode::LinkedListNode(string& val)
{
    this->next = nullptr;
    this->value = val;
}

LinkedListNode::~LinkedListNode()
{
    delete(this->next);
}

LinkedList::LinkedList()
{
    this->length=0;
    this->first=nullptr;
    this->last=nullptr;
}

LinkedList::~LinkedList()
{
}

void LinkedList::push_back(string& s)
{
    LinkedListNode* new_node = new LinkedListNode(s);
    if (this->first)
    {
        if (!this->last)
            throw std::runtime_error("How is there a first, but no last?");
        this->last->next = new_node;
    }
    else
    {
        if (this->last)
            throw std::runtime_error("How is there a last, but no first?");
        this->first = new_node;
    }
    this->last = new_node;
    this->length++;
}

void LinkedList::push_front(string& s)
{
    LinkedListNode* new_node = new LinkedListNode(s);
    new_node->next= this->first;
    if (this->first)
    {
        if (!this->last)
            throw std::runtime_error("How is there a first, but no last?");
    }
    else
    {
        if (this->last)
            throw std::runtime_error("How is there a last, but no first?");
    this->last=new_node;
    }
    this->first= new_node;
    this->length++;
    
}

void LinkedList::pop_front(bool all_of_it)
{
if (!this->first)
    throw std::runtime_error("There are no nodes to pop off :(");
else if (all_of_it==true)
{
    delete(this->first);
    this->last=nullptr;
    this->first=nullptr;
    this->length=0;
}
else if (all_of_it==false){
    LinkedListNode* old_node = this->first->next; 
    this->first->next = nullptr;
    delete(this->first);
    this->first = old_node;
    this->length--;
    if (this->length==0){
        this->last=nullptr;
    }

}
}

int LinkedList::size()
{
return(this->length);
}
void LinkedList::set_size(int val)
{
    this->length=val;
}

string LinkedList::get_first()
{
    if(!this->first)
        throw std::runtime_error("There is no first value my boy");
    return(this->first->value);
}

string LinkedList::get_last()
{
    return(this->last->value);
}

void LinkedList::two_list(int index,LinkedList& second)
{
    if(index>=this->length)
        throw std::runtime_error("The index you have put in is too large, or the length of the previous list");
    if(index<=0)
        throw std::runtime_error("Index needs to be a positive number");

    for (int i = 0; i < index; i++) {
        second.push_back(this->first->value);
        (this->pop_front(false));
        //string new_word = get_first();  
        //second.push_back(new_word);           
    }
}

LinkedList LinkedList::merge(LinkedList& a, LinkedList& b)
{
    bool merging=true;
    LinkedList merged_list;
    while (merging){
        if(a.size()==0){
            merging=false;
            unsigned long int rest=b.size();
            for(unsigned long int i=1;i<=rest;i++){
                string b_first=b.get_first();
                merged_list.push_back(b_first);
                b.pop_front(false);
            }
        }
        else if(b.size()==0){
            merging=false;
            unsigned long int rest=a.size();
            for(unsigned long int i=1;i<=rest;i++){
                string a_first=a.get_first();
                merged_list.push_back(a_first);
                a.pop_front(false);
            }
        }
        else{
            string a_first=a.get_first();
            string b_first=b.get_first();
            int compare_value=smart_compare(a_first, b_first);
            g_count++;
            if (compare_value==0){
                merged_list.push_back(a_first);
                a.pop_front(false);
                merged_list.push_back(b_first);
                b.pop_front(false);
            }
            else if (compare_value<=-1){
                merged_list.push_back(a_first);
                a.pop_front(false);
            }
            else if (compare_value>=1){
                merged_list.push_back(b_first);
                b.pop_front(false);
            }
            else{
               throw std::runtime_error("Your compare value was out of range"); 
            }
        }
}
return merged_list;
}

LinkedList LinkedList::sort(LinkedList& a)
{
    if (a.size()==1)
        return a;
    else if (a.size()<=0)
       throw std::runtime_error("Your list cant be sorted its empty or negative");
    else{
        int index = a.size() / 2;
        LinkedList new_list2;
        a.two_list(index, new_list2);
        LinkedList sorted_a = sort(a); // Recursively sort the first half
        LinkedList sorted_new_list2 = sort(new_list2); // Recursively sort the second 
        LinkedList new_list = merge(sorted_a, sorted_new_list2); // Merge the sorted two
        return new_list;
    }  
}



