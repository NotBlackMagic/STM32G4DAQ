#ifndef HAL_FMAC_H_
#define HAL_FMAC_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32g4xx.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_fmac.h"

void FMACInit();
uint8_t FMACFIRInit(uint8_t numTaps, int16_t* pCoeffs, uint8_t blockSize, uint8_t postShift);
uint8_t FMACIIRInit(uint8_t numStages, int16_t* pCoeffs, uint8_t blockSize, uint8_t postShift);
uint8_t FMACFIR(int16_t* pSrc, int16_t* pDst, uint8_t blockSize);
uint8_t FMACIIR(int16_t* pSrc, int16_t* pDst, uint8_t blockSize);

#ifdef __cplusplus
}
#endif

#endif /* HAL_FMAC_H_ */
