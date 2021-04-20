#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <sys/time.h>
#include <vector>
#include <pthread.h>

#include "thread.h"
#include "config.h"
#include "cpu.h"
#include "../libs/check.h"

typedef void* (*THREADFUNCPTR)(void*);

static int  numThread_o = 0;

class System
{
  public:
    /* Constructure */
    /* Part 1 & Part 3 */
    System (char*); 
    void loadInput (char*);
    void setUpMatrix (int, int);

    void singleCoreMatrixMulti (); // Single thread matrix multiplicaiton

    /* Part 1 */
    void globalMultiCoreMatrixMulti (); // Global multi-thread matrix multiplication
    void partitionMultiCoreMatrixMulti ();

    /* Part 2 */
    void partitionFirstFit ();
    void partitionBestFit ();
    void partitionWorstFit ();

    void cleanMultiResult (); // Clear the result store in multiResutl
    void setStartTime ();
    void setEndTime ();
    double period () { return _timeUse; };

  private:
    int numThread;             // thread number of current system
    Thread* threadSet;         // list of thread
    CPU* cpuSet;               // list of cpu
    Check* check;

    struct timeval start;       // store the start time
    struct timeval end;         // store the end time
    double _timeUse;            // store the interval between start and end time

	float ***matrix;            // matrix for each thread
	float ***singleResult;      // single-core matrix multiplication result for each thread
	float ***multiResult;		// mulit-core matrix multiplication result for each thread
    // pass the schedule table array
    int SCHED[CORE_NUM][32];
    int UNSCHED[32];
  
};
#endif
