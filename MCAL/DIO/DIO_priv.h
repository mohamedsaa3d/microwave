#ifndef _DIO_PRIVATE_H_
#define _DIO_PRIVATE_H_

/*###########################################*/
/* DIO Registers Addressing Definitions */
#define TRISA *((volatile u8*)(0x085))
#define TRISB *((volatile u8*)(0x086))
#define TRISC *((volatile u8*)(0x087))
#define TRISD *((volatile u8*)(0x088))
#define TRISE *((volatile u8*)(0x089))

#define PORTA *((volatile u8*)(0x005))
#define PORTB *((volatile u8*)(0x006))
#define PORTC *((volatile u8*)(0x007))
#define PORTD *((volatile u8*)(0x008))
#define PORTE *((volatile u8*)(0x009))


#define OPTION_REG *((volatile u8*)(0x181))




typedef enum PORTINDEX
{
    A,B,C,D,E
}PORT_INDEX;

typedef enum PININDEX
{
    PIN0, PIN1, PIN2, PIN3, PIN4, PIN5, PIN6, PIN7
}PIN_INDEX;

typedef enum PINDIR
{
    OUTPUT, INPUT
}PIN_DIR;

typedef enum PINLVL
{
    LOW, HIGH
}PIN_LEVEL;


typedef enum ONOFFSTATE
{
    OFF, ON
}DIG_STATE;


#endif /* _DIO_PRIVATE_H_ */
