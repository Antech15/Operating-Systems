#include <iostream>
#include "readyqueue.h"

using namespace std;

//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient comments to your code


/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
     Root = NULL;
 }

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {

  pcbPtr->setState(ProcState::READY); //sets state to ready
  count++; //updates counter
  // Set up a new vertex first
  Vertex *N;         // N will point to the new vertex to be inserted
  N = new Vertex;    // a new vertex is created
  N->Left  = NULL;   // make sure it does not
  N->Right = NULL;   // point to anything
  N->Elem = pcbPtr;      // put element E in it
  N->Up = NULL;      // no parent for now

  if (Root == NULL)  // Special case: we have a brand new empty tree
       Root = N;      // the new vertex is added as the root
   
  else  // the tree is not empty
  {
    Vertex *V;       // V will point to the current vertex
    Vertex *Parent;  // Parent will always point to V's parent
       
    V = Root;        // start with the root as V
    Parent = NULL;   // above V so it does not point to anything  
       
    // go down the tree until you cannot go any further        
    while (V != NULL)
	  {
	    if (N->Elem->priority < V->Elem->priority)  // what I have is smaller than V
	    {  
		    Parent = V; //  change Parent to be V to go down 
		    V = V->Left; // change V to be V's Left 
	    }
	    else // what I have is bigger than V
	    {  
		    Parent = V; // change Parent to be V to go down
		    V = V->Right; // change V to be V's Right 
	    }
	 }//end of while
       
       // reached NULL -- Must add N as the Parent's child
       
    if (Parent != NULL && N->Elem->priority < Parent->Elem->priority)  
	  {  
	    Parent->Left = N; // Parent's Left should point to the same place as N 
	    N->Up = Parent; // N must point UP to the Parent 
	  }
    else 
	  {
      if(Parent != NULL)
      {
        Parent->Right = N; // Parent's Right should point to the same place as N 
	      N->Up = Parent; // N must point UP to the Parent   
      }
	  }
       
  }
}

/**
* @brief traverses the tree, deleting all vertexes
*
* @param V: the pointer to the vertex slot
*/
void ReadyQueue::dtraverse(Vertex *V)  // recursive post order traversal
    {
    if (V != NULL)
        {
            dtraverse(V->Left);         // destroy left sub tree of V
            dtraverse(V->Right);       //  destroy right sub tree of V
            delete V;                  //  delete V
        }
    }

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
  
  Vertex *V = Root;       // the current vertex
  PCB* p;

  while(V->Right != NULL) //finds highest priority
    V = V->Right;
  
  p = V->Elem;
  p->setState(ProcState::RUNNING); //changes state to running and returns
  DeleteVertex(V->Elem);
  count--; //decrements counter
  return p;  
}

/**
* @brief Deletes a vertex slot
*
* @param p: Pointer of the PCB to be deleted
*/
void ReadyQueue::DeleteVertex(PCB* E)
{
  Vertex *V;       // the current vertex
  Vertex *Parent;  // Parent will always point to V's parent

  // case 1: Lonely Root  --------------------
  if ((E->getID() == Root->Elem->getID()) && (Root->Left == NULL) && (Root->Right == NULL))
  {
    delete Root; 
    Root = NULL;
    return; 
  }  // only the Root was there and deleted it
  
  // case 2:  One Substree Root ----------------
  else if(E->getID() == Root->Elem->getID()) // if what you want to delete is the root
  {  
    if((Root->Right == NULL) && (Root->Left != NULL))// and it has only the left subtree
    {  //   change the root to the left child and return
      //   making sure the old root has been deleted and the new root's UP is NULL
      V = Root;
      Root = Root->Left;
      delete V;
      Root->Up = NULL;
      return; 
    }
    else if((Root->Left == NULL) && (Root->Right != NULL)) // and it has only the right subtree
    { // change the root to the right child and return
      // making sure the old root has been deleted and the new root's UP is NULL 
      V = Root;
      Root = Root->Right;
      delete V;
      Root->Up = NULL;
      return;
    }
  }// end of deleting the root with one subtree
  
  // ---- Otherwise deleting something else  --------------
  
  V = Root;  // start with the root to look for E
  Parent = NULL;  // above the V so does not point to anything yet

  // going down the tree looking for E
  while (V != NULL)
  { 
    if (E->getID() == V->Elem->getID())   // found it
	  { 
	    tremove(V, Parent); // call remove here to remove V
	    return; 
	  }
    else
	    if (E->getPriority() < V->Elem->getPriority())
	    {  
	      Parent = V; // update Parent and V here to go down
	      V = V->Left; 
	    }
	    else
	    {  
	      Parent = V; // update Parent and V here to go down
	      V = V->Right;
	    }  
      
  }// end of while
}

/**
* @brief removes a vertex slot knowing its parent
*
* @param V, the pointer vertex to be deleted
* @param P, The pointer of the parent vertex
*/
void ReadyQueue::tremove(Vertex *V, Vertex *P)
{
  if((V->Left == NULL) && (V->Right == NULL)) // if V is a leaf (case 1)
    {
      if(P->Left == V) // if V is a left child of P
	    {
	      delete V; // delete V and also make Parent's left NULL
	      P->Left = NULL;  
	    }
      else // V is a right child of the Parent
	    { 
	      delete V; // delete V and also make Parent's right NULL
	      P->Right = NULL; 
	    }
    }//end of leaf case
  
  else if((V->Left != NULL) && (V->Right == NULL)) // if V has just the left child so bypass V (case 2)
  {    
    Vertex* C = V->Left; // C is the left child
    if(P->Left == V)// You need if then else to determine Parent's left or right
	    P->Left = C;//    should point to C; 
    else
	    P->Right = C;
      
    C->Up = P; // Make C point UP to the parent;
    delete V; // Be sure to delete V  
  }// end of V with left child       
  
  else if((V->Right != NULL) && (V->Left == NULL)) // if V has just the right child so bypass V (case 2)
  {    
    Vertex* C = V->Right;  // C is the right child
    if(P->Left == V) // You need if then else to determine Parent's left or right
	    P->Left = C;//    should point to C;
    else
	    P->Right = C;
      
    C->Up = P; // Make C point UP to the parent;   
    delete V; // Be sure to delete V 
  }//end of V with right child
  
  else // V has two children (case 3)
  {
    PCB* Melem;
    // find MAX element in the left sub-tree of V
    Melem = findMax(V); 
    V->Elem = Melem; // Replace V's element with Melem here
  }//end of V with two children
  
}

/**
* @brief finds the PCB with the highest priority
*
* @param V: the pointer to the current vertex slot
*/
PCB* ReadyQueue::findMax(Vertex *V)
{
  Vertex *Parent = V;
  V = V->Left;          // start with the left child of V
  
  while(V->Right != NULL) // while the right child of V is still available
  {
    Parent = V; // update Parent and V to go to the right
    V = V->Right;
  }
  
  // reached NULL Right  -- V now has the MAX element
  PCB* X = V->Elem;
  tremove(V, Parent);    // remove the MAX vertex 
  return X;             // return the MAX element
}


/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
  return count;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    cout << "Display Processes in ReadyQueue:" << endl;
    if(Root != NULL)
      INorderTraversal(Root);  // start in-order traversal from the root
}

/**
* @brief traverses the tree to print PCB's in priority order
*
* @param V: The current vertex slot
*/
void ReadyQueue::INorderTraversal(Vertex *V)
{
  if (V != NULL)
  {
    INorderTraversal(V->Right); //  traverse left sub-tree of V recursively
    V->Elem->display();//cout << "ID: " << V->Elem->getID() << ", Priority: " << V->Elem->getPriority() << ", State: " << V->Elem->getState() << endl;
    INorderTraversal(V->Left); //  traverse right sub-tree of V recursively
  }
}
