#ifndef HAL_DAC_H_
#define HAL_DAC_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_dac.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_gpio.h"

void DAC1Init();
void DAC4Init();
void DAC1Write(uint8_t channel, uint16_t value);
void DAC4Write(uint8_t channel, uint16_t value);

#ifdef __cplusplus
}
#endif

#endif /* HAL_DAC_H_ */
