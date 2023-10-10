/**
* Assignment 3: CPU Scheduler
 * @file scheduler_fcfs.cpp
 * @author Andres Hinojosa
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_fcfs.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here
SchedulerFCFS::SchedulerFCFS()
{
  //initializes variables
  avgTA = 0;
  avgWT = 0;
  time = 0; 
  count = 0;
}

SchedulerFCFS::~SchedulerFCFS()
{
 //deletes all objects
  for(unsigned int i = 0; i < processes.size(); i++)
      processes.pop_back();
  
}

void SchedulerFCFS::init(std::vector<PCB>& process_list)
{
  //creates a new list of the objects
  for(PCB obj: process_list)
    {
      processes.push_back(obj);
      count++;
    }
}

void SchedulerFCFS::print_results()
{
  //prints results
  for(unsigned int i = 0; i < processes.size(); i++)
    {
      cout << processes[i].name << " turn-around time = " << processes[i].taTime << ", waiting time = " << processes[i].waTime << endl;
      avgTA += processes[i].taTime;
      avgWT += processes[i].waTime;
    }
  
  cout << "Average turn-around time = " << ((double)avgTA)/((double)count) << ", Average waiting time = " << ((double)avgWT)/((double)count) << endl;

}

void SchedulerFCFS::simulate()
{
  //Goes through each process and finishes them in order
  for(unsigned int i = 0; i < processes.size(); i++)
    {
      //updates PCB data
      processes[i].waTime = time;
      time += processes[i].burst_time;
      processes[i].taTime = time;
    } 

}
