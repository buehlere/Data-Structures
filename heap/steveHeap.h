/*
 * Tung Nguyen
 * 7, November, 2018
 * File: Heap.h
 * ------------------------
 * Binary Heap Tree Class-Template  definition
 */

#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <string>
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Point.h"
#include <algorithm>

using namespace std;

void error(string msg)
{
  cerr << msg << endl;
  exit(EXIT_FAILURE);
}

/*
 * Class: Heap<T>
 * ---------------------------
 * This class implements a Heap of the specified value type
 */
template<typename T>
class Heap
{
public:
  Heap(); //default constructor
  Heap(T elements[], int arraySize);// build a heap tree
  T remove();
  void insert(T element);
  int getSize() const;
  void print();
  void increasePriority(T currElement, T newElement);
  void heapSort(T list[], int arraySize);

private:
  vector<T> v;

  int parent(int i)
  {
    if (i%2==0)
      return i/2 - 1;
    else
      return i/2;
  }

  void heapifyUp(int i)
  {
    int parents = parent(i);
    T temp;
    if (v[parents] > v[i] && i!=0 )
    {
      temp = v[parents];
      v[parents] = v[i];
      v[i] = temp;
      heapifyUp(parents);
    }
  }

  void heapifyDown(int i){
      // Max heapify
      // Maintain the heap property
      T temp;
      int left;
      int right;
      int maxindex = i;

      if (i == 0) {
        left = 1;
        right = left + 1;
      }
      else {
        left = 2*i;
        right = left + 1;
      }

      if(left < v.size() && v[left] < v[i])
        maxindex = left;
      if (right < v.size() && v[right] < v[maxindex])
        maxindex = right;
      if (maxindex != i) {
        temp = v[i];
        v[i] = v[maxindex];
        v[maxindex] = temp;
        heapifyDown(maxindex);
      }
    }

};

template<typename T>
/*
 * Function: print
 * Usage: heap.print()
 * -------------------
 * Print out all elements in the heap
 */
void Heap<T>::print()
{
  for (int i = 0; i<v.size(); i++)
    cout << v[i] << " ";
}

/*
 * Constructor: Heap
 * Usage: Heap<T> h;
 * -----------------
 * Initializes a heap
 */
template<typename T>
Heap<T>::Heap(T elements[], int arraySize)
{
  // build heap tree by using Floyd's method
  for (int i = 0; i < arraySize; i++)
  {
    insert(elements[i]);
  }
}

/*
 * Default Constructor: DoubleLink
 * Usage: Heap<T> h;
 * ------------------------------
 * Initializes a new empty Heap
 */
template<typename T>
Heap<T>::Heap()
{
}

/*
 * Implementation method: remove
 * Usage: heap.remove();
 * ------------------------------
 * Delete the root of the heap
 */
template<typename T>
T Heap<T>::remove()
{
  // check the size of vector
  if (v.size() < 1)
    error("Heap is overflow");
  // Swaping the first and last element so that we can pop back
  T removedElement = v[0];
  v[0] = v[v.size() -1];
  v[v.size() -1] = removedElement;
    // Remove the last element
  v.pop_back();
  // Maintain the heap property by calling heapifyDown
  heapifyDown(0);
  return removedElement;
}

/*
 * Implementation method: insert
 * Usage: h.insert();
 * ------------------------------
 * Insert a new node to the heap and maintain the heap property
 */
template<typename T>
void Heap<T>::insert(T element)
{
   // Append element to the heapHeap<T> h(list[], arraySize);
   v.push_back(element);
   // The index of the last node
   int lastElement = v.size() - 1;
   // Maintain the heap property
   heapifyUp(lastElement);
}

/*
 * Implementation method: increasePriority
 * Usage: h.increasePriority(7,9);
 * ------------------------------
 * Increase priorty of an element
 */
template<typename T>
void Heap<T>::increasePriority(T currElement, T newElement)
{
  // T temp;
  // int i = v.size() - 1;
  // if (newElement < currElement)
  //   error("New key is smaller than current key");
  // currElement = newElement;
  // while (i > 0 && v[parent(i)] < currElement)
  // {
  //   temp = v[parent(i)];
  //   v[parent(i)]= currElement;
  //   currElement = temp;
  //   heapifyUp(v[parent(i)]);
  // }
  if (newElement < currElement)
    error("New key is smaller than current key");
  ptrdiff_t pos = distance(v.begin(), find(v.begin(), v.end(), currElement));
  v[pos] = newElement;
  heapifyUp(pos);
}

/*
 * Implementation method: increasePriority
 * Usage: h.getSize();
 * ------------------------------
 * Get the number of element in the heap
 */
template<typename T>
int Heap<T>::getSize() const
{
  return v.size();
}

/*
 * Implementation method: heapSort
 * Usage: heapSort(list, size)
 * ------------------------------
 * Sort the element in a heap by using heap sort technique
 */
template <typename T>
void heapSort(T list[], int arraySize)
{
  // Build a max heap
  Heap<T> h(list, arraySize);
  for (int i = 0; i < arraySize; i++)
    {
      list[i] = h.remove();
    }
}

#endif
