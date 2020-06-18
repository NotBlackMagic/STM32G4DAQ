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

void TIM3Init();

#ifdef __cplusplus
}
#endif

#endif /* HAL_TIMER_H_ */
