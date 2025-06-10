#ifndef DSPBENCHMARK_H_
#define DSPBENCHMARK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32g4xx.h"
#include "timer.h"

#include "stdlib.h"

#include "arm_math.h"

#define ARRAY_SIZE									1024

void DSPBenchmark();

//IIR Filter Test
uint32_t DSPBenchmarkIIRQ15(uint16_t blockLen, uint8_t cycles);
uint32_t DSPBenchmarkIIRQ31(uint16_t blockLen, uint8_t cycles);
uint32_t DSPBenchmarkIIRF32(uint16_t blockLen, uint8_t cycles);

//FIR Filter Test
uint32_t DSPBenchmarkFIRQ15(uint16_t blockLen, uint8_t cycles);
uint32_t DSPBenchmarkFIRQ31(uint16_t blockLen, uint8_t cycles);
uint32_t DSPBenchmarkFIRF32(uint16_t blockLen, uint8_t cycles);

#ifdef __cplusplus
}
#endif

#endif /* DSPBENCHMARK_H_ */
