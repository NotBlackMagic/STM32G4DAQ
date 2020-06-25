#include "analogOut.h"

AnalogOutCHStruct analogOutAChannels[2];
AnalogOutCHStruct analogOutBChannels[2];

/**
  * @brief	This function initializes the Analog OUT Channel:
  * 		- Initialize structures
  * 		- Initializes DAC DMA Channels
  * @param	None
  * @return	None
  */
void AnalogOutInit() {
	//Enable bus clocks
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMAMUX1);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	//Configure DMA
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_DAC1_CH1);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&analogOutAChannels[0].buffer, LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_1, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 20);
//	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_1);
//	LL_DAC_EnableIT_DMAUDR1(DAC1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMAMUX_REQ_DAC1_CH2);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_HALFWORD);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2, (uint32_t)&analogOutAChannels[1].buffer, LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_2, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, 20);
//	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_2);
//	LL_DAC_EnableIT_DMAUDR1(DAC1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);

	//Configure Interrupts DMA
//	NVIC_SetPriority(DMA1_Channel3_IRQn, 0);
//	NVIC_EnableIRQ(DMA1_Channel3_IRQn);

	//{2048, 2680, 3252, 3705, 3996, 4095, 3996, 3705, 3252, 2680, 2048, 1415, 844, 391, 100, 0, 100, 391, 844, 1415}
	uint16_t i;
	for(i = 0; i < 512; i++) {
		analogOutAChannels[0].buffer[i] = 0;
		analogOutAChannels[1].buffer[i] = 0;
	}
}

/**
  * @brief	This function sets an Analog OUT Channel
  * @param	anBlock: Which analog block, A or B
  * @param	channel: Which channel to configure
  * @param	config: The configuration for the analog OUT channel, AnalogOutCHStruct
  * @return	None
  */
void AnalogOutConfigChannel(uint8_t anBlock, uint8_t channel, AnalogOutCHStruct config) {
	if(anBlock == ANALOG_OUT_BLOCK_A) {
		analogOutAChannels[channel - 1] = config;

		if(channel == 0x01) {
			//Change Timer settings, DAC update rate
			TIM6SetFreq(analogOutAChannels[channel - 1].frequency);

			//Change DMA Settings, buffer length
			LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, analogOutAChannels[channel - 1].bufferLength);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
		}
		else if(channel == 0x02) {
			//Change DMA Settings, buffer length
			LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, analogOutAChannels[channel - 1].bufferLength);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);
		}
	}
	else if(anBlock == ANALOG_OUT_BLOCK_B) {
		analogOutBChannels[channel - 1] = config;
	}
}
