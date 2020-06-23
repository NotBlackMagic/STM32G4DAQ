#include "ada4254.h"

void ADA4254Init(uint8_t anBlock) {
	uint8_t data;

	//Set the GPIO Functions
	// -GPIO0/1 as Mux selector
	// -GPIO2 as Mux Enable
	// -GPIO4 CLK input (1 MHz)
	ADA4254WriteRegister(anBlock, GPIO_DIR, 0x07);	//Set GPIO Directions
	ADA4254WriteRegister(anBlock, SF_CFG, 0x03);	//Set GPIO Special Functions
//	ADA4254WriteRegister(anBlock, SYNC_CFG, Div_1);	//Set Input Clock division
	ADA4254WriteRegister(anBlock, GPIO_DATA, 0x04);	//Set GPIO Output Values

	//Disable Input Multiplexer Protection, allow IN1 and IN2 mixing
	data = MUX_PROT_DIS;
	ADA4254WriteRegister(anBlock, ANALOG_ERR_DIS, data);

	//Set Internal Mux connections: Set to IN1+ and IN1-
	data = SW_A1_MASK + SW_B2_MASK;
	ADA4254WriteRegister(anBlock, INPUT_MUX, data);

	//Set Input gain: 1/16; Output scaling: 1 V/V; External MUX: CH4 -> Channel 1
	data = ((Gain_1_8 << 3) & IN_AMP_GAIN_MASK) + (0x03 & EXT_MUX_MASK);
	ADA4254WriteRegister(anBlock, GAIN_MUX, data);
}

uint8_t ADA4254GetRevisionID() {
	uint16_t data = DIE_REV_ID | ADA4254_READ_MASK;

	data = data << 8;

	GPIOWrite(GPIO_OUT_AMPA_CS, 0);

	uint16_t rxData = SPI1ReadWrite(data);

	GPIOWrite(GPIO_OUT_AMPA_CS, 1);

	return (rxData & 0xFF);
}

uint8_t ADA4254SetCurrent(uint8_t anBlock, CurrentSource source, CurrentValue value) {
	uint8_t data = ((source << 6) & EX_CURRENT_SEL_MASK) + (value & EX_CURRENT_MASK);

	ADA4254WriteRegister(anBlock, EX_CURRENT_CFG, data);

	return 0;
}

void ADA4254WriteRegister(uint8_t anBlock, uint8_t reg, uint8_t data) {
	uint16_t txData = ((reg | ADA4254_WRITE_MASK) << 8) + (data & 0xFF);

	if(anBlock == ANALOG_IN_BLOCK_A) {
		GPIOWrite(GPIO_OUT_AMPA_CS, 0);
		SPI1ReadWrite(txData);
		GPIOWrite(GPIO_OUT_AMPA_CS, 1);
	}
	else if(anBlock == ANALOG_IN_BLOCK_B) {
		GPIOWrite(GPIO_OUT_AMPB_CS, 0);
		SPI3ReadWrite(txData);
		GPIOWrite(GPIO_OUT_AMPB_CS, 1);
	}
}

uint8_t ADA4254ReadRegister(uint8_t anBlock, uint8_t reg) {
	uint16_t rxData = 0;
	uint16_t txData = ((reg | ADA4254_READ_MASK) << 8);

	if(anBlock == ANALOG_IN_BLOCK_A) {
		GPIOWrite(GPIO_OUT_AMPA_CS, 0);
		rxData = SPI1ReadWrite(txData);
		GPIOWrite(GPIO_OUT_AMPA_CS, 1);
	}
	else if(anBlock == ANALOG_IN_BLOCK_B) {
		GPIOWrite(GPIO_OUT_AMPB_CS, 0);
		rxData = SPI3ReadWrite(txData);
		GPIOWrite(GPIO_OUT_AMPB_CS, 1);
	}

	return (rxData & 0xFF);
}
