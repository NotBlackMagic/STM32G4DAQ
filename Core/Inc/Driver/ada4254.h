#ifndef DRIVER_ADA4254_H_
#define DRIVER_ADA4254_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "gpio.h"
#include "spi.h"

#include "ada4254_regs.h"

void ADA4254Init(uint8_t anBlock);

uint8_t ADA4254GetRevisionID();
uint8_t ADA4254SetCurrent(uint8_t anBlock, CurrentSource source, CurrentValue value);

void ADA4254WriteRegister(uint8_t anBlock, uint8_t reg, uint8_t data);
uint8_t ADA4254ReadRegister(uint8_t anBlock, uint8_t reg);

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_ADA4254_H_ */
