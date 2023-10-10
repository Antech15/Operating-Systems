/**
 * Assignment 2: Simple UNIX Shell
 * @file pcbtable.h
 * @author Andres Hinojosa
 * @brief This is the main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @version 0.1
 */
// You must complete the all parts marked as "TODO". Delete "TODO" after you are done.
// Remember to add sufficient and clear comments to your code

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

#define MAX_LINE 80 // The maximum length command

/**
 * @brief parse out the command and arguments from the input command separated by spaces
 *
 * @param command
 * @param args
 * @return int
 */
int parse_command(char command[], char *args[])
{
  int count = 0; //used as a counter and index for args[]
  char *temp; //temporarily holds a string
  temp = strtok(command, " \n"); //seperates the keywords

  //loops through all keywords
  while(temp != NULL) 
    {
      args[count] = temp; //adds to args
      temp = strtok(NULL, " \n"); //temp gets first keyword
      count++;
    }
  
  return count;
}

/**
 * @brief The main function of a simple UNIX Shell. You may add additional functions in this file for your implementation
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @return The exit status of the program
 */
int main(int argc, char *argv[])
{
  char command[MAX_LINE];       // the command that was entered
  char *args[MAX_LINE / 2 + 1]; // parsed out command line arguments
  int should_run = 1;           /* flag to determine when to exit program */
  
  int fd[2]; //used for pipe EC
  char *history[MAX_LINE / 2 + 1]; //holds the last used command
  bool check = false; //checks if there is a command in history
  bool check2 = false; //checks if there is an '&' in command
  bool out = false; // checks if there is a '>' in command
  bool pipeCheck = false;  //checks if there is '|' in command
  int orOperator = 0; //index of '|'
  int outOperator = 0;  //index of '>'

  while (should_run)
    {
      if(pipe(fd) == -1) //if pipe fails
	exit(EXIT_FAILURE);

      //checks get reset each time
      check2 = false;
      out = false;
      pipeCheck = false;

      printf("osh>");
      fflush(stdout);
      // Read the input command
      fgets(command, MAX_LINE, stdin);
      // Parse the input command
      int num_args = parse_command(command, args);
           
      if(strcmp(args[0], "exit") == 0){should_run = 0;} //if exit was typed, exit()
      
      
      //checks for '|' or '>'
      for(int i = 0; i < num_args; i++)
	{
	  if(strcmp(args[i], "|") == 0)
	    {
	      pipeCheck = true;
	      orOperator = i;
	    }
	  else if(strcmp(args[i], ">") == 0)
	    {
	      out = true;
	      outOperator = i;
	    }
	}
      
      //checks for '>' or '<'
      if(args[1] != NULL)
	{
      	  if(strcmp(args[1], ">") == 0)
	    out = true;
	  
	  else if(strcmp(args[1], "<") == 0)
	    {
	      args[1] = args[2];
	      args[2] = NULL;
	      num_args = 2; 
	    }
	}

      //checks if & is in command
      if(strcmp(args[0], "!!") != 0 && (!pipeCheck))
	{
	  args[num_args] = NULL;
	  history[0] = strdup(args[0]);
	  
	  //space case
	  if(strcmp(args[num_args - 1], "&") == 0)
            {
	      args[num_args - 1] = NULL;
	      num_args--;
	      check2 = true;
            }
	  
	  //no space case
	  else if(args[num_args - 1][strlen(args[num_args - 1]) - 1] == '&')
	    {
	      //check for & at the end right here.
	      args[num_args - 1][strlen(args[num_args - 1]) - 1] = '\0';
	      history[num_args - 1] = strdup(args[num_args - 1]);
	      check2 = true;
	    }
	  //adds to history
	  if(args[1] != NULL && num_args == 2)
	    history[1] = strdup(args[1]);
	  else if(num_args == 1)
	    {
	      args[1] = NULL;
	      history[1] = NULL;
	    }
	  check = true;
	}
            
      //first child process
      int rc = fork();

      if(rc < 0) //fail
	{
	  printf("fork failed");
	  exit(1);
	}
      if(rc > 0) //parent
	{
	  close(fd[0]);
	  close(fd[1]);	  
	  if(!check2)
	    int wc = wait(NULL); 
	}
      if(rc == 0) //child process
	{
	  //'>' case	  
	  if(out)
	    {
	      int index = 2;
	      out = false;
	      history[1] = NULL;
	      history[0] = strdup(args[0]);

	      //if > not in index 1
	      if(outOperator != 0)
		{
		  history[1] = strdup(args[1]);
		  history[2] = NULL;
		  index = outOperator + 1;
		}
	      //opens file and writes
	      int rfd = open(args[index], O_CREAT | O_RDWR | O_TRUNC, 0644);
	      dup2(rfd, STDOUT_FILENO);
	      close(rfd);
	      
	      //execution
	      if(execvp(history[0], history) == -1)
		cout << "Command not found." << endl;
	      
	      //saves to history
	      history[1] = strdup(args[1]);
	      history[2] = strdup(args[2]);
	    }
	  
	  //'|' case
	  else if(pipeCheck)
	    {

	      args[orOperator] = NULL;
	      
	      //child 1 executes first func
	      int child1 = fork();	      
	      if(child1 < 0)
		{
		  printf("fork failed");
		  exit(1);
		}

	      if(child1 == 0) //first child
		{
		  close(fd[0]);
   		  dup2(fd[1], STDOUT_FILENO);//writes output to pipe
		  close(fd[1]);

		  if(execvp(args[0], args) == -1)
		    cout << "Command not found." << endl;
		}

	      waitpid(child1, NULL, 0);
	    
	      //second child executes function using output of child1 in pipe
	      int child2 = fork();
	      if(child2 < 0)
		{
		  printf("fork failed");
		  exit(1);
		}

	      if(child2 == 0) //second child
		{
		  close(fd[1]);
		  dup2(fd[0], STDIN_FILENO);//gets output as input
		  close(fd[0]);

		  //execution
		  if(execlp(args[orOperator + 1], args[orOperator + 1], args[orOperator + 2], NULL) == -1)
                    cout << "Command not found." << endl;
		}
	      close(fd[0]);
	      close(fd[1]);

	      waitpid(child2, NULL, 0);
	    }

	  //'!!' case
	  else if(strcmp(args[0], "!!") == 0)
	    {
	      
	      if(!check) //no history
		cout << "No command history found." << endl;
	      else
		{
		  //shows last command
		  cout << history[0];
		  if(history[1] != NULL)
		    cout << " " << history[1];
		  cout << endl;

		  //execution
		  if(execvp(history[0], history) == -1)
		    cout << "Command not found." << endl;
		  check = false;
		}
	    }
	  else //regular case
	    {
	      if(execvp(args[0], args) == -1)
		cout << "Command not found." << endl;  
	    }
	}
    } 
  return 0;
}
