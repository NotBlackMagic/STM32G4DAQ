#ifndef COMMANDS_OPCODES_H_
#define COMMANDS_OPCODES_H_

#ifdef __cplusplus
 extern "C" {
#endif

//Commands Opcode
#define OPCODE_RESET							0x01
#define OPCODE_CONNECT							0x02
#define OPCODE_DISCONNECT						0x03

//Config Opcodes
#define OPCODE_SET_CURRENT_A					0x11	//Configure Current output A
#define OPCODE_SET_CURRENT_B					0x12	//Configure Current output A
#define OPCODE_SET_ANALOG_IN_A					0x13	//Configure Analog In Block A
#define OPCODE_SET_ANALOG_IN_A_CH				0x14	//Configure Analog In Block A Channel
#define OPCODE_SET_ANALOG_OUT_A_CH				0x15	//Configure Analog Out Block A Channel
#define OPCODE_SET_ANALOG_OUT_B_CH				0x16	//Configure Analog Out Block B Channel

//Data to PC Opcodes
#define OPCODE_TX_ANALOG_IN_A					0x81	//Send Analog In data

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_OPCODES_H_ */
