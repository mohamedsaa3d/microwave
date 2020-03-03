
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_
#include <xc.h>

#include "../../Libraries/BIT_MATH.h"
#include "../../Libraries/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_int.h"
#include "../../HAL/PICGenious/PICGenious_config.h"
#include "LCD_CONFIG.h"
#include "LCD_priv.h"


void LCD_Initialization(void);
void LCD_WriteCMD(u8 CMD);
void LCD_WriteDATA(u8 DATA);
void LCD_WriteLINE(u8 DATA[]);
void LCD_WriteNUMBER(s32 DATA);
void LCD_GOTO_XY(u8 X_AXIS, u8 Y_AXIS);


#endif /* LCD_INTERFACE_H_ */
