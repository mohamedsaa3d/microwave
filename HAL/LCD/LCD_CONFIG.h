#ifndef LCD_CONFIG_
#define LCD_CONFIG_

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000UL //Specify the XTAL crystal FREQ (20MHz)
#endif

/* LCD Pins Configuration is imported from PICGenious_config.h */

#define LCD_EN_PIN   1
#define LCD_EN_PORT  E

#define LCD_RS_PIN   2
#define LCD_RS_PORT  E

#define LCD_D0_PIN   0
#define LCD_D0_PORT  D

#define LCD_D1_PIN   1
#define LCD_D1_PORT  D

#define LCD_D2_PIN   2
#define LCD_D2_PORT  D

#define LCD_D3_PIN   3
#define LCD_D3_PORT  D

#define LCD_D4_PIN   4
#define LCD_D4_PORT  D

#define LCD_D5_PIN   5
#define LCD_D5_PORT  D

#define LCD_D6_PIN   6
#define LCD_D6_PORT  D

#define LCD_D7_PIN   7
#define LCD_D7_PORT  D



/* In case of 4-Bit Mode : Select the higher or lower port nibble */
//#define LCD_DATA_NIBBLE  LOWER            /*Select LOWER / HIGHER */

/* LCD Option Configurations */
/*
 *  Set DISP     0 or 1      :  To Turn on/off the display                                *
 *  Set CURSOR   0 or 1      :  To Turn on/off the cursor                                 *
 *  Set BLINK    0 or 1      :  To Turn on/off the cursor blinking                        *
 *  Set DATA_LENGTH   0 or 1 :  Sets interface data length   (1) 8-bit    / (0) 4-bit     *
 *  Set NO_OF_LINES   0 or 1 :  Sets numbers of display line (1) 2-line   / (0) 1-line    *
 *  Set FONT          0 or 1 :  Sets display font type       (1) 5x11dots / (0) 5x8dots   *
 *  Set MAXLINES      2 or 4 :  Sets LCD Size                (2) 2-Lines  / (4) 4-Lines   *
 *  Set MAXCHARS      2 or 4 :  Sets LCD Size                (16) For 16 Characters Line  */


#define DATA_LENGTH   0
#define DISP          1
#define CURSOR        0
#define BLINK         0
#define NO_OF_LINES   1
#define FONT          1
#define MAXLINES      4
#define MAXCHARS      16





#endif
