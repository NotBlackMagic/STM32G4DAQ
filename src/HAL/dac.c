#include "dac.h"

/**
  * @brief	This function initializes the DAC1 and respective GPIOs
  * @param	None
  * @return	None
  */
void DAC1Init() {
	//Enable bus clocks
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC1);

	//Configure Output Channels
	//DAC Channel 1
	LL_DAC_SetSignedFormat(DAC1, LL_DAC_CHANNEL_1, LL_DAC_SIGNED_FORMAT_DISABLE);
	LL_DAC_SetTriggerSource(DAC1, LL_DAC_CHANNEL_1, LL_DAC_TRIG_EXT_TIM6_TRGO);
	LL_DAC_SetWaveAutoGeneration(DAC1, LL_DAC_CHANNEL_1, LL_DAC_WAVE_AUTO_GENERATION_NONE);
	LL_DAC_SetOutputBuffer(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_BUFFER_ENABLE);
	LL_DAC_SetOutputConnection(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_CONNECT_GPIO);
	LL_DAC_SetOutputMode(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_MODE_NORMAL);
	LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_1);
	LL_DAC_DisableDMADoubleDataMode(DAC1, LL_DAC_CHANNEL_1);
	LL_DAC_EnableDMAReq(DAC1, LL_DAC_CHANNEL_1);
	//DAC Channel 2
	LL_DAC_SetSignedFormat(DAC1, LL_DAC_CHANNEL_2, LL_DAC_SIGNED_FORMAT_DISABLE);
	LL_DAC_SetTriggerSource(DAC1, LL_DAC_CHANNEL_2, LL_DAC_TRIG_EXT_TIM6_TRGO);
	LL_DAC_SetWaveAutoGeneration(DAC1, LL_DAC_CHANNEL_2, LL_DAC_WAVE_AUTO_GENERATION_NONE);
	LL_DAC_SetOutputBuffer(DAC1, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_BUFFER_ENABLE);
	LL_DAC_SetOutputConnection(DAC1, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_CONNECT_GPIO);
	LL_DAC_SetOutputMode(DAC1, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_MODE_NORMAL);
	LL_DAC_EnableTrigger(DAC1, LL_DAC_CHANNEL_2);
	LL_DAC_DisableDMADoubleDataMode(DAC1, LL_DAC_CHANNEL_2);
	LL_DAC_EnableDMAReq(DAC1, LL_DAC_CHANNEL_2);

	//Configure Interrupts
//	NVIC_SetPriority(TIM6_DAC_IRQn, 0);
//	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	//Enable DAC
	LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_1);
	LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_2);
}

/**
  * @brief	This function initializes the DAC4 and respective connection to internal OpAmps
  * @param	None
  * @return	None
  */
void DAC4Init() {
	//Enable bus clocks
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_DAC4);

	//Configure Output Channels
	//DAC Channel 1
	LL_DAC_SetSignedFormat(DAC4, LL_DAC_CHANNEL_1, LL_DAC_SIGNED_FORMAT_DISABLE);
	LL_DAC_SetTriggerSource(DAC4, LL_DAC_CHANNEL_1, LL_DAC_TRIG_EXT_TIM7_TRGO);
	LL_DAC_SetWaveAutoGeneration(DAC4, LL_DAC_CHANNEL_1, LL_DAC_WAVE_AUTO_GENERATION_NONE);
	LL_DAC_SetOutputBuffer(DAC4, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_BUFFER_DISABLE);
	LL_DAC_SetOutputConnection(DAC4, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_CONNECT_INTERNAL);
	LL_DAC_SetOutputMode(DAC4, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_MODE_NORMAL);
	LL_DAC_EnableTrigger(DAC4, LL_DAC_CHANNEL_1);
	LL_DAC_DisableDMADoubleDataMode(DAC4, LL_DAC_CHANNEL_1);
	LL_DAC_EnableDMAReq(DAC4, LL_DAC_CHANNEL_1);
	//DAC Channel 2
	LL_DAC_SetSignedFormat(DAC4, LL_DAC_CHANNEL_2, LL_DAC_SIGNED_FORMAT_DISABLE);
	LL_DAC_SetTriggerSource(DAC4, LL_DAC_CHANNEL_2, LL_DAC_TRIG_EXT_TIM7_TRGO);
	LL_DAC_SetWaveAutoGeneration(DAC4, LL_DAC_CHANNEL_2, LL_DAC_WAVE_AUTO_GENERATION_NONE);
	LL_DAC_SetOutputBuffer(DAC4, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_BUFFER_DISABLE);
	LL_DAC_SetOutputConnection(DAC4, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_CONNECT_INTERNAL);
	LL_DAC_SetOutputMode(DAC4, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_MODE_NORMAL);
	LL_DAC_EnableTrigger(DAC4, LL_DAC_CHANNEL_2);
	LL_DAC_DisableDMADoubleDataMode(DAC4, LL_DAC_CHANNEL_2);
	LL_DAC_EnableDMAReq(DAC4, LL_DAC_CHANNEL_2);

	//Configure Interrupts
//	NVIC_SetPriority(TIM6_DAC_IRQn, 0);
//	NVIC_EnableIRQ(TIM6_DAC_IRQn);

	//Enable DAC
	LL_DAC_Enable(DAC4, LL_DAC_CHANNEL_1);
	LL_DAC_Enable(DAC4, LL_DAC_CHANNEL_2);
}


/**
  * @brief	This function writes a value to the DAC to be output
  * @param	channel: DAC Channel to set
  * @param	value: 12-bit Value to set the DAC Channel to
  * @return	None
  */
void DAC1Write(uint8_t channel, uint16_t value) {
	if(channel == 0x01) {
		LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, value);
		LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_1);
	}
	else if(channel == 0x02) {
		LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_2, value);
		LL_DAC_TrigSWConversion(DAC1, LL_DAC_CHANNEL_2);
	}
}

/**
  * @brief	This function writes a value to the DAC to be output
  * @param	channel: DAC Channel to set
  * @param	value: 12-bit Value to set the DAC Channel to
  * @return	None
  */
void DAC4Write(uint8_t channel, uint16_t value) {
	if(channel == 0x01) {
		LL_DAC_ConvertData12RightAligned(DAC4, LL_DAC_CHANNEL_1, value);
		LL_DAC_TrigSWConversion(DAC4, LL_DAC_CHANNEL_1);
	}
	else if(channel == 0x02) {
		LL_DAC_ConvertData12RightAligned(DAC4, LL_DAC_CHANNEL_2, value);
		LL_DAC_TrigSWConversion(DAC4, LL_DAC_CHANNEL_2);
	}
}
