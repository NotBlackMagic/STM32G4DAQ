#include "dspBenchmark.h"

uint32_t DSPBenchmarkIIRQ15(uint16_t blockLen, uint8_t cycles) {
	uint32_t q15Time = 0;

	//Q15 IIR Filter
	int16_t irrStateQ15[8];
	int16_t iirCoeffQ15[12] = {	1262, 0, 2523, 1262, 17187, -4850,		// b0, 0, b1, b2, a1, a2
								1032, 0, 2048, 1032, 21643, -10371 };	// b0, 0, b1, b2, a1, a2
	arm_biquad_casd_df1_inst_q15 armIIRInstanceQ15;
	arm_biquad_cascade_df1_init_q15(&armIIRInstanceQ15, 2, iirCoeffQ15, irrStateQ15, 1);

	int16_t iirTestSampRawQ15[ARRAY_SIZE];
	int16_t iirTestSampFiltQ15[ARRAY_SIZE];

	uint16_t i;
	for(i = 0; i < ARRAY_SIZE; i++) {
		int value = rand();
		iirTestSampRawQ15[i] = (value >> 16);
	}

	uint8_t cnt;
	for(cnt = 0; cnt < cycles; cnt++) {
		TIM2Start();
		for(i = 0; i < ARRAY_SIZE; i+= blockLen) {
			arm_biquad_cascade_df1_fast_q15(&armIIRInstanceQ15, &iirTestSampRawQ15[i], &iirTestSampFiltQ15[i], blockLen);
//			arm_biquad_cascade_df1_q15(&armIIRInstanceQ15, &iirTestSampRawQ15[i], &iirTestSampFiltQ15[i], blockLen);
		}
		q15Time += TIM2Stop();
	}

	return (q15Time / cycles);
}

uint32_t DSPBenchmarkIIRQ31(uint16_t blockLen, uint8_t cycles) {
	uint32_t q31Time = 0;

	//Q31 IIR Filter
	int32_t irrStateQ31[8];
	int32_t iirCoeffQ31[10] = {	82678120, 165356241, 82678120, 1126355173, -317827580,		// b0, b1, b2, a1, a2
								67645735, 134217728, 67645735, 1418412950, -679678575 };	// b0, b1, b2, a1, a2
	arm_biquad_casd_df1_inst_q31 armIIRInstanceQ31;
	arm_biquad_cascade_df1_init_q31(&armIIRInstanceQ31, 2, iirCoeffQ31, irrStateQ31, 1);

	int32_t iirTestSampRawQ31[ARRAY_SIZE];
	int32_t iirTestSampFiltQ31[ARRAY_SIZE];

	uint16_t i;
	for(i = 0; i < ARRAY_SIZE; i++) {
		int value = rand();
		iirTestSampRawQ31[i] = value;
	}

	uint8_t cnt;
	for(cnt = 0; cnt < cycles; cnt++) {
		TIM2Start();
		for(i = 0; i < ARRAY_SIZE; i+= blockLen) {
			arm_biquad_cascade_df1_fast_q31(&armIIRInstanceQ31, &iirTestSampRawQ31[i], &iirTestSampFiltQ31[i], blockLen);
//			arm_biquad_cascade_df1_q31(&armIIRInstanceQ31, &iirTestSampRawQ31[i], &iirTestSampFiltQ31[i], blockLen);
		}
		q31Time += TIM2Stop();
	}

	return (q31Time / cycles);
}

uint32_t DSPBenchmarkIIRF32(uint16_t blockLen, uint8_t cycles) {
	uint32_t f32Time = 0;

	//Float IIR Filter
	float irrStateF32[8];
	float iirCoeffF32[10] = {	0.077f, 0.154f, 0.077f, 1.049f, -0.296f,	// b0, b1, b2, a1, a2
								0.063f, 0.125f, 0.063f, 1.321f, -0.633f };	// b0, b1, b2, a1, a2
	arm_biquad_casd_df1_inst_f32 armIIRInstanceF32;
	arm_biquad_cascade_df1_init_f32(&armIIRInstanceF32, 2, iirCoeffF32, irrStateF32);

	float iirTestSampRawF32[ARRAY_SIZE];
	float iirTestSampFiltF32[ARRAY_SIZE];

	uint16_t i;
	for(i = 0; i < ARRAY_SIZE; i++) {
		int value = rand();
		iirTestSampRawF32[i] = (float)value / RAND_MAX;
	}

	uint8_t cnt;
	for(cnt = 0; cnt < cycles; cnt++) {
		TIM2Start();
		for(i = 0; i < ARRAY_SIZE; i+= blockLen) {
			arm_biquad_cascade_df1_f32(&armIIRInstanceF32, &iirTestSampRawF32[i], &iirTestSampFiltF32[i], blockLen);
		}
		f32Time += TIM2Stop();
	}

	return (f32Time / cycles);
}

uint32_t DSPBenchmarkFIRQ15(uint16_t blockLen, uint8_t cycles) {
	uint32_t q15Time = 0;

	//Q15 FIR Filter
	int16_t firStateQ15[14 + blockLen];
	int16_t firCoeffQ15[14] = {	238, -1405, -2523, -331, 2361, 6841, 9722,
								9722, 6841, 2361, -331, -2523, -1405, 238 };	// b[tabs-1], b[tabs-2], ..., b[1], b[0]
	arm_fir_instance_q15 armFIRInstanceQ15;
	arm_fir_init_q15(&armFIRInstanceQ15, 14, firCoeffQ15, firStateQ15, blockLen);

	int16_t firTestSampRawQ15[ARRAY_SIZE];
	int16_t firTestSampFiltQ15[ARRAY_SIZE];

	uint16_t i;
	for(i = 0; i < ARRAY_SIZE; i++) {
		int value = rand();
		firTestSampRawQ15[i] = (value >> 16);
	}

	uint8_t cnt;
	for(cnt = 0; cnt < cycles; cnt++) {
		TIM2Start();
		for(i = 0; i < ARRAY_SIZE; i+= blockLen) {
			arm_fir_fast_q15(&armFIRInstanceQ15, &firTestSampRawQ15[i], &firTestSampFiltQ15[i], blockLen);
//			arm_fir_q15(&armFIRInstanceQ15, &firTestSampRawQ15[i], &firTestSampFiltQ15[i], blockLen);
		}
		q15Time += TIM2Stop();
	}

	return (q15Time / cycles);
}

uint32_t DSPBenchmarkFIRQ31(uint16_t blockLen, uint8_t cycles) {
	uint32_t q31Time = 0;

	//Q31 FIR Filter
	int32_t firStateQ31[14 + blockLen - 1];
	int32_t firCoeffQ31[14] = {	15617145, -91668754, -165319540, -21663557, 154717993, 448342380, 637157174,
								637157174, 448342380, 154717993, -21663557, -165319540, -91668754, 15617145 };	// b[tabs-1], b[tabs-2], ..., b[1], b[0]
 	arm_fir_instance_q31 armFIRInstanceQ31;
 	arm_fir_init_q31(&armFIRInstanceQ31, 14, firCoeffQ31, firStateQ31, blockLen);

	int32_t firTestSampRawQ31[ARRAY_SIZE];
	int32_t firTestSampFiltQ31[ARRAY_SIZE];

	uint16_t i;
	for(i = 0; i < ARRAY_SIZE; i++) {
		int value = rand();
		firTestSampRawQ31[i] = value;
	}

	uint8_t cnt;
	for(cnt = 0; cnt < cycles; cnt++) {
		TIM2Start();
		for(i = 0; i < ARRAY_SIZE; i+= blockLen) {
			arm_fir_fast_q31(&armFIRInstanceQ31, &firTestSampRawQ31[i], &firTestSampFiltQ31[i], blockLen);
//			arm_fir_q31(&armFIRInstanceQ31, &firTestSampRawQ31[i], &firTestSampFiltQ31[i], blockLen);
		}
		q31Time += TIM2Stop();
	}

	return (q31Time / cycles);
}

uint32_t DSPBenchmarkFIRF32(uint16_t blockLen, uint8_t cycles) {
	uint32_t f32Time = 0;

	//Float FIR Filter
	float firStateF32[14 + blockLen - 1];
	float firCoeffF32[14] = { 	0.0072723547, -0.042865904, -0.076982910, -0.010087880, 0.072046180, 0.20877569, 0.29669943,
								0.29669943, 0.20877569, 0.072046180, -0.010087880, -0.076982910, -0.042865904, 0.0072723547 };	// b[tabs-1], b[tabs-2], ..., b[1], b[0]
	arm_fir_instance_f32 armFIRInstanceF32;
	arm_fir_init_f32(&armFIRInstanceF32, 14, firCoeffF32, firStateF32, blockLen);

	float firTestSampRawF32[ARRAY_SIZE];
	float firTestSampFiltF32[ARRAY_SIZE];

	uint16_t i;
	for(i = 0; i < ARRAY_SIZE; i++) {
		int value = rand();
		firTestSampRawF32[i] = (float)value / RAND_MAX;
	}

	uint8_t cnt;
	for(cnt = 0; cnt < cycles; cnt++) {
		TIM2Start();
		for(i = 0; i < ARRAY_SIZE; i+= blockLen) {
			arm_fir_f32(&armFIRInstanceF32, &firTestSampRawF32[i], &firTestSampFiltF32[i], blockLen);
		}
		f32Time += TIM2Stop();
	}

	return (f32Time / cycles);
}

void DSPBenchmark() {
	TIM2Init();

	volatile uint32_t benchQ15 = 0;
	volatile uint32_t benchQ31 = 0;
	volatile uint32_t benchF32 = 0;

	//Test 1: Block Length = 1, Cycles = 10
	benchQ15 = DSPBenchmarkIIRQ15(1, 10);
	benchQ31 = DSPBenchmarkIIRQ31(1, 10);
	benchF32 = DSPBenchmarkIIRF32(1, 10);

	//Test 2: Block Length = 4, Cycles = 10
	benchQ15 = DSPBenchmarkIIRQ15(4, 10);
	benchQ31 = DSPBenchmarkIIRQ31(4, 10);
	benchF32 = DSPBenchmarkIIRF32(4, 10);

	//Test 3: Block Length = 16, Cycles = 10
	benchQ15 = DSPBenchmarkIIRQ15(16, 10);
	benchQ31 = DSPBenchmarkIIRQ31(16, 10);
	benchF32 = DSPBenchmarkIIRF32(16, 10);

	//Test 4: Block Length = 128, Cycles = 10
	benchQ15 = DSPBenchmarkIIRQ15(128, 10);
	benchQ31 = DSPBenchmarkIIRQ31(128, 10);
	benchF32 = DSPBenchmarkIIRF32(128, 10);
}
