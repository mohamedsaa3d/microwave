#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include "interrupt_private.h"
#include "interrupt_config.h"
#include "../../Libraries/BIT_MATH.h"
#include "../../Libraries/STD_TYPES.h"
#include "../DIO/DIO_int.h"
#include "../../HAL/PICGenious/PICGenious_config.h"


//#define ISR(vector_no) void vector_no(void)__attribute__((signal,__INTR_ATTRS)); \
//					   void vector_no(void)

//-------------------------------------------------------------------------
//Definition of Interrupt Service Routine according to the XC8 compiler
void __interrupt() ISR(void);
//-------------------------------------------------------------------------
void Interrupt_Initialization(void);
void Interrupt_GlobalEnable(DIG_STATE GIE);

void Interrupt_Select(void);

void Interrupt_INT0_Options(void);
void Interrupt_T0_Options(void);
void Interrupt_T1_Options(void);


void Interrupt_INT0ISR(void);
void Interrupt_T0ISR(void);
void Interrupt_T1ISR(void);
void Interrupt_ADCISR(void);

void ISR_CALLBACK( ISR_LIST ISR_ID , void(*functionPTR)(void)  );



#endif /* _INTERRUPT_H_ */
