#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_adc.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_tim.h"

#include "analogOut.h"
#include "pinMaping.h"

void TIM3Init();
void TIM4Init();
void TIM6Init();
void TIM7Init();
void TIM8Init();
void TIM15Init();

void TIM4SetFreq(uint32_t freq);
void TIM6SetFreq(uint32_t freq);
void TIM7SetFreq(uint32_t freq);
void TIM15SetFreq(uint32_t freq);

void TIM3SetARR(uint16_t arr);
void TIM8SetARR(uint16_t arr);

#ifdef __cplusplus
}
#endif

#endif /* HAL_TIMER_H_ */
