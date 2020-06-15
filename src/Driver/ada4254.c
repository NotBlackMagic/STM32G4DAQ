#include "ada4254.h"

void ADA4254SetCurrent(CurrentValue value) {
	uint8_t data[2];

	data[0] = EX_CURRENT_CFG | ADA4254_WRITE_MASK;
	data[1] = ((Iout_LV << 6) & EX_CURRENT_SEL_MASK) + (value & EX_CURRENT_MASK);

	GPIOWrite(GPIO_OUT_AMPA_CS, 0);

	SPI1ReadWrite(data[0]);
	SPI1ReadWrite(data[1]);

	GPIOWrite(GPIO_OUT_AMPA_CS, 1);
}

uint8_t ADA4254GetRevisionID() {
	uint8_t data = DIE_REV_ID | ADA4254_READ_MASK;


	GPIOWrite(GPIO_OUT_AMPA_CS, 0);

	SPI1ReadWrite(data);
	uint8_t byte = SPI1ReadWrite(0x00);

	GPIOWrite(GPIO_OUT_AMPA_CS, 1);

	return byte;
}
