#ifndef MINHEAP_H
#define MINHEAP_H
#include<iostream>
#include<string.h>
using namespace std;

template <class T>
class MinHeap
{
private:
    int maxSize;
    int currentSize;
    T *heap;
    void siftDown(int start,int m);//自上而下，从start到m下滑调整为最小堆
    void siftUp(int start);//自下而上，从start上滑调整为最小堆
public:
    MinHeap(int sz=0);
    bool insert(T);
    T removeMin();
    bool isEmpty()
    {return currentSize==0;}
    bool isFull()
    {return currentSize==maxSize;}
    void makeEmpty()
    {currentSize=0;}
};

#endif // MINHEAP_H
