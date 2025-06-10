#include "fmac.h"

#include "stm32g4xx_ll_adc.h"
#include "stm32g4xx_ll_dac.h"
#include "stm32g4xx_ll_dma.h"

/**
  * @brief	This function initializes the FMAC Engine
  * @param	None
  * @return	None
  */
void FMACInit() {
	//Peripheral clock enable
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_FMAC);

	//Configure DMA
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMAMUX1);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	//Input and output arrays, from where to read and write data
//	uint16_t inputBufferLength = 1024;
//	int16_t inputBuffer[1024];
//	uint16_t outputBufferLength = 1024;
//	int16_t outputBuffer[1024];

	//ADC to FMAC to DAC example, single channel with no Core utilization
//	//DMA1 Channel 1 from ADC to FMACs
//	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_ADC1);
//	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
//	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);
//	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);
//	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
//	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_NOINCREMENT);
//	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_WORD);
//	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_WORD);
//	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA), (uint32_t)&(FMAC->WDATA), LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
//	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 1);
//	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
//
//	//DMA1 Channel 2 from FMAC to DAC
//	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMAMUX_REQ_DAC1_CH1);
//	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
//	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_HIGH);
//	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_CIRCULAR);
//	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PERIPH_NOINCREMENT);
//	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_NOINCREMENT);
//	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PDATAALIGN_WORD);
//	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_WORD);
//	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2, (uint32_t)&(FMAC->RDATA), LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_1, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
//	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, 1);
//	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);

	//ADC to Memory to FMAC to Memory to DAC, dual channel with some Core intervention
	//DMA1 Channel 1 from ADC1 to Memory
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMAMUX_REQ_ADC1);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);
//	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_1, LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA), (uint32_t)&inBuffer_AN1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
//	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 1064);
//	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);

	//DMA1 Channel 2 from Memory to FMAC
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_2, LL_DMAMUX_REQ_FMAC_WRITE);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_2, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MODE_NORMAL);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_2, LL_DMA_MDATAALIGN_HALFWORD);
//	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_2, (uint32_t)&inBuffer_AN1, (uint32_t)&(FMAC->WDATA), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
//	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_2, 1064);
//	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_2);

	//DMA1 Channel 3 from FMAC to Memory
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_3, LL_DMAMUX_REQ_FMAC_READ);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_3, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MODE_NORMAL);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_3, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_3, LL_DMA_MDATAALIGN_HALFWORD);
//	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_3, (uint32_t)&(FMAC->RDATA), (uint32_t)&outBuffer_AN1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
//	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_3, 1064);
//	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_3);

	//DMA1 Channel 4 from Memory to DAC
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_4, LL_DMAMUX_REQ_DAC1_CH1);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_4, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_4, LL_DMA_MDATAALIGN_HALFWORD);
//	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_4, (uint32_t)&outBuffer_AN1, LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_1, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
//	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_4, 1064);
//	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_4);

	//DMA1 Channel 5 from ADC2 to Memory
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_5, LL_DMAMUX_REQ_ADC2);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_5, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_5, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_5, LL_DMA_MDATAALIGN_HALFWORD);
//	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_5, LL_ADC_DMA_GetRegAddr(ADC2, LL_ADC_DMA_REG_REGULAR_DATA), (uint32_t)&inBuffer_AN2, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
//	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_5, 1064);
//	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_5);

	//DMA1 Channel 6 from Memory to DAC
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_6, LL_DMAMUX_REQ_DAC1_CH2);
	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_6, LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_6, LL_DMA_PRIORITY_HIGH);
	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_6, LL_DMA_MODE_CIRCULAR);
	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_6, LL_DMA_PERIPH_NOINCREMENT);
	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_6, LL_DMA_MEMORY_INCREMENT);
	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_6, LL_DMA_PDATAALIGN_WORD);
	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_6, LL_DMA_MDATAALIGN_HALFWORD);
//	LL_DMA_ConfigAddresses(DMA1, LL_DMA_CHANNEL_6, (uint32_t)&outBuffer_AN1, LL_DAC_DMA_GetRegAddr(DAC1, LL_DAC_CHANNEL_2, LL_DAC_DMA_REG_DATA_12BITS_RIGHT_ALIGNED), LL_DMA_DIRECTION_MEMORY_TO_PERIPH);
//	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_6, 1064);
//	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_6);
}

uint8_t FMACFIRInit(uint8_t numTaps, int16_t* pCoeffs, uint8_t blockSize, uint8_t postShift) {
	//Check if everything fits in local buffer (256 bytes)
	if(((2 * numTaps) + (2 * blockSize)) > 256) {
		//Required buffer space to large
		return 1;
	}

	//Start with reseting the FMAC Unit
	LL_FMAC_EnableReset(FMAC);

	//Configure Buffer memory base and lengths
	//Set the coefficient buffer
	LL_FMAC_SetX2Base(FMAC, 0);
	LL_FMAC_SetX2BufferSize(FMAC, numTaps);

	//Set the input buffer
	LL_FMAC_SetX1Base(FMAC, numTaps);
	LL_FMAC_SetX1BufferSize(FMAC, numTaps);
	LL_FMAC_SetX1FullWatermark(FMAC, LL_FMAC_WM_0_THRESHOLD_1);

	//Set the output buffer
	LL_FMAC_SetYBase(FMAC, (2 * numTaps));
	LL_FMAC_SetYBufferSize(FMAC, blockSize);
	LL_FMAC_SetYEmptyWatermark(FMAC, LL_FMAC_WM_0_THRESHOLD_1);

	//Load empty values to input buffer (X1)
	LL_FMAC_SetFunction(FMAC, LL_FMAC_FUNC_LOAD_X1);
	LL_FMAC_SetParamP(FMAC, numTaps);	//Number of values to be loaded into X1 buffer
//	LL_FMAC_SetParamQ(FMAC, 0);			//Not used
//	LL_FMAC_SetParamR(FMAC, 0);			//Not used
	LL_FMAC_EnableStart(FMAC);			//Start FMAC processing

	uint8_t i;
	for(i = 0; i < numTaps; i++) {
		LL_FMAC_WriteData(FMAC, 0x00);
	}

	//Load X2 buffer (Coefficient buffer)
	LL_FMAC_SetFunction(FMAC, LL_FMAC_FUNC_LOAD_X2);
	LL_FMAC_SetParamP(FMAC, numTaps);	//Number of values to be loaded into X2 buffer @ X2_BASE
	LL_FMAC_SetParamQ(FMAC, 0);			//Number of values to be loaded into X2 buffer @ X2_BASE + N
//	LL_FMAC_SetParamR(FMAC, 0);			//Not used
//	LL_FMAC_EnableStart(FMAC);			//Start FMAC processing

	for(i = 0; i < numTaps; i++) {
		LL_FMAC_WriteData(FMAC, pCoeffs[i]);
	}

	//Configure the read/write method
	//Write: Polling; Read: Polling
	LL_FMAC_DisableIT_WR(FMAC);
	LL_FMAC_DisableIT_RD(FMAC);
	LL_FMAC_EnableDMAReq_WRITE(FMAC);
	LL_FMAC_EnableDMAReq_READ(FMAC);

	//Enable Clipping: Values saturate and do not wrap
	LL_FMAC_EnableClipping(FMAC);

	//Configure FMAC Unit
	LL_FMAC_SetFunction(FMAC, LL_FMAC_FUNC_CONVO_FIR);
	LL_FMAC_SetParamP(FMAC, numTaps);	//Number of coefficients (N+1)
//	LL_FMAC_SetParamQ(FMAC, 0);			//Not Used
	LL_FMAC_SetParamR(FMAC, postShift);	//Gain applied to the accumulator output
	LL_FMAC_EnableStart(FMAC);			//Start FMAC processing

	return 0;
}

uint8_t FMACIIRInit(uint8_t numStages, int16_t* pCoeffs, uint8_t blockSize, uint8_t postShift) {
	//Function is based on arm_biquad_cascade_df1_q15 so numStages is number of biquad sections which each have 3 feed-forward and 2 feed-back parts
	uint8_t n = 3 * numStages;		//Feed-forward coefficients (b[n])
	uint8_t m = 2 * numStages;		//Feed-back coefficients (a[n])

	//Check if everything fits in local buffer (256 bytes)
	if(((2*n) + (2*m) + (2*blockSize)) > 256) {
		//Required buffer space to large
		return 1;
	}

	//Start with reseting the FMAC Unit
	LL_FMAC_EnableReset(FMAC);

	//Configure Buffer memory base and lengths
	//Set the coefficient buffer
	LL_FMAC_SetX2Base(FMAC, 0);
	LL_FMAC_SetX2BufferSize(FMAC, (n + m));

	//Set the input buffer
	LL_FMAC_SetX1Base(FMAC, (n + m));
	LL_FMAC_SetX1BufferSize(FMAC, (n + blockSize));
	LL_FMAC_SetX1FullWatermark(FMAC, LL_FMAC_WM_0_THRESHOLD_1);

	//Set the output buffer
	LL_FMAC_SetYBase(FMAC, (2 * n + m + blockSize));
	LL_FMAC_SetYBufferSize(FMAC, (m + blockSize));
	LL_FMAC_SetYEmptyWatermark(FMAC, LL_FMAC_WM_0_THRESHOLD_1);

	//Load empty values to input buffer (X1)
	LL_FMAC_SetFunction(FMAC, LL_FMAC_FUNC_LOAD_X1);
	LL_FMAC_SetParamP(FMAC, n);		//Number of values to be loaded into X1 buffer
//	LL_FMAC_SetParamQ(FMAC, 0);		//Not used
//	LL_FMAC_SetParamR(FMAC, 0);		//Not used
	LL_FMAC_EnableStart(FMAC);		//Start FMAC processing

	uint8_t i;
	for(i = 0; i < n; i++) {
		LL_FMAC_WriteData(FMAC, 0x00);
	}

	//Load empty values to output buffer (Y)
	LL_FMAC_SetFunction(FMAC, LL_FMAC_FUNC_LOAD_Y);
	LL_FMAC_SetParamP(FMAC, m);		//Number of values to be loaded into Y buffer
//	LL_FMAC_SetParamQ(FMAC, 0);		//Not used
//	LL_FMAC_SetParamR(FMAC, 0);		//Not used
	LL_FMAC_EnableStart(FMAC);		//Start FMAC processing

	for(i = 0; i < m; i++) {
		LL_FMAC_WriteData(FMAC, 0x00);
	}

	//Load X2 buffer (Coefficient buffer)
	LL_FMAC_SetFunction(FMAC, LL_FMAC_FUNC_LOAD_X2);
	LL_FMAC_SetParamP(FMAC, n);		//Number of values to be loaded into X2 buffer @ X2_BASE
	LL_FMAC_SetParamQ(FMAC, m);		//Number of values to be loaded into X2 buffer @ X2_BASE + N
//	LL_FMAC_SetParamR(FMAC, 0);		//Not used
	LL_FMAC_EnableStart(FMAC);		//Start FMAC processing

	//First the feed-forward coefficients (b)
	for(i = 0; i < numStages; i++) {
		LL_FMAC_WriteData(FMAC, pCoeffs[6*i + 0]);	//b0
		LL_FMAC_WriteData(FMAC, pCoeffs[6*i + 2]);	//b1
		LL_FMAC_WriteData(FMAC, pCoeffs[6*i + 3]);	//b2
	}

	//Second the feed-back coefficients (a)
	for(i = 0; i < numStages; i++) {
		LL_FMAC_WriteData(FMAC, pCoeffs[6*i + 4]);	//a1
		LL_FMAC_WriteData(FMAC, pCoeffs[6*i + 5]);	//a2
	}

	//Configure the read/write method
	//Write: Polling; Read: Polling
	LL_FMAC_DisableIT_WR(FMAC);
	LL_FMAC_DisableIT_RD(FMAC);
	LL_FMAC_EnableDMAReq_WRITE(FMAC);
	LL_FMAC_EnableDMAReq_READ(FMAC);

	//Enable Clipping: Values saturate and do not wrap
	LL_FMAC_EnableClipping(FMAC);

	//Configure FMAC Unit
	LL_FMAC_SetFunction(FMAC, LL_FMAC_FUNC_IIR_DIRECT_FORM_1);
	LL_FMAC_SetParamP(FMAC, n);				//Number of feed-forward (b) coefficients
	LL_FMAC_SetParamQ(FMAC, m);				//Number of feed-back (a) coefficients
	LL_FMAC_SetParamR(FMAC, postShift);		//Gain applied to the accumulator output
	LL_FMAC_EnableStart(FMAC);				//Start FMAC processing

	return 0;
}

uint8_t FMACFIR(int16_t* pSrc, int16_t* pDst, uint8_t blockSize) {
	//Write data to input buffer
	uint8_t i = 0;
	while(i < blockSize) {
		while(LL_FMAC_IsActiveFlag_X1FULL(FMAC) == 0x01);
		LL_FMAC_WriteData(FMAC, pSrc[i++]);
	}

	//Wait for completion
	while(LL_FMAC_IsActiveFlag_YEMPTY(FMAC) == 0x01);

	//Read data from output buffer
	i = 0;
	while(i < blockSize) {
		while(LL_FMAC_IsActiveFlag_YEMPTY(FMAC) == 0x01);
		pDst[i++] = LL_FMAC_ReadData(FMAC);
	}

	//Check if a saturation of the accumulator occurred
	if(LL_FMAC_IsActiveFlag_SAT(FMAC) == 0x01) {
		return 1;
	}

	return 0;
}

uint8_t FMACIIR(int16_t* pSrc, int16_t* pDst, uint8_t blockSize) {
	//Write data to input buffer
	uint8_t i = 0;
	while(i < blockSize) {
		while(LL_FMAC_IsActiveFlag_X1FULL(FMAC) == 0x01);
		LL_FMAC_WriteData(FMAC, pSrc[i++]);
	}

	//Wait for completion
	while(LL_FMAC_IsActiveFlag_YEMPTY(FMAC));

	//Read data from output buffer
	i = 0;
	while(i < blockSize) {
		while(LL_FMAC_IsActiveFlag_YEMPTY(FMAC) == 0x01);
		pDst[i++] = LL_FMAC_ReadData(FMAC);
	}

	//Check if a saturation of the accumulator occurred
	if(LL_FMAC_IsActiveFlag_SAT(FMAC) == 0x01) {
		return 1;
	}

	return 0;
}
