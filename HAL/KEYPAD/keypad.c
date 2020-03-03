#include "keypad.h"

void Keypad_Initialization(void)
{

	/*
	 * KEYPAD PORT LAYOUT
	 *   RB0       RB1       RB2
	 *   C0        C1        C2
	 *-----------------------------*
	 *         |         |         *
	 *    1    |    2    |    3    *  R0  RD0
	 *-----------------------------*
	 *         |         |         *
	 *    4    |    5    |    6    *  R1  RD1
	 *-----------------------------*
	 *         |         |         *
	 *    7    |    8    |    9    *  R2  RD2
	 *-----------------------------*
	 *         |         |         *
	 *   DEL   |    0    |  ENTER  *  R3  RD3
	 *-----------------------------*
	 */
    
    //NOTE:  ADCON1_REG Must be set To be able to use RB0 , RB1 , RB2 pins as digital pins not analog

    DIO_u8SetPinDirection(KEYPAD_C0_PORT , KEYPAD_C0_PIN , INPUT);
    DIO_u8SetPinDirection(KEYPAD_C1_PORT , KEYPAD_C1_PIN , INPUT);
    DIO_u8SetPinDirection(KEYPAD_C2_PORT , KEYPAD_C2_PIN , INPUT);
    
    CLR_BIT(OPTION_REG,7); //Enabling PORTB PULL-UP (KEYPAD COLLUMNS is normally high)
    
    DIO_u8SetPinDirection(KEYPAD_R0_PORT , KEYPAD_R0_PIN , OUTPUT);   
    DIO_u8SetPinDirection(KEYPAD_R1_PORT , KEYPAD_R1_PIN , OUTPUT);
    DIO_u8SetPinDirection(KEYPAD_R2_PORT , KEYPAD_R2_PIN , OUTPUT);
    DIO_u8SetPinDirection(KEYPAD_R3_PORT , KEYPAD_R3_PIN , OUTPUT);
    
    // Setting initial HIGH signals on the ROWS
    DIO_u8SetPinValue(KEYPAD_R0_PORT , KEYPAD_R0_PIN , HIGH);   
    DIO_u8SetPinValue(KEYPAD_R1_PORT , KEYPAD_R1_PIN , HIGH);
    DIO_u8SetPinValue(KEYPAD_R2_PORT , KEYPAD_R2_PIN , HIGH);
    DIO_u8SetPinValue(KEYPAD_R3_PORT , KEYPAD_R3_PIN , HIGH);
}

u8 Keypad_ReadKey(u8* KeyValue)
{
    u8 KeyPressedFlag;
	u8 row_iteration;
	u8 col_iteration;
	u8 reading;
	u8 ReturnData=0; //Any value not in the range 0:11

	KeyPressedFlag = 0; /*Setting the flag : indicates that no key is pressed yet , user must reset it after reading*/
	*KeyValue = 0;

	for ( row_iteration=0 ; row_iteration<4 ; row_iteration++ )
	{
        //Give a LOW signal for a ROW
        switch(row_iteration)
        {
            case 0:
                DIO_u8SetPinValue( KEYPAD_R0_PORT, KEYPAD_R0_PIN , LOW ); //Set ROW to LOW
                break;
            case 1:
                DIO_u8SetPinValue( KEYPAD_R1_PORT, KEYPAD_R1_PIN , LOW ); //Set ROW to LOW
                break;
            case 2:
                DIO_u8SetPinValue( KEYPAD_R2_PORT, KEYPAD_R2_PIN , LOW ); //Set ROW to LOW
                break;
            case 3:
                DIO_u8SetPinValue( KEYPAD_R3_PORT, KEYPAD_R3_PIN , LOW ); //Set ROW to LOW
                break;
        }
        

		for ( col_iteration=0 ; col_iteration<3 ; col_iteration++ )
		{
            // Reading which Column is pulled down
            if(col_iteration == 0)
            {
                DIO_u8GetPinValue( KEYPAD_C0_PORT, KEYPAD_C0_PIN , &reading );
            }
            else if (col_iteration == 1)
            {
                DIO_u8GetPinValue( KEYPAD_C1_PORT, KEYPAD_C1_PIN , &reading );
            }
            else
            {
                DIO_u8GetPinValue( KEYPAD_C2_PORT, KEYPAD_C2_PIN , &reading );
            }


			if( !reading ) /*If a pressed button is found*/
			{
				switch(row_iteration)
				{
					case 0:
						switch(col_iteration)
						{
							case 0:
								ReturnData=1;
								break;
							case 1:
								ReturnData=2;
								break;
							case 2:
								ReturnData=3;
								break;
						}
						break;
					case 1:
						switch(col_iteration)
						{
							case 0:
								ReturnData=4;
								break;
							case 1:
								ReturnData=5;
								break;
							case 2:
								ReturnData=6;
								break;
						}
						break;
					case 2:
						switch(col_iteration)
						{
							case 0:
								ReturnData=7;
								break;
							case 1:
								ReturnData=8;
								break;
							case 2:
								ReturnData=9;
								break;
						}
						break;
					case 3:
						switch(col_iteration)
						{
							case 0:
								ReturnData=DELETE; //10 means : 'DELETE' ('*' on Keypad)
								break;
							case 1:
								ReturnData=0;
								break;
							case 2:
								ReturnData=ENTER; //11 means : 'ENTER' ('#' on Keypad)
								break;
						}
						break;
				}

				KeyPressedFlag = 1; /*Setting the flag : indicates that a key is pressed and ready to be send*/
				*KeyValue = ReturnData; /* Returning the pressed key value */
				//__delay_ms(10); //Wait sometime to suppress debouncing
			}
		}
        
		//Remove the LOW signal that was given to a ROW

        switch(row_iteration)
        {
            case 0:
                DIO_u8SetPinValue( KEYPAD_R0_PORT, KEYPAD_R0_PIN , HIGH ); break; /*Set ROW to LOW*/
            case 1:
                DIO_u8SetPinValue( KEYPAD_R1_PORT, KEYPAD_R1_PIN , HIGH ); break; /*Set ROW to LOW*/
            case 2:
                DIO_u8SetPinValue( KEYPAD_R2_PORT, KEYPAD_R2_PIN , HIGH ); break; /*Set ROW to LOW*/
            case 3:
                DIO_u8SetPinValue( KEYPAD_R3_PORT, KEYPAD_R3_PIN , HIGH ); break; /*Set ROW to LOW*/
        }

	}

	return KeyPressedFlag;
}
