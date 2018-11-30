/*
Author: Eric Buehler
Date: 10/4/2018
filename: HeapSort.cpp
This file tests the Heap.h
*/

#include <iostream>
#include "HeapMin.h"
using namespace std;



int main()
{
  //----------------
  //sort
  //----------------
  cout << "\n\n";
  cout << "Testing heap sort" << "\n";
  const int SIZE = 20;
  int list[SIZE];
   for(int i=0; i < SIZE; i++)
   {
       list[i] = rand() % 100 + 1;
   }
  cout << "unsorted: " << "\n";
  for (int i = 0; i < SIZE; i++)
    cout << list[i] << " ";
  cout << "\n";
  heapSort(list, SIZE);
  cout << "sorted: " << "\n";
  for (int i = 0; i < SIZE; i++)
    cout << list[i] << " ";
  cout << "\n\n";
  //----------------
  //testing methods
  //----------------

  //constructor
  const int SIZE2 = 5;
  int list2[] = {4,3,6,2,0};
  cout << "testing methods" << "\n";
  Heap<int> heap(list2, SIZE2);
  cout << "checking constructor: ";
  heap.print();
  cout << "\n\n";

  //insert
  heap.insert(5);
  heap.insert(1);
  cout << "inserting 5 and 1: ";
  heap.print();
  cout << "\n\n";

  //length
  cout << "checking length: " << heap.getSize() << "\n\n";

  //remove
  cout << "remove max element: " << heap.remove();
  cout << "\n";
  cout << "checking heap structure after remove: ";
  heap.print();
  cout << "\n\n";

  //increase priority
  heap.increasePriority(2,5);
  cout << "changing two's priority to five: ";
  heap.print();
  cout << "\n\n";
  return 0;
}
