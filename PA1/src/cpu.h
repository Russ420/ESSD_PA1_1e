#ifndef _CPU_H_
#define _CPU_H_

#include <iostream>
#include <stdio.h>

#include "thread.h"

class CPU
{
	
  public:
    CPU ();
	void createCPU (int,int); // Set up thread list and id
	void pushThreadToCPU (Thread*); // Push thread id to thread list
    void emptyCPU (); // Clear the thread list
	void printCPUInformation (); // Print the partition result
    
    float utilization () {return _utilization;};
    int cpuId () {return _cpuId;};

  private:
	int *threadList ;      // List of thread in this cpu
	int threadCount;       // Number of theread in this cpu
	int _cpuId;            // CPU id whic used assign
	float _utilization;    // Utilization of this cpu

};
#endif
