#include "timer.h"

#include "math.h"

/**
  * @brief	This function initializes the TIM2 and respective GPIO
  * @param	None
  * @return	None
  */
//void TIM2Init() {
//	//Enable bus clocks
//	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
//	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
//
//	//Configure GPIO, TIM1 PWM Outputs
//	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_15, LL_GPIO_MODE_ALTERNATE);
//	LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_15, LL_GPIO_SPEED_FREQ_HIGH);
//	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_15, LL_GPIO_OUTPUT_PUSHPULL);
//	LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_15, LL_GPIO_PULL_NO);
//	LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_15, LL_GPIO_AF_1);
//
//	//Configure the Timer
////	LL_TIM_SetCounterMode(TIM2, LL_TIM_COUNTERMODE_UP);
//	LL_TIM_SetPrescaler(TIM2, 0);		//Leave timer at full clock speed
//	LL_TIM_SetAutoReload(TIM2, 1);		//Set output clock to frequency
//	LL_TIM_SetClockDivision(TIM2, LL_TIM_CLOCKDIVISION_DIV1);
//	LL_TIM_SetRepetitionCounter(TIM2, 0);
//	LL_TIM_EnableARRPreload(TIM2);
//	LL_TIM_SetTriggerInput(TIM2, LL_TIM_TS_TI1FP1);
////	LL_TIM_ConfigETR(TIM2, LL_TIM_ETR_POLARITY_NONINVERTED, LL_TIM_ETR_PRESCALER_DIV1, LL_TIM_ETR_FILTER_FDIV1);
//	LL_TIM_SetClockSource(TIM2, LL_TIM_CLOCKSOURCE_EXT_MODE1);
//	LL_TIM_IC_SetFilter(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV1);
//	LL_TIM_IC_SetPolarity(TIM2, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_BOTHEDGE);
//	LL_TIM_SetTriggerOutput(TIM2, LL_TIM_TRGO_CC1IF);
//	LL_TIM_SetTriggerOutput2(TIM2, LL_TIM_TRGO2_CC1F);
//	LL_TIM_DisableMasterSlaveMode(TIM2);
////	LL_TIM_ConfigBRK(TIM2, LL_TIM_BREAK_POLARITY_LOW, LL_TIM_BREAK_FILTER_FDIV1, LL_TIM_BREAK_AFMODE_INPUT);
//
//	//Enable Timer
//	LL_TIM_EnableCounter(TIM2);
//}

/**
  * @brief	This function initializes the TIM3, for Analog In Block B:
  * 		- Timer clock source is ADA4254 Clock Output
  * 		- Timer generates ADC2 Conversion Trigger
  * @param	None
  * @return	None
  */
void TIM3Init() {
	//Enable bus clocks
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);

	//Configure GPIO, TIM3 Output
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
	LL_GPIO_SetPinSpeed(GPIOC, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(GPIOC, LL_GPIO_PIN_6, LL_GPIO_PULL_NO);
	LL_GPIO_SetAFPin_0_7(GPIOC, LL_GPIO_PIN_6, LL_GPIO_AF_2);

	//Configure the Timer
//	LL_TIM_SetCounterMode(TIM3, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM3, 0);		//Leave timer at full clock speed
	LL_TIM_SetAutoReload(TIM3, 2);		//Set output clock
	LL_TIM_SetClockDivision(TIM3, LL_TIM_CLOCKDIVISION_DIV1);
	LL_TIM_SetRepetitionCounter(TIM3, 0);
	LL_TIM_EnableARRPreload(TIM3);
	LL_TIM_SetTriggerInput(TIM3, LL_TIM_TS_TI1FP1);
//	LL_TIM_ConfigETR(TIM3, LL_TIM_ETR_POLARITY_NONINVERTED, LL_TIM_ETR_PRESCALER_DIV1, LL_TIM_ETR_FILTER_FDIV1);
	LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_EXT_MODE1);
	LL_TIM_IC_SetFilter(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_IC_FILTER_FDIV1);
	LL_TIM_IC_SetPolarity(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_BOTHEDGE);
	LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_CC1IF);
	LL_TIM_SetTriggerOutput2(TIM3, LL_TIM_TRGO2_CC1F);
	LL_TIM_DisableMasterSlaveMode(TIM3);
//	LL_TIM_ConfigBRK(TIM3, LL_TIM_BREAK_POLARITY_LOW, LL_TIM_BREAK_FILTER_FDIV1, LL_TIM_BREAK_AFMODE_INPUT);

	//Enable Timer
	LL_TIM_EnableCounter(TIM3);
}

/**
  * @brief	This function initializes the TIM4: Used for DAC1 Channel 2 Trigger
  * @param	None
  * @return	None
  */
void TIM4Init() {
	//Enable bus clocks
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);

	//Configure the Timer
//	LL_TIM_SetCounterMode(TIM4, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM4, 14);		//Reduce timer from full clock speed, SystemCoreClock, to SystemCoreClock / 15 = 10 Mhz
	volatile uint16_t arr = __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM4), 1000000);		//Calculate ARR register value for clock to be 1MHz
	LL_TIM_SetAutoReload(TIM4, arr);	//Set ARR value
	LL_TIM_DisableARRPreload(TIM4);
	LL_TIM_SetTriggerOutput(TIM4, LL_TIM_TRGO_UPDATE);
	LL_TIM_DisableMasterSlaveMode(TIM4);

	//Enable Timer
	LL_TIM_EnableCounter(TIM4);
}

/**
  * @brief	This function initializes the TIM6: Used for DAC1 Channel 1 Trigger
  * @param	None
  * @return	None
  */
void TIM6Init() {
	//Enable bus clocks
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);

	//Configure the Timer
//	LL_TIM_SetCounterMode(TIM6, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM6, 14);		//Reduce timer from full clock speed, SystemCoreClock, to SystemCoreClock / 15 = 10 Mhz
	volatile uint16_t arr = __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM6), 1000000);		//Calculate ARR register value for clock to be 1MHz
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
  * @brief	This function initializes the TIM7: Used for DAC4 Channel 1 Trigger
  * @param	None
  * @return	None
  */
void TIM7Init() {
	//Enable bus clocks
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);

	//Configure the Timer
//	LL_TIM_SetCounterMode(TIM7, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM7, 14);		//Reduce timer from full clock speed, SystemCoreClock, to SystemCoreClock / 15 = 10 Mhz
	volatile uint16_t arr = __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM7), 1000000);		//Calculate ARR register value for clock to be 1MHz
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
  * @brief	This function initializes the TIM8, for Analog In Block A:
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
	LL_TIM_SetAutoReload(TIM8, 2);		//Set output clock
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
  * @brief	This function initializes the TIM15: Used for DAC4 Channel 2 Trigger
  * @param	None
  * @return	None
  */
void TIM15Init() {
	//Enable bus clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);

	//Configure the Timer
//	LL_TIM_SetCounterMode(TIM15, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM15, 14);		//Reduce timer from full clock speed, SystemCoreClock, to SystemCoreClock / 15 = 10 Mhz
	volatile uint16_t arr = __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM15), 1000000);		//Calculate ARR register value for clock to be 1MHz
	LL_TIM_SetAutoReload(TIM15, arr);	//Set ARR value
	LL_TIM_DisableARRPreload(TIM15);
	LL_TIM_SetTriggerOutput(TIM15, LL_TIM_TRGO_UPDATE);
	LL_TIM_DisableMasterSlaveMode(TIM15);

	//Enable Timer
	LL_TIM_EnableCounter(TIM15);
}

/**
  * @brief	This function sets the output frequency of TIM4, sets the ARR and CCR values
  * @param	freq: Desired timer frequency on PWM output
  * @return	None
  */
void TIM4SetFreq(uint32_t freq) {
	LL_TIM_SetAutoReload(TIM4, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM4), freq));	//Set output clock to frequency
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
  * @brief	This function sets the output frequency of TIM15, sets the ARR value
  * @param	freq: Desired timer frequency of TIM update calls
  * @return	None
  */
void TIM15SetFreq(uint32_t freq) {
	LL_TIM_SetAutoReload(TIM15, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM15), freq));	//Set output clock to frequency
}

/**
  * @brief	This function sets the TIM3 ARR value
  * @param	arr: Desired timer ARR value
  * @return	None
  */
void TIM3SetARR(uint16_t arr) {
	LL_TIM_SetAutoReload(TIM3, arr);
}

/**
  * @brief	This function sets the TIM8 ARR value
  * @param	arr: Desired timer ARR value
  * @return	None
  */
void TIM8SetARR(uint16_t arr) {
	LL_TIM_SetAutoReload(TIM8, arr);
}
