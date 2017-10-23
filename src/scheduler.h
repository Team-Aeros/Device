#ifndef dev_scheduler_h
#define dev_scheduler_h

// Scheduler data structure for storing task data
typedef struct
{
   // Pointer to task
   void (*pTask)(void);
   // Initial delay in ticks
   unsigned int delay;
   // Periodic interval in ticks
   unsigned int period;
   // Runme flag (indicating when the task is due to run)
   unsigned char runme;
} Task;

// Function prototypes
void sch_init_t1(void);
void sch_start(void);

// Core scheduler functions
void sch_dispatch_tasks(void);
unsigned char sch_add_task(void (*)(void), const unsigned int, const unsigned int);
unsigned char sch_delete_task(const unsigned char);

#define SCH_MAX_TASKS 5

#endif