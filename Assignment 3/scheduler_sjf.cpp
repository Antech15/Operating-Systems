/**
* Assignment 3: CPU Scheduler
 * @file scheduler_sjf.cpp
 * @author Andres Hinojosa
 * @brief This Scheduler class implements the SJF scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_sjf.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here

SchedulerSJF::SchedulerSJF()
{
  //initializes variables
  avgTA = 0;
  avgWT = 0;
  time = 0; 
  count = 0;
}

SchedulerSJF::~SchedulerSJF()
{
 //deletes all objects
  for(unsigned int i = 0; i < processes.size(); i++)
    processes.pop_back();
  
}

void SchedulerSJF::init(std::vector<PCB>& process_list)
{
  //creates a new list of the objects
  for(PCB obj: process_list)
    {
      processes.push_back(obj);
      count++;
    }
}

void SchedulerSJF::print_results()
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

void SchedulerSJF::simulate()
{

  bool notDone = true;
  unsigned int j;
  
  while(notDone)
    {
      unsigned int shortest = 500;
      notDone = false;
      
      for(unsigned int i = 0; i < processes.size(); i++)
        {
          //finds shortest job that isnt finished
          if(processes[i].burst_time < shortest && !(processes[i].check))
            {
              shortest = processes[i].burst_time;
              j = i;
              notDone = true;
            }
        } 
      //updates pcb's data & current time
      if(notDone)
        {
          processes[j].check = true;
          processes[j].waTime = time;
          time += processes[j].burst_time;
          processes[j].taTime = time;
        }
    }
}
