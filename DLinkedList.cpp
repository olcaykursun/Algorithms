#include <iostream>
#include <string>

using namespace std;

typedef string Elem;				// list element type

class DNode {					// doubly linked list node
private:
    Elem elem;					// node element value
    DNode* prev = nullptr;				// previous node in list
    DNode* next = nullptr;				// next node in list
    friend class DLinkedList;			// allow DLinkedList access
};

class DLinkedList {				// doubly linked list
public:
    DLinkedList();				// constructor
    ~DLinkedList();				// destructor
    bool empty() const;				// is list empty?
    const Elem& front() const;			// get front element
    const Elem& back() const;			// get back element
    void addFront(const Elem& e);		// add to front of list
    void addBack(const Elem& e);		// add to back of list
    void removeFront();				// remove from front
    void removeBack();				// remove from back

    //members for debugging purposes
    void print();
    int n;

private:					// local type definitions
    DNode* header;				// list sentinels
    DNode* trailer;

protected:					// local utilities
    void add(DNode* v, const Elem& e);		// insert new node before v
    void remove(DNode* v);			// remove node v
};

void DLinkedList::print() {
    DNode* current = header->next;
    cout << "[ ";
    while (current != trailer)
    {
        cout << current->elem << " ";
        current = current->next;
    }
    cout << "]\n";
}

DLinkedList::DLinkedList() : n(0) {			// constructor
    header = new DNode;				// create sentinels
    trailer = new DNode;
    header->next = trailer;			// have them point to each other
    trailer->prev = header;
}

DLinkedList::~DLinkedList() {			// destructor
    while (!empty()) removeFront();		// remove all but sentinels
    delete header;				// remove the sentinels
    delete trailer;
}

bool DLinkedList::empty() const		// is list empty?
{
    return (header->next == trailer);
}

const Elem& DLinkedList::front() const	// get front element
{
    return header->next->elem;
}

const Elem& DLinkedList::back() const		// get back element
{
    return trailer->prev->elem;
}

// insert new node before v
void DLinkedList::add(DNode* v, const Elem& e) {
    DNode* u = new DNode;  u->elem = e;		// create a new node for e
    u->next = v;				// link u in between v

    DNode* t = v->prev;

    u->prev = t;				// ...and v->prev
    t->next = u;
    v->prev = u;
}

void DLinkedList::addFront(const Elem& e)	// add to front of list
{
    add(header->next, e);
    n++;
}

void DLinkedList::addBack(const Elem& e)	// add to back of list
{
    add(trailer, e);
    n++;
}

void DLinkedList::remove(DNode* v) {		// remove node v
    DNode* u = v->prev;				// predecessor
    DNode* w = v->next;				// successor
    u->next = w;				// unlink v from list
    w->prev = u;
    delete v;
    n--;
}

void DLinkedList::removeFront()		// remove from font
{
    if (!empty()) remove(header->next);
}

void DLinkedList::removeBack()		// remove from back
{
    if (!empty()) remove(trailer->prev);
}

DLinkedList* foo()
{
    DLinkedList* a = new DLinkedList;
    a->addFront("5");
    return a;
}

int main() {
    DLinkedList lst;
    DLinkedList* tmp;
    tmp = foo();
//    lst = *tmp;
    lst.addFront("7");
    lst.addBack("1");

    lst.print();
    tmp->print();
    delete tmp;
    lst.print();

    return EXIT_SUCCESS;
}
