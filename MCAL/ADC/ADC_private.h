
#ifndef _ADC_PRIVATE_H_
#define _ADC_PRIVATE_H_




#define ADRESH_REG *((volatile u8*)(0x01E))
#define ADRESL_REG *((volatile u8*)(0x09E))


#define ADCON0_REG *((volatile u8*)(0x01F))
#define ADCON1_REG *((volatile u8*)(0x09F))
#define ADCON2_REG *((volatile u8*)(0x09B))

#define ADC_RESOLUTION 1024

typedef enum ADCCHANNEL
{
    NONE,AN0,AN1,AN2,AN3,AN4,AN5,AN6,AN7,AN8,AN9,AN10,AN11,AN12,AN13
}CHANNEL;

//typedef enum PRESC
//{
//    P2,P4,P8,P16,P32,P64,PRC
//}PRESCALER;

//typedef enum RESULTADJUST
//{
//    LEFT,RIGHT
//}RADJUST;

//typedef enum VREFERENCE
//{
//    EXTERNALV,VDD
//}VREF;





#endif /* _MCAL_ADC_ADC_PRIVATE_H_ */
