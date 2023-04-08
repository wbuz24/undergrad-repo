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
  return flink; 
};

Dnode* Dnode::Prev()
{
 return blink;
};

Dlist::Dlist()
{
  sentinel->s = "";
  sentinel->flink = sentinel;
  sentinel->blink = sentinel;
  size = 0;
};

Dlist::Dlist(const Dlist &d)
{
  Dlist *copy = new Dlist;
  Dnode *l;  
  for (l = d.Begin(); l != d.End(); l = l->Next()) copy->Push_Back(l->s); 
   
};

Dlist& Dlist::operator= (const Dlist &d)
{

};

Dlist::~Dlist()
{

};

void Dlist::Clear()
{
};

bool Dlist::Empty() const
{
  

};

size_t Dlist::Size() const
{
  return size;
};

void Dlist::Push_Front(const string &s)
{
  Dnode *d = new Dnode;
  d->s = s;
  d->flink = sentinel->flink;
  sentinel->flink = d;
  d->blink = sentinel;
  size--;

};

void Dlist::Push_Back(const string &s)
{
  Dnode *d = new Dnode;
  d->s = s;
  d->flink = sentinel;
  d->blink = sentinel->blink;
  sentinel->blink = d;
  size++;
};

string Dlist::Pop_Front()
{
  string s;
  Dnode *d = sentinel->flink; // beginning of dlist (not sentinel node)
  sentinel->flink = d->flink; // set sentinel's flink
  d->flink->blink = sentinel; // sent flink's blink to sentinel
  s = d->s;                   // grab string for returning
  delete d;
  return s;

};

string Dlist::Pop_Back()
{
 string s;
 Dnode *d = sentinel->blink;  // go to end of dlist
 s = d->s;                    // grab string for return
 sentinel->blink = d->blink;  // set sentinel blink 
 d->blink->flink = sentinel;  // sent blink's flink
 delete d;                    // delete the node
 return s;
};

Dnode* Dlist::Begin() const
{
  return sentinel->flink;
};

Dnode* Dlist::End() const
{
  return sentinel;
}; // Pointer to "one past" the last node on the list.
   
Dnode* Dlist::Rbegin() const
{
  return sentinel;  
};        // Pointer to the last node on the list
    
Dnode* Dlist::Rend() const
{
  return sentinel->flink;
};          // Pointer to "one before" the first node on the list.

void Dlist::Insert_Before(const std::string &s, Dnode *n)
{
  Dnode *prev = n->blink; // next and previous Dnodes
  
  Dnode *newnode = new Dnode; // create newnode and set it's pointers
  newnode->s = s;
  newnode->blink = prev;
  newnode->flink = n;

  prev->flink = newnode; // reset surrounding node pointers to newnode
  n->blink = newnode;
    
};

void Dlist::Insert_After(const std::string &s, Dnode *n)
{
  Dnode *next = n->flink;

  Dnode *newnode = new Dnode; // create newnode and set it's pointers;
  newnode->s = s;
  newnode->blink = n;
  newnode->flink = next;

  n->flink = newnode; // reset surrounding node pointers to newnode
  next->blink = newnode;

};
    
void Dlist::Erase(Dnode *n)
{
  Dnode *next = n->flink;
  Dnode *prev = n->blink;
  
  next->blink = prev; // reset next & prev's pointers
  prev->flink = next;

  delete n; // delete node
};
