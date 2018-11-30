/*
Author: Eric Buehler
Date: 11/11/2018
filename: Job.h
This header file creates the job class, which is necessary for the JobSim.h,
which the Job class is friends with.
*/


#ifndef _Job_h
#define _Job_h

#include <iostream>
class JobSim;

class Job {


friend class JobSim;
public:
  Job();
  bool operator>(Job j2);
  bool operator<(Job j2);
  Job& operator=(Job j2);
  friend ostream& operator<<(ostream& os, Job job)
  {
    //overloaded stream operator
    os << "(" + to_string(job.Priority) + ")";
    return os;
  }

private:
  int JobNo;
  int Priority;
  int createdTime;
  int totalTimeNeed;
  int completedTime;
  int timeLeft;
  int inExe; //keeps track if a job has been in the processor


};

Job::Job()
{

}


bool Job::operator<(Job j2)
{
  //overloaded less than operator
  if(Priority < j2.Priority)
  {
    return true;
  } else return false;
}


bool Job::operator>(Job j2)
{
  //overloaded greater than operator
  if(Priority > j2.Priority)
  {
    return true;
  } else return false;
}


Job& Job::operator=(Job j2)
{
  //overloaded assignment operator 
  JobNo = j2.JobNo;
  Priority = j2.Priority;
  createdTime = j2.createdTime;
  totalTimeNeed = j2.totalTimeNeed;
  completedTime = j2.completedTime;
  timeLeft = j2.timeLeft;
  inExe = j2.inExe;
  return *this;
}




#endif
