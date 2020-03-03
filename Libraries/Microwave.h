#ifndef _MICROWAVE_
#define _MICROWAVE_

#include "scheduler.h"

// #####################################################################
// NOTE : Periodicity is used in terms of scheduler ticks (default 1 ms)
// #####################################################################

//The timer tick maybe not accurate during simulation
//so scale is used to get the ticks closer to real time
#define PD_SCALE     0.2           

#define MAX_TIMER_MINUTES 60
#define MAX_TIMER_SECONDS 60
// ------------------------------
//  TASK : SET RUN CONFIGURATION
// ------------------------------
#define RCONFG_PERIOD    25     //Setting Periodicity
#define RCONFG_IDELAY    0       //Setting Initial Delay for the task
#define RCONFG_ISTATUS   ready   //Setting the initial task status
#define RCONFG_PRIORITY  0       //Setting the task priority

// ------------------------------
//  TASK : SCANNING START BUTTON
// ------------------------------
#define START_PERIOD    90     //Setting Periodicity
#define START_IDELAY    100       //Setting Initial Delay for the task
#define START_ISTATUS   ready   //Setting the initial task status
#define START_PRIORITY  1       //Setting the task priority

// ------------------------------
//  TASK : SCANNING CANCEL BUTTON
// ------------------------------
#define CANCEL_PERIOD   90     //Setting Periodicity
#define CANCEL_IDELAY   100       //Setting Initial Delay for the task
#define CANCEL_ISTATUS  ready   //Setting the initial task status
#define CANCEL_PRIORITY  2      //Setting the task priority

// ------------------------------
//  TASK : SCANNING KEYPAD 
// ------------------------------
#define KEYPAD_PERIOD   90     //Setting Periodicity
#define KEYPAD_IDELAY   100       //Setting Initial Delay for the task
#define KEYPAD_ISTATUS  ready   //Setting the initial task status
#define KEYPAD_PRIORITY  3      //Setting the task priority

// ------------------------------
//  TASK : SCANNING WEIGHT SENSOR
// ------------------------------
#define WEIGHT_PERIOD   500     //Setting Periodicity
#define WEIGHT_IDELAY   3000       //Setting Initial Delay for the task
#define WEIGHT_ISTATUS  ready   //Setting the initial task status
#define WEIGHT_PRIORITY  4      //Setting the task priority


// ------------------------------
//  TASK : SCANNING DOOR SENSOR
// ------------------------------
#define DOOR_PERIOD     500    //Setting Periodicity
#define DOOR_IDELAY     100       //Setting Initial Delay for the task
#define DOOR_ISTATUS    ready   //Setting the initial task status
#define DOOR_PRIORITY   5       //Setting the task priority

// ------------------------------
//  TASK : UPDATING RUNNING TIMER
// ------------------------------
#define UPDTIME_PERIOD   1000    //Setting Periodicity
#define UPDTIME_IDELAY   3000       //Setting Initial Delay for the task
#define UPDTIME_ISTATUS  ready   //Setting the initial task status
#define UPDTIME_PRIORITY  6      //Setting the task priority


// ------------------------------
//  TASK : SCANNING TEMP SENSOR 
// ------------------------------
#define TEMP_PERIOD   500     //Setting Periodicity
#define TEMP_IDELAY   3000     //Setting Initial Delay for the task
#define TEMP_ISTATUS  ready   //Setting the initial task status
#define TEMP_PRIORITY  7      //Setting the task priority


//-----------------------------------------------


typedef struct
{
    u32 BUFFER ;     //Buffer to store entered number digits
    u8 PRESS_FLAG;   //IF any key is pressed this flag is set
    u8 ENTER_FLAG;   //ENTER BUTTON  (1 if Pressed)
    u8 START_FLAG;   //START BUTTON  (1 if Pressed)
    u8 CANCELL_FLAG; //CANCEL BUTTON (1 if Pressed)
}KEYPAD_BUFFER_STRUCT;

typedef struct
{
    u8 MIN;
    u8 SEC;
    u8 MFLAG;
    u8 SFLAG;
    u8 CONFIRMED;
}SETTIME_STRUCT;

typedef struct
{
    u8 TEMPERATURE;
    u8 WEIGHT;
    u8 DOOR;
    u8 PAUSE;
}SENSORS_STRUCT;

//----------------------------------------------

void CREATE_TASKS_QUEUE(void);
void SCAN_START_API(void);
void SCAN_CANCEL_API(void);
void SCAN_KEYPAD_API(void);
void SCAN_TEMP_API(void);
void SCAN_WEIGHT_API(void);
void SCAN_DOOR_API(void);
void UPDATE_TIME_API(void);
void RUN_CONFIG_API(void);












#endif