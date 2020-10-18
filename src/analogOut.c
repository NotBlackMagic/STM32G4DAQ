#include "analogOut.h"

__attribute__((section(".ram2"))) AnalogOutCHStruct analogOutAChannels[2];
__attribute__((section(".ram2"))) AnalogOutCHStruct analogOutBChannels[2];

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

	//Init DAC output buffers
	//{2048, 2680, 3252, 3705, 3996, 4095, 3996, 3705, 3252, 2680, 2048, 1415, 844, 391, 100, 0, 100, 391, 844, 1415}
	uint16_t i;
	for(i = 0; i < ANALOG_OUT_BUFFER_SIZE; i++) {
		analogOutAChannels[0].buffer[i] = 2048;
		analogOutAChannels[1].buffer[i] = 2048;
		analogOutBChannels[0].buffer[i] = 2048;
		analogOutBChannels[1].buffer[i] = 2048;
	}

	analogOutAChannels[0].bufferLength = 1;
	analogOutAChannels[1].bufferLength = 1;
	analogOutBChannels[0].bufferLength = 1;
	analogOutBChannels[1].bufferLength = 1;

	//Configure DMA
	//DMA1 Channel 1 to DAC1 Channel 1
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_DAC1_CH1);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, (uint32_t)&analogOutAChannels[0].buffer, LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_1, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, analogOutAChannels[0].bufferLength);
//	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_1);
//	LL_DAC_EnableIT_DMAUDR1(DAC1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

	//DMA1 Channel 2 to DAC1 Channel 2
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMAMUX_REQ_DAC1_CH2);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_HALFWORD);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2, (uint32_t)&analogOutAChannels[1].buffer, LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_2, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, analogOutAChannels[1].bufferLength);
//	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_2);
//	LL_DAC_EnableIT_DMAUDR1(DAC1);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);

	//DMA1 Channel 3 to DAC4 Channel 1
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_3, LL_DMAMUX_REQ_DAC4_CH1);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_3, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MDATAALIGN_HALFWORD);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_3, (uint32_t)&analogOutBChannels[0].buffer, LL_DAC_DMA_GetRegAddr(DAC4, LL_DAC_CHANNEL_1, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, analogOutBChannels[0].bufferLength);
//	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_3);
//	LL_DAC_EnableIT_DMAUDR1(DAC4);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

	//DMA1 Channel 4 to DAC4 Channel 2
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_4, LL_DMAMUX_REQ_DAC4_CH2);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MDATAALIGN_HALFWORD);
	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_4, (uint32_t)&analogOutBChannels[1].buffer, LL_DAC_DMA_GetRegAddr(DAC4, LL_DAC_CHANNEL_2, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, analogOutBChannels[1].bufferLength);
//	LL_DMA_EnableIT_TE(DMA1, LL_DMA_CHANNEL_4);
//	LL_DAC_EnableIT_DMAUDR1(DAC4);
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);

	//Configure Interrupts DMA
//	NVIC_SetPriority(DMA1_Channel3_IRQn, 0);
//	NVIC_EnableIRQ(DMA1_Channel3_IRQn);
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
			//Change DMA Settings, buffer length
			LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_1);
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, analogOutAChannels[0].bufferLength);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

			TIM6SetFreq(config.frequency);
		}
		else if(channel == 0x02) {
			//Change DMA Settings, buffer length
			LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_2);
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, analogOutAChannels[1].bufferLength);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);

			TIM4SetFreq(config.frequency);
		}
	}
	else if(anBlock == ANALOG_OUT_BLOCK_B) {
		analogOutBChannels[channel - 1] = config;

		if(channel == 0x01) {
			//Change DMA Settings, buffer length
			LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_3);
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, analogOutBChannels[0].bufferLength);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

			TIM7SetFreq(config.frequency);
		}
		else if(channel == 0x02) {
			//Change DMA Settings, buffer length
			LL_DMA_DisableChannel(DMA1, LL_DMA_CHANNEL_4);
			LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, analogOutBChannels[1].bufferLength);
			LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);

			TIM15SetFreq(config.frequency);
		}
	}
}
