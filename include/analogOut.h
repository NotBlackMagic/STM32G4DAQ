#ifndef ANALOGOUT_H_
#define ANALOGOUT_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_dac.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_dma.h"
#include "stm32g4xx_ll_gpio.h"

#include "dac.h"
#include "timer.h"
#include "pinMaping.h"

#define ANALOG_OUT_BLOCK_A						0x01
#define ANALOG_OUT_BLOCK_B						0x02

#define ANALOG_OUT_BUFFER_SIZE					128

typedef enum {
	Mode_None,
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
	uint8_t dtc;
} AnalogOutCHConfigStruct;

typedef struct {
	uint8_t channel;
	uint32_t frequency;
	uint16_t buffer[ANALOG_OUT_BUFFER_SIZE];
	uint16_t bufferLength;
} AnalogOutCHStruct;

void AnalogOutInit();
void AnalogOutConfigChannel(uint8_t anBlock, uint8_t channel, AnalogOutCHStruct config);
void AnalogOutHandler(uint8_t anBlock);

#ifdef __cplusplus
}
#endif

#endif /* ANALOGOUT_H_ */
