#ifndef _PICGENIOS_
#define _PICGENIOS_

#include <xc.h>
#include "../../MCAL/DIO/DIO_int.h"
#include "../../MCAL/INTERRUPT/interrupt.h"
#include "PICGenious_config.h"
#include "../../MCAL/ADC/ADC.h"
#include "../LCD/LCD_interface.h"
#include "../KEYPAD/keypad.h"
#include "../../Libraries/scheduler.h"





void PICGenios_INIT(void);
void PICGEN_BUZZER(DIG_STATE STATE);
void PICGEN_MOTOR(DIG_STATE STATE);
void PICGEN_LED(DIG_STATE STATE);
void PICGEN_HEATER(DIG_STATE STATE);



#endif