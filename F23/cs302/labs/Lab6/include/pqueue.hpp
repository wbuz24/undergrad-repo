#include <iostream>
#include <vector>
#include <set>

/* The Main Priority Queue Interface. */

class PQueue {
  public:
    virtual ~PQueue() {};
    virtual void    Push(double d) = 0;
    virtual double  Pop()          = 0;
    virtual size_t  Size() const   = 0;
    virtual bool    Empty() const  = 0;
    virtual void    Print() const  = 0;
};

/* PQueueSet: Implementing the priority 
   queue with a multiset */

class PQueueSet : public PQueue {
  public:
    void    Push(double d);
    double  Pop();
    size_t  Size() const;
    bool    Empty() const;
    void    Print() const;

    PQueueSet();
  protected:
    std::multiset <double> elements;
};

/* PQueueHeap: Implementing the priority 
   queue with a binary heap.  You'll note
   that there is a second constructor
   here that creates the priority queue
   from a vector of doubles. */

class PQueueHeap : public PQueue {
  public:
    void    Push(double d);
    double  Pop();
    size_t  Size() const;
    bool    Empty() const;
    void    Print() const;

    PQueueHeap();
    PQueueHeap(const std::vector <double> &init);
  protected:
    std::vector <double> h;
    void Percolate_Down(size_t index);
};
