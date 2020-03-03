#include "scheduler.h"


volatile Task tasksArray [TasksMaxPeriority];
volatile u8 TasksIndexPointer=0; //holds the highest priority in the tasks scheduler (0 To TasksMaxPeriority)
Task* QUEUE_PTR = &tasksArray;
void SCHEDULER_START(void)
{
    //Turning OFF INTERRUPT while Initializing the scheduler
    Interrupt_GlobalEnable(OFF);
    
    //Initializing the KIT Drivers
	PICGenios_INIT(); 
    
    //Linking the Scheduler to the TIMER0 ISR by the callback API
	ISR_CALLBACK( TIMER0, SCHEDULER_CALLER); 
    ISR_CALLBACK( ADC, ADC_Read_API); //ADC result will be connected to the ADC interrupt
    
    SCH_TaskArray_Init();
    CREATE_TASKS_QUEUE();
    
    //NOW we can Turn ON the INTERRUPT to start the process
    Interrupt_GlobalEnable(ON);
}


void SCH_TaskArray_Init(void)
{
    u8 LoopIndex;
  
    //Initializing the task array with dormant tasks status
    for(LoopIndex=0 ; LoopIndex<TasksMaxPeriority ; LoopIndex++)
    {
        (tasksArray+LoopIndex)->TaskStatus = dormant;
        (tasksArray+LoopIndex)->periodicity = 0x0000;
        (tasksArray+LoopIndex)->ptr = NULL;
        (tasksArray+LoopIndex)->tempDelay = 0x0000;
    }
}


void SCH_CreateTask( Task* EnteredTask ,u8 TaskPriority)
{
    //This API takes 2 arguments:
    // ----- EnteredTask   : it's the address of the task struct to be added in the scheduler
    // ----- TaskPriotrity : it's the Priority of the added task
    

    // so we've to check that we won't exceed max no. of tasks first 
    // Assuming that adding a pre entered priority will replace the previous task with the same priority
	if( TaskPriority < TasksMaxPeriority )
	{
		/* We still can create another task */
		/*-------------------------------------------------------------------------------------------*/
        //TaskPriority = TaskPriority -1; //Adjusting the index to the range: (0) To (TaskPriotrity-1)
        
        //################### Setting the TASK ###################
		(tasksArray+TaskPriority)->periodicity = EnteredTask->periodicity ; //Setting the Priority
        (tasksArray+TaskPriority)->TaskStatus  = EnteredTask->TaskStatus ;  //Setting the Initial Status
		(tasksArray+TaskPriority)->ptr         = EnteredTask->ptr ;         //Setting the Task function
		(tasksArray+TaskPriority)->tempDelay   = EnteredTask->tempDelay ;   //Setting the initial Delay
        
        //########### Setting the actual index of highest task priority #########
        //TaskPriority = TaskPriority +1; //Adding the one that we've subtracted before
        
		if ( TaskPriority > TasksIndexPointer )
		{
			/* We want to store the actual highest priority in the tasks into "TasksIndexPointer"  */
			TasksIndexPointer = TaskPriority; 
		}

		/*-------------------------------------------------------------------------------------------*/
	}
	else
	{
		/* There is no space for another task */
	}


}



void SCH_TaskRESUME(u8 TaskPriority)
{
	(tasksArray+TaskPriority)->TaskStatus  = ready;
}

void SCH_TaskPAUSE(u8 TaskPriority)
{
	(tasksArray+TaskPriority)->TaskStatus  = dormant;
}

void SchedulerLOOP(void)
{
	u8 i=0; //Assuming max no. of tasks = 256

	if( TasksIndexPointer != 0 )
	{
		for( i=0 ; i<=TasksIndexPointer ; i++ )
		{
			if( tasksArray[i].tempDelay==0 && tasksArray[i].periodicity!=0  && tasksArray[i].TaskStatus==ready )
			{
                
				tasksArray[i].TaskStatus=running; //Set task status to running
				tasksArray[i].ptr(); //Call the task function
				tasksArray[i].tempDelay = tasksArray[i].periodicity - 1;
				tasksArray[i].TaskStatus=ready;
			}
			else
			{
				(tasksArray[i].tempDelay)-- ; //Task needs to wait some ticks first
			}
		}
	}
	else
	{
		/* No tasks in the scheduler */
	}


}



void SCHEDULER_CALLER(void)
{
	/* Scheduler Calling API : Calls the scheduler every 1 Tick */

	static u16 overflowCount=0;

	overflowCount++;

	if ( overflowCount == (OVERFLOWS) )
	{
		/* Loading the Remainder Timer Ticks to timer counter register */
        TMR0 = (256-REMAINDER);
	}
	else if( overflowCount == (OVERFLOWS + 1) )
	{
		/* It's a Scheduler tick, Call the Scheduler API */
		SchedulerLOOP();
        
        overflowCount=0;
	}

}
