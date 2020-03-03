
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "../../Libraries/STD_TYPES.h"
#include "DIO_priv.h"

/*###########################################*/
#define MAX_PORT_INDEX 4 //Maximum No. of Ports (We have PORTS A,B,C,D,E )
#define MAX_PIN_INDEX  7 //Maximum No. of PINS  (We have PINS 0,1,2,3,4,5,6,7 )

#define PORT_DIR_INPUT  0xFF //Used to  set a port to INPUT
#define PORT_DIR_OUTPUT 0x00 //Used to  set a port to OUTPUT

#define PORT_LVL_HIGH  0xFF //Used to  set a port to HIGH
#define PORT_LVL_LOW   0x00 //Used to  set a port to LOW

/*###########################################*/


u8 DIO_u8SetPinDirection(PORT_INDEX PORT , PIN_INDEX PIN , PIN_DIR DIR);
/* Function Description :
	 * This function is used to initialize a pin to be input or output
	 * the function takes 3 arguments :
	 * 						* Port number indexed as below :
	 * 							PORT_A = 0
	 * 							PORT_B = 1
	 * 							PORT_C = 2
	 * 							PORT_D = 3
	 * 						* Pin number indexed as below :
	 * 							PIN0 = 0
	 * 							PIN1 = 1
	 * 							PIN2 = 2
	 * 							PIN3 = 3
	 * 							PIN4 = 4
	 * 							PIN5 = 5
	 * 							PIN6 = 6
	 * 							PIN7 = 7
	 * 						* Pin Direction (Input/Output) :
	 * 							PIN_INPUT  = 0
	 * 							PIN_OUTPUT = 1
	 */


u8 DIO_u8SetPinValue(PORT_INDEX PORT , PIN_INDEX PIN , PIN_LEVEL LEVEL);
/* Function Description :
	 * This function is used to set a pin to be HIGH or LOW
	 * the function takes 3 arguments :
	 * 						* Port number indexed as below :
	 * 							PORT_A = 0
	 * 							PORT_B = 1
	 * 							PORT_C = 2
	 * 							PORT_D = 3
	 * 						* Pin number indexed as below :
	 * 							PIN0 = 0
	 * 							PIN1 = 1
	 * 							PIN2 = 2
	 * 							PIN3 = 3
	 * 							PIN4 = 4
	 * 							PIN5 = 5
	 * 							PIN6 = 6
	 * 							PIN7 = 7
	 * 						* Pin Value :
	 * 							PIN_LOW  = 0
	 * 							PIN_HIGH = 1
	 */

u8 DIO_u8GetPinValue(PORT_INDEX PORT , PIN_INDEX PIN , u8* u8Value );
/* Function Description :
	 * This function is used to read a pin value
	 * the function takes 3 arguments :
	 * 						* Port number indexed as below :
	 * 							PORT_A = 0
	 * 							PORT_B = 1
	 * 							PORT_C = 2
	 * 							PORT_D = 3
	 * 						* Pin number indexed as below :
	 * 							PIN0 = 0
	 * 							PIN1 = 1
	 * 							PIN2 = 2
	 * 							PIN3 = 3
	 * 							PIN4 = 4
	 * 							PIN5 = 5
	 * 							PIN6 = 6
	 * 							PIN7 = 7
	 * 						* Address of variable to store the pin value :
	 * 							the address of the variable that will holds the pin value
	 * 							if pin is LOW return value is  0
	 * 							if pin is HIGH return value is 1
	 */

/*----------------------------------------------------------------------------------------------*/
u8 DIO_u8SetPortDirection(PORT_INDEX PORT , PIN_DIR DIR);
/* Function Description :
	 * This function is used to initialize a port to be input or output
	 * the function takes 3 arguments :
	 * 						* Port number indexed as below :
	 * 							PORT_A = 0
	 * 							PORT_B = 1
	 * 							PORT_C = 2
	 * 							PORT_D = 3
	 * 						* Port Direction (Input/Output) :
	 * 							PORT_INPUT  = 0
	 * 							PORT_OUTPUT = 1
	 */


u8 DIO_u8SetPortValue(PORT_INDEX PORT , PIN_LEVEL LEVEL);
/* Function Description :
	 * This function is used to set a port to be HIGH or LOW
	 * the function takes 3 arguments :
	 * 						* Port number indexed as below :
	 * 							PORT_A = 0
	 * 							PORT_B = 1
	 * 							PORT_C = 2
	 * 							PORT_D = 3
	 * 						* Port Value :
	 * 							PORT_LOW  = 0
	 * 							PORT_HIGH = 1
	 */

u8 DIO_u8GetPortValue(PORT_INDEX PORT , u8* u8Value);
/* Function Description :
	 * This function is used to read a port value
	 * the function takes 3 arguments :
	 * 						* Port number indexed as below :
	 * 							PORT_A = 0
	 * 							PORT_B = 1
	 * 							PORT_C = 2
	 * 							PORT_D = 3
	 * 						* Return Pin Value storing address :
	 * 							the address of the variable that will holds the pin value
	 * 							if pin is LOW return value is  0
	 * 							if pin is HIGH return value is 1
	 */


#endif /* _DIO_INTERFACE_H_ */