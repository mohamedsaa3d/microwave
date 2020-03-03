#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../PICGenious/PICGenious_config.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../Libraries/BIT_MATH.h"
#include "../../Libraries/STD_TYPES.h"
#include <xc.h>

void Keypad_Initialization(void);
u8 Keypad_ReadKey(u8* KeyValue);

#define DELETE 10 //Returning value when DELETE is pressed
#define ENTER  11 //Returning value when ENTER is pressed

#endif
