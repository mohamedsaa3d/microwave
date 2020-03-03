#include "PICGenious_int.h"



//PinsConfiguration
void PICGenios_INIT(void)
{
    ADC_Init();
    Keypad_Initialization();
    LCD_Initialization();
    
    DIO_u8SetPinDirection(START_PORT  , START_PIN  , INPUT);
    DIO_u8SetPinDirection(CANCEL_PORT , CANCEL_PIN , INPUT);
    DIO_u8SetPinDirection(WEIGHT_PORT , WEIGHT_PIN , INPUT);
    DIO_u8SetPinDirection(DOOR_PORT   , DOOR_PIN   , INPUT);
    DIO_u8SetPinDirection(BUZZER_PORT , BUZZER_PIN , OUTPUT);
    DIO_u8SetPinDirection(MOTOR_PORT  , MOTOR_PIN  , OUTPUT);
    DIO_u8SetPinDirection(LED_PORT    , LED_PIN    , OUTPUT);
    DIO_u8SetPinDirection(HEATER_PORT , HEATER_PIN , OUTPUT);
    
    PICGEN_BUZZER(OFF);
    PICGEN_LED(OFF);
    Interrupt_Initialization(); //Global Interrupt Still Disabled (Needs to be enabled)
}


//----------------------------------------------------------------------

void PICGEN_BUZZER(DIG_STATE STATE)
{
    if(STATE == ON)
    {
        DIO_u8SetPinValue(BUZZER_PORT , BUZZER_PIN , LOW);
    }
    else
    {
        DIO_u8SetPinValue(BUZZER_PORT , BUZZER_PIN , HIGH);
    }
}

//----------------------------------------------------------------------

void PICGEN_MOTOR(DIG_STATE STATE)
{
    if(STATE == ON)
    {
        //DIO_u8SetPinValue(MOTOR_PORT , MOTOR_PIN , HIGH);
        TOGGLE_BIT(PORTC,MOTOR_PIN);
    }
    else
    {
        DIO_u8SetPinValue(MOTOR_PORT , MOTOR_PIN , LOW);
    }
}

//----------------------------------------------------------------------

void PICGEN_LED(DIG_STATE STATE)
{
    if(STATE == ON)
    {
        DIO_u8SetPinValue(LED_PORT , LED_PIN , HIGH);
    }
    else
    {
        DIO_u8SetPinValue(LED_PORT , LED_PIN , LOW);
    }
}

//----------------------------------------------------------------------

void PICGEN_HEATER(DIG_STATE STATE)
{
    if(STATE == ON)
    {
        DIO_u8SetPinValue(HEATER_PORT , HEATER_PIN , HIGH);
    }
    else
    {
        DIO_u8SetPinValue(HEATER_PORT , HEATER_PIN , LOW);
    }
}

