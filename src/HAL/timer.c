#include "timer.h"

#include "math.h"

/**
  * @brief	This function initializes the TIM1 and respective GPIO
  * @param	None
  * @return	None
  */
void TIM2Init() {
	//Enable bus clocks
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);

	//Configure GPIO, TIM1 PWM Outputs
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_9, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_10);

	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_10, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_10, LL_GPIO_AF_10);

	//Configure the Timer
	//LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM2, __LL_TIM_CALC_PSC(SystemCoreClock, 20000000));	//Set pre-scaler to have a clock of 10MHz
	LL_TIM_EnableARRPreload(TIM2);	//Enable Auto-reload
	LL_TIM_SetAutoReload(TIM2, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM2), 1000000));	//Set output clock to 125kHz
	LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);	//Set output Mode
	LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH4, LL_TIM_OCMODE_PWM1);	//Set output Mode
	//LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);	//Set output polarity
	LL_TIM_OC_SetCompareCH3(TIM2, ( (LL_TIM_GetAutoReload(TIM2) + 1 ) / 2)); //Set Output duty-cycle to 50%
	LL_TIM_OC_SetCompareCH4(TIM2, ( (LL_TIM_GetAutoReload(TIM2) + 1 ) / 2)); //Set Output duty-cycle to 50%
	LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH3);	//Enable Preload
	LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH4);	//Enable Preload
	LL_TIM_DisableMasterSlaveMode(TIM2);

	//Configure Interrupts
//	NVIC_SetPriority(TIM2_IRQn, 0);
//	NVIC_EnableIRQ(TIM2_IRQn);
//	LL_TIM_EnableIT_CC1(TIM2);

	//Enable Timer and Output
	LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH3);
	LL_TIM_CC_EnableChannel(TIM2, LL_TIM_CHANNEL_CH4);
	LL_TIM_EnableCounter(TIM2);
	LL_TIM_GenerateEvent_UPDATE(TIM2);
}

void TIM2_IRQHandler(void) {
	/* Check whether CC1 interrupt is pending */
	if(LL_TIM_IsActiveFlag_CC1(TIM2) == 1) {
		/* Clear the update interrupt flag*/
		LL_TIM_ClearFlag_CC1(TIM2);
	}
}

/**
  * @brief	This function initializes the TIM3 and respective GPIO
  * @param	None
  * @return	None
  */
void TIM3Init() {
	//Enable bus clocks
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

	//Configure GPIO, TIM3 Output
//	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
//	LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
//	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_PUSHPULL);
//	LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_6, LL_GPIO_PULL_NO);
//	LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_6, LL_GPIO_AF_2);

	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_7, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_7, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_7, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_7, LL_GPIO_AF_2);

	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_8, LL_GPIO_AF_2);

	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_9, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_9, LL_GPIO_AF_2);

	//Configure the Timer
	//LL_TIM_SetCounterMode(TIM3, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM3, __LL_TIM_CALC_PSC(SystemCoreClock, 10000000));	//Set pre-scaler to have a clock of 1MHz
	LL_TIM_EnableARRPreload(TIM3);	//Enable Auto-reload
	LL_TIM_SetAutoReload(TIM3, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM3), 500000));	//Set output clock to 125kHz
	LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);	//Set output Mode
	LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH3, LL_TIM_OCMODE_PWM1);	//Set output Mode
	LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH4, LL_TIM_OCMODE_PWM1);	//Set output Mode
	//LL_TIM_OC_SetPolarity(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);	//Set output polarity
	LL_TIM_OC_SetCompareCH2(TIM3, ((LL_TIM_GetAutoReload(TIM3) + 1 ) / 2)); //Set Output duty-cycle to 50%
	LL_TIM_OC_SetCompareCH3(TIM3, ((LL_TIM_GetAutoReload(TIM3) + 1 ) / 2)); //Set Output duty-cycle to 50%
	LL_TIM_OC_SetCompareCH4(TIM3, ((LL_TIM_GetAutoReload(TIM3) + 1 ) / 2)); //Set Output duty-cycle to 50%
	LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH2);	//Enable Preload
	LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH3);	//Enable Preload
	LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH4);	//Enable Preload
//	LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_CC1IF);
	LL_TIM_DisableMasterSlaveMode(TIM3);

	//Configure Interrupts
	NVIC_SetPriority(TIM3_IRQn, 0);
	NVIC_EnableIRQ(TIM3_IRQn);
	LL_TIM_EnableIT_CC1(TIM3);			//Enable capture/compare interrupt

	//Enable Timer and Output
	LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH2);
	LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH3);
	LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH4);
	LL_TIM_EnableCounter(TIM3);
	LL_TIM_GenerateEvent_UPDATE(TIM3);
}

uint8_t out = 0;
void TIM3_IRQHandler() {
	if(LL_TIM_IsActiveFlag_CC1(TIM3) == 1) {
	    LL_TIM_ClearFlag_CC1(TIM3);

//	    GPIOWrite(GPIO_IO_SCL, out);
//	    GPIOWrite(GPIO_IO_SDA, out);

	    if(out == 0x00) {
	    	out = 0x01;
	    }
	    else {
	    	out = 0x00;
	    }
	}
}

/**
  * @brief	This function initializes the TIM4 and respective GPIO
  * @param	None
  * @return	None
  */
void TIM4Init() {
	//Enable bus clocks
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

	//Configure GPIO, TIM4 Output
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_6, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_6, LL_GPIO_AF_2);

	//Configure the Timer
	//LL_TIM_SetCounterMode(TIM4, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM4, __LL_TIM_CALC_PSC(SystemCoreClock, 1000000));	//Set pre-scaler to have a clock of 1MHz
	LL_TIM_EnableARRPreload(TIM4);	//Enable Auto-reload
	LL_TIM_SetAutoReload(TIM4, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM4), 125000));	//Set output clock to 1MHz
	LL_TIM_OC_SetMode(TIM4, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);	//Set output Mode
	//LL_TIM_OC_SetPolarity(TIM4, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);	//Set output polarity
	LL_TIM_OC_SetCompareCH1(TIM4, ( (LL_TIM_GetAutoReload(TIM4) + 1 ) / 2)); //Set Output duty-cycle to 50%
	LL_TIM_OC_EnablePreload(TIM4, LL_TIM_CHANNEL_CH1);	//Enable Preload
	LL_TIM_SetTriggerOutput(TIM4, LL_TIM_TRGO_CC1IF);
	LL_TIM_DisableMasterSlaveMode(TIM4);

	//Configure Interrupts
//	NVIC_SetPriority(TIM4_IRQn, 0);
//	NVIC_EnableIRQ(TIM4_IRQn);
//	LL_TIM_EnableIT_CC1(TIM4);			//Enable capture/compare interrupt

	//Enable Timer and Output
	LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(TIM4);
	LL_TIM_GenerateEvent_UPDATE(TIM4);
}

/**
  * @brief	This function initializes the TIM6
  * @param	None
  * @return	None
  */
void TIM6Init() {
	//Enable bus clocks
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);

	//Configure the Timer
//	LL_TIM_SetCounterMode(TIM6, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM6, 0);		//Leave timer at full clock speed
	volatile uint16_t arr = __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM6), 2000000);		//Calculate ARR register value for clock to be 2MHz
	LL_TIM_SetAutoReload(TIM6, arr);	//Set ARR value
	LL_TIM_DisableARRPreload(TIM6);
	LL_TIM_SetTriggerOutput(TIM6, LL_TIM_TRGO_UPDATE);
	LL_TIM_DisableMasterSlaveMode(TIM6);

	//Configure Interrupts
//	NVIC_SetPriority(TIM6_DAC_IRQn, 0);
//	NVIC_EnableIRQ(TIM6_DAC_IRQn);
//	LL_TIM_EnableIT_UPDATE(TIM6);

	//Enable Timer
	LL_TIM_EnableCounter(TIM6);
}

/**
  * @brief	This function initializes the TIM7
  * @param	None
  * @return	None
  */
void TIM7Init() {
	//Enable bus clocks
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);

	//Configure the Timer
//	LL_TIM_SetCounterMode(TIM7, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM7, 0);		//Leave timer at full clock speed
	volatile uint16_t arr = __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM7), 2000000);		//Calculate ARR register value for clock to be 2MHz
	LL_TIM_SetAutoReload(TIM7, arr);	//Set ARR value
	LL_TIM_DisableARRPreload(TIM7);
	LL_TIM_SetTriggerOutput(TIM7, LL_TIM_TRGO_UPDATE);
	LL_TIM_DisableMasterSlaveMode(TIM7);

	//Configure Interrupts
//	NVIC_SetPriority(TIM7_DAC_IRQn, 0);
//	NVIC_EnableIRQ(TIM7_DAC_IRQn);
//	LL_TIM_EnableIT_UPDATE(TIM7);

	//Enable Timer
	LL_TIM_EnableCounter(TIM7);
}

/**
  * @brief	This function initializes the TIM8:
  * 		- Timer clock source is ADA4254 Clock Output
  * 		- Timer generates ADC1 Conversion Trigger
  * @param	None
  * @return	None
  */
void TIM8Init() {
	//Enable bus clocks
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);

	//Configure GPIO, TIM8 Input
	LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_6, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_6, LL_GPIO_AF_5);

	//Configure the Timer
//	LL_TIM_SetCounterMode(TIM8, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM8, 0);		//Leave timer at full clock speed
	LL_TIM_SetAutoReload(TIM8, 1);		//Set output clock to frequency
	LL_TIM_SetClockDivision(TIM8, LL_TIM_CLOCKDIVISION_DIV1);
	LL_TIM_SetRepetitionCounter(TIM8, 0);
	LL_TIM_EnableARRPreload(TIM8);
	LL_TIM_SetTriggerInput(TIM8, LL_TIM_TS_TI1FP1);
//	LL_TIM_ConfigETR(TIM8, LL_TIM_ETR_POLARITY_NONINVERTED, LL_TIM_ETR_PRESCALER_DIV1, LL_TIM_ETR_FILTER_FDIV1);
	LL_TIM_SetClockSource(TIM8, LL_TIM_CLOCKSOURCE_EXT_MODE1);
	LL_TIM_IC_SetFilter(TIM8, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV1);
	LL_TIM_IC_SetPolarity(TIM8, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_BOTHEDGE);
	LL_TIM_SetTriggerOutput(TIM8, LL_TIM_TRGO_CC1IF);
	LL_TIM_SetTriggerOutput2(TIM8, LL_TIM_TRGO2_CC1F);
	LL_TIM_DisableMasterSlaveMode(TIM8);
//	LL_TIM_ConfigBRK(TIM8, LL_TIM_BREAK_POLARITY_LOW, LL_TIM_BREAK_FILTER_FDIV1, LL_TIM_BREAK_AFMODE_INPUT);

	//Enable Timer
	LL_TIM_EnableCounter(TIM8);
}

/**
  * @brief	This function sets the output frequency of TIM3, sets the ARR and CCR values
  * @param	freq: Desired timer frequency on PWM output
  * @return	None
  */
void TIM3SetFreq(uint32_t freq) {
	LL_TIM_SetAutoReload(TIM3, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM3), freq));	//Set output clock to frequency
	LL_TIM_OC_SetCompareCH1(TIM3, ( (LL_TIM_GetAutoReload(TIM3) + 1 ) / 2)); 							//Set Output duty-cycle to 50%
}

/**
  * @brief	This function sets the output frequency of TIM4, sets the ARR and CCR values
  * @param	freq: Desired timer frequency on PWM output
  * @return	None
  */
void TIM4SetFreq(uint32_t freq) {
	LL_TIM_SetAutoReload(TIM4, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM4), freq));	//Set output clock to frequency
	LL_TIM_OC_SetCompareCH1(TIM4, ( (LL_TIM_GetAutoReload(TIM4) + 1 ) / 2)); 							//Set Output duty-cycle to 50%
}

/**
  * @brief	This function sets the output frequency of TIM6, sets the ARR value
  * @param	freq: Desired timer frequency of TIM update calls
  * @return	None
  */
void TIM6SetFreq(uint32_t freq) {
	LL_TIM_SetAutoReload(TIM6, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM6), freq));	//Set output clock to frequency
}

/**
  * @brief	This function sets the output frequency of TIM7, sets the ARR value
  * @param	freq: Desired timer frequency of TIM update calls
  * @return	None
  */
void TIM7SetFreq(uint32_t freq) {
	LL_TIM_SetAutoReload(TIM7, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM7), freq));	//Set output clock to frequency
}

/**
  * @brief	This function sets the output frequency of TIM8, sets the ARR value
  * @param	freq: Desired timer frequency of TIM update calls
  * @return	None
  */
//void TIM8SetFreq(uint32_t freq) {
//	LL_TIM_SetAutoReload(TIM8, __LL_TIM_CALC_ARR(1000000, LL_TIM_GetPrescaler(TIM8), freq));	//Set output clock to frequency
//}

/**
  * @brief	This function sets the ARR value
  * @param	arr: Desired timer ARR value
  * @return	None
  */
void TIM8SetARR(uint16_t arr) {
	LL_TIM_SetAutoReload(TIM8, arr);
}
