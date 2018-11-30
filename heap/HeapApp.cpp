/*
Author: Eric Buehler
Date: 10/4/2018
filename: HeapSort.cpp
This file tests the JobSim.h 
*/

#include <iostream>
#include "HeapMin.h"
#include "JobSim.h"
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
  //----------------
  //Simulation
  // //----------------
  JobSim sim(3,50,20,3,15);
  sim.runSim();
  sim.finalReport();
  return 0;
}
