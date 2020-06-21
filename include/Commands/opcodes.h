#ifndef COMMANDS_OPCODES_H_
#define COMMANDS_OPCODES_H_

#ifdef __cplusplus
 extern "C" {
#endif

#define OPCODE_SET_CURRENT_A					0x01	//Configure Current output A
#define OPCODE_SET_CURRENT_B					0x02	//Configure Current output A
#define OPCODE_SET_ANALOG_IN_A					0x03	//Configure Analog In Block A
#define OPCODE_SET_ANALOG_IN_A_CH				0x04	//Configure Analog In Block A Channel

#define OPCODE_TX_ANALOG_IN_A					0x81	//Send Analog In data

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_OPCODES_H_ */
