#include "analogIn.h"

#define ANALOG_IN_SEQUENCER_LENGTH					128

AnalogInStruct analogInA;
AnalogInCHStruct analogInAChannels[4];
AnalogInStruct analogInB;
AnalogInCHStruct analogInBChannels[4];

uint8_t analogInAChSeqIndex;
uint8_t analogInACHSequencer[ANALOG_IN_SEQUENCER_LENGTH];
uint8_t analogInBChSeqIndex;
uint8_t analogInBCHSequencer[ANALOG_IN_SEQUENCER_LENGTH];

/**
  * @brief	This function initializes the Analog IN Channels:
  * 		- Initialize structures
  * 		- Initialize ADA4254 Amplifier
  * 		- Calibrate ADC offset
  * @param	None
  * @return	None
  */
void AnalogInInit() {
	//Initialize external hardware/IC
	ADA4254Init(ANALOG_IN_BLOCK_A);

	//Init Analog In Block A structs
	analogInA.config = (AnalogInConfigStruct){Mode_Differential, Sample_125k, Scale_1V};
	analogInA.offsetCall = 0;

	//Init Analog In Block B structs
	analogInB.config = (AnalogInConfigStruct){Mode_Differential, Sample_125k, Scale_1V};
	analogInB.offsetCall = 0;

	//Initialize structures
	uint8_t i = 0;
	for(i = 0; i < 4; i++) {
		//Init Analog In Block A Channel structs
		analogInAChannels[i].channel = i + 1;
		analogInAChannels[i].config = (AnalogInCHConfigStruct){0x00, Divison_1, Resolution_12Bit, Gain_1_8};
		analogInAChannels[i].bufferIndex = 0;

		//Init Analog In Block B Channel structs
		analogInBChannels[i].channel = i + 1;
		analogInBChannels[i].config = (AnalogInCHConfigStruct){0x00, Divison_1, Resolution_12Bit, Gain_1_8};
		analogInBChannels[i].bufferIndex = 0;
	}

	//Initialize sequencer
	for(i = 0; i < ANALOG_IN_SEQUENCER_LENGTH; i++) {
		analogInACHSequencer[i] = 0;
		analogInBCHSequencer[i] = 0;
	}
	analogInAChSeqIndex = 0;
	analogInBChSeqIndex = 0;

	//Calibrate ADCs
//	AnalogInCalibration(ANALOG_IN_BLOCK_A);
}

/**
  * @brief	This function calibrates the Analog In Block, the ADC offset
  * @param	anBlocks: Which analog block, A or B
  * @return	None
  */
void AnalogInCalibration(uint8_t anBlock) {
	if(anBlock == ANALOG_IN_BLOCK_A) {
		//Set up for calibration
		LL_ADC_DisableIT_EOC(ADC1);
		ADA4254WriteRegister(anBlock, INPUT_MUX, SW_D12_MASK);		//Set Internal Mux connections: Set to D12, short analog IN

		uint32_t callSum = 0;

		uint8_t i;
		for(i = 0; i < 64; i++) {
			while(LL_ADC_IsActiveFlag_EOC(ADC1) == 0x00);
			uint16_t value = LL_ADC_REG_ReadConversionData32(ADC1);
			callSum += value;
			LL_ADC_ClearFlag_EOC(ADC1);
		}

		analogInA.offsetCall = 2048 - (callSum >> 6);

		//Reset settings
		ADA4254WriteRegister(anBlock, INPUT_MUX, (SW_A1_MASK + SW_B2_MASK));
		LL_ADC_EnableIT_EOC(ADC1);
	}
	else if(anBlock == ANALOG_IN_BLOCK_B) {

	}
}


/**
  * @brief	This function sets an Analog IN Block
  * @param	anBlock: Which analog block, A or B
  * @param	config: The configuration for the analog IN block, AnalogInConfigStruct
  * @return	None
  */
void AnalogInConfig(uint8_t anBlock, AnalogInConfigStruct config) {
	if(anBlock == ANALOG_IN_BLOCK_A) {
		analogInA.config = config;

		//Set Mode, ADA4254 Internal MUX
		uint8_t mode = SW_A1_MASK + SW_A2_MASK;
		if(analogInA.config.mode == Mode_Differential) {
			mode = SW_A1_MASK + SW_A2_MASK;
		}
		else if(analogInA.config.mode == Mode_Single_INP) {
			mode = SW_A1_MASK + SW_B2_MASK;
		}
		else if(analogInA.config.mode == Mode_Single_INN) {
			mode = SW_B1_MASK + SW_B2_MASK;
		}
		ADA4254WriteRegister(anBlock, INPUT_MUX, mode);

		//Set Sample Rate
		uint32_t sampleFreq = (4 << analogInA.config.rate) - 1;
		TIM8SetARR(sampleFreq);

		//Set Scaling, ADA4254 output gain
	}
	else if(anBlock == ANALOG_IN_BLOCK_B) {
		analogInB.config = config;
	}
}

/**
  * @brief	This function sets an Analog IN Channel
  * @param	anBlock: Which analog block, A or B
  * @param	channel: Which analog channel, 1 to 4
  * @param	config: The set configuration for the channel, AnalogInCHConfigStruct
  * @return	None
  */
void AnalogInConfigChannel(uint8_t anBlock, uint8_t channel, AnalogInCHConfigStruct config) {
	if(anBlock == ANALOG_IN_BLOCK_A) {
		analogInAChannels[channel - 1].config = config;

		if(config.enabled != 0x00) {
			uint8_t division = (0x01 << config.division);
			uint8_t indexOffset = 0;

			if(division > 1) {
				indexOffset = channel - 1;
			}

			uint8_t i;
			for(i = indexOffset; i < ANALOG_IN_SEQUENCER_LENGTH; i++) {
				if(((i - indexOffset) % division) == 0x00) {
					analogInACHSequencer[i] = channel;
				}
				else if(analogInACHSequencer[i] == channel) {
					analogInACHSequencer[i] = 0;
				}
			}

		}
		else {
			uint8_t i;
			for(i = 0; i < ANALOG_IN_SEQUENCER_LENGTH; i++) {
				if(analogInACHSequencer[i] == channel) {
					analogInACHSequencer[i] = 0;
				}
			}
		}
	}
	else if(anBlock == ANALOG_IN_BLOCK_B) {
		analogInBChannels[channel - 1].config = config;
	}
}
/**
  * @brief	This function reads an Analog IN Channel
  * @param	anBlock: Which analog block, A or B
  * @param	channel: Which analog channel, 1 to 4
  * @param	data: data array to be filled with the buffer data
  * @return	Length of the buffer
  */
uint16_t AnalogInGetData(uint8_t anBlock, uint8_t channel, uint8_t* data) {
	uint16_t length = 0;
	if(anBlock == ANALOG_IN_BLOCK_A) {
		length = analogInAChannels[channel - 1].bufferIndex;
		analogInAChannels[channel - 1].bufferIndex = 0;

		uint16_t i;
		for(i = 0; i < length; i++) {
			data[i] = analogInAChannels[channel - 1].buffer[i];
		}
	}
	else if(anBlock == ANALOG_IN_BLOCK_B) {
		length = analogInBChannels[channel - 1].bufferIndex;
		analogInBChannels[channel - 1].bufferIndex = 0;

		uint16_t i;
		for(i = 0; i < length; i++) {
			data[i] = analogInBChannels[channel - 1].buffer[i];
		}
	}
	return length;
}

/**
  * @brief	This function handles all the analog In functions, switching and re-configurations
  * @param	anBlock: Signals the Handler which ADC IRQ called this function, which analog Block A or B
  * @return	None
  */
void AnalogInHandler(uint8_t anBlock) {
	if(anBlock == ANALOG_IN_BLOCK_A) {
		uint8_t channel = analogInACHSequencer[analogInAChSeqIndex];
		//Check if have channel to read and read it to buffer
		if(channel != 0x00) {
			//Read ADC to analog channel buffer
			uint16_t value = LL_ADC_REG_ReadConversionData32(ADC1);

			//Apply calibration offset
			value += analogInA.offsetCall;

			//Write to Buffer
			analogInAChannels[channel - 1].buffer[analogInAChannels[channel - 1].bufferIndex] = (value >> 8);
			analogInAChannels[channel - 1].buffer[analogInAChannels[channel - 1].bufferIndex + 1] = value;

			//Update Buffer index, buffer is circular
			analogInAChannels[channel - 1].bufferIndex += 2;
			if(analogInAChannels[channel - 1].bufferIndex >= 512) {
				analogInAChannels[channel - 1].bufferIndex = 0;
			}
		}

		//Set up next channel to be read: Set ADA4254
		analogInAChSeqIndex += 1;
		if(analogInAChSeqIndex >= ANALOG_IN_SEQUENCER_LENGTH) {
			analogInAChSeqIndex = 0;
		}

		//Check if next channel in sequencer is different from current one, only switch MUX and Gain if different
//		if(analogInACHSequencer[analogInAChSeqIndex] != channel) {
			channel = analogInACHSequencer[analogInAChSeqIndex];
			if(channel != 0x00) {
				uint8_t gain = analogInAChannels[channel - 1].config.gain;
				uint8_t reg = ((gain << 3) & IN_AMP_GAIN_MASK) + ((3 - (channel - 1)) & EXT_MUX_MASK);;
				ADA4254WriteRegister(ANALOG_IN_BLOCK_A, GAIN_MUX, reg);
			}
//		}
	}
	else if(anBlock == ANALOG_IN_BLOCK_B) {

	}
}
