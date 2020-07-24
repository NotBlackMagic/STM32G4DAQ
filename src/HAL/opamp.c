#include "opamp.h"

/**
  * @brief	This function initializes the OpAmp4 and respective GPIOs
  * @param	None
  * @return	None
  */
void OpAmp4Init() {
	//Init OpAmp as non-inverting follower connected to DAC
	LL_OPAMP_SetPowerMode(OPAMP4, LL_OPAMP_POWERMODE_NORMAL);
	LL_OPAMP_SetFunctionalMode(OPAMP4, LL_OPAMP_MODE_FOLLOWER);
	LL_OPAMP_SetInputNonInverting(OPAMP4, LL_OPAMP_INPUT_NONINVERT_DAC);
	LL_OPAMP_SetInputsMuxMode(OPAMP4, LL_OPAMP_INPUT_MUX_DISABLE);
	LL_OPAMP_SetInternalOutput(OPAMP4, LL_OPAMP_INTERNAL_OUPUT_DISABLED);
	LL_OPAMP_SetTrimmingMode(OPAMP4, LL_OPAMP_TRIMMING_FACTORY);

	//Enable OpAmp
	LL_OPAMP_Enable(OPAMP4);
}

/**
  * @brief	This function initializes the OpAmp4 and respective GPIOs
  * @param	None
  * @return	None
  */
void OpAmp5Init() {
	//Init OpAmp as non-inverting follower connected to DAC
	LL_OPAMP_SetPowerMode(OPAMP5, LL_OPAMP_POWERMODE_NORMAL);
	LL_OPAMP_SetFunctionalMode(OPAMP5, LL_OPAMP_MODE_FOLLOWER);
	LL_OPAMP_SetInputNonInverting(OPAMP5, LL_OPAMP_INPUT_NONINVERT_DAC);
	LL_OPAMP_SetInputsMuxMode(OPAMP5, LL_OPAMP_INPUT_MUX_DISABLE);
	LL_OPAMP_SetInternalOutput(OPAMP5, LL_OPAMP_INTERNAL_OUPUT_DISABLED);
	LL_OPAMP_SetTrimmingMode(OPAMP5, LL_OPAMP_TRIMMING_FACTORY);

	//Enable OpAmp
	LL_OPAMP_Enable(OPAMP5);
}
