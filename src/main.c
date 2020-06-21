#include "adc.h"
#include "dac.h"
#include "gpio.h"
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

	GPIOSetPinMode(GPIO_IO_GPIO0, GPIO_Mode_Output);

	TIM3Init();

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
	AnalogInInit();

	uint32_t timestamp = 0;

	uint8_t isVCPConnected = 0;
	uint8_t txUSBData[512];
	uint16_t txLength;
	uint8_t rxUSBData[512];
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
			uint16_t dataLength = AnalogInGetData(1, 1, &txUSBData[4]);
			if(dataLength != 0x00) {
				txUSBData[0] = OPCODE_TX_ANALOG_IN_A;	//Set Opcode
				txUSBData[1] = 0x00;	//Set Packet Length
				txUSBData[2] = 0x00;	//Set Packet Length
				txUSBData[3] = 0x01;	//Set Analog In Channel

				//Set Packet Length
				dataLength += 1;	//Add the channel number byte to length
				txUSBData[1] = (dataLength >> 8);
				txUSBData[2] = (dataLength);

				//Add CRC
				txUSBData[3 + dataLength] = 0x00;
				txUSBData[4 + dataLength] = 0x00;

				//Add Opcode, length and CRC bytes to length
				dataLength += 5;

				USBVCPWrite(txUSBData, dataLength);
			}
		}
	}
}

void Error_Handler(void) {

}
