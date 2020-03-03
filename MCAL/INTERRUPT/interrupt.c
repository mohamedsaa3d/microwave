#include "interrupt.h"
#include "../../HAL/LCD/LCD_interface.h"

/* GLOBAL Pointers to the callback functions (Will be called inside ISRs) */
void  (*ISR_INT0_FUNC_PTR)(void)       = NULL;
void  (*ISR_TIMER0_FUNC_PTR)(void)     = NULL;
void  (*ISR_TIMER1_FUNC_PTR)(void)     = NULL;
void  (*ISR_ADC_FUNC_PTR)(void)        = NULL;


void Interrupt_Initialization(void)
{    
    Interrupt_Select();
            
#if INT0_EN==ENABLED
    Interrupt_INT0_Options();
#endif
#if TIMER0_EN==ENABLED    
    Interrupt_T0_Options();
#endif
#if TIMER1_EN==ENABLED   
    Interrupt_T1_Options();
#endif
    //--------------------------------------------------------------------
    //NOTE : Global Interrupt must be Turned ON used the corresponding API
    //Interrupt_GlobalEnable(GLOBAL_IEN);
}

void Interrupt_GlobalEnable(DIG_STATE GIE)
{
    //------------------------------------------------------------------
    // Enable/Disable the Global Interrupt
    //------------------------------------------------------------------
    if(GIE==ON) 
        SET_BIT(INTCON,7); //Enables all unmasked interrupts
    else
    {
        CLR_BIT(INTCON,7); //Disables all interrupts
    }
}


void Interrupt_Select(void)
{
    //-- ----------------------------------------------------------------
    //Enable/Disable the TIMER0 Overflow Interrupt
    //------------------------------------------------------------------
#if TIMER0_EN == ENABLED
    SET_BIT(INTCON,5); //Enable TIMER0 interrupt
 #elif TIMER0_EN == DISABLED   
    CLR_BIT(INTCON,5); //Disable TIMER0 interrupt
#endif
    
    
    //------------------------------------------------------------------
    //Enable/Disable the External Interrupt on (RB0/INT0) PIN
    //------------------------------------------------------------------
#if INT0_EN == ENABLED
    SET_BIT(INTCON,4); //Enable External interrupt on pin RB0/INT
#elif TIMER0_EN == DISABLED 
    CLR_BIT(INTCON,4); //Disable External interrupt on pin RB0/INT
#endif
    
    
    //------------------------------------------------------------------
    //Enable/Disable the Peripherals Interrupt (TIMER1 / ADC)
    //------------------------------------------------------------------
#if TIMER1_EN==ENABLED || ADC_INT_EN==ENABLED
    //Enables Peripherals interrupts
    SET_BIT(INTCON,6); //First we must set PEIE bit
#else
    CLR_BIT(INTCON,6); //Clear PEIE if we don't need peripherals interrupt
#endif       
    
    
    //------------------------------------------------------------------
    //Enable/Disable the TIMER1 Overflow Interrupt
    //------------------------------------------------------------------
#if TIMER1_EN == ENABLED
    SET_BIT(PIE1,0); //Enable TIMER1 interrupt
#elif TIMER1_EN == DISABLED
    CLR_BIT(PIE1,0); //Disable TIMER1 interrupt
#endif
    
    
    //------------------------------------------------------------------
    //Enable/Disable the ADC Conversion Interrupt
    //------------------------------------------------------------------    
#if ADC_INT_EN == ENABLED
    SET_BIT(PIE1,6); //Enable ADC interrupt
#elif ADC_INT_EN == DISABLED
    CLR_BIT(PIE1,6); //Disable ADC interrupt
#endif
               
}

void Interrupt_INT0_Options(void)
{
    //------------------------------------------------------------------
    //Selecting Falling/Rising Edge for the External Interrupt on (RB0/INT0) PIN
    //------------------------------------------------------------------
#if INT0_SENSE == FALLING
    CLR_BIT(OPTION_REG,6); //INT0 interrupt occurs at Falling Edge 
#elif INT0_SENSE == RISING
    SET_BIT(OPTION_REG,6); //INT0 interrupt occurs at Rising Edge 
#endif
}

void Interrupt_T0_Options(void)
{
    //------------------------------------------------------------------
    //Selecting TIMER0 increment on Rising/Falling Clock edge
    //------------------------------------------------------------------
#if TIMER0_SENSE == RISING   
    CLR_BIT(OPTION_REG,4);//Increment on LOW-to-HIGH transition on RA4/T0CKI pin
#elif TIMER0_SENSE == FALLING   
    SET_BIT(OPTION_REG,4);//Increment on HIGH-to-LOW transition on RA4/T0CKI pin
#endif        
    
    //------------------------------------------------------------------
    //Selecting Clock Source for the Timer 0 
    //------------------------------------------------------------------
#if TIMER0_CS == INTERNAL     
    CLR_BIT(OPTION_REG,5);//TIMER0 Clock is an Internal instruction cycle clock (F_OSC/4)
#elif TIMER0_CS == EXTERNAL     
    SET_BIT(OPTION_REG,5);//TIMER0 Clock is a Transition on T0CKI pin 
#endif
  
    //------------------------------------------------------------------
    //Selecting TIMER0 Clock Prescaler
    //------------------------------------------------------------------
#if TIMER0_PS == TPS2
    CLR_BIT(OPTION_REG,0);
    CLR_BIT(OPTION_REG,1);
    CLR_BIT(OPTION_REG,2);
#elif TIMER0_PS == TPS4
    SET_BIT(OPTION_REG,0);
    CLR_BIT(OPTION_REG,1);
    CLR_BIT(OPTION_REG,2);
#elif TIMER0_PS == TPS8
    CLR_BIT(OPTION_REG,0);
    SET_BIT(OPTION_REG,1);
    CLR_BIT(OPTION_REG,2);
#elif TIMER0_PS == TPS16
    SET_BIT(OPTION_REG,0);
    SET_BIT(OPTION_REG,1);
    CLR_BIT(OPTION_REG,2);
#elif TIMER0_PS == TPS32
    CLR_BIT(OPTION_REG,0);
    CLR_BIT(OPTION_REG,1);
    SET_BIT(OPTION_REG,2);
#elif TIMER0_PS == TPS64
    SET_BIT(OPTION_REG,0);
    CLR_BIT(OPTION_REG,1);
    SET_BIT(OPTION_REG,2);
#elif TIMER0_PS == TPS128
    CLR_BIT(OPTION_REG,0);
    SET_BIT(OPTION_REG,1);
    SET_BIT(OPTION_REG,2);
#elif TIMER0_PS == TPS256
    SET_BIT(OPTION_REG,0);
    SET_BIT(OPTION_REG,1);
    SET_BIT(OPTION_REG,2);
#endif
 
}


void Interrupt_T1_Options(void)
{
    SET_BIT(T1CON,0); //Timer1 is ON (Powered UP)
    //------------------------------------------------------------------
    //Selecting Clock Source for the Timer 0 
    //------------------------------------------------------------------
#if TIMER1_CS == INTERNAL
    CLR_BIT(T1CON,1); //TIMER0 Clock is an Internal instruction cycle clock (F_OSC/4)
#elif TIMER1_CS == EXTERNAL
    SET_BIT(T1CON,1); //TIMER0 Clock is a Transition on T0CKI pin (RISING EDGE)
#endif
    //------------------------------------------------------------------
    //Selecting TIMER1 Clock Prescaler (NOTE: the i/p clock is F_OSC/4)
    //------------------------------------------------------------------
#if TIMER1_PS == TPS1
    CLR_BIT(T1CON,4);
    CLR_BIT(T1CON,5);
#elif TIMER1_PS == TPS2
    SET_BIT(T1CON,4);
    CLR_BIT(T1CON,5);
#elif TIMER1_PS == TPS4
    CLR_BIT(T1CON,4);
    SET_BIT(T1CON,5);
#elif TIMER1_PS == TPS8
    SET_BIT(T1CON,4);
    SET_BIT(T1CON,5);
#endif
}


void Interrupt_INT0ISR(void)
{
    //Executed when INT0 Interrupt Flag (INT0IF) is set
    if( GET_BIT(INTCON,1) )
    {
        if( ISR_INT0_FUNC_PTR != NULL )
        {
            // Call the desired function if it has been assigned to the ISR
            ISR_INT0_FUNC_PTR();
        }
        else
        {
            /* Nothing to do*/
        }
        //Flag bit INT0IF must be cleared in software in the ISR before re-enabling this interrupt
        CLR_BIT(INTCON,1); 
    }
}

void Interrupt_T0ISR(void)
{
    //Executed when Timer0 Interrupt Flag (TMR0IF) is set
    if( GET_BIT(INTCON,2) )
    {
        if( ISR_TIMER0_FUNC_PTR != NULL )
        {
            // Call the desired function if it has been assigned to the ISR
            ISR_TIMER0_FUNC_PTR();
        }
        
        //Flag bit TMR0IF must be cleared in software in the ISR before re-enabling this interrupt
        CLR_BIT(INTCON,2);
    }
}

void Interrupt_T1ISR(void)
{
    //Executed when Timer0 Interrupt Flag (TMR0IF) is set
    if( GET_BIT(PIR1,0) )
    {
        if( ISR_TIMER1_FUNC_PTR != NULL )
        {
            //Call the desired function if it has been assigned to the ISR
            ISR_TIMER1_FUNC_PTR();
        }

        //Flag bit TMR1IF must be cleared in software in the ISR before re-enabling this interrupt
        CLR_BIT(PIR1,0);
    }
}



void Interrupt_ADCISR(void)
{
    //Executed when ADC Interrupt Flag (ADIF) is set
    if( GET_BIT(PIR1,6) )
    {
        if( ISR_ADC_FUNC_PTR != NULL )
        {
            //Call the desired function if it has been assigned to the ISR
            ISR_ADC_FUNC_PTR();
        }

        //Flag bit ADIF must be cleared in software in the ISR before re-enabling this interrupt
        CLR_BIT(PIR1,6);
    }
}


void __interrupt() ISR(void)
{
    //This API is executed once an interrupt occurs
#if INT0_EN == ENABLED
    Interrupt_INT0ISR(); //Priority (1)
#endif
#if TIMER0_EN == ENABLED
    Interrupt_T0ISR();   //Priority (2)
#endif
#if TIMER1_EN == ENABLED
    Interrupt_T1ISR();   //Priority (3)
#endif
#if ADC_INT_EN == ENABLED
    Interrupt_ADCISR();  //Priority (4)
#endif

}

void ISR_CALLBACK( ISR_LIST ISR_ID , void(*functionPTR)(void)  )
{
    //This API performs callback operation 
    //which means (receiving a function from a higher layer)
	switch (ISR_ID)
	{
		case INT0:
			ISR_INT0_FUNC_PTR = functionPTR;
			break;
		case TIMER0:
			ISR_TIMER0_FUNC_PTR = functionPTR;
			break;
        case TIMER1:
			ISR_TIMER1_FUNC_PTR = functionPTR;
			break;
        case ADC:
			ISR_ADC_FUNC_PTR = functionPTR;
			break;
	}

}

