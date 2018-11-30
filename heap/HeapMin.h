/*
Author: Eric Buehler
Date: 10/4/2018
filename: Heap.h
This header file implements a Min-Heap structure.
*/



#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <algorithm>
#include "Point.h"
#include "Job.h"
#include <stdexcept>
using namespace std;

//Min-Heap
template<typename T>
class Heap
{
public:
  Heap();
  Heap(T elements[], int arraySize);// build a heap tree
  T remove();
  void insert(T element);
  int getSize() const;
  void increasePriority(T curElement, T newElement);
  void heapSort(T list[], int arraySize);
  void print(); //aditional method to print tree
  T min();


private:
  vector<T> v;
  void heapifyUp(int i)
  /*
  The purpose of this function is to traverse up the tree.
  input: index of where to start traversal
  output: NA, maintains heap structure
  Time Complexity: O(logn) we only have to traverse the height of tree (logn)
  */
  {
    int parent = (i-1)/2;
    while(v[i] < v[parent] && i != 0)
    {

        //perform swap
       T temp = v[parent];
       v[parent] = v[i];
       v[i] = temp;
       //update index
       i = parent;
       parent = (i-1)/2;
    }
  }

  void heapifyDown(int i)
  {
    /*
    The purpose of this function is to traverse down the tree.
    input: index of where to start traversal
    output: NA, maintains heap structure
    Time Complexity: O(logn) we only have to traverse the height of tree (logn)
    */
    int left ; //relation of right node
    int right; //relation of left node
    int largest; //keep track of largest node
    //check left

    if (i == 0)
      {
        left = 1;
        right = left + 1;
      }
      else
      {
        left = (2*i)+1;
        right = left + 1;
      }

    if(left <= v.size() && v[left] < v[i])
    {
      largest = left;
    } else
    {
      largest = i;
    }
    //check right
    if(right <= v.size() && v[right]< v[largest])
    {
      largest = right;
    }
    if(largest != i)
    {
      //swap largest, recursive call to continue down the tree
      T temp = v[largest];
      v[largest] = v[i];
      v[i] = temp;
      heapifyDown(largest);
    }
  }

};

template<typename T>
Heap<T>::Heap()
{
  //empty constructor
}

template<typename T>
Heap<T>::Heap(T elements[], int arraySize)
{
  /*
  this function constructs a heap structure when provided an array and the
  array size.
  input: an array of elements , size of the array
  output: NA, constructs tree when provided optional arguments
  Time Complexity: O(n) Floyd's method 
  O(n) soon.
  */
  for(int i=0; i < arraySize; i++)
  {
    v.push_back(elements[i]);
  }
  int size = v.size();
  for(int i = (size / 2); i>= 0; i--)
  {
    heapifyDown(i);
  }
}

template<typename T>
T Heap<T>::min()
{
  return v[0];
}

// Remove the root from the heap
template<typename T>
T Heap<T>::remove()
{
  /*
  this function constructs removes the Min value of the tree (the root), and
  maintains the heap structure.
  input: NA, removes Min
  output: the removed element (the root of the Min heap)
  Time Complexity: O(logn) We delete the root and maintain heap structure
  */
  // check the size of vector
  if(v.size() < 1)
  {
    std::cout << "heap underflow" << "\n";
    throw std::invalid_argument( "heap underflow" );

  }

  T removedElement = v[0];
  // Copy the last to root
  v[0] = v[v.size() - 1];
  // Remove the last element
  v.pop_back();
  // Maintain the heap property by calling heapifyDown
  heapifyDown(0);
  return removedElement;
}

// Insert element into the heap and maintain the heap property
template<typename T>
void Heap<T>::insert(T element)
{
  /*
  this function inserts an element into the Min heap. It first adds the element
  to the vector, and then maintains the heap structure with heapifyUp.
  input: the element to be added to the heap structure
  output: NA, element is added to heap
  Time Complexity: O(logn) We add the new element and call heapify up
  */
  v.push_back(element);
  int index = v.size()-1;
  heapifyUp(index);
}

template<typename T>
void Heap<T>::increasePriority(T curElement, T newElement)
{
  /*
  this function increase the priority of the given elements
  input: the value to be replaced, and the new element
  output: the removed element (the root of the Min heap)
  Time Complexity: O(logn) We add the new element and call heapify up
  */
  if(newElement > curElement)
  {
    //check to see if the element is smaller
    std::cout << "new is greater than current key" << "\n";
    throw std::invalid_argument( "new is greater than current key" );
  }
  //identify location of curElement
  ptrdiff_t pos = distance(v.begin(), find(v.begin(), v.end(), curElement));
  //replace curElement with newElement
  v[pos] = newElement;
  //maintain heap structure after replace.
  heapifyUp(pos);
}

template <typename T>
void  Heap<T>::print()
{
  /*
   prints the heap structure.
  */
  for(int i = 0; i < v.size() ; i++)
  {
    std::cout << v[i] << " ";
  }
}

// Get the number of element in the heap
template<typename T>
int Heap<T>::getSize() const
{
  return v.size();
}

template <typename T>
void heapSort(T list[], int arraySize)
{
  /*
  this performs the heap sort algorithm on a provided array
  input: an array of elements, and the size of the array
  output: NA, but the array is sorted.
  Time Complexity: O(nlogn), We must build the heap and then delete Min
  for the size of the array
  */
   Heap<T> heaper(list, arraySize); //turn array into heap
   for(int i = 0; i < arraySize ; i++)
   {
     //iteratively remove Min element and add to the end of the array
     list[i] = heaper.remove();
   }
}





#endif
