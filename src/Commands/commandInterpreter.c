#include "commandInterpreter.h"

#define COMMAND_PAYLOAD_OFFSET						3

uint8_t CommandInterpreter(uint8_t* data, uint16_t dataLength) {
	uint8_t opcode = data[0];
	uint16_t payloadLength = (data[1] << 8) + data[2];
	uint16_t crc = (data[3 + payloadLength] << 8) + data[4 + payloadLength];

	switch(opcode) {
		case OPCODE_SET_CURRENT_A:
			ADA4254SetCurrent(ANALOG_IN_BLOCK_A, data[COMMAND_PAYLOAD_OFFSET], data[COMMAND_PAYLOAD_OFFSET+1]);
			break;
		case OPCODE_SET_CURRENT_B:
			ADA4254SetCurrent(ANALOG_IN_BLOCK_B, data[COMMAND_PAYLOAD_OFFSET], data[COMMAND_PAYLOAD_OFFSET+1]);
			break;
		case OPCODE_SET_ANALOG_IN_A: {
			AnalogInConfigStruct config;

			config.mode = data[COMMAND_PAYLOAD_OFFSET+0];
			config.rate = data[COMMAND_PAYLOAD_OFFSET+1];
			config.scale = data[COMMAND_PAYLOAD_OFFSET+2];

			AnalogInConfig(ANALOG_IN_BLOCK_A, config);
			break;
		}
		case OPCODE_SET_ANALOG_IN_A_CH: {
			AnalogInCHConfigStruct config;

			uint8_t channel = data[COMMAND_PAYLOAD_OFFSET+0];
			config.enabled = data[COMMAND_PAYLOAD_OFFSET+1];
			config.division = data[COMMAND_PAYLOAD_OFFSET+2];
			config.resolution = data[COMMAND_PAYLOAD_OFFSET+3];
			config.gain = data[COMMAND_PAYLOAD_OFFSET+4];

			AnalogInConfigChannel(ANALOG_IN_BLOCK_A, channel, config);
			break;
		}
		case OPCODE_SET_ANALOG_OUT_A_CH: {
			AnalogOutCHConfigStruct config;

			uint8_t channel = data[COMMAND_PAYLOAD_OFFSET+0];
			config.mode = data[COMMAND_PAYLOAD_OFFSET+1];
			config.offset = (data[COMMAND_PAYLOAD_OFFSET+2] << 8) + data[COMMAND_PAYLOAD_OFFSET+3];
			config.frequency = (data[COMMAND_PAYLOAD_OFFSET+4] << 16) + (data[COMMAND_PAYLOAD_OFFSET+5] << 8) + data[COMMAND_PAYLOAD_OFFSET+6];
			config.amplitude = (data[COMMAND_PAYLOAD_OFFSET+7] << 8) + data[COMMAND_PAYLOAD_OFFSET+8];
			config.dtc = data[COMMAND_PAYLOAD_OFFSET+9];

			AnalogOutConfigChannel(ANALOG_OUT_BLOCK_A, channel, config);
			break;
		}
		default:
			return 1;
			break;
	}

	return 0;
}
