
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#undef _XTAL_FREQ
#define _XTAL_FREQ 1000000UL //Specify the XTAL crystal FREQ (8MHz)


//----------- PINS Config ------------
#define START_PIN  3
#define START_PORT B
//---------------------------------
#define CANCEL_PIN  4
#define CANCEL_PORT B
//---------------------------------
#define WEIGHT_PIN  6
#define WEIGHT_PORT C
//---------------------------------
#define DOOR_PIN  7//7
#define DOOR_PORT C
//---------------------------------
#define PAUSE_PIN  1//4
#define PAUSE_PORT C
//---------------------------------
#define TEMP_PIN   AN2
#define VDD_VOLT       5
#define LM35_VOLT_CEL  10  //LM35 output : 10mV / Celsius
//---------------------------------
#define BUZZER_PIN   1 
#define BUZZER_PORT  C
//---------------------------------
#define MOTOR_PIN   2 
#define MOTOR_PORT  C
//---------------------------------
#define LED_PIN  6
#define LED_PORT B
//---------------------------------
#define HEATER_PIN  5
#define HEATER_PORT C

//---------------------------------
#define KEYPAD_C0_PIN   0
#define KEYPAD_C0_PORT  B

#define KEYPAD_C1_PIN   1
#define KEYPAD_C1_PORT  B

#define KEYPAD_C2_PIN   2
#define KEYPAD_C2_PORT  B

#define KEYPAD_R0_PIN   3
#define KEYPAD_R0_PORT  D

#define KEYPAD_R1_PIN   2
#define KEYPAD_R1_PORT  D

#define KEYPAD_R2_PIN   1
#define KEYPAD_R2_PORT  D

#define KEYPAD_R3_PIN   0
#define KEYPAD_R3_PORT  D
//--------------------------------- 








#endif	/* XC_HEADER_TEMPLATE_H */

