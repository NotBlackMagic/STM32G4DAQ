#include "gpio.h"

/**
  * @brief	This function initializes the GPIO that don't use a peripheral (ADC/UART/SPI etc)
  * @param	None
  * @return	None
  */
void GPIOInit() {
	//Enable Port Clocks
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);

	//Enable EXTI/AFIO Clocks

	//Enable PC14 and PC15 as general IO
//	PWR->CR |= 1<<8;
//	RCC->BDCR &= 0xFFFFFFFE;
//	BKP->CR &= 0xFFFFFFFE;
//	PWR->CR &= 0xFFFFFEFF;

	//Set Fixed Output GPIO's
//	GPIOSetPinMode(GPIO_OUT_ADCA_CS, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_AMPA_CS, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_DACA_CS, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_AMPB_CS ,GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_DACB_CS ,GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_OUT_STATUS_LED ,GPIO_Mode_Output);

	//Set Flexible GPIO Pins to Input
	GPIOSetPinMode(GPIO_IO_GPIO0, GPIO_Mode_Output);
	GPIOSetPinMode(GPIO_IO_GPIO1, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_GPIO2, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_GPIO3, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_GPIO4, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_GPIO5, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_GPIO6, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_GPIO7, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_GPIO8, GPIO_Mode_Input);

	//Set Flexible I2C IO Pins to Input
	GPIOSetPinMode(GPIO_IO_SCL, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_SDA, GPIO_Mode_Input);

	//Set Flexible SPI IO Pins to Input
	GPIOSetPinMode(GPIO_IO_SCK, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_MISO, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_MOSI, GPIO_Mode_Input);

	//Set Flexible UART IO Pins to Input
	GPIOSetPinMode(GPIO_IO_TX, GPIO_Mode_Input);
	GPIOSetPinMode(GPIO_IO_RX, GPIO_Mode_Input);

	//Set ADC Input GPIO's
	GPIOSetPinMode(GPIO_ADC_A_INP, GPIO_Mode_Analog);
	GPIOSetPinMode(GPIO_ADC_A_INN, GPIO_Mode_Analog);
	GPIOSetPinMode(GPIO_ADC_B_INP, GPIO_Mode_Analog);
	GPIOSetPinMode(GPIO_ADC_B_INN, GPIO_Mode_Analog);

	//Set DAC Output GPIO's
	GPIOSetPinMode(GPIO_DAC_A_CH1, GPIO_Mode_Analog);
	GPIOSetPinMode(GPIO_DAC_A_CH2, GPIO_Mode_Analog);
	GPIOSetPinMode(GPIO_DAC_B_CH1, GPIO_Mode_Analog);
	GPIOSetPinMode(GPIO_DAC_B_CH2, GPIO_Mode_Analog);

	//Set Output Pins to Initial State
//	GPIOWrite(GPIO_OUT_ADCA_CS, 1);
	GPIOWrite(GPIO_OUT_AMPA_CS, 1);
	GPIOWrite(GPIO_OUT_DACA_CS, 1);
	GPIOWrite(GPIO_OUT_ADCAB_CS, 1);
	GPIOWrite(GPIO_OUT_AMPB_CS, 1);
	GPIOWrite(GPIO_OUT_DACB_CS, 1);
	GPIOWrite(GPIO_OUT_STATUS_LED, 0);
}

/**
  * @brief	This function sets the output mode type of a pin
  * @param	gpio: Pin to define output mode
  * @param	mode: Output mode of this pin
  * @return	None
  */
void GPIOSetPinMode(uint8_t gpio, GPIOOutputMode mode) {
	uint8_t port = (gpio >> 4);
	uint8_t pin = gpio & 0x0F;
	LL_GPIO_SetPinMode(gpioPorts[port], gpioPins[pin], gpioOutputMode[mode]);

	if(mode == GPIO_Mode_Analog) {
		LL_GPIO_SetPinPull(gpioPorts[port], gpioPins[pin], LL_GPIO_PULL_NO);
	}
}

/**
  * @brief	This function sets the output of a pin
  * @param	gpio: Pin to set output
  * @param	on: 1 output is set high, 0 output is set low
  * @return	None
  */
void GPIOWrite(uint8_t gpio, uint8_t on) {
	uint8_t port = (gpio >> 4);
	uint8_t pin = gpio & 0x0F;
	if(on == 1) {
		LL_GPIO_SetOutputPin(gpioPorts[port], gpioPins[pin]);
	}
	else {
		LL_GPIO_ResetOutputPin(gpioPorts[port], gpioPins[pin]);
	}
}

/**
  * @brief	This function gets the input state of a pin
  * @param	gpio: Pin to set output
  * @return	1 input is set high, 0 input is set low
  */
uint8_t GPIORead(uint8_t gpio) {
	uint8_t port = (gpio >> 4);
	uint8_t pin = gpio & 0x0F;
	return LL_GPIO_IsInputPinSet(gpioPorts[port], gpioPins[pin]);
}

/**
  * @brief	This function is the Handler for GPIO0s
  * @param	None
  * @return	None
  */
void EXTI0_IRQHandler(void) {

}

/**
  * @brief	This function is the Handler for GPIO1s
  * @param	None
  * @return	None
  */
void EXTI1_IRQHandler(void) {

}

/**
  * @brief	This function is the Handler for GPIO2s
  * @param	None
  * @return	None
  */
void EXTI2_IRQHandler(void) {

}

/**
  * @brief	This function is the Handler for GPIO3s
  * @param	None
  * @return	None
  */
void EXTI3_IRQHandler(void) {

}

/**
  * @brief	This function is the Handler for GPIO4s
  * @param	None
  * @return	None
  */
void EXTI4_IRQHandler(void) {

}

/**
  * @brief	This function is the Handler for GPIO5s to GPIO9s
  * @param	None
  * @return	None
  */
void EXTI9_5_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_8) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_8) == 0x01) {
		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_8);
	}
}

/**
  * @brief	This function is the Handler for GPIO10s to GPIO15s
  * @param	None
  * @return	None
  */
void EXTI15_10_IRQHandler(void) {
	if(LL_EXTI_IsEnabledIT_0_31(LL_EXTI_LINE_11) == 0x01 && LL_EXTI_IsActiveFlag_0_31(LL_EXTI_LINE_11) == 0x01) {
		//Clear Interrupt Flag
		LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_11);
	}
}
