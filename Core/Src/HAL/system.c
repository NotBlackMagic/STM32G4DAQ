#include "system.h"

/**
  * @brief	This function initializes the VRef for both ADC and DAC
  * @param	vref: Set Vref as Input or output, when output set Vref voltage
  * @return	Error: 0 -> No Error, 1 -> Setting VRef output Voltage Error
  */
uint8_t SystemVrefEnable(SystemVRefVoltage vref) {
	//Enable Port Clocks
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	if(vref == VRef_Ext) {
		//Set VRef+ Pin as input, Buffer off and High-Z mode
		LL_VREFBUF_Disable();
		LL_VREFBUF_EnableHIZ();
	}
	else {
		//Set VRef Output Voltage
		if(vref == VRef_2048) {
			LL_VREFBUF_SetVoltageScaling(LL_VREFBUF_VOLTAGE_SCALE0);	//Set VRef to 2.048V
		}
		else if(vref == VRef_2500) {
			LL_VREFBUF_SetVoltageScaling(LL_VREFBUF_VOLTAGE_SCALE1);	//Set VRef to 2.5V
		}
		else {
			LL_VREFBUF_SetVoltageScaling(LL_VREFBUF_VOLTAGE_SCALE2);	//Set VRef to 2.9V
		}

		//Set VRef+ Pin as output VRef voltage, Buffer On
		LL_VREFBUF_Enable();
		LL_VREFBUF_DisableHIZ();

		//Wait for VRef Ready Flag, or timeout
		uint32_t timeout = GetSysTick();
		while((timeout + 1000) > GetSysTick() && LL_VREFBUF_IsVREFReady() == 0x00);

		if(LL_VREFBUF_IsVREFReady() == 0x00) {
			//VRef not Ready, something wrong
			return 1;
		}
	}

	return 0;
}
