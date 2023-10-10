/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority.cpp
 * @author Andres Hinojosa
 * @brief This Scheduler class implements the Priority scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code


#include "scheduler_priority.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here
SchedulerPriority::SchedulerPriority()
{
  //initializes variables
  avgTA = 0;
  avgWT = 0;
  time = 0; 
  count = 0;
}

SchedulerPriority::~SchedulerPriority()
{
 //deletes all objects
  for(unsigned int i = 0; i < processes.size(); i++)
    processes.pop_back();
  
}

void SchedulerPriority::init(std::vector<PCB>& process_list)
{
  //creates a new list of the objects
  for(PCB obj: process_list)
    {
      processes.push_back(obj);
      count++;
    }
}

void SchedulerPriority::print_results()
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

void SchedulerPriority::simulate()
{

  bool notDone = true; //simulation is not finished
  unsigned int j; //saves index of current PCB
  
  while(notDone)
    {
      unsigned int highest = 0;
      notDone = false;
      
      for(unsigned int i = 0; i < processes.size(); i++)
	      {
          //looks for pcb with highest priority that is unvisited
	        if(processes[i].priority > highest && !(processes[i].check))
            {
              //updtates highest priority & saves index
              highest = processes[i].priority;
              j = i;
              notDone = true;
            }
            
        } 
      if(notDone) //updates the PCB's wait and turn-around times and the current time
	      {
	        processes[j].check = true;
          processes[j].waTime = time;
          time += processes[j].burst_time;
          processes[j].taTime = time;
        }
    }
}
