
#include "DIO_int.h"
#include "../../Libraries/BIT_MATH.h"
#include "../../Libraries/STD_TYPES.h"


u8 DIO_u8SetPinDirection(PORT_INDEX PORT , PIN_INDEX PIN , PIN_DIR DIR)
{
	/* Function internal Error Flag */
	u8 u8ErrorState = 0;

	/* Invalid Input Protection : checking if the arguments indexes are in a valid range */
	if (    ( PORT  <=  MAX_PORT_INDEX )
	     && ( PIN   <=  MAX_PIN_INDEX  )
	     && (( DIR  == INPUT )||( DIR == OUTPUT ))
	   )
	{
		/* Fetching the port number index */
		switch( PORT )
			{
				case A:
					if( DIR == OUTPUT )
					{
						/* The pin is requested to be O/P */
						CLR_BIT( TRISA ,PIN );
					}
					else
					{
						/* The pin is requested to be I/P */
						SET_BIT( TRISA ,PIN );
					}
					break;

				case B:
					if( DIR == OUTPUT )
					{
						/* The pin is requested to be O/P */
						CLR_BIT( TRISB ,PIN );
					}
					else
					{
						/* The pin is requested to be I/P */
						SET_BIT( TRISB ,PIN );
					}
					break;

				case C:
					if( DIR == OUTPUT )
					{
						/* The pin is requested to be O/P */
						CLR_BIT( TRISC ,PIN );
					}
					else
					{
						/* The pin is requested to be I/P */
						SET_BIT( TRISC ,PIN );
					}
					break;

				case D:
					if( DIR == OUTPUT )
					{
						/* The pin is requested to be O/P */
						CLR_BIT( TRISD ,PIN );
					}
					else
					{
						/* The pin is requested to be I/P */
						SET_BIT( TRISD ,PIN );
					}
					break;
                    
				case E:
					if( DIR == OUTPUT )
					{
						/* The pin is requested to be O/P */
						CLR_BIT( TRISE ,PIN );
					}
					else
					{
						/* The pin is requested to be I/P */
						SET_BIT( TRISE ,PIN );
					}
					break;
            }
    }
    else
    {
        //API has wrong inputs
        u8ErrorState = 1;
    }

	return u8ErrorState;

}

    
u8 DIO_u8SetPinValue(PORT_INDEX PORT , PIN_INDEX PIN , PIN_LEVEL LEVEL)
{
	/* Function internal Error Flag */
	u8 u8ErrorState = 0;

	/* Invalid Input Protection : checking if the arguments indexes are in a valid range */
	if (    ( PORT  <=  MAX_PORT_INDEX )
	     && ( PIN   <=  MAX_PIN_INDEX  )
	     && (( LEVEL  == LOW )||( LEVEL == HIGH ))
	   )
	{
		/* Fetching the port number index */
		switch( PORT )
			{
				case A:
					if( LEVEL == LOW )
					{
						/* The pin is requested to be LOW */
						CLR_BIT( PORTA , PIN );
					}
					else
					{
						/* The pin is requested to be HIGH */
						SET_BIT( PORTA , PIN );
					}
					break;

				case B:
					if( LEVEL == LOW )
					{
						/* The pin is requested to be LOW */
						CLR_BIT( PORTB , PIN );
					}
					else
					{
						/* The pin is requested to be HIGH */
						SET_BIT( PORTB , PIN );
					}
					break;

				case C:
					if( LEVEL == LOW )
					{
						/* The pin is requested to be LOW */
						CLR_BIT( PORTC , PIN );
					}
					else
					{
						/* The pin is requested to be HIGH */
						SET_BIT( PORTC , PIN );
					}
					break;

				case D:
					if( LEVEL == LOW )
					{
						/* The pin is requested to be LOW */
						CLR_BIT( PORTD , PIN );
					}
					else
					{
						/* The pin is requested to be HIGH */
						SET_BIT( PORTD , PIN );
					}
					break;
                    
				case E:
					if( LEVEL == LOW )
					{
						/* The pin is requested to be LOW */
						CLR_BIT( PORTE , PIN );
					}
					else
					{
						/* The pin is requested to be HIGH */
						SET_BIT( PORTE , PIN );
					}
					break;
			}
	}
	else
	{
		//API has wrong inputs
        u8ErrorState = 1;
	}

	return u8ErrorState;
}



u8 DIO_u8GetPinValue(PORT_INDEX PORT , PIN_INDEX PIN , u8* u8Value )
{
	/* Function internal Error Flag */
	u8 u8ErrorState = 0;

	/* Invalid Input Protection : checking if the arguments indexes are in a valid range */
	if (     ( PORT  <=  MAX_PORT_INDEX )
	      && ( PIN   <=  MAX_PIN_INDEX  )
		  && ( NULL  !=  u8Value        )
	   )
	{
		/* Fetching the port number index */
		switch( PORT )
			{
				case A:
					/* Returning the PIN value */
					*u8Value = GET_BIT( PORTA , PIN );
					break;

				case B:
					/* Returning the PIN value */
					*u8Value = GET_BIT( PORTB , PIN );
					break;

				case C:
					/* Returning the PIN value */
					*u8Value = GET_BIT( PORTC , PIN );
					break;

				case D:
					/* Returning the PIN value */
					*u8Value = GET_BIT( PORTD , PIN );
					break;
                    
				case E:
					/* Returning the PIN value */
					*u8Value = GET_BIT( PORTE , PIN );
					break;
			}
	}
	else
	{
		//API has wrong inputs
        u8ErrorState = 1;
	}

	return u8ErrorState;
}

/*------------------------------------------------------------------------------------*/

//u8 DIO_u8SetPortDirection(PORT_INDEX PORT , PIN_DIR DIR)
//{
//	/* Function internal Error Flag */
//	u8 u8ErrorState = 0;
//
//	/* Invalid Input Protection : checking if the arguments indexes are in a valid range */
//	if (  ( PORT <= MAX_PORT_INDEX )&& (( DIR  == INPUT )||( DIR == OUTPUT ))  )
//	{
//		/* Fetching the port number index */
//		switch( PORT )
//			{
//				case A:
//					if( DIR == INPUT )
//					{
//						/* The PORT is requested to be LOW */
//						TRISA = PORT_DIR_INPUT;
//					}
//					else
//					{
//						/* The pin is requested to be HIGH */
//						TRISA = PORT_DIR_OUTPUT;
//					}
//					break;
//
//				case B:
//					if( DIR == INPUT )
//					{
//						/* The PORT is requested to be LOW */
//						TRISB = PORT_DIR_INPUT;
//					}
//					else
//					{
//						/* The pin is requested to be HIGH */
//						TRISB = PORT_DIR_OUTPUT;
//					}
//					break;
//
//				case C:
//					if( DIR == INPUT )
//					{
//						/* The PORT is requested to be LOW */
//						TRISC = PORT_DIR_INPUT;
//					}
//					else
//					{
//						/* The pin is requested to be HIGH */
//						TRISC = PORT_DIR_OUTPUT;
//					}
//					break;
//
//				case D:
//					if( DIR == INPUT )
//					{
//						/* The PORT is requested to be LOW */
//						TRISD = PORT_DIR_INPUT;
//					}
//					else
//					{
//						/* The pin is requested to be HIGH */
//						TRISD = PORT_DIR_OUTPUT;
//					}
//					break;
//                    
//                case E:
//					if( DIR == INPUT )
//					{
//						/* The PORT is requested to be LOW */
//						TRISE = PORT_DIR_INPUT;
//					}
//					else
//					{
//						/* The pin is requested to be HIGH */
//						TRISE = PORT_DIR_OUTPUT;
//					}
//					break;         
//			}
//	}
//	else
//	{
//		u8ErrorState = 1;
//	}
//
//	return u8ErrorState;
//
//}
//
//u8 DIO_u8SetPortValue(PORT_INDEX PORT , PIN_LEVEL LEVEL)
//{
//	/* Function internal Error Flag */
//	u8 u8ErrorState = 0;
//
//	/* Invalid Input Protection : checking if the arguments indexes are in a valid range */
//	if (    ( PORT <= MAX_PORT_INDEX )&& (( LEVEL  == LOW )||( LEVEL == HIGH ))  )
//	{
//		/* Fetching the port number index */
//		switch( PORT )
//			{
//				case A:
//                    if(LEVEL==HIGH)
//                    {
//                        PORTA = PORT_LVL_HIGH; //Set Port to HIGH
//                    }
//                    else
//                    {
//                        PORTA = PORT_LVL_LOW; //Set Port to LOW
//                    }
//					break;
//
//				case B:
//                    if(LEVEL==HIGH)
//                    {
//                        PORTB = PORT_LVL_HIGH; //Set Port to HIGH
//                    }
//                    else
//                    {
//                        PORTB = PORT_LVL_LOW; //Set Port to LOW
//                    }
//					break;
//
//				case C:
//                    if(LEVEL==HIGH)
//                    {
//                        PORTC = PORT_LVL_HIGH; //Set Port to HIGH
//                    }
//                    else
//                    {
//                        PORTC = PORT_LVL_LOW; //Set Port to LOW
//                    }
//					break;
//
//				case D:
//                    if(LEVEL==HIGH)
//                    {
//                        PORTD = PORT_LVL_HIGH; //Set Port to HIGH
//                    }
//                    else
//                    {
//                        PORTD = PORT_LVL_LOW; //Set Port to LOW
//                    }
//					break;
//                    
//				case E:
//                    if(LEVEL==HIGH)
//                    {
//                        PORTE = PORT_LVL_HIGH; //Set Port to HIGH
//                    }
//                    else
//                    {
//                        PORTE = PORT_LVL_LOW; //Set Port to LOW
//                    }
//					break;                    
//			}
//	}
//	else
//	{
//		u8ErrorState = 1;
//	}
//
//	return u8ErrorState;
//}
//
//u8 DIO_u8GetPortValue(PORT_INDEX PORT , u8* u8Value)
//{
//	/* Function internal Error Flag */
//	u8 u8ErrorState = 0;
//
//	/* Invalid Input Protection : checking if the arguments indexes are in a valid range */
//	if (    ( PORT  <=  MAX_PORT_INDEX ) && ( NULL  !=  u8Value )    )
//	{
//		/* Fetching the port number index */
//		switch( PORT )
//			{
//				case A:
//					/* Returning the PORTA value */
//					*u8Value = PORTA;
//					break;
//
//				case B:
//					/* Returning the PORTB value */
//					*u8Value = PORTB;
//					break;
//
//				case C:
//					/* Returning the PORTC value */
//					*u8Value = PORTC;
//					break;
//
//				case D:
//					/* Returning the PORTD value */
//					*u8Value = PORTD;
//					break;
//                    
//				case E:
//					/* Returning the PORTE value */
//					*u8Value = PORTE;
//					break;                   
//			}
//	}
//	else
//	{
//		u8ErrorState = 1;
//	}
//
//	return u8ErrorState;
//}
