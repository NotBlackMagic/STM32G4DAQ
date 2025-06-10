#ifndef HAL_TIMER_H_
#define HAL_TIMER_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_tim.h"

#include "pinMaping.h"

void TIM1Init();
void TIM3Init();
void TIM4Init();
void TIM6Init();
void TIM7Init();
void TIM8Init();
void TIM15Init();

void TIM1SetFreq(uint32_t freq);
void TIM4SetFreq(uint32_t freq);
void TIM6SetFreq(uint32_t freq);
void TIM7SetFreq(uint32_t freq);
void TIM15SetFreq(uint32_t freq);

void TIM3SetARR(uint16_t arr);
void TIM8SetARR(uint16_t arr);

void TIM1SetCompare(uint8_t channel, uint16_t value);

void TIM1EnableOutput(uint8_t channel, uint8_t enable);

#ifdef __cplusplus
}
#endif

#endif /* HAL_TIMER_H_ */
