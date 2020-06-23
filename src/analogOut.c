#include "analogOut.h"

AnalogOutCHStruct analogOutAChannels[2];
AnalogOutCHStruct analogOutBChannels[2];

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
	analogOutAChannels[0].buffer[0] = 2048;
	analogOutAChannels[0].buffer[1] = 2680;
	analogOutAChannels[0].buffer[2] = 3252;
	analogOutAChannels[0].buffer[3] = 3705;
	analogOutAChannels[0].buffer[4] = 3996;
	analogOutAChannels[0].buffer[5] = 4095;
	analogOutAChannels[0].buffer[6] = 3996;
	analogOutAChannels[0].buffer[7] = 3705;
	analogOutAChannels[0].buffer[8] = 3252;
	analogOutAChannels[0].buffer[9] = 2680;
	analogOutAChannels[0].buffer[10] = 2048;
	analogOutAChannels[0].buffer[11] = 1415;
	analogOutAChannels[0].buffer[12] = 844;
	analogOutAChannels[0].buffer[13] = 391;
	analogOutAChannels[0].buffer[14] = 100;
	analogOutAChannels[0].buffer[15] = 0;
	analogOutAChannels[0].buffer[16] = 100;
	analogOutAChannels[0].buffer[17] = 391;
	analogOutAChannels[0].buffer[18] = 844;
	analogOutAChannels[0].buffer[19] = 1415;

	analogOutAChannels[1].buffer[0] = 2048;
	analogOutAChannels[1].buffer[1] = 2680;
	analogOutAChannels[1].buffer[2] = 3252;
	analogOutAChannels[1].buffer[3] = 3705;
	analogOutAChannels[1].buffer[4] = 3996;
	analogOutAChannels[1].buffer[5] = 4095;
	analogOutAChannels[1].buffer[6] = 3996;
	analogOutAChannels[1].buffer[7] = 3705;
	analogOutAChannels[1].buffer[8] = 3252;
	analogOutAChannels[1].buffer[9] = 2680;
	analogOutAChannels[1].buffer[10] = 2048;
	analogOutAChannels[1].buffer[11] = 1415;
	analogOutAChannels[1].buffer[12] = 844;
	analogOutAChannels[1].buffer[13] = 391;
	analogOutAChannels[1].buffer[14] = 100;
	analogOutAChannels[1].buffer[15] = 0;
	analogOutAChannels[1].buffer[16] = 100;
	analogOutAChannels[1].buffer[17] = 391;
	analogOutAChannels[1].buffer[18] = 844;
	analogOutAChannels[1].buffer[19] = 1415;
}

void AnalogOutConfigChannel(uint8_t anBlock, uint8_t channel, AnalogOutCHConfigStruct config) {
	if(anBlock == ANALOG_OUT_BLOCK_A) {
		analogOutAChannels[channel - 1].config = config;

		if(analogOutAChannels[channel - 1].config.mode == Mode_DC) {
			DAC1Write(channel, analogOutAChannels[channel - 1].config.offset);
		}
	}
	else if(anBlock == ANALOG_OUT_BLOCK_B) {
		analogOutBChannels[channel - 1].config = config;
	}
}

uint16_t value = 0;
void AnalogOutHandler(uint8_t anBlock) {
	if(anBlock == ANALOG_IN_BLOCK_A) {
		LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_1, value);
		LL_DAC_ConvertData12RightAligned(DAC1, LL_DAC_CHANNEL_2, value);

		value += 128;
		if(value > 4095) {
			value = 0;
		}
	}
}
