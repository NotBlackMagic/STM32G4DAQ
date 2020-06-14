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
	LL_DAC_SetTriggerSource(DAC1, LL_DAC_CHANNEL_1, LL_DAC_TRIG_SOFTWARE);
	LL_DAC_SetWaveAutoGeneration(DAC1, LL_DAC_CHANNEL_1, LL_DAC_WAVE_AUTO_GENERATION_NONE);
	LL_DAC_SetOutputBuffer(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_BUFFER_ENABLE);
	LL_DAC_SetOutputConnection(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_CONNECT_GPIO);
	LL_DAC_SetOutputMode(DAC1, LL_DAC_CHANNEL_1, LL_DAC_OUTPUT_MODE_NORMAL);
	LL_DAC_DisableTrigger(DAC1, LL_DAC_CHANNEL_1);
	LL_DAC_DisableDMADoubleDataMode(DAC1, LL_DAC_CHANNEL_1);
	//DAC Channel 2
	LL_DAC_SetSignedFormat(DAC1, LL_DAC_CHANNEL_2, LL_DAC_SIGNED_FORMAT_DISABLE);
	LL_DAC_SetTriggerSource(DAC1, LL_DAC_CHANNEL_2, LL_DAC_TRIG_SOFTWARE);
	LL_DAC_SetWaveAutoGeneration(DAC1, LL_DAC_CHANNEL_2, LL_DAC_WAVE_AUTO_GENERATION_NONE);
	LL_DAC_SetOutputBuffer(DAC1, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_BUFFER_ENABLE);
	LL_DAC_SetOutputConnection(DAC1, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_CONNECT_GPIO);
	LL_DAC_SetOutputMode(DAC1, LL_DAC_CHANNEL_2, LL_DAC_OUTPUT_MODE_NORMAL);
	LL_DAC_DisableTrigger(DAC1, LL_DAC_CHANNEL_2);
	LL_DAC_DisableDMADoubleDataMode(DAC1, LL_DAC_CHANNEL_2);

	//Enable DAC
	LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_1);
	LL_DAC_Enable(DAC1, LL_DAC_CHANNEL_2);
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
