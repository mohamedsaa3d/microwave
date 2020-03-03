
#ifndef _SCHEDULER_
#define _SCHEDULER_


#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "../MCAL/INTERRUPT/interrupt.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/PICGenious/PICGenious_int.h"
#include "Microwave.h"

//########################### SCHEDULER TICK TIME CONFIG ################################
	/* Tick Calculation :
     *      FOR : F_CPU = 8 MHZ     ,  TIMER PRESCALER = 8    ,   (8-Bit TIMER) 
     *      TIMER0 Counter Tick Time = 1 uSec
     * *************************************************************************
	 * 	>>>	Scheduler Tick Time      = 1 milliSec
     *      Timer Overflows          = 3
     *      Timer Remaining Counts   = 232
     * -------------------------------------------------------------------------
	 * 	>>>	Scheduler Tick Time      = 2 milliSec
     *      Timer Overflows          = 7
     *      Timer Remaining Counts   = 208
     * -------------------------------------------------------------------------
	 * 	>>>	Scheduler Tick Time      = 5 milliSec
     *      Timer Overflows          = 19
     *      Timer Remaining Counts   = 136
     * -------------------------------------------------------------------------
	 * 	>>>	Scheduler Tick Time      = 1 Sec
     *      Timer Overflows          = 3906
     *      Timer Remaining Counts   = 64
	 */

#define OVERFLOWS  19  //Set no. of Timer Overflows as mentioned above
#define REMAINDER  136 //Set no. of Remainder Timer Ticks as mentioned above


//######################################################################
//Maximum number of task periorities in the project
//Assuming that we can't give the same priority for more than one task
#define TasksMaxPeriority  8 
//######################################################################

typedef enum
{
	dormant,ready,running,waiting
/*
 * Each task typically is an infinite loop that can be in any one of five states:
 *
- Dormant: a task that resides in memory but has not been made available to the multitasking kernel.
- Ready:   a task that can execute but its priority is less than the currently running task.
- Running: a task that has the control of CPU
- Waiting: a task requires the occurrence of an event (I/O operation, shared resource, timing pulse,...)
 *
 * Task Priority : it's the index of each task in the scheduling loop in range of [ 0 TO (TasksMaxNo-1) ]
 *
 */           
}enumTaskSTATUS;


typedef struct
{
	u16 tempDelay;               //Initial Task Delay ticks
	u16 periodicity;             //Periodicity of the task
	enumTaskSTATUS TaskStatus;   //Storing the Status of the task
    void (*ptr)(void);           //Pointer to the task function to be called
	
}Task;



void SCHEDULER_START(void);
void SCH_TaskArray_Init(void);
void SCH_CreateTask(Task* EnteredTask,u8 TaskPriority);
void SCH_TaskPAUSE(u8 TaskPriority);
void SCH_TaskRESUME(u8 TaskPriority);
void SCHEDULER_CALLER(void);
void SchedulerLOOP(void);




#endif /* _SCHEDULER_ */
