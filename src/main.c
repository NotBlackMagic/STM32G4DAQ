#include "adc.h"
#include "dac.h"
#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "system.h"
#include "uart.h"
#include "usb_vcp.h"

#include "ada4254.h"

#include "pinMaping.h"

int main(void) {
	//Configure the system clock
	SystemClockInit();
	SystemTickInit();

	//Initialize all configured peripherals
	GPIOInit();
	USBVCPInit();
	SPI1Init();		//SPI to Analog A Block
	SPI2Init();		//SPI to External Interface
	SPI3Init();		//SPI to Analog B Block
	UART1Init();
	SystemVrefEnable(VRef_2048);
	ADC1Init();
	DAC1Init();

	//Start ADC Conversions
	ADC1Start();

	//Set DAC to something
	DAC1Write(1, 2048);
	DAC1Write(2, 1024);

	//Give time for all to init, ADA4254 auto-calibration for example
	Delay(1000);

	//Init Analog Channels
	ADA4254Init();

	uint32_t timestamp = 0;

	uint8_t isVCPConnected = 0;
	uint8_t rxUSBData[512];
	uint16_t rxLength;
	while(1) {
		//USB/AT Command Interpreter
		if(USBVCPRead(rxUSBData, &rxLength) == 1) {

		}

		//This Sets the LED1 to the Virtual COM Connection state, LED is ON if connected
		if(USBVCPIsConnected()) {
			if(isVCPConnected == 0) {
				//First Connection, write welcome message
				USBVCPWrite("Welcome to VUHFRadio V1! \n", 26);
				USBVCPWrite("Hardware Version: 1.3, May 2020 \n", 33);
				USBVCPWrite("Software Version: 0.9, May 2020 \n", 33);
				USBVCPWrite("This Module uses AT Commands, for more info write AT+LIST \n", 59);

				isVCPConnected = 1;
			}
		}
		else {
			isVCPConnected = 0;
		}
		GPIOWrite(GPIO_OUT_STATUS_LED, USBVCPIsConnected());

		if(timestamp + 1000 < GetSysTick()) {
			timestamp = GetSysTick();

			uint8_t str[100];
			uint8_t len = sprintf(str, "AN CH1: %d \n", analogCH1);
			USBVCPWrite(str, len);
		}
	}
}

void Error_Handler(void) {

}
