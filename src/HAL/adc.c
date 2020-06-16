#include "adc.h"

volatile uint16_t analogCH1;

/**
  * @brief	This function initializes the ADC1 and respective GPIOs
  * @param	None
  * @return	None
  */
void ADC1Init() {
	//Enable bus clocks
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC12);

	//Configure the ADC
	LL_ADC_SetResolution(ADC1, LL_ADC_RESOLUTION_12B);			//Set ADC Base Resolution to 12bits
	LL_ADC_SetDataAlignment(ADC1, LL_ADC_DATA_ALIGN_RIGHT);		//Align Data to the Right
	LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);
	LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
	LL_ADC_REG_SetSequencerDiscont(ADC1, LL_ADC_REG_SEQ_DISCONT_DISABLE);
	LL_ADC_REG_SetContinuousMode(ADC1, LL_ADC_REG_CONV_CONTINUOUS);
	LL_ADC_REG_SetDMATransfer(ADC1, LL_ADC_REG_DMA_TRANSFER_NONE);
	LL_ADC_REG_SetOverrun(ADC1, LL_ADC_REG_OVR_DATA_OVERWRITTEN);
	LL_ADC_SetGainCompensation(ADC1, 0x00);
	LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
//	LL_ADC_ConfigOverSamplingRatioShift(ADC1, LL_ADC_OVS_RATIO_256, LL_ADC_OVS_SHIFT_RIGHT_4);
//	LL_ADC_SetOverSamplingDiscont(ADC1, LL_ADC_OVS_REG_CONT);
	LL_ADC_DisableDeepPowerDown(ADC1);
	LL_ADC_EnableInternalRegulator(ADC1);
	LL_ADC_SetCommonClock(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_SYNC_PCLK_DIV1);
	LL_ADC_SetMultimode(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_MULTI_INDEPENDENT);

	//Configure Input Channel
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_1);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_1, LL_ADC_SAMPLINGTIME_640CYCLES_5);	//Should give Fs = 160MHz / (640.5 + 12.5) = 245kSps
	LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_1, LL_ADC_DIFFERENTIAL_ENDED);

	//Run ADC self calibration
	LL_ADC_StartCalibration(ADC1, LL_ADC_DIFFERENTIAL_ENDED);
	while(LL_ADC_IsCalibrationOnGoing(ADC1) != 0);

	//Configure Interrupts
	LL_ADC_EnableIT_EOC(ADC1);

	NVIC_SetPriority(ADC1_2_IRQn, 0);
	NVIC_EnableIRQ(ADC1_2_IRQn);

	//Enable ADC
	LL_ADC_Enable(ADC1);
	while(LL_ADC_IsActiveFlag_ADRDY(ADC1) == 0);
}

/**
  * @brief	This function triggers an ADC1 Conversion, or starts the continuous conversion
  * @param	None
  * @return	None
  */
void ADC1Start() {
	LL_ADC_ClearFlag_EOC(ADC1);

	LL_ADC_REG_StartConversion(ADC1);
}

/**
  * @brief	ADC1 and ADC2 IRQ Handler
  * @param	None
  * @return	None
  */
uint8_t ledOn = 0x01;
void ADC1_2_IRQHandler(void) {
	if(LL_ADC_IsActiveFlag_EOC(ADC1) == 0x01 && LL_ADC_IsEnabled(ADC1) == 0x01) {
		analogCH1 = LL_ADC_REG_ReadConversionData12(ADC1);

		LL_ADC_ClearFlag_EOC(ADC1);
	}
}