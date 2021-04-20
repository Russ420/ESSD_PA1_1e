#include "cpu.h"

CPU::CPU()
{
    threadCount = 0;
    _utilization = 0;
}


/* 
 * Set up the thread list data structure and cpu id.
 *
 */
void
CPU::createCPU(int thread_num, int cpu_id)
{
	threadList = new int[thread_num];
	threadCount = 0;
	_cpuId = cpu_id;
	_utilization = 0;
}


/*
 * Push thread into the thread list and update the utilization
 * for this cpu.
 *
 */
void
CPU::pushThreadToCPU(Thread* thread)
{
	threadList[threadCount] = thread->ID();
	_utilization += thread->utilization();
	threadCount++;
}


/*
 * Reset all varialb.
 *
 */
void
CPU::emptyCPU(void)
{
	for (int i = 0; i < threadCount; i++)
		threadList[i] = 0;
	threadCount = 0;
	_utilization = 0;
}


void
CPU::printCPUInformation()
{
    std::cout << "Core Number : " << _cpuId << std::endl;
    std::cout << "[ " ;
	for (int i = 0; i < threadCount; i++)
        std::cout << threadList[i] << ", " ;
    std::cout << "]" << std::endl;
    std::cout << "Total Utilization : " << _utilization << std::endl;
    std::cout << std::endl;
}
