#ifndef COMMANDS_COMMANDINTERPRETER_H_
#define COMMANDS_COMMANDINTERPRETER_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "opcodes.h"

#include "ada4254.h"

uint8_t CommandInterpreter(uint8_t* data, uint16_t dataLength);

#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_COMMANDINTERPRETER_H_ */
