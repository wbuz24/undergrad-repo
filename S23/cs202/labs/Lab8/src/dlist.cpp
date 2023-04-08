/* Will Buziak
 * Lab 8
 * cs202
 * Double-y Linked Lists
 * dlist.cpp
 * without useing the STL, implement doubley linked lists
 */ 

#include <iostream>
#include "dlist.hpp"
using namespace std;

Dnode* Dnode::Next() 
{ 
    return flink; // implicit this
};

Dnode* Dnode::Prev()
{
    return blink; // implicit this
};

Dlist::Dlist()
{
    Dnode *sentinel = new Dnode; // create a sentinel node
    sentinel->s = "";
    sentinel->flink = sentinel;
    sentinel->blink = sentinel;
    size = 0;
};

Dlist::Dlist(const Dlist &d)
{
    Dnode *sentinel = new Dnode;
    sentinel->s = ""; // create the sentinel node
    sentinel->flink = sentinel;
    sentinel->blink = sentinel;
    Dnode *l;
    size = 0;
    for (l = d.Begin(); l!= d.End(); l = l->Next()) {
        Push_Back(l->s); // copy each node from d
    }
};

Dlist& Dlist::operator= (const Dlist &d)
{
    Clear(); // clear the current Dlist
    Dnode *l;
    for (l = d.Begin(); l!= d.End(); l = l->Next()) Push_Back(l->s); // copy each node from d
    return *this;
};

Dlist::~Dlist()
{
    Clear(); // clear all nodes
    delete sentinel; // delete sentinel node
};

void Dlist::Clear()
{
    Dnode *l;
    for (l = Begin(); l != End(); l = l->Next()) Pop_Front(); // clear each element, save the sentinel node;
};

bool Dlist::Empty() const
{
    if (size != 0) return true;
    else return false; // check if size is equal to zero
};

size_t Dlist::Size() const
{
    return size; // return the size
};

void Dlist::Push_Front(const string &s)
{
    Dnode *next = sentinel->Next();
    Insert_Before(s, next); // insert before the first node
};

void Dlist::Push_Back(const string &s)
{
    Insert_Before(s, sentinel); // inserting before the "end"
};

string Dlist::Pop_Front()
{
    string s;
    Dnode *d = sentinel->flink; // beginning of dlist (not sentinel node)
    s = d->s;                   // grab string for returning
    Erase(d);
    return s;
};

string Dlist::Pop_Back()
{
    string s;
    Dnode *d = sentinel->blink;  // go to end of dlist
    s = d->s;
    Erase(d);
    return s;
};

Dnode* Dlist::Begin() const
{
    return sentinel->flink; // sentinel->flink is first node in the list
};

Dnode* Dlist::End() const
{
    return sentinel; 
}; // Pointer to "one past" the last node on the list.

Dnode* Dlist::Rbegin() const
{
    return sentinel->blink;  
};        // Pointer to the last node on the list

Dnode* Dlist::Rend() const
{
    return sentinel;
};          // Pointer to "one before" the first node on the list.

void Dlist::Insert_Before(const std::string &s, Dnode *n)
{
    Dnode *newnode = new Dnode; // create newnode and set it's pointers
    newnode->s = s;
    newnode->blink = n->blink;
    cout << "push back\n";
    newnode->flink = n;

    n->blink->flink = newnode; // reset surrounding node pointers to newnode
    n->blink = newnode;
    size++;

};

void Dlist::Insert_After(const std::string &s, Dnode *n)
{
    Dnode *next = n->flink;
    Insert_Before(s, next); // insert before the next node
};

void Dlist::Erase(Dnode *n)
{
    Dnode *next = n->flink;
    Dnode *prev = n->blink;

    next->blink = prev; // reset next & prev's pointers
    prev->flink = next;

    size--;

    delete n; // delete node
};
