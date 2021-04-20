#ifndef _CONFIG_H_
#define _CONFIG_H_
#include <sched.h>

#define PART 3

/* The scheduler include SCHED_FIFO and SCHED_RR */
#define SCHEDULING SCHED_RR

/* Constant hyperparameter */
#define CORE_NUM 4
#define UTILIZATION_DIVIDER 2000

#endif
