#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <iostream>
#include "Node.h"
using namespace std;

template <class T>
class List{
private:
    Node<T>* root;
    Node<T>* tail;
    int length;
public:
    List();
    List(const List<T>& rhs);
    List<T>& operator=(const List<T>& rhs);
    List<T>& assign(const List<T>& rhs);
    ~List();
    void clear();
    bool isEmpty() const;
    Node<T>* begin() const;
    Node<T>* end() const;
    int size();
    void push_back(const T& value);
    T& getBack();
    T& getFront();
    void pop_back();
    void pop_front();
    void print() const;
};


#endif // LIST_H_INCLUDED
