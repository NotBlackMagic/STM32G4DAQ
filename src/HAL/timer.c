#include "timer.h"

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
	//LL_TIM_SetCounterMode(TIM3, LL_TIM_COUNTERMODE_UP);
	LL_TIM_SetPrescaler(TIM3, __LL_TIM_CALC_PSC(SystemCoreClock, 1000000));	//Set pre-scaler to have a clock of 1MHz
	LL_TIM_EnableARRPreload(TIM3);	//Enable Auto-reload
	LL_TIM_SetAutoReload(TIM3, __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM3), 125000));	//Set output clock to 125kHz
	LL_TIM_OC_SetMode(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);	//Set output Mode
	//LL_TIM_OC_SetPolarity(TIM3, LL_TIM_CHANNEL_CH1, LL_TIM_OCPOLARITY_HIGH);	//Set output polarity
	LL_TIM_OC_SetCompareCH1(TIM3, ( (LL_TIM_GetAutoReload(TIM3) + 1 ) / 2)); //Set Output duty-cycle to 50%
	LL_TIM_OC_EnablePreload(TIM3, LL_TIM_CHANNEL_CH1);	//Enable Preload
	LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_CC1IF);
	LL_TIM_DisableMasterSlaveMode(TIM3);

	//Configure Interrupts
	NVIC_SetPriority(TIM3_IRQn, 0);
	NVIC_EnableIRQ(TIM3_IRQn);
	LL_TIM_EnableIT_CC1(TIM3);			//Enable capture/compare interrupt

	//Enable Timer and Output
	LL_TIM_CC_EnableChannel(TIM3, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(TIM3);
	LL_TIM_GenerateEvent_UPDATE(TIM3);
}

void TIM3_IRQHandler(void) {
	if(LL_TIM_IsActiveFlag_CC1(TIM3) == 1) {
		LL_TIM_ClearFlag_CC1(TIM3);
	}
}
