#ifndef _ADC_H_
#define _ADC_H_

#include "../../Libraries/BIT_MATH.h"
#include "../../Libraries/STD_TYPES.h"
#include "ADC_private.h"
#include "ADC_config.h"


void ADC_Init(void);
void ADC_ReadPin(CHANNEL channel,u16* value);
void ADC_Read_API(void);


#endif /* _MCAL_ADC_ADC_H_ */
