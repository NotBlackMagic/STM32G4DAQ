#ifndef HAL_RCC_H_
#define HAL_RCC_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_cortex.h"
#include "stm32g4xx_ll_pwr.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_system.h"

void SystemClockInit();
void SystemTickInit();
void Delay(uint32_t ms);
uint32_t GetSysTick();
void GetSysTickAsTime(uint8_t* hour, uint8_t* min, uint8_t* sec, uint16_t* ms);

#ifdef __cplusplus
}
#endif

#endif /* HAL_RCC_H_ */
