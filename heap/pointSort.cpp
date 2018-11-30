/*
Author: Eric Buehler
Date: 10/4/2018
filename: pointSort.cpp
This file tests heap sort on the point class (I use a my min heap)
*/

#include <iostream>
#include "HeapMin.h"
using namespace std;



int main()
{
// //----------------
// //sort
// //----------------
cout << "\n\n";
cout << "Sorting Point Type" << "\n";
const int SIZE = 10;
Point<int> list[SIZE];
 for(int i=0; i < SIZE; i++)
 {
     Point<int> point(rand() % 100 + 1,rand() % 100 + 1);
     list[i] = point;
 }
cout << "unsorted: " << "\n";
for (int i = 0; i < SIZE; i++)
   cout << list[i] << " ";
cout << "\n\n";
heapSort(list, SIZE);
cout << "sorted: " << "\n";
for (int i = 0; i < SIZE; i++)
  cout << list[i] << " ";
cout << "\n\n";
}
