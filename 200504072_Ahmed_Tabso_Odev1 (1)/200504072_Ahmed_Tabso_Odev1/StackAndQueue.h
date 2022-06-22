#ifndef STACKANDQUEUE_H_INCLUDED
#define STACKANDQUEUE_H_INCLUDED

#include "List.h"
#include "List.cpp"

template <class T>
class Stack : private List<T> {
public:
    Stack();
    bool isEmpty() const;
    int size();
    void push(const T& value);
    void pop();
    T topAndPop();
    T getTop() ;
    void print() const;
};

template <class T>
class Queue : private List<T>{
public:
	Queue();
	bool isEmpty() const;
	int size();
   	void enqueue(const T& value);
   	void dequeue();
   	T dequeueAndFront();
   	T getFront();
    void print() const;
};

#endif // STACKANDQUEUE_H_INCLUDED
