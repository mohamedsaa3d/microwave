#include "LCD_interface.h"

void LCD_Initialization(void)
{
    //NOTE: ADCON1_REG Must be set to be able to use EN , RS pins as digital pins not analog
    
    DIO_u8SetPinDirection(LCD_EN_PORT , LCD_EN_PIN , OUTPUT);
    DIO_u8SetPinDirection(LCD_RS_PORT , LCD_RS_PIN , OUTPUT);
    DIO_u8SetPinValue (LCD_RS_PORT , LCD_RS_PIN , LOW);  /* RS LOW to write a Command */
    DIO_u8SetPinValue (LCD_EN_PORT , LCD_RS_PIN , LOW);  /* RS LOW to write a Command */
    /* Wait for Power on initialization time  */
	__delay_ms(30);
    DIO_u8SetPinValue (LCD_EN_PORT , LCD_RS_PIN , HIGH);  /* RS LOW to write a Command */
    
    /* Command PINS Config */
    DIO_u8SetPinDirection(LCD_D4_PORT , LCD_D4_PIN , OUTPUT);
    DIO_u8SetPinDirection(LCD_D5_PORT , LCD_D5_PIN , OUTPUT);
    DIO_u8SetPinDirection(LCD_D6_PORT , LCD_D6_PIN , OUTPUT);
    DIO_u8SetPinDirection(LCD_D7_PORT , LCD_D7_PIN , OUTPUT);

#if   DATA_LENGTH == 0  //4-Bit Mode
	//The Data bus pins will only be: (D4 - D5 - D6 - D7)

#elif   DATA_LENGTH == 1 //8-Bit Mode
    //The Data bus pins will be: (D0 - D1 - D2 - D3 - D4 - D5 - D6 - D7)
    DIO_u8SetPinDirection(LCD_D0_PORT , LCD_D0_PIN , OUTPUT);
    DIO_u8SetPinDirection(LCD_D1_PORT , LCD_D1_PIN , OUTPUT);
    DIO_u8SetPinDirection(LCD_D2_PORT , LCD_D2_PIN , OUTPUT);
    DIO_u8SetPinDirection(LCD_D3_PORT , LCD_D3_PIN , OUTPUT);
#endif
    	


	/*  DATA_LENGTH (4/8-Bit) /  NO_OF_LINES (2-Lines) /  FONT (5x11 dots) */
    /* Note the Config Command should be repeated many times according to the PICSIM manual (Example) */
	LCD_WriteCMD( FunctionSet );
	//__delay_ms(10);
	LCD_WriteCMD( FunctionSet );
	//__delay_ms(10);
	LCD_WriteCMD( FunctionSet );
	//__delay_ms(10);
    
	/*  Display (ON) /  CURSOR (ON) /  BLINKING (ON) */
	LCD_WriteCMD( DisplayControl );
	//__delay_ms(10);

	LCD_WriteCMD( ClearDisplay );
	//__delay_ms(10);


}


void LCD_WriteCMD( u8 CMD )
{
	 DIO_u8SetPinValue (LCD_RS_PORT , LCD_RS_PIN , LOW);  /* RS LOW to write a Command */

	 /*_________________________________________________________________________________*/
	 #if   DATA_LENGTH == 0

	 	 /* Sending the higher nibble (4-bits) */
	 	DIO_u8SetPinValue( LCD_D4_PORT , LCD_D4_PIN , GET_BIT(CMD,4) );
        DIO_u8SetPinValue( LCD_D5_PORT , LCD_D5_PIN , GET_BIT(CMD,5) );
        DIO_u8SetPinValue( LCD_D6_PORT , LCD_D6_PIN , GET_BIT(CMD,6) );
        DIO_u8SetPinValue( LCD_D7_PORT , LCD_D7_PIN , GET_BIT(CMD,7) );

	 	//LCD_EN_TRIG();
        DIO_u8SetPinValue (LCD_EN_PORT , LCD_EN_PIN , HIGH);  /* EN Trigger */
        //__delay_ms(5);
        DIO_u8SetPinValue (LCD_EN_PORT , LCD_EN_PIN , LOW);  /* EN Trigger */
        //__delay_ms(5); 

	 	 /* Sending the lower nibble (4-bits) */
	 	DIO_u8SetPinValue( LCD_D4_PORT , LCD_D4_PIN , GET_BIT(CMD,0) );
        DIO_u8SetPinValue( LCD_D5_PORT , LCD_D5_PIN , GET_BIT(CMD,1) );
        DIO_u8SetPinValue( LCD_D6_PORT , LCD_D6_PIN , GET_BIT(CMD,2) );
        DIO_u8SetPinValue( LCD_D7_PORT , LCD_D7_PIN , GET_BIT(CMD,3) );

	 	//LCD_EN_TRIG();
        DIO_u8SetPinValue (LCD_EN_PORT , LCD_EN_PIN , HIGH);  /* EN Trigger */
        //__delay_ms(5);
        DIO_u8SetPinValue (LCD_EN_PORT , LCD_EN_PIN , LOW);  /* EN Trigger */
        //__delay_ms(5); 

	 #elif DATA_LENGTH == 1
        
        DIO_u8SetPinValue( LCD_D0_PORT , LCD_D0_PIN , GET_BIT(CMD,0) );
        DIO_u8SetPinValue( LCD_D1_PORT , LCD_D1_PIN , GET_BIT(CMD,1) );
        DIO_u8SetPinValue( LCD_D2_PORT , LCD_D2_PIN , GET_BIT(CMD,2) );
        DIO_u8SetPinValue( LCD_D3_PORT , LCD_D3_PIN , GET_BIT(CMD,3) );
        DIO_u8SetPinValue( LCD_D4_PORT , LCD_D4_PIN , GET_BIT(CMD,4) );
        DIO_u8SetPinValue( LCD_D5_PORT , LCD_D5_PIN , GET_BIT(CMD,5) );
        DIO_u8SetPinValue( LCD_D6_PORT , LCD_D6_PIN , GET_BIT(CMD,6) );
        DIO_u8SetPinValue( LCD_D7_PORT , LCD_D7_PIN , GET_BIT(CMD,7) );

	 #endif
	 /*_________________________________________________________________________________*/

}


void LCD_WriteDATA( u8 DATA )
{
	DIO_u8SetPinValue (LCD_RS_PORT , LCD_RS_PIN , HIGH);  /* RS HIGH to write a DATA */

	 /*_________________________________________________________________________________*/
	 #if   DATA_LENGTH == 0

	 	 /* Sending the high nibble (4-bits) */
	 	DIO_u8SetPinValue( LCD_D4_PORT , LCD_D4_PIN , GET_BIT(DATA,4) );
        DIO_u8SetPinValue( LCD_D5_PORT , LCD_D5_PIN , GET_BIT(DATA,5) );
        DIO_u8SetPinValue( LCD_D6_PORT , LCD_D6_PIN , GET_BIT(DATA,6) );
        DIO_u8SetPinValue( LCD_D7_PORT , LCD_D7_PIN , GET_BIT(DATA,7) );

        DIO_u8SetPinValue (LCD_EN_PORT , LCD_EN_PIN , HIGH);  /* EN Trigger */
        //__delay_ms(5);
        DIO_u8SetPinValue (LCD_EN_PORT , LCD_EN_PIN , LOW);  /* EN Trigger */
        //__delay_ms(5); 

	 	 /* Sending the low nibble (4-bits) */
	 	DIO_u8SetPinValue( LCD_D4_PORT , LCD_D4_PIN , GET_BIT(DATA,0) );
        DIO_u8SetPinValue( LCD_D5_PORT , LCD_D5_PIN , GET_BIT(DATA,1) );
        DIO_u8SetPinValue( LCD_D6_PORT , LCD_D6_PIN , GET_BIT(DATA,2) );
        DIO_u8SetPinValue( LCD_D7_PORT , LCD_D7_PIN , GET_BIT(DATA,3) );

        
        DIO_u8SetPinValue (LCD_EN_PORT , LCD_EN_PIN , HIGH);  /* EN Trigger */
        //__delay_ms(5);
        DIO_u8SetPinValue (LCD_EN_PORT , LCD_EN_PIN , LOW);  /* EN Trigger */
        //__delay_ms(5); 

	 #elif DATA_LENGTH == 1
        
        DIO_u8SetPinValue( LCD_D0_PORT , LCD_D0_PIN , GET_BIT(DATA,0) );
        DIO_u8SetPinValue( LCD_D1_PORT , LCD_D1_PIN , GET_BIT(DATA,1) );
        DIO_u8SetPinValue( LCD_D2_PORT , LCD_D2_PIN , GET_BIT(DATA,2) );
        DIO_u8SetPinValue( LCD_D3_PORT , LCD_D3_PIN , GET_BIT(DATA,3) );
        DIO_u8SetPinValue( LCD_D4_PORT , LCD_D4_PIN , GET_BIT(DATA,4) );
        DIO_u8SetPinValue( LCD_D5_PORT , LCD_D5_PIN , GET_BIT(DATA,5) );
        DIO_u8SetPinValue( LCD_D6_PORT , LCD_D6_PIN , GET_BIT(DATA,6) );
        DIO_u8SetPinValue( LCD_D7_PORT , LCD_D7_PIN , GET_BIT(DATA,7) );

	 	DIO_u8SetPinValue (LCD_EN_PORT , LCD_EN_PIN , HIGH);  /* EN Trigger */
	 	__delay_ms(5);
	 	DIO_u8SetPinValue (LCD_EN_PORT , LCD_EN_PIN , LOW);  /* EN Trigger */
        __delay_ms(5);

	 #endif
	 /*_________________________________________________________________________________*/
}


void LCD_WriteLINE(u8 DATA[])
{
	u8 loop_index = 0;

	while( DATA[loop_index] != '\0' )
	{
		LCD_WriteDATA( DATA[loop_index] );
		loop_index++;
	}
}

void LCD_WriteNUMBER(s32 DATA)
{
	u32 Temp = 1;
	u8  counts=0;

	if(DATA<0)
	{
        //If it's a negative number then display a negative sign
        LCD_WriteDATA('-');
		DATA = DATA * -1;
	}
	else if(DATA==0)
	{
        //If it's a ZERO
		LCD_WriteDATA('0');
	}
    //Printing the digits
	while(DATA !=0 )
	{
		// Reversing the Number
        // Ex : if we want to print a number DATA= 1234 then Temp= 43211
        //      Then it's get printed digit by digit as shown >> Prints (1)
        //                                                    >> Prints (2)
        //                                                    >> Prints (3)
        //                                                    >> Prints (4)
        //NOTE: a (1) is added to the end of the reversed number to be able to prints numbers like 100,200,..
		Temp = (Temp*10) + (DATA%10);
		DATA=DATA/10;
		counts++;
	}
    //Note after the first loop (of reversing the number) the counts = (no. of digits + 1)
	while(counts !=0 )
	{
        /* Printing digit by digit */
		LCD_WriteDATA( (Temp%10)+'0' ); //'0' is used to convert the digit to ASCII
		Temp = Temp/10;
		counts--;
	}

}

void LCD_GOTO_XY(u8 X_AXIS, u8 Y_AXIS)
{
	if(X_AXIS<=MAXCHARS && Y_AXIS<=MAXLINES)
	{
		if( 1 == Y_AXIS )
		{
			LCD_WriteCMD( FISRT_LINE_POS + X_AXIS-1 );
		}
		else if( 2 == Y_AXIS )
		{
			LCD_WriteCMD( SECOND_LINE_POS + X_AXIS-1 );
		}
        else if( 3 == Y_AXIS )
        {
            LCD_WriteCMD( THIRD_LINE_POS + X_AXIS-1 );
        }
        else if( 4 == Y_AXIS )
        {
            LCD_WriteCMD( FOURTH_LINE_POS + X_AXIS-1 );
        }
	}

}
