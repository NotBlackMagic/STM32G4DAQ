#include "analogOut.h"

AnalogOutCHConfigStruct analogOutAChannels[2];
AnalogOutCHConfigStruct analogOutBChannels[2];

void AnalogOutConfigChannel(uint8_t anBlock, uint8_t channel, AnalogOutCHConfigStruct config) {
	if(anBlock == ANALOG_OUT_BLOCK_A) {
		analogOutAChannels[channel - 1] = config;
	}
	else if(anBlock == ANALOG_OUT_BLOCK_B) {
		analogOutBChannels[channel - 1] = config;
	}
}
