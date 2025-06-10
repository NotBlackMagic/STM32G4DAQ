#ifndef ANALOGIN_H_
#define ANALOGIN_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_adc.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_gpio.h"

#include "timer.h"

#include "ada4254.h"

typedef enum {
	Mode_Off,
	Mode_Differential,
	Mode_Single
} AnalogInMode;

typedef enum {
	Sample_250k,
	Sample_125k,
	Sample_62k50,
	Sample_31k25,
	Sample_15k63,
	Sample_7k81,
	Sample_3k91,
	Sample_1k95,
	Sample_0k98,
	Sample_0k49,
	Sample_0k24,
	Sample_0k12
} AnalogInSamplerate;

typedef enum {
	Resolution_8Bit,
	Resolution_9Bit,
	Resolution_10Bit,
	Resolution_11Bit,
	Resolution_12Bit,
	Resolution_13Bit,
	Resolution_14Bit,
	Resolution_15Bit,
	Resolution_16Bit
} AnalogInResolution;

typedef enum {
	Scale_1V,
	Scale_1V25,
	Scale_1V375
} AnalogInScale;

typedef struct {
	AnalogInSamplerate rate;
	AnalogInScale scale;
} AnalogInConfigStruct;

typedef struct {
	AnalogInConfigStruct config;
	int16_t offsetCall;
} AnalogInStruct;

typedef struct {
	AnalogInMode mode;
	uint8_t division;
	AnalogInResolution resolution;
	InputGain gain;
} AnalogInCHConfigStruct;

typedef struct {
	uint8_t channel;
	AnalogInCHConfigStruct config;
	uint8_t buffer[512];
	uint16_t bufferReadIndex;
	uint16_t bufferWriteIndex;
} AnalogInCHStruct;

void AnalogInInit();
void AnalogInCalibration(uint8_t anBlock);
void AnalogInConfig(uint8_t anBlock, AnalogInConfigStruct config);
void AnalogInConfigChannel(uint8_t anBlock, uint8_t channel, AnalogInCHConfigStruct config);
void AnalogInStopAll();
uint16_t AnalogInGetData(uint8_t anBlock, uint8_t channel, uint8_t* data);
void AnalogInHandler(uint8_t anBlock);

#ifdef __cplusplus
}
#endif

#endif /* ANALOGIN_H_ */
