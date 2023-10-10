/**
* Assignment 3: CPU Scheduler
 * @file scheduler_priority_rr.cpp
 * @author Andres Hinojosa
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include "scheduler_priority_rr.h"

// TODO: add implementation of SchedulerFCFS constructor, destrcutor and 
// member functions init, print_results, and simulate here
SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum)
{
  //initializes variables
  q = time_quantum;
  avgTA = 0;
  avgWT = 0;
  time = 0; 
  count = 0;
}

SchedulerPriorityRR::~SchedulerPriorityRR()
{
 //deletes all objects
  for(unsigned int i = 0; i < processes.size(); i++)
    processes.pop_back();
  
}

void SchedulerPriorityRR::init(std::vector<PCB>& process_list)
{
  //creates a new list of the objects
  for(PCB obj: process_list)
    {
      processes.push_back(obj);
      count++;
    }
}

void SchedulerPriorityRR::print_results()
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

void SchedulerPriorityRR::simulate()
{
  
  bool notDone = true; //while simulation is not finished
  unsigned int current = 10;    
  bool left = false; //there is still processes to be finished

  while(notDone)
    {
      notDone = false;
      left = false;

      for(unsigned int i = 0; i < processes.size(); i++)
	      {
          if(processes[i].burst_time > 0) //at least 1 process not finished
            left = true;
          
          if(processes[i].burst_time > 0 && processes[i].priority == current) //if pcb is current priority
            {
              //updtate pcb data
              processes[i].visits++;
              processes[i].waTime += (time - processes[i].waTime);

              if(q < processes[i].burst_time) //case where pcb will not finish
                {
                  processes[i].burst_time -= q;
                  time += q;
                }      
              else //case where pcb will finish
                {
                  time += processes[i].burst_time;
                  processes[i].burst_time = 0;
                  processes[i].taTime = time;
                  processes[i].waTime -= ((processes[i].visits - 1) * q);
                }
              notDone = true;
            }          
        }
      if(!notDone && left) //all pcbs in current priority have been finished
        {
          current--;
          notDone = true;
        }
    }
}
