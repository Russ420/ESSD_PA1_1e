#ifndef _CHECK_H_
#define _CHECK_H_

#include <cassert>
#include <iostream>

#include <pthread.h>
#include <unistd.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <sched.h>

enum CheckState {
    GLOBAL,
    PARTITION,
    PARTITION_FF,
    PARTITION_BF,
    PARTITION_WF,
    PARTITION_RR,
    PARTITION_FIFO
};

class Check
{

  public:
    Check(float*** = NULL, float*** = NULL, int = 0, int = 0);
    void initialCheck(float***, float***, int, int);
    void setThreadWithIndex(int, pthread_t*);
    void setMatrixSizeWithIndex(int, int);
    void setCheckState(CheckState);

    void checkCorrectness();
    void checkPart1Global();
    void checkPart1Partition();
    void checkPart2Partition();
    void checkPart3Scheduler();
    void compareResult();

  private:
    int *matrixSize;             // matrix for each thread
    float ***singleResult;       // single-core matrix multiplication result for each thread
    float ***multiResult;        // mulit-core matrix multiplication result for each thread

    int PID;                     // current process id
    int numThread;               // number of creating thread
    int numCore;                 // number of core are used
    int checkCount;
    int schedulingPolicy;
    bool correctnessResult;
    bool correctnessScheduling;
    bool *cpuList;
    int *partitionList;          
    pthread_t **threadList;      // point to each thread

    CheckState checkState;
};

#endif

