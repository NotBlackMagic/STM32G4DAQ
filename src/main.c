#include "adc.h"
#include "dac.h"
#include "gpio.h"
#include "opamp.h"
#include "rcc.h"
#include "spi.h"
#include "system.h"
#include "timer.h"
#include "uart.h"
#include "usb_vcp.h"

#include "ada4254.h"
#include "analogIn.h"
#include "opcodes.h"
#include "pinMaping.h"

int main(void) {
	//Configure the system clock
	SystemClockInit();
	SystemTickInit();

	//Initialize all configured peripherals
	GPIOInit();
	USBVCPInit();
	SystemVrefEnable(VRef_2048);

	//------------------------------------------//
	//			Init Analog Block A				//
	//------------------------------------------//
	//Init SPI for Analog A Block
	SPI1Init();

	//Init ADC and ADC trigger Timer
	TIM8Init();
	ADC1Init();

	//Init DAC and DAC trigger Timer
	TIM6Init();
	DAC1Init();

	//Start ADC Conversions
	ADC1Start();
	//------------------------------------------//

	//------------------------------------------//
	//			Init Analog Block B				//
	//------------------------------------------//
	//Init SPI for Analog B Block
	SPI3Init();

	//Init ADC and ADC trigger Timer

	//Init DAC and DAC trigger Timer
	TIM7Init();
	DAC4Init();
	OpAmp4Init();
	OpAmp5Init();

	//Start ADC Conversions

	//Set DAC to 0V, "Idle" voltage
	DAC4Write(1, 2048);
	DAC4Write(2, 2048);

	//------------------------------------------//

	//Possible Init External peripheral interfaces
//	SPI2Init();		//SPI to External Interface
//	UART1Init();

	//Give time for all to init, ADA4254 auto-calibration for example
	Delay(1000);

	//Init Analog Channels
	AnalogInInit();
	AnalogOutInit();

	uint32_t timestamp = 0;

	uint8_t isVCPConnected = 0;
	uint8_t txUSBData[1024];
	uint16_t txLength;
	uint8_t rxUSBData[1024];
	uint16_t rxLength;
	while(1) {
		//USB/AT Command Interpreter
		if(USBVCPRead(rxUSBData, &rxLength) == 1) {
			CommandInterpreter(rxUSBData, rxLength);
		}

		//This Sets the LED1 to the Virtual COM Connection state, LED is ON if connected
		if(USBVCPIsConnected()) {
			if(isVCPConnected == 0) {
				//First Connection, write welcome message
				isVCPConnected = 1;
			}
		}
		else {
			isVCPConnected = 0;
		}
		GPIOWrite(GPIO_OUT_STATUS_LED, USBVCPIsConnected());

		//Check if USB TX is ready for new data
		if(USBVCPTXStatus() == 0x00) {
			uint16_t txUSBDataIndex = 0;
			uint8_t channel = 1;
			for(channel = 1; channel < 9; channel++) {
				uint16_t dataLength = AnalogInGetData(1, channel, &txUSBData[txUSBDataIndex + 4]);
				if(dataLength != 0x00) {
					txUSBData[txUSBDataIndex++] = OPCODE_TX_ANALOG_IN_A;	//Set Opcode

					dataLength += 1;	//Add Channel indicator to payload length
					txUSBData[txUSBDataIndex++] = (dataLength >> 8);		//Set Packet Length
					txUSBData[txUSBDataIndex++] = (dataLength);				//Set Packet Length
					txUSBData[txUSBDataIndex++] = channel;					//Set Analog In Channel

					//Add payload
					txUSBDataIndex += dataLength;

					//Add CRC
					txUSBData[txUSBDataIndex++] = 0x00;
					txUSBData[txUSBDataIndex++] = 0x00;
				}
			}

			if(txUSBDataIndex > 1) {
				USBVCPWrite(txUSBData, txUSBDataIndex);
			}
		}
	}
}

void Error_Handler(void) {

}
