#ifndef _LCD_PRIV_H_
#define _LCD_PRIV_H_


/* LCD Commands Binary Codes */
#define ClearDisplay    0x01
#define ReturnHome      0x02
#define FISRT_LINE_POS  0x80
#define SECOND_LINE_POS 0xC0
#define THIRD_LINE_POS  0xA8
#define FOURTH_LINE_POS 0xD0
#define CGRAM_ADDRESS   0b01000000
#define ShiftCursorL    0b00010000
#define ShiftCursorR    0b00010100

#define BlackChar       0xFF
#define SmileChar       0xC2


/* Forming the Control Byte by concatenating the control bits */

#define DisplayControl  BYTE_CONC(0,0,0,0,1,DISP,CURSOR,BLINK)

#define FunctionSet     BYTE_CONC(0,0,1,DATA_LENGTH,NO_OF_LINES,FONT,0,0)


#endif
