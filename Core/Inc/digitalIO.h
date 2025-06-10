#ifndef INC_DIGITALIO_H_
#define INC_DIGITALIO_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_gpio.h"
#include "stm32g4xx_ll_tim.h"

#include "gpio.h"
#include "timer.h"

#include "pinMaping.h"

typedef enum {
	Mode_Input,
	Mode_Output,
	Mode_PWM
} DigitalIOMode;

void DigitalIOInit();
void DigitalIOSetMode(uint8_t channel, DigitalIOMode mode);
void DigitalIOSetOutputLevel(uint8_t channel, uint8_t level);
uint8_t DigitalIOGetInputLevel(uint8_t channel);
void DigitalIOSetPWM(uint8_t channel, uint32_t frequency, uint16_t dutyCycle, uint8_t outputEn);

#ifdef __cplusplus
}
#endif

#endif /* INC_DIGITALIO_H_ */
