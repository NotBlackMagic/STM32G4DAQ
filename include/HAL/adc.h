#ifndef HAL_ADC_H_
#define HAL_ADC_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_adc.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_gpio.h"

#include "analogIn.h"

void ADC1Init();
void ADC2Init();
void ADC1Start();
void ADC2Start();

#ifdef __cplusplus
}
#endif

#endif /* HAL_ADC_H_ */
