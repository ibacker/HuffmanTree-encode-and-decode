#include "minheap.h"
template <class T>
MinHeap<T>::MinHeap(int sz)
{
   maxSize = sz;
   heap = new T[maxSize];
   if(heap== NULL)
   {
       std::cout<<"分配失败";
       exit(1);
   }
   currentSize = 0;
}
template <class T>
void MinHeap<T>::siftDown(int start,int m)
{
   int i = start;
   int j = 2*i+1;
   T temp = heap[i];
   while(j<=m)
   {
       if(j<m && heap[j]>heap[j+1])j++;
       if(temp<heap[j])break;
       else
       {
           heap[i] = heap[j];
           i = j;
           j = 2*j+1;

       }
   }
   heap[i] = temp;
}
template <class T>
void MinHeap<T>::siftUp(int start)
{
   int j = start;
   int i = (j-1)/2;
   T temp = heap[j];
   while(j>0)
   {
       if(heap[i]<temp) break;
       else
       {
           heap[j] = heap[i];
           j = i;
           i = (j-1)/2;
       }
   }
   heap[j] = temp;
}
template <class T>
bool MinHeap<T>::insert(T x)
{
    if(currentSize==maxSize)
    {
        std::cout<<"Heap full";
        return false;
    }
    heap[currentSize++] = x;
    siftUp(currentSize-1);
    return true;
}
template <class T>
T MinHeap<T>::removeMin()
{

    if(!currentSize)
    {
        std::cout<<"Heap empty";
        exit(1);
    }
    T x = heap[0];
    heap[0] = heap[currentSize-1];
    currentSize--;
    siftDown(0,currentSize-1);
    return x;
}
