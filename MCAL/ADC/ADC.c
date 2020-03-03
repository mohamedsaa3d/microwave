#include "ADC.h"
#include "../INTERRUPT/interrupt.h"

volatile u16 GLOBAL_ADC_BUFFER=0; //This variable holds the ADC result

void ADC_Init(void)
{

	SET_BIT( ADCON0_REG , 0 ); /* Enable ADC */
    
//######################### ADC Pre-scaler Select  #########################
    
#if ADC_PRESCALER == P2 //ADC Clock will be F_CPU/2
        CLR_BIT( ADCON0_REG , 6 );
        CLR_BIT( ADCON0_REG , 7 );
        CLR_BIT( ADCON1_REG , 6 );
#endif
#if ADC_PRESCALER == P4 //ADC Clock will be F_CPU/4
        CLR_BIT( ADCON0_REG , 6 );
        CLR_BIT( ADCON0_REG , 7 );
        SET_BIT( ADCON1_REG , 6 );
#endif 
#if ADC_PRESCALER == P8 //ADC Clock will be F_CPU/8
        SET_BIT( ADCON0_REG , 6 );
        CLR_BIT( ADCON0_REG , 7 );
        CLR_BIT( ADCON1_REG , 6 );
#endif 
#if ADC_PRESCALER == P16 //ADC Clock will be F_CPU/16
        CLR_BIT( ADCON0_REG , 6 );
        SET_BIT( ADCON0_REG , 7 );
        SET_BIT( ADCON1_REG , 6 );
#endif 
#if ADC_PRESCALER == P32 //ADC Clock will be F_CPU/32
        CLR_BIT( ADCON0_REG , 6 );
        SET_BIT( ADCON0_REG , 7 );
        CLR_BIT( ADCON1_REG , 6 );
#endif 
#if ADC_PRESCALER == P64 //ADC Clock will be F_CPU/64
        CLR_BIT( ADCON0_REG , 6 );
        SET_BIT( ADCON0_REG , 7 );
        SET_BIT( ADCON1_REG , 6 );
#endif 
#if ADC_PRESCALER == PRC //ADC Clock derived from an RC oscillation
        SET_BIT( ADCON0_REG , 6 );
        SET_BIT( ADCON0_REG , 7 ); 
#endif          

//######################### ADC Result Adjust Selection  #########################
        
#if Res_Adjust == LEFT
        CLR_BIT( ADCON1_REG , 7 ); /* ADC Left Adjust Select  */
#endif
#if Res_Adjust == RIGHT
        SET_BIT( ADCON1_REG , 7 ); /* ADC Right Adjust Select  */
#endif
        
//######################### ADC Reference Selection  #########################
        
#if Volt_Ref == VDD
        CLR_BIT( ADCON1_REG , 4 ); /* ADC POS Reference Selection : VDD */
        CLR_BIT( ADCON1_REG , 5 ); /* ADC NEG Reference Selection : VSS */
#endif
#if Volt_Ref == EXTERNAL_REF  
        SET_BIT( ADCON1_REG , 4 ); /* ADC POS Reference Selection : REF+ */
        SET_BIT( ADCON1_REG , 5 ); /* ADC NEG Reference Selection : REF- */
#endif  
    
//######################### Setting Pins AN0 TO AN13  #########################
    
#if MAX_ADC_CHANNELS_NEEDED == 0 //ALL PINS WILL BE DIGITAL (NO ANALOG IS USED)
        SET_BIT( ADCON1_REG , 0 ); 
        SET_BIT( ADCON1_REG , 1 ); 
        SET_BIT( ADCON1_REG , 2 );
        SET_BIT( ADCON1_REG , 3 );
#endif   
#if MAX_ADC_CHANNELS_NEEDED == 1 //ONLY AN0 WILL BE ANALOG AND THE REST ARE DIGITAL
        CLR_BIT( ADCON1_REG , 0 ); 
        SET_BIT( ADCON1_REG , 1 ); 
        SET_BIT( ADCON1_REG , 2 );
        SET_BIT( ADCON1_REG , 3 );
#endif
#if MAX_ADC_CHANNELS_NEEDED == 2 //AN0 TO AN1 WILL BE ANALOG AND THE REST ARE DIGITAL
        SET_BIT( ADCON1_REG , 0 ); 
        CLR_BIT( ADCON1_REG , 1 ); 
        SET_BIT( ADCON1_REG , 2 );
        SET_BIT( ADCON1_REG , 3 );
#endif          
#if MAX_ADC_CHANNELS_NEEDED == 3 //AN0 TO AN2 WILL BE ANALOG AND THE REST ARE DIGITAL
        CLR_BIT( ADCON1_REG , 0 ); 
        CLR_BIT( ADCON1_REG , 1 ); 
        SET_BIT( ADCON1_REG , 2 );
        SET_BIT( ADCON1_REG , 3 );
#endif            
#if MAX_ADC_CHANNELS_NEEDED == 4 //AN0 TO AN3 WILL BE ANALOG AND THE REST ARE DIGITAL
        SET_BIT( ADCON1_REG , 0 ); 
        SET_BIT( ADCON1_REG , 1 ); 
        CLR_BIT( ADCON1_REG , 2 );
        SET_BIT( ADCON1_REG , 3 );
#endif            
#if MAX_ADC_CHANNELS_NEEDED == 5 //AN0 TO AN4 WILL BE ANALOG AND THE REST ARE DIGITAL
        CLR_BIT( ADCON1_REG , 0 ); 
        SET_BIT( ADCON1_REG , 1 ); 
        CLR_BIT( ADCON1_REG , 2 );
        SET_BIT( ADCON1_REG , 3 );
#endif             
#if MAX_ADC_CHANNELS_NEEDED == 6 //AN0 TO AN5 WILL BE ANALOG AND THE REST ARE DIGITAL
        SET_BIT( ADCON1_REG , 0 ); 
        CLR_BIT( ADCON1_REG , 1 ); 
        CLR_BIT( ADCON1_REG , 2 );
        SET_BIT( ADCON1_REG , 3 );
#endif          
#if MAX_ADC_CHANNELS_NEEDED == 7 //AN0 TO AN6 WILL BE ANALOG AND THE REST ARE DIGITAL
        CLR_BIT( ADCON1_REG , 0 ); 
        CLR_BIT( ADCON1_REG , 1 ); 
        CLR_BIT( ADCON1_REG , 2 );
        SET_BIT( ADCON1_REG , 3 );
#endif              
#if MAX_ADC_CHANNELS_NEEDED == 8 //AN0 TO AN7 WILL BE ANALOG AND THE REST ARE DIGITAL
        SET_BIT( ADCON1_REG , 0 ); 
        SET_BIT( ADCON1_REG , 1 ); 
        SET_BIT( ADCON1_REG , 2 );
        CLR_BIT( ADCON1_REG , 3 );
#endif           
#if MAX_ADC_CHANNELS_NEEDED == 9 //AN0 TO AN8 WILL BE ANALOG AND THE REST ARE DIGITAL
        CLR_BIT( ADCON1_REG , 0 ); 
        SET_BIT( ADCON1_REG , 1 ); 
        SET_BIT( ADCON1_REG , 2 );
        CLR_BIT( ADCON1_REG , 3 );
#endif            
#if MAX_ADC_CHANNELS_NEEDED == 10 //AN0 TO AN9 WILL BE ANALOG AND THE REST ARE DIGITAL
        SET_BIT( ADCON1_REG , 0 ); 
        CLR_BIT( ADCON1_REG , 1 ); 
        SET_BIT( ADCON1_REG , 2 );
        CLR_BIT( ADCON1_REG , 3 );
#endif           
#if MAX_ADC_CHANNELS_NEEDED == 11 //AN0 TO AN10 WILL BE ANALOG AND THE REST ARE DIGITAL
        CLR_BIT( ADCON1_REG , 0 ); 
        CLR_BIT( ADCON1_REG , 1 ); 
        SET_BIT( ADCON1_REG , 2 );
        CLR_BIT( ADCON1_REG , 3 );
#endif            
#if MAX_ADC_CHANNELS_NEEDED == 12 //AN0 TO AN11 WILL BE ANALOG AND THE REST ARE DIGITAL
        SET_BIT( ADCON1_REG , 0 ); 
        SET_BIT( ADCON1_REG , 1 ); 
        CLR_BIT( ADCON1_REG , 2 );
        CLR_BIT( ADCON1_REG , 3 );
#endif           
#if MAX_ADC_CHANNELS_NEEDED == 13 //AN0 TO AN12 WILL BE ANALOG AND THE REST ARE DIGITAL
        CLR_BIT( ADCON1_REG , 0 ); 
        SET_BIT( ADCON1_REG , 1 ); 
        CLR_BIT( ADCON1_REG , 2 );
        CLR_BIT( ADCON1_REG , 3 );
#endif           
#if MAX_ADC_CHANNELS_NEEDED == 14 //AN0 TO AN13 WILL BE ANALOG AND THE REST ARE DIGITAL
        SET_BIT( ADCON1_REG , 0 ); 
        CLR_BIT( ADCON1_REG , 1 ); 
        CLR_BIT( ADCON1_REG , 2 );
        CLR_BIT( ADCON1_REG , 3 );
#endif           
               
}

void ADC_ReadPin(CHANNEL channel,u16* value)
{
    //u8 Conversion_Running_Flag =0;
    
	switch(channel)
	{
//		case AN0:
//			CLR_BIT( ADCON0_REG , 3 );  
//			CLR_BIT( ADCON0_REG , 4 );  
//			CLR_BIT( ADCON0_REG , 5 );  
//			CLR_BIT( ADCON0_REG , 1 );  
//			break;
//            
//		case AN1:
//			SET_BIT( ADCON0_REG , 3 );  
//			CLR_BIT( ADCON0_REG , 4 );  
//			CLR_BIT( ADCON0_REG , 5 );  
//			CLR_BIT( ADCON0_REG , 1 );  
//			break;
            
		case AN2:
			CLR_BIT( ADCON0_REG , 3 );  
			SET_BIT( ADCON0_REG , 4 );  
			CLR_BIT( ADCON0_REG , 5 );  
			CLR_BIT( ADCON0_REG , 1 );  
			break;
            
//		case AN3:
//			SET_BIT( ADCON0_REG , 3 );  
//			SET_BIT( ADCON0_REG , 4 );  
//			CLR_BIT( ADCON0_REG , 5 );  
//			CLR_BIT( ADCON0_REG , 1 );  
//			break;            
//            
//		case AN4:
//			CLR_BIT( ADCON0_REG , 3 );  
//			CLR_BIT( ADCON0_REG , 4 );  
//			SET_BIT( ADCON0_REG , 5 );  
//			CLR_BIT( ADCON0_REG , 1 );  
//			break;              
// 
//		case AN5:
//			SET_BIT( ADCON0_REG , 3 );  
//			CLR_BIT( ADCON0_REG , 4 );  
//			SET_BIT( ADCON0_REG , 5 );  
//			CLR_BIT( ADCON0_REG , 1 );  
//			break;                  
//            
//		case AN6:
//			CLR_BIT( ADCON0_REG , 3 );  
//			SET_BIT( ADCON0_REG , 4 );  
//			SET_BIT( ADCON0_REG , 5 );  
//			CLR_BIT( ADCON0_REG , 1 );  
//			break;    
//            
//		case AN7:
//			SET_BIT( ADCON0_REG , 3 );  
//			SET_BIT( ADCON0_REG , 4 );  
//			SET_BIT( ADCON0_REG , 5 );  
//			CLR_BIT( ADCON0_REG , 1 );  
//			break; 
//            
//		case AN8:
//			CLR_BIT( ADCON0_REG , 3 );  
//			CLR_BIT( ADCON0_REG , 4 );  
//			CLR_BIT( ADCON0_REG , 5 );  
//			SET_BIT( ADCON0_REG , 1 );  
//			break;  
//            
//		case AN9:
//			SET_BIT( ADCON0_REG , 3 );  
//			CLR_BIT( ADCON0_REG , 4 );  
//			CLR_BIT( ADCON0_REG , 5 );  
//			SET_BIT( ADCON0_REG , 1 );  
//			break;              
//
//		case AN10:
//			CLR_BIT( ADCON0_REG , 3 );  
//			SET_BIT( ADCON0_REG , 4 );  
//			CLR_BIT( ADCON0_REG , 5 );  
//			SET_BIT( ADCON0_REG , 1 );  
//			break;  
//
//		case AN11:
//			SET_BIT( ADCON0_REG , 3 );  
//			SET_BIT( ADCON0_REG , 4 );  
//			CLR_BIT( ADCON0_REG , 5 );  
//			SET_BIT( ADCON0_REG , 1 );  
//			break;
//
//		case AN12:
//			CLR_BIT( ADCON0_REG , 3 );  
//			CLR_BIT( ADCON0_REG , 4 );  
//			SET_BIT( ADCON0_REG , 5 );  
//			SET_BIT( ADCON0_REG , 1 );  
//			break;            
//
//        case AN13:
//			SET_BIT( ADCON0_REG , 3 );  
//			CLR_BIT( ADCON0_REG , 4 );  
//			SET_BIT( ADCON0_REG , 5 );  
//			SET_BIT( ADCON0_REG , 1 );  
//			break;       
	}
    

    SET_BIT( ADCON0_REG , 2 ); /* Start Conversion */
    
    
#if ADC_MODE == POLLING	
    
	while( GET_BIT(ADCON0_REG,2) ); /* Wait till the conversion is finished */

	*value = (ADRESH_REG<<8)+(ADRESL_REG); /* Return the value */
#elif ADC_MODE == INTERRUPT
   
    *value = GLOBAL_ADC_BUFFER; /* Return the value */
#endif
    

    
}

void ADC_Read_API(void)
{
    //This API is executed when ADC interrupt occurs
    GLOBAL_ADC_BUFFER = (ADRESH_REG<<8)+(ADRESL_REG); //Return the value
    CLR_BIT(PIR1,6); //Clear the interrupt flag
}