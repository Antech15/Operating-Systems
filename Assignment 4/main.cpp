/**
* Assignment 4: Producer Consumer Problem
 * @file main.cpp
 * @author Andres Hinojosa
 * @brief The main program for the producer consumer problem.
 * @version 0.1
 */
//You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code
#include <iostream>
#include "buffer.h"
#include <unistd.h>
#include <pthread.h>
#include<semaphore.h>

using namespace std;

// global buffer object
Buffer buffer;
// global mutex object
pthread_mutex_t mutex;
// global semaphores for full and empty
sem_t semFull;
sem_t semEmpty;

// Producer thread function
// param is the number of the producer
void *producer(void *param) {
  // Each producer insert its own ID into the buffer
  // For example, thread 1 will insert 1, thread 2 will insert 2, and so on.
  buffer_item item = *((int *) param);

  //fixes a bug that prints 0 instead of 1
   if(item == 0)
  item++;

  while (true) {
    /* sleep for a random period of time */
    usleep(rand()%1000000);

    //semaphore waits and locks mutex
    sem_wait(&semEmpty);
    pthread_mutex_lock(&mutex);

    //waits when buffer is full
    while(buffer.is_full())
      sem_wait(&semEmpty);
      
    //inserts item here
    if (buffer.insert_item(item)) {
      cout << "Producer " << item << ": Inserted item " << item << endl;
      buffer.print_buffer();
    } else {
      cout << "Producer error condition"  << endl;    // shouldn't come here
    }

    //unlocks mutex and signals semaphore full
    pthread_mutex_unlock(&mutex);
    sem_post(&semFull);
  }
}

// Consumer thread function
// param is the number of the consumer
void *consumer(void *param) {
  buffer_item item;
  
  while (true) {
    /* sleep for a random period of time */
     usleep(rand() % 1000000);
    
     //semaphore waits and locks mutex
    sem_wait(&semFull);
    pthread_mutex_lock(&mutex);
    
    //waits when buffer is empty
    while(buffer.is_empty())
      sem_wait(&semFull);

    pthread_mutex_lock(&mutex);          
    //removes item
    if (buffer.remove_item(&item)) {
      cout << "Consumer " << item << ": Removed item " << item << endl;
      buffer.print_buffer();
    } else {
      cout << "Consumer error condition" << endl;    // shouldn't come here
    }

    //unlocks mutex and signals semaphore empty
    pthread_mutex_unlock(&mutex);
    sem_post(&semEmpty);
  }
}

int main(int argc, char *argv[]) {

  /* TODO: 1. Get command line arguments argv[1],argv[2],argv[3] */
  if(argc == 4)
    {
      //gets number of producers and consumers
      int numProducers = atoi(argv[2]);
      int numConsumers = atoi(argv[3]);
    
      /* TODO: 2. Initialize buffer and synchronization primitives */
      
      //array of all the producer/consumers
      pthread_t producers[numProducers];
      pthread_t consumers[numConsumers];

      //initializes mutex and semaphores
      pthread_mutex_init(&mutex, NULL);
      sem_init(&semFull, 0, 0);
      sem_init(&semEmpty, 0, buffer.get_size());

      /* TODO: 3. Create producer thread(s).
       * You should pass an unique int ID to each producer thread, starting from 1 to number of threads */
      for(int i = 1; i < numProducers + 1; i++)
	{
	  //creates an address to the number
	  int *temp = &i;
	  
	  //creates producer
	  pthread_create(&producers[i], NULL, producer, temp);
	}
      
      /* TODO: 4. Create consumer thread(s) */
      for(int i = 0;  i < numConsumers; i++)
	{	 
	  //creates address to the number
	  int *temp = &i;
	  
	  //creates consumer
	  pthread_create(&consumers[i], NULL, consumer, temp);      
	}

      //destroys the mutex and semaphores
      pthread_mutex_destroy(&mutex);
      sem_destroy(&semFull); 
      sem_destroy(&semEmpty);

      /* TODO: 5. Main thread sleep */
      usleep(atoi(argv[1]) * 1000000);

      /* TODO: 6. Exit */
      exit(0);
    }
  else
    //error condition
    cout << "Parameter error" << endl;
}
