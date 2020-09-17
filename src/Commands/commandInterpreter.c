#include "commandInterpreter.h"

#include "usb_vcp.h"

#define COMMAND_PAYLOAD_OFFSET						3

/**
  * @brief	This function handles received command packets
  * @param	data: Received Data array
  * @param	dataLength: Received Data array length
  * @return	0-> Command Good, 1-> Command Failed/Wrong
  */
uint8_t CommandInterpreter(uint8_t* data, uint16_t dataLength) {
	//DAQ Command Packet format
	//[Opcode]  [Length]   [Payload]  [...]     [CRC]
	//[uin8_t] [uint16_t] [uint8_t * Length] [uint16_t]

	//Packet Field decoding
	uint8_t opcode = data[0];
	uint16_t payloadLength = (data[1] << 8) + data[2];
	uint16_t crc = (data[3 + payloadLength] << 8) + data[4 + payloadLength];

	switch(opcode) {
		case OPCODE_RESET:
			break;
		case OPCODE_CONNECT:
			usbCOMPortOpen = 0x01;
			break;
		case OPCODE_DISCONNECT:
			usbCOMPortOpen = 0x00;

			//Clear Analog In sequencer, stop reading data from ADC
			AnalogInStopAll();
			break;
		case OPCODE_SET_CURRENT_A:
			ADA4254SetCurrent(ANALOG_IN_BLOCK_A, data[COMMAND_PAYLOAD_OFFSET], data[COMMAND_PAYLOAD_OFFSET+1]);
			break;
		case OPCODE_SET_CURRENT_B:
			ADA4254SetCurrent(ANALOG_IN_BLOCK_B, data[COMMAND_PAYLOAD_OFFSET], data[COMMAND_PAYLOAD_OFFSET+1]);
			break;
		case OPCODE_SET_ANALOG_IN_A: {
			AnalogInConfigStruct config;

			config.rate = data[COMMAND_PAYLOAD_OFFSET+0];
			config.scale = data[COMMAND_PAYLOAD_OFFSET+1];

			AnalogInConfig(ANALOG_IN_BLOCK_A, config);
			break;
		}
		case OPCODE_SET_ANALOG_IN_A_CH: {
			AnalogInCHConfigStruct config;

			uint8_t channel = data[COMMAND_PAYLOAD_OFFSET+0];
			config.mode = data[COMMAND_PAYLOAD_OFFSET+1];
			config.division = data[COMMAND_PAYLOAD_OFFSET+2];
			config.resolution = data[COMMAND_PAYLOAD_OFFSET+3];
			config.gain = data[COMMAND_PAYLOAD_OFFSET+4];

			AnalogInConfigChannel(ANALOG_IN_BLOCK_A, channel, config);
			break;
		}
		case OPCODE_SET_ANALOG_OUT_A_CH: {
			AnalogOutCHStruct config;

			config.channel = data[COMMAND_PAYLOAD_OFFSET+0];
			config.frequency = (data[COMMAND_PAYLOAD_OFFSET+1] << 16) + (data[COMMAND_PAYLOAD_OFFSET+2] << 8) + data[COMMAND_PAYLOAD_OFFSET+3];
			config.bufferLength = (data[COMMAND_PAYLOAD_OFFSET+4] << 8) + data[COMMAND_PAYLOAD_OFFSET+5];

			if(config.bufferLength > ANALOG_OUT_BUFFER_SIZE) {
				//New DAC samples array is to long
				return 1;
			}

			uint16_t i;
			for(i = 0; i < config.bufferLength; i++) {
				config.buffer[i] = (data[(COMMAND_PAYLOAD_OFFSET+6) + (i*2)] << 8) + data[(COMMAND_PAYLOAD_OFFSET+7) + (i*2)];
			}

			AnalogOutConfigChannel(ANALOG_OUT_BLOCK_A, config.channel, config);
			break;
		}
		case OPCODE_SET_ANALOG_OUT_B_CH: {
			AnalogOutCHStruct config;

			config.channel = data[COMMAND_PAYLOAD_OFFSET+0];
			config.frequency = (data[COMMAND_PAYLOAD_OFFSET+1] << 16) + (data[COMMAND_PAYLOAD_OFFSET+2] << 8) + data[COMMAND_PAYLOAD_OFFSET+3];
			config.bufferLength = (data[COMMAND_PAYLOAD_OFFSET+4] << 8) + data[COMMAND_PAYLOAD_OFFSET+5];

			if(config.bufferLength > ANALOG_OUT_BUFFER_SIZE) {
				//New DAC samples array is to long
				return 1;
			}

			uint16_t i;
			for(i = 0; i < config.bufferLength; i++) {
				config.buffer[i] = (data[(COMMAND_PAYLOAD_OFFSET+6) + (i*2)] << 8) + data[(COMMAND_PAYLOAD_OFFSET+7) + (i*2)];
			}

			AnalogOutConfigChannel(ANALOG_OUT_BLOCK_B, config.channel, config);
			break;
		}
		default:
			return 1;
			break;
	}

	return 0;
}
