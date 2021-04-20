#ifndef _THREAD_H_
#define _THREAD_H_

#include <cassert>
#include <stdio.h>
#include <math.h>
#include <iostream>
//#include <unistd.h>

#include <pthread.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <sched.h>
#include <errno.h>

#include "config.h"
#include "../libs/check.h"

static pthread_mutex_t count_Mutex;	// pthread lock variable
static int current_PID = -1;
static int ThreadCnt   = 0;

class Thread
{

  public:
    void setThreadID (int); // Set the _ID of thread
	void setThreadCore (int); // Set the core thread pinned on
	void setThreadMatrixSize (int); // Set the hight / widht of matrix which thread calculate on
    void setStartCalculatePoint (int);  // Set the start calculate point for matrix multiplication. (hint: part1)
    void setEndCalculatePoint (int); // Set the end calculate point for matrix multiplication. (hint: part1)
    void setSchedulingPolicy (int); // Set the scheduling policy for thread. (hint: part3)
    void setCheck (Check*);
	
	void initialThread (float**, float**, float**); // Set the pointer point to singleResult, multResult, and matrix define in System.
	void singleMatrixMultiplication (); // Single thread matrix multiplication.
	void printInformation (); // Print out the thread informaiton.

    /* Part1 and Part3 */
    static void* matrixMultiplication (void*); // Multi-thread matrix multiplication

    /* Part1 */
	void setUpCPUAffinityMask (int); // Pined the thread on specify core

    /* Part 3 */
    void setUpScheduler (); // Set the scheduling policy for specify thread.

    float utilization () {return _utilization;};
    int matrixSize () {return _matrixSize;};
    int ID () {return _ID;};
    int schedulingPolicy () {return _schedulingPolicy;};

  public:
    pthread_t pthreadThread;
    struct    context_switch
    {
      int     prev[CORE_NUM] = {0};
      int     pres[CORE_NUM] = {0};
      int     ptr_prev    = 0;
      int     ptr_pres    = 0;
    };
    struct context_switch cs;
  private:
    int _schedulingPolicy;       // Scheduling policy for thread
	float _utilization;          // utilization of the thread
	int _matrixSize;	         // Matrix width / height
	int _ID;                     // ID that user assign

	int PID;                     // Thread ID which system assign
	int setCore = -1;            // the core thread pinned on (user assign)
	int core;                    // Core thread executed on (system assign)
    int startCalculatePoint;     // start point for matrix multiplicatio
    int endCalculatePoint;       // end poiint for matrix multiplication
	float **matrix;              // 2-D matrix
	float **singleResult;        // Store the single-core matrix multiplication result
	float **multiResult;		 // Store the multi-core matrix multiplication result

    Check *check;
  int pid_prev    = -1;
};
#endif
