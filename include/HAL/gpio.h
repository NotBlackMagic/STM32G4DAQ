#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_exti.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_pwr.h"
#include "stm32g4xx_ll_rcc.h"

#include "pinMaping.h"

typedef enum {
	GPIO_Mode_Analog = 0,
	GPIO_Mode_Input = 1,
	GPIO_Mode_Output = 2,
	GPIO_Mode_Alternate = 3
} GPIOOutputMode;

static uint32_t gpioOutputMode[4] = {	LL_GPIO_MODE_ANALOG,
										LL_GPIO_MODE_INPUT,
										LL_GPIO_MODE_OUTPUT,
										LL_GPIO_MODE_ALTERNATE
};

static GPIO_TypeDef* gpioPorts[7] = {	GPIOA,
										GPIOB,
										GPIOC,
										GPIOD,
										GPIOE,
										GPIOF,
										GPIOG};

static uint32_t gpioPins[16] = {	LL_GPIO_PIN_0,
									LL_GPIO_PIN_1,
									LL_GPIO_PIN_2,
									LL_GPIO_PIN_3,
									LL_GPIO_PIN_4,
									LL_GPIO_PIN_5,
									LL_GPIO_PIN_6,
									LL_GPIO_PIN_7,
									LL_GPIO_PIN_8,
									LL_GPIO_PIN_9,
									LL_GPIO_PIN_10,
									LL_GPIO_PIN_11,
									LL_GPIO_PIN_12,
									LL_GPIO_PIN_13,
									LL_GPIO_PIN_14,
									LL_GPIO_PIN_15
};

void GPIOInit();
void GPIOSetPinMode(uint8_t gpio, GPIOOutputMode mode);
void GPIOWrite(uint8_t gpio, uint8_t on);
uint8_t GPIORead(uint8_t gpio);

#ifdef __cplusplus
}
#endif

#endif /* HAL_GPIO_H_ */
