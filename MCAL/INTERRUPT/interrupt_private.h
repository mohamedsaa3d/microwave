
#ifndef _INTERRUPT_PRIVATE_H_
#define _INTERRUPT_PRIVATE_H_

#define INTCON *((volatile u8*)(0x0B))
#define TMR0   *((volatile u8*)(0x01))
#define PIR1   *((volatile u8*)(0x0C))
#define PIR2   *((volatile u8*)(0x0D))
#define PIE1   *((volatile u8*)(0x8C))
#define T1CON  *((volatile u8*)(0x10))




typedef enum
{
  //This list of all interrupts in the microcontroller used to assign ISR to each of them if needed
    INT0
  , TIMER0
  , TIMER1
  , ADC

}ISR_LIST;





#endif /* _INTERRUPT_PRIVATE_H_ */
