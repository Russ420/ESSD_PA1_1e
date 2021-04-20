#include "thread.h"

void
Thread::setThreadID(int ID)
{
	_ID = ID;
}


void
Thread::setThreadCore(int core)
{ 
	setCore = core;
}


void
Thread::setThreadMatrixSize(int matrix_size)
{
	_matrixSize = matrix_size;
}	


/*
 * Set up the affinity mask for the thread.
 *
 * @ Part1 Recommendation:
 * Implement the function to pinned current thread
 * to core with index CPU_NUM.
 *
 */
void
Thread::setUpCPUAffinityMask(int cpu_num)
{
	/*~~~~~~~~~~~~Your code(PART1)~~~~~~~~~~~*/
    // Pined the thread to core.
	cpu_set_t	cpu;
	CPU_ZERO(&cpu);
	CPU_SET(cpu_num, &cpu);
	//std::cout << "CPU" << cpu_num << " ";
	sched_setaffinity(0, sizeof(cpu_set_t), &cpu);
	//std::cout << CPU_ISSET(cpu_num, &cpu) << std::endl;
	//std::cout <<  syscall(SYS_gettid) << std::endl;
	/*~~~~~~~~~~~~~~~~~~END~~~~~~~~~~~~~~~~~~*/
}


void
Thread::setStartCalculatePoint(int start_calculate_point)
{
    startCalculatePoint = start_calculate_point;
}


void
Thread::setEndCalculatePoint(int end_calculate_point)
{
    endCalculatePoint = end_calculate_point;
}


void
Thread::setSchedulingPolicy(int policy)
{
    _schedulingPolicy = policy;
}


void 
Thread::setCheck (Check* tmp_check)
{
    check = tmp_check;
}


/*
 * Set up the _utilization of the thread depend on the size of matrix.
 * Let matrix pointer (singleResult, multiResult and Matrix) point 
 * to the matrix whcih create by System.
 *
 */
void
Thread::initialThread(float** single_result, float** multi_result, float** input_matrix)
{
	_utilization = float(_matrixSize / float(UTILIZATION_DIVIDER));	

    startCalculatePoint = 0;
    endCalculatePoint = _matrixSize;

    singleResult = single_result;
    multiResult = multi_result;
    matrix = input_matrix;
}


/*
 * Matrix multiplication operation and store the result into
 * singleResult which used to check the corennectness of multiResult 
 * by compare singleResult with multiResult.
 *
 */
void
Thread::singleMatrixMultiplication()
{	
	/* Print Thread information */
	core = sched_getcpu();
	PID = syscall(SYS_gettid);
	printInformation();

	/* Multiplication */
	for (int i = 0 ; i < _matrixSize; i++) {
		for (int j = 0 ; j < _matrixSize; j++) {
			singleResult[i][j] = 0;
			for (int k = 0 ; k < _matrixSize; k++) {
				singleResult[i][j] += matrix[i][k]*matrix[k][j];
			}	
		}
	}
}


/*
 * Matrix multiplication operation and store the result into
 * multieResult. 
 *
 * 1. For all part, pinned the thread to coresspond core dependent
 *    on variable setCore. 
 *
 * 2. For all part, using the system call the check is thread migrat
 *    to others core or not.
 *
 * 3. For Part3, call the member function setUpScheduler to set the 
 *    scheduler for current thread, and print out the Core0 current
 *    executed thread id to observie the different between FIFO and RR.
 *
 * @ Part1 Recommendation:
 * Implementation of pinned the current thread onto specify core.
 * Could be accomplish by call function SetUpCPUAffinityMask or other methods.
 * Implementation of detected the thread is migrate or not. 
 *
 * @ Part3 Recommendation:
 * Implementation of detected the Core0 is encounter the context
 * switch or not. If there is context swich then print out it was
 * switch from thread # to thread #.
 *
 */
void*
Thread::matrixMultiplication(void* args)
{
    Thread *obj = (Thread*)args;

#if (PART == 3)
    obj->setUpScheduler();
#endif

	/*~~~~~~~~~~~~Your code(PART1)~~~~~~~~~~~*/
	// self declared variable
	int core_prev = -1;
	
    // Set up the affinity mask
	
// ADD UP PART == 3 FOR DEBUG	
#if (PART ==2)
	pthread_mutex_lock( &count_Mutex );
	obj->core = sched_getcpu();
	obj->PID = syscall(SYS_gettid);
	obj->printInformation();
	pthread_mutex_unlock( &count_Mutex );
#endif

	/*~~~~~~~~~~~~~~~~~~END~~~~~~~~~~~~~~~~~~*/

    /* matrix multiplication */
	for (int i = obj->startCalculatePoint; i < obj->endCalculatePoint; i++) {
		for (int j = 0 ; j < obj->_matrixSize; j++) {
			obj->multiResult[i][j] = 0;
			for (int k = 0 ; k < obj->_matrixSize; k++) {
				obj->multiResult[i][j] += obj->matrix[i][k] * obj->matrix[k][j];
            }	

	        /*~~~~~~~~~~~~Your code(PART1)~~~~~~~~~~~*/
            // Observe the thread migration
#if (PART == 1)			
			core_prev = obj->core;
			if(core_prev != (obj->core=sched_getcpu()))
			{
				pthread_mutex_lock( &count_Mutex );
				std::cout << "The thread "<< obj->_ID <<" PID " ;
				std::cout << syscall(SYS_gettid) ;
				std::cout << " is moved from CPU "<< core_prev <<" to " ;
				std::cout << obj->core << std::endl;
				core_prev = obj->core;
				pthread_mutex_unlock( &count_Mutex );
			}
#endif
	        /*~~~~~~~~~~~~~~~~~~END~~~~~~~~~~~~~~~~~~*/

		}
#if (PART == 3)
			/*~~~~~~~~~~~~Your code(PART3)~~~~~~~~~~~*/
			// Obaserve the execute thread on core-0
			if(sched_getcpu() == 0)
			{
				if(current_PID == -1)
				{
					current_PID = syscall(SYS_gettid);
					std::cout << "The Core" << sched_getcpu() << " start PID-" << current_PID  << std::endl;
				}
				else if(current_PID != syscall(SYS_gettid))
				{
					// print the context switch thread
					std::cout << "The Core" << sched_getcpu() << " context switch from PID-" << current_PID << " to PID-"<< syscall(SYS_gettid) << std::endl;
					current_PID = syscall(SYS_gettid);
				}
			}
#endif
			
	    /*~~~~~~~~~~~~~~~~~~END~~~~~~~~~~~~~~~~~~*/

	}

#if (PART == 3)
ThreadCnt = ThreadCnt + 1;
//std::cout << ThreadCnt << std::endl;
if(ThreadCnt == 10)
{
	ThreadCnt	= 0;
	current_PID = -1;
}

#endif
	pthread_mutex_lock( &count_Mutex );
    obj->check->checkCorrectness();
	pthread_mutex_unlock( &count_Mutex );
    return 0;
}


/*
 * Print out the tread information.
 *
 */
void
Thread::printInformation()
{
    std::cout << "Thread ID : " << _ID ;
    std::cout << "\tPID : " << PID;
    std::cout << "\tCore : " << core;
#if (PART != 1)
    std::cout << "\tUtilization : " << _utilization;
    std::cout << "\tMatrixSize : " << _matrixSize;	
#endif
    std::cout << std::endl;
}


/* 
 * Set up the scheduler for current thread.
 *
 * @ Part3 Recommendation:
 * Using function sched_setscheduler to set up the scheduling
 * policy, or other method.
 *
 */
void
Thread::setUpScheduler()
{
	/*~~~~~~~~~~~~Your code(PART3)~~~~~~~~~~~*/
    // Set up the scheduler for current thread
#if (SCHEDULING == SCHED_FIFO)
	struct sched_param sp;
	sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
	sched_setscheduler(0, SCHED_FIFO, &sp);
#endif
#if (SCHEDULING == SCHED_RR)
	struct sched_param sp;
	sp.sched_priority = sched_get_priority_max(SCHED_RR);
	sched_setscheduler(0, SCHED_RR, &sp);
#endif
	/*~~~~~~~~~~~~~~~~~~END~~~~~~~~~~~~~~~~~~*/
}
