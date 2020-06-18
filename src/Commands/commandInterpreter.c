#include "commandInterpreter.h"

uint8_t CommandInterpreter(uint8_t* data, uint16_t dataLength) {
	uint8_t opcode = data[0];
	uint8_t payloadLength = data[1];

	uint8_t payload[512];

	uint16_t i;
	for(i = 0; i < payloadLength; i++) {
		payload[i] = data[2 + i];
	}

	uint16_t crc = (data[2 + payloadLength] << 8) + data[3 + payloadLength];

	switch(opcode) {
		case OPCODE_SET_CURRENT_A:
			ADA4254SetCurrent(ANALOG_IN_BLOCK_A, payload[0], payload[1]);
			break;
		case OPCODE_SET_CURRENT_B:
			ADA4254SetCurrent(ANALOG_IN_BLOCK_B, payload[0], payload[1]);
			break;
		default:
			return 1;
			break;
	}

	return 0;
}
