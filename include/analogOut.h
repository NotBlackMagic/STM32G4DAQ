#ifndef ANALOGOUT_H_
#define ANALOGOUT_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_dac.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_gpio.h"

#define ANALOG_OUT_BLOCK_A					0x01
#define ANALOG_OUT_BLOCK_B					0x02

typedef enum {
	Mode_Off,
	Mode_DC,
	Mode_Sine,
	Mode_Square,
	Mode_Ramp,
	Mode_Noise
} AnalogOutMode;

typedef struct {
	AnalogOutMode mode;
	uint16_t offset;
	uint32_t frequency;
	uint16_t amplitude;
	uint8_t dc;
} AnalogOutCHConfigStruct;

void AnalogOutConfigChannel(uint8_t anBlock, uint8_t channel, AnalogOutCHConfigStruct config);

#ifdef __cplusplus
}
#endif

#endif /* ANALOGOUT_H_ */
