#include "ada4254.h"

void ADA4254Init() {
	uint8_t data;

	//Set the GPIO Functions
	// -GPIO0/1 as Mux selector
	// -GPIO2 as Mux Enable
	// -GPIO4 Nothing yet
	ADA4254WriteRegister(GPIO_DIR, 0x07);	//Set GPIO Directions
	ADA4254WriteRegister(SF_CFG, 0x03);		//Set GPIO Special Functions
	ADA4254WriteRegister(GPIO_DATA, 0x04);	//Set GPIO Output Values

	//Set Internal Mux connections: Set to IN1+ and IN1-
	data = SW_A1_MASK + SW_A2_MASK;
	ADA4254WriteRegister(INPUT_MUX, data);

	//Set Input gain: 1; Output scaling: 1 V/V; External MUX: CH1
	data = ((Gain_1 << 3) & IN_AMP_GAIN_MASK) + (0x00 & EXT_MUX_MASK);
	ADA4254WriteRegister(GAIN_MUX, data);
}

uint8_t ADA4254GetRevisionID() {
	uint16_t data = DIE_REV_ID | ADA4254_READ_MASK;

	data = data << 8;

	GPIOWrite(GPIO_OUT_AMPA_CS, 0);

	uint16_t rxData = SPI1ReadWrite(data);

	GPIOWrite(GPIO_OUT_AMPA_CS, 1);

	return (rxData & 0xFF);
}

uint8_t ADA4254SetCurrent(CurrentValue value) {
	uint8_t data = ((Iout_HV << 6) & EX_CURRENT_SEL_MASK) + (value & EX_CURRENT_MASK);

	ADA4254WriteRegister(EX_CURRENT_CFG, data);

	uint8_t check = ADA4254ReadRegister(EX_CURRENT_CFG);

	if(data != check) {
		return 1;
	}

	return 0;
}

void ADA4254WriteRegister(uint8_t reg, uint8_t data) {
	uint16_t txData = ((reg | ADA4254_WRITE_MASK) << 8) + (data & 0xFF);

	GPIOWrite(GPIO_OUT_AMPA_CS, 0);
	SPI1ReadWrite(txData);
	GPIOWrite(GPIO_OUT_AMPA_CS, 1);
}

uint8_t ADA4254ReadRegister(uint8_t reg) {
	uint16_t txData = ((reg | ADA4254_READ_MASK) << 8);

	GPIOWrite(GPIO_OUT_AMPA_CS, 0);
	uint16_t rxData = SPI1ReadWrite(txData);
	GPIOWrite(GPIO_OUT_AMPA_CS, 1);

	return (rxData & 0xFF);
}
