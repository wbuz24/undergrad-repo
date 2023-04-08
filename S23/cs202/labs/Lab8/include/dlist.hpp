#pragma once
#include <string>

class Dnode {
  friend class Dlist;
  public:
    std::string s;
    Dnode *Next();
    Dnode *Prev();
  protected:
    Dnode *flink;
    Dnode *blink;
};

class Dlist {
  public:

    /* Constructors, Destructor, Assignment Overload */

    Dlist();
    Dlist(const Dlist &d);
    Dlist& operator= (const Dlist &d);
    ~Dlist();

    void Clear();          // This should not delete the sentinel node.
    bool Empty() const;
    size_t Size() const;

    /* Put new strings on the front or back of the list */

    void Push_Front(const std::string &s);
    void Push_Back(const std::string &s);

    /* Remove and return the first or last element of the list */

    std::string Pop_Front();
    std::string Pop_Back();

    Dnode *Begin() const;         // Pointer to the first node on the list 
    Dnode *End() const;           // Pointer to "one past" the last node on the list.
    Dnode *Rbegin() const;        // Pointer to the last node on the list
    Dnode *Rend() const;          // Pointer to "one before" the first node on the list.

    void Insert_Before(const std::string &s, Dnode *n);
    void Insert_After(const std::string &s, Dnode *n);
    void Erase(Dnode *n);

  protected:
    Dnode *sentinel;
    size_t size;
};
