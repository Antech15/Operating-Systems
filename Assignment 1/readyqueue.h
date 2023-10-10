/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.h
 * @author Andres Hinojosa (TODO: your name)
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code
#pragma once

#include "pcb.h"

struct Vertex
{
  Vertex *Up;  //points to the parent node 
  Vertex *Left; //points to left child
  PCB *Elem; //contains the PCB pointer
  Vertex *Right; //points to right child
};   


/**
 * @brief A queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 */
class ReadyQueue {
private:
    // choose a data structure for the ReadyQueue. No STL class is allowed.
    Vertex *Root; //initializes the root vertex
public:
    /**
     * @brief Construct a new ReadyQueue object
     *
     */
    ReadyQueue();

    /**
     * @brief Destructor
     */
    ~ReadyQueue() {
        dtraverse(Root);
        Root = NULL;
    }

  //keeps track of the number of PCBs
  int count = 0;

    /**
     * @brief traverses the tree, deleting all vertexes
     *
     * @param V: the pointer to the vertex slot
     */
    void dtraverse(Vertex *V);
    /**
     * @brief Add a PCB representing a process into the ready queue.
     *
     * @param pcbPtr: the pointer to the PCB to be added
     */
    /**
     * @brief traverses the tree to print PCB's in priority order
     *
     * @param V: The current vertex slot
     */
    void INorderTraversal(Vertex *V);

    /**
     * @brief Deletes a vertex slot
     *
     * @param p: Pointer of the PCB to be deleted
     */
    void DeleteVertex(PCB* p);

    /**
     * @brief removes a vertex slot knowing its parent
     *
     * @param V, the pointer vertex to be deleted
     * @param P, The pointer of the parent vertex
     */
    void tremove(Vertex *V, Vertex *P);

    /**
     * @brief finds the PCB with the highest priority
     *
     * @param V: the pointer to the current vertex slot
     */
    PCB* findMax(Vertex *V);

	// You may add additional member functions, but don't change the definitions of the following four member functions.

    /**
     * @brief Add a PCB representing a process into the ready queue.
     *
     * @param pcbPtr: the pointer to the PCB to be added
     */
	void addPCB(PCB* pcbPtr);

    /**
     * @brief Remove and return the PCB with the highest priority from the queue
     *
     * @return PCB*: the pointer to the PCB with the highest priority
     */
	PCB* removePCB();

    /**
     * @brief Returns the number of elements in the queue.
     *
     * @return int: the number of PCBs in the queue
     */
	int size();

     /**
      * @brief Display the PCBs in the queue.
      */
	void displayAll();

};