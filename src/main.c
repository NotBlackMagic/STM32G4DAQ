#include "gpio.h"
#include "rcc.h"
#include "spi.h"
#include "uart.h"
#include "usb_vcp.h"

#include "pinMaping.h"

int main(void) {
	//Configure the system clock
	SystemClockInit();
	SystemTickInit();

	//Initialize all configured peripherals
	GPIOInit();
	USBVCPInit();
	SPI1Init();
	SPI2Init();
	SPI3Init();
	UART1Init();

	//Turn Status LED on
	GPIOWrite(GPIO_OUT_STATUS_LED, 0x01);

	while(1) {

	}
}

void Error_Handler(void) {

}
