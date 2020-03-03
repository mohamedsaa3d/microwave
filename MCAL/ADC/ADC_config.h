
#ifndef _ADC_CONFIG_H_
#define _ADC_CONFIG_H_

#define ADC_MODE  INTERRUPT
// Select the ADC Result fetch mode ( POLLING / INTERRUPT )
        
#define MAX_ADC_CHANNELS_NEEDED  3 
//Select How many ADC channels will be used (Controls the pins AN0:AN13)
//   0  : Then AN0 TO AN13 will be Digital
//   1  : Then AN0 be Analog , the rest will be digital
//   2  : Then AN0 TO AN1 be Analog , the rest will be digital
//   3  : Then AN0 TO AN2 be Analog , the rest will be digital
//   4  : Then AN0 TO AN3 be Analog , the rest will be digital
//   5  : Then AN0 TO AN4 be Analog , the rest will be digital
//   6  : Then AN0 TO AN5 be Analog , the rest will be digital
//   7  : Then AN0 TO AN6 be Analog , the rest will be digital
//   8  : Then AN0 TO AN7 be Analog , the rest will be digital
//   9  : Then AN0 TO AN8 be Analog , the rest will be digital
//   10 : Then AN0 TO AN9 be Analog , the rest will be digital
//   11 : Then AN0 TO AN10 be Analog , the rest will be digital
//   12 : Then AN0 TO AN11 be Analog , the rest will be digital
//   13 : Then AN0 TO AN12 be Analog , the rest will be digital
//   14 : Then AN0 TO AN13 be Analog


#define ADC_PRESCALER  PRC 
//Select the ADC Conversion Clock (The Higher Prescaler, the Lower ADC Frequency)
//   P2  : ADC Clock will be F_CPU/2
//   P4  : ADC Clock will be F_CPU/4
//   P8  : ADC Clock will be F_CPU/8
//   P16 : ADC Clock will be F_CPU/16
//   P32 : ADC Clock will be F_CPU/32
//   P64 : ADC Clock will be F_CPU/64
//   PRC : ADC Clock derived from an RC oscillation

#define Res_Adjust LEFT
//ADC Result Adjust Selection
//   LEFT  : ADC Left Adjust Select 
//   RIGHT : ADC Right Adjust Select 

#define Volt_Ref VDD
//ADC Reference Selection
//   VDD          : >> ADC POS Reference Selection <<VDD>>
//                  >> ADC NEG Reference Selection <<VSS>>
//
//   EXTERNAL_REF : >> ADC POS Reference Selection <<REF+>>
//                  >> ADC NEG Reference Selection <<REF->>




#endif /* _MCAL_ADC_ADC_CONFIG_H_ */
