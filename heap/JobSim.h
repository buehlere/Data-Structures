/*
Author: Eric Buehler
Date: 11/11/2018
filename: JobSim.h
The file simulates job scheduling in an operating system. Jobs are generated at
random times. Each job is given both a random priority from 1 to 4, where 1 is
the highest priority and a random amount of time to complete its execution.
Jobs do not begin execution and run to completion, but instead share the
processor. The operating system  executes a job for a fixed unit of time called
a time slice. At the end of the time slice, the current job’s execution is
suspended. The job is then placed on a priority queue, where it
waits for its next share of processor time. The job having the highest
priority is then removed from the priority queue and executed for a time slice.
When a job is first generated, it will begin executing immediately if the
processor is free. Otherwise it will be
placed on the priority queue.
*/

#ifndef _JobSim_h
#define _JobSim_h

#include <iostream>
#include "HeapMin.h"
#include <queue>
#include "Job.h"

class JobSim {

public:
  //vars
  int TIME_SLICE;
  int SIM_DURATION;
  int JOB_PROB;
  int JOB_MINTIME;
  int JOB_MAXTIME;

  //methods
  JobSim(int slice, int duration, int percentage, int min, int max);
  void runSim();
  void createJob(int jobNumer);
  void finalReport();
  void process(Job inProc);


private:

  //heap
  Heap<Job> PQJob;

  //queues
  queue<Job> completedJobs;
  queue<Job> currentlyExJobs;
  queue<Job> WaitingJobs;

  //job vars
  Job currentJob;
  //time

  int counterTime;

  //assigning some variables
  bool Create;
  int jobNumber;




};

JobSim::JobSim(int slice, int duration, int percentage, int min, int max)
{
/*
  This is the constructor for the simulation.
  -inputs:
    -int slice = the time a job will be processed
    -int duration = the length of the simulation.
    -int percentage = the probability a job will get created.
    -int min = smaller amount of time it will take to process a job.
    -int max = largest amount of time it will take to process a job.
  -outputs: NA
  Time-Copmlexity: O(1)
*/
  TIME_SLICE = slice;
  SIM_DURATION = duration;
  JOB_PROB = percentage;
  JOB_MINTIME = min;
  JOB_MAXTIME = max;
}

void JobSim::runSim()
{
  /*
  The purpose of this function is to run the simulation. If a node is created
  it is either processed if the heap is empty or pushed onto the heap. If a
  job isn't created the highest priority job is processed off the heap.
  If both the heap is empty and the no job is created, the time marker is updated
  and printed.
  -inputs: NA
  -outputs: NA
  Time-Copmlexity: O(n^3) the main while loop calls the process function, which
  is n^2
  */

  //sim will last as long as duration isn't zero
  while(SIM_DURATION > 0)
  {

     //probability check for variable creation
     Create = (rand() % 100) < JOB_PROB;

     if(Create == true)
     {

       //job number and create job
       jobNumber += 1;
       createJob(jobNumber);

       //check to see if tree is empty, then go straight to processing.
       if(PQJob.getSize() == 0)
       {
         //send to process
         process(currentJob);

       } else
       {
        //send to heap
        PQJob.insert(currentJob);

       }
     } else
     if(PQJob.getSize() > 0)
     {
       //send to process
       process(PQJob.remove());

     } else
     {
       //print out time marker
       std::cout << "Time Marker: " << counterTime << "\n";
       std::cout << "  " << "Waiting jobs: " << WaitingJobs.size();
       std::cout << ", Executing: " << "null" << "\n\n";
       counterTime += 1;
       SIM_DURATION -= 1;
     }

   }
  return;

}

void JobSim::createJob(int jobNumber)
{
  /*
  The purpose of this function is to create a job.
  -inputs: the number job that is being created.
  -outputs: NA, but a node variable is created.
  Time-Copmlexity: O(1)
  */

  //generate random priority and random time needed
  int priority = rand() % 4 + 1;
  int neededTime = rand() % JOB_MAXTIME + JOB_MINTIME;


  //assigning variables jobs variables
  //Job currentJob(jobNumber, priority, counterTime, neededTime, neededTime, 0);
  currentJob.JobNo = jobNumber;
  currentJob.Priority = priority;
  currentJob.createdTime = counterTime;
  currentJob.totalTimeNeed = neededTime;
  currentJob.timeLeft = neededTime;
  currentJob.inExe = 0;
  std::cout << "  " << "Created " << "job" << currentJob.JobNo
            << " priority(" << currentJob.Priority << ")"
            << ",  " << "Time left is " << currentJob.timeLeft << "\n\n";

  //waiting
  WaitingJobs.push(currentJob);

}

void JobSim::process(Job inProc)
{
  /*
  The purpose of this function is to process a job for the given time slice.
  If the job still has time left it's time is zero the job is copmleted.
  If there is still time left on a job by its completetion then it is
  put back into the heap. The queue are also properly updated. The
  possibility of a node being created during the the time slice is also
  accounted for.
  -inputs: a job type object
  -outputs: no output, jobs processed by the time slice and added to the
  Time-Copmlexity: O(n^2) a main loop which contains a heap insert.
  */

  //if the job hasn't been processed before it is taken off the waiting
  //queue
  if(WaitingJobs.size() != 0 && inProc.timeLeft == inProc.totalTimeNeed)
  {
    WaitingJobs.pop();
  }

  //if the job hasn't been in the processed before it is added to the
  //currently executing queue
  if(inProc.inExe == 0) currentlyExJobs.push(inProc);


  for(int i=0; i < TIME_SLICE && SIM_DURATION > 0; i++)
  {

    //update time
    SIM_DURATION -= 1;
    counterTime += 1;

    //prints
    std::cout << "Time Marker: " << counterTime << "\n";
    std::cout << "  " << "Executing: job" << inProc.JobNo << ", ";
    std::cout << "Created: " << inProc.createdTime << ", ";
    std::cout << "Time-Left: " << inProc.timeLeft << ", ";
    std::cout << "priority(" << currentJob.Priority << "), ";
    std::cout << "Waiting jobs: " << WaitingJobs.size() <<"\n\n";

    //subtract from time left if greater than zero
    if(inProc.timeLeft > 0)
    {
      inProc.timeLeft = inProc.timeLeft - 1; //process

      //allow the possibility of a job being created
      //probability check for variable creation
      Create = (rand() % 100) < JOB_PROB;

      if(Create == true)
      {
        //job number and create job
        jobNumber += 1;
        createJob(jobNumber);
        PQJob.insert(currentJob);
      }

    } else
    {

      //the job is complete
      inProc.timeLeft = 0;
      inProc.completedTime = counterTime;

      //updating queues
      if(currentlyExJobs.size() != 0) currentlyExJobs.pop();
      completedJobs.push(inProc);

      //return from function, no need to continue processing
      return;
    }
  }

  //if it doesn't finish, insert to heap
  inProc.inExe = 1;
  PQJob.insert(inProc);
  return;
}

void JobSim::finalReport()
{
  /*
  The purpose of this function is to provide a summary of the simulation
  -inputs: NA
  -outputs: NA
  Time-Copmlexity: O(n)
  */
  int timeRemaining = 0;
  std::cout << "Final Report" << "\n\n";
  std::cout << "number of jobs : " << jobNumber <<"\n";
  std::cout << "executing : " << currentlyExJobs.size() <<"\n";
  std::cout << "completed : " << completedJobs.size() <<"\n";
  std::cout << "Waiting : " << WaitingJobs.size() <<"\n\n";

  std::cout << "\n" << "Executing Jobs:" << "\n\n";
  while(!currentlyExJobs.empty())
  {
    Job a = currentlyExJobs.front();
    currentlyExJobs.pop();
    std::cout << "Executing: job" << a.JobNo << ", ";
    std::cout << "priority(" << a.Priority << "), ";
    std::cout << "Created: " << a.createdTime << ", ";
    std::cout << "Time-Left: " << a.timeLeft << ", ";
    std::cout << "Complete Time: " << a.completedTime << "\n";
    timeRemaining += a.timeLeft; //summing time left
  }
  std::cout << "\n" << "Completed Jobs:" << "\n\n";
  while(!completedJobs.empty())
  {
    Job a = completedJobs.front();
    completedJobs.pop();
    std::cout << "Executing: job" << a.JobNo << ", ";
    std::cout << "priority(" << a.Priority << "), ";
    std::cout << "Created: " << a.createdTime << ", ";
    std::cout << "Time-Left: " << a.timeLeft << ", ";
    std::cout << "Complete Time: " << a.completedTime << "\n";
  }

  std::cout << "\n" << "Waiting Jobs:" << "\n\n";
  while(!WaitingJobs.empty())
  {
    Job a = WaitingJobs.front();
    WaitingJobs.pop();
    std::cout << "Executing: job" << a.JobNo << ", ";
    std::cout << "priority(" << a.Priority << "), ";
    std::cout << "Created: " << a.createdTime << ", ";
    std::cout << "Time-Left: " << a.timeLeft << ", ";
    std::cout << "Complete Time: " << a.completedTime << "\n\n";
    timeRemaining += a.timeLeft; //summing time left
  }
  timeRemaining = timeRemaining / jobNumber;
  std::cout << "the average time left for unfinished jobs is " << timeRemaining <<"\n";

}


#endif
