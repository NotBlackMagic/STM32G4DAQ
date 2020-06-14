#ifndef HAL_SYSTEM_H_
#define HAL_SYSTEM_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_system.h"

#include "rcc.h"

typedef enum {
	VRef_Ext,
	VRef_2048,
	VRef_2500,
	VRef_2900
} SystemVRefVoltage;

uint8_t SystemVrefEnable(SystemVRefVoltage vref);

#ifdef __cplusplus
}
#endif

#endif /* HAL_SYSTEM_H_ */
