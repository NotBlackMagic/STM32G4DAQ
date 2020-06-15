#ifndef DRIVER_ADA4254_H_
#define DRIVER_ADA4254_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "gpio.h"
#include "spi.h"

#include "ada4254_regs.h"

void ADA4254SetCurrent(CurrentValue value);
uint8_t ADA4254GetRevisionID();

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_ADA4254_H_ */
