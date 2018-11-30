/*
Author: Eric Buehler
Date: 10/4/2018
filename: jobSim.cpp
This file tests the JobSim.h
*/

#include <iostream>
#include "HeapMin.h"
#include "JobSim.h"
using namespace std;



int main()
{
  //----------------
  //Simulation
  // //----------------
  JobSim sim(3,50,20,3,15);
  sim.runSim();
  sim.finalReport();
  return 0;
}
