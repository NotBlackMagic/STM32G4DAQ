#include "digitalIO.h"

//Digital IO mapping from logical IO number to MCU IO number
const uint8_t gpioMapping[9] = {	GPIO_IO_GPIO0, GPIO_IO_GPIO1, GPIO_IO_GPIO2, GPIO_IO_GPIO3, GPIO_IO_GPIO4,
										GPIO_IO_GPIO5, GPIO_IO_GPIO6, GPIO_IO_GPIO7, GPIO_IO_GPIO8 };

/**
  * @brief	This function initializes the Digital IO Channels
  * @param	None
  * @return	None
  */
void DigitalIOInit() {

}

/**
  * @brief	This function sets a Digital IO channel mode
  * @param	channel: Digital IO channel number
  * @param	mode: Output level, 0 or 1
  * @return	None
  */
void DigitalIOSetMode(uint8_t channel, DigitalIOMode mode) {
	if(channel > 8) {
		return;
	}

	switch(mode) {
		case Mode_Input:
			GPIOSetPinMode(gpioMapping[channel], GPIO_Mode_Input);
			break;
		case Mode_Output:
			GPIOSetPinMode(gpioMapping[channel], GPIO_Mode_Output);
			break;
		case Mode_PWM:
			GPIOSetPinMode(gpioMapping[channel], GPIO_Mode_Alternate);
			break;
	}
}

/**
  * @brief	This function sets a Digital IO channel output level
  * @param	channel: Digital IO channel number
  * @param	level: Output level, 0 or 1
  * @return	None
  */
void DigitalIOSetOutputLevel(uint8_t channel, uint8_t level) {
	if(channel > 8) {
		return;
	}
	if(level > 1) {
		level = 1;
	}
	GPIOWrite(gpioMapping[channel], level);
}

/**
  * @brief	This function sets a Digital IO channel input level
  * @param	channel: Digital IO channel number
  * @return	Input level, 0 or 1
  */
uint8_t DigitalIOGetInputLevel(uint8_t channel) {
	if(channel > 8) {
		return 0;
	}
	return GPIORead(gpioMapping[channel]);
}

/**
  * @brief	This function sets a Digital IO channel PWM output
  * @param	channel: Digital IO channel number
  * @param	frequency: PWM frequency
  * @param	dutyCycle: PWM Duty Cycle
  * @param	outputEn: PWM output enable
  * @return	None
  */
void DigitalIOSetPWM(uint8_t channel, uint32_t frequency, uint16_t dutyCycle, uint8_t outputEn) {
	if(channel > 8) {
		return;
	}

	//Update PWM frequency but keep duty cycle, and after change duty cycle
	switch(channel) {
		case 0:
			//TIM1 CH3
			TIM1SetFreq(frequency);
			TIM1SetCompare(3, dutyCycle);
			TIM1EnableOutput(3, outputEn);
			break;
		case 1:
			//TIM1 CH2
			TIM1SetFreq(frequency);
			TIM1SetCompare(2, dutyCycle);
			TIM1EnableOutput(2, outputEn);
			break;
		case 2:
			//TIM3 CH2
			break;
		case 3:
			//TIM5 CH1
			break;
		case 4:
			//TIM2 CH3
			break;
		case 5:
			//TIM1 CH1
			TIM1SetFreq(frequency);
			TIM1SetCompare(1, dutyCycle);
			TIM1EnableOutput(1, outputEn);
			break;
		case 6:
			//TIM1 CH4
			TIM1SetFreq(frequency);
			TIM1SetCompare(4, dutyCycle);
			TIM1EnableOutput(4, outputEn);
			break;
		case 7:
			//No Timer
			break;
		case 8:
			//No Timer
			break;
	}
}
