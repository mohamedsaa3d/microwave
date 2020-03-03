/*
 * interrupt_config.h
 *
 *  Created on: 12 Apr 2019
 *      Author: MohamedSaa3D
 */

#ifndef _INTERRUPT_CONFIG_H_
#define _INTERRUPT_CONFIG_H_

///*---------------------------------------------------------------------*/
///* INTERRUPT CONTROL :   DISABLED  /  ENABLED                          */
///*---------------------------------------------------------------------*/
#define GLOBAL_IEN      ENABLED    //ENABLE/DISABLE GLOBAL INTERRUPT

#define INT0_EN         DISABLED   //Enable/Disable External Interrupt on pin RB0/INT

#define TIMER0_EN       ENABLED    //SELECT TIMER0 Interrupt :  ENABLED/DISABLED

#define TIMER1_EN       DISABLED   //Enable/Disable TIMER1 Interrupt

#define ADC_INT_EN      ENABLED   //Enable/Disable ADC Conversion Interrupt

///*----------------------------------------------------------------------------------*/
///* SENSE EDGE CONTROL :  FALLING  /  RISING                                         */
///*----------------------------------------------------------------------------------*/

#define INT0_SENSE      RISING     //The INT0 interrupts on this edge

#define TIMER0_SENSE    RISING     //The timer0 counter increments on this edge


///*---------------------------------------------------------------------------------------*/
///                                      CS >> INTERNAL , EXTERNAL                         */
///* CLOCK SOURCE / PRESCALER  CONTROL :                                                   */
///*                                     PS >> TPS2,TPS4,TPS8,TPS16,TPS32,TPS64,TPS128     */
///*---------------------------------------------------------------------------------------*/

#define TIMER0_CS       INTERNAL   //Use the (F_OSC/4) Clock as the timer clock

#define TIMER0_PS       TPS2       //Select the timer prescaler

#define TIMER1_CS       INTERNAL   //Use the (F_OSC/4) Clock as the timer clock
#define TIMER1_PS       TPS8       //Select the timer prescaler





#endif /* _INTERRUPT_CONFIG_H_ */
