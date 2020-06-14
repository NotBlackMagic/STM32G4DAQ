#ifndef DRIVER_ADA4254_REGS_H_
#define DRIVER_ADA4254_REGS_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

#define ADA4254_WRITE_MASK			0x00
#define ADA4254_READ_MASK			0x80

#define GAIN_MUX					0x00	//GAIN_MUX Register
#define OUT_SCAL_1375_MASK			0x80	//Output Amplifier Scaling Gain Mask: G4 (1.375 V/V)
#define IN_AMP_GAIN_MASK			0x78	//Input Amplifier Gain setting Mask: G[3:0]
#define EXT_MUX_MASK				0x03	//External Multiplexer Control Mask (GPIO0 & GPIO1)
typedef enum {
	Gain_1_16,
	Gain_1_8,
	Gain_1_4,
	Gain_1_2,
	Gain_1,
	Gain_2,
	Gain_4,
	Gain_8,
	Gain_16,
	Gain_32,
	Gain_64,
	Gain_128
} InputGain;

#define RESET						0x01	//Software Reset Register
#define RESET_MASK					0x01	//Software Reset Bit Mask

#define SYNC_CFG					0x02	//Clock Sync Configuration Register
#define CLK_OUT_SEL_MASK			0x40	//Clock Output Select Mask
#define SYNC_POL_MASK				0x10	//Clock Synchronization Polarity Mask
#define SYNC_DIV_MASK				0x07	//Internal Clock Divider Mask
typedef enum {
	Div_1,
	Div_2,
	Div_4,
	Div_8,
	Div_16,
	Div_32
} SyncClkDiv;

#define DIGITAL_ERR					0x03	//Digital Error Register
typedef union {
	struct {
		uint8_t none0 : 1;			//Reserved
		uint8_t calBusy : 1;		//Calibration Busy Flag
		uint8_t spiCRCErr : 1;		//SPI CRC Error Flag
		uint8_t spiRWErr : 1;		//SPI Read/Write Error Flag
		uint8_t spiSCLKCntErr : 1;	//SPI SCLK Count Error Flag
		uint8_t none1 : 1;			//Reserved
		uint8_t memMapCRCErr : 1;	//Memory Map CRC Error Flag
		uint8_t romCRCErr : 1;		//ROM CRC Error Flag
	};
	uint8_t raw;
} DigitalError;

#define ANALOG_ERR					0x04	//Analog Error Register
typedef union {
	struct {
		uint8_t gainRest : 1;		//Gain Reset Flag
		uint8_t porHV : 1;			//Power-On Reset HV Supply Flag
		uint8_t none0 : 1;			//Reserved
		uint8_t wbErr : 1;			//Wire Break Detector Error Flag
		uint8_t faultInt : 1;		//Fault Interrupt Flag
		uint8_t outAmpErr : 1;		//Output Amplifier Error Flag
		uint8_t inAmpErr : 1;		//Input Amplifier Error Flag
		uint8_t muxOVErr : 1;		//Input Multiplexer Overvoltage Error Flag
	};
	uint8_t raw;
} AnalogError;

#define GPIO_DATA					0x05	//GPIO Data Register

#define INPUT_MUX					0x06	//Internal Mux Control Register
#define SW_A1_MASK					0x40	//Channel 1 Input Switch 1 Mask
#define SW_A2_MASK					0x20	//Channel 1 Input Switch 2 Mask
#define SW_B1_MASK					0x10	//Channel 2 Input Switch 1 Mask
#define SW_B2_MASK					0x08	//Channel 2 Input Switch 2 Mask
#define SW_C1_MASK					0x04	//PGIA Input Test Switch 1 Mask
#define SW_C2_MASK					0x02	//PGIA Input Test Switch 2 Mask
#define SW_D12_MASK					0x01	//PGIA Input Short Switch Mask

#define WB_DETECT					0x07	//Wire Break Detection Register
#define WB_G_RST_DIS_MASK			0x80	//Wire Break Gain Reset Disable Mask
#define SW_F1_MASK					0x08	//Fault Switch 1 Mask
#define SW_F2_MASK					0x04	//Fault Switch 2 Mask
#define WB_CURRENT_MASK				0x03	//Detection Current Selection
typedef enum {
	Curr_250nA,
	Curr_2uA,
	Curr_4uA,
	Curr_16uA
} WBCurrent;

#define GPIO_DIR					0x08	//GPIO Direction Register

#define SCS							0x09	//Sequential CS Register

#define ANALOG_ERR_DIS				0x0A	//Analog Error Mask Register
typedef union {
	struct {
		uint8_t gainRestMask : 1;	//Gain Reset Flag Mask
		uint8_t porHVMask : 1;		//Power-On Reset HV Supply Flag Mask
		uint8_t none0 : 1;			//Reserved
		uint8_t wbErrMask : 1;		//Wire Break Detector Error Flag Mask
		uint8_t faultIntMask : 1;	//Fault Interrupt Flag Mask
		uint8_t outAmpErrMask : 1;	//Output Amplifier Error Flag Mask
		uint8_t inAmpErrMask : 1;	//Input Amplifier Error Flag Mask
		uint8_t muxOVErrMask : 1;	//Input Multiplexer Overvoltage Error Flag Mask
	};
	uint8_t raw;
} AnalogErrorMask;

#define DIGITAL_ERR_DIS				0x0B	//Digital Error Mask Register
typedef union {
	struct {
		uint8_t none0 : 1;				//Reserved
		uint8_t calBusyMask : 1;		//Calibration Busy Flag Mask
		uint8_t spiCRCErrMask : 1;		//SPI CRC Error Flag Mask
		uint8_t spiRWErrMask : 1;		//SPI Read/Write Error Flag Mask
		uint8_t spiSCLKCntErrMask : 1;	//SPI SCLK Count Error Flag Mask
		uint8_t none1 : 1;				//Reserved
		uint8_t memMapCRCErrMask : 1;	//Memory Map CRC Error Flag Mask
		uint8_t romCRCErrMask : 1;		//ROM CRC Error Flag Mask
	};
	uint8_t raw;
} DigitalErrorMask;

#define SF_CFG						0x0C	//Special Function Configuration Register
#define INT_CLK_OUT_MASK			0x20	//Internal Oscillator Output on GPIO4 Mask
#define EXT_CLK_IN_MASK				0x10	//External Oscillator Input on GPIO4 Mask
#define FAULT_INT_OUT_MASK			0x08	//Fault Interrupt Output on GPIO3 Mask
#define CAL_BUSY_OUT_MASK			0x04	//Calibration Busy Output on GPIO2 Mask
#define EXT_MUX_EN_MASK				0x03	//Enable External Multiplexer Control on GPIO0 and GPIO1 Mask

#define ERR_CFG						0x0D	//Error Configuration Register
#define ERR_LATCH_DIS_MASK			0x80	//Disable Error Latching Mask
#define ERR_DELAY_MASK				0x0F	//Error Suppression Time Mask
typedef enum {
	Sup_0us,
	Sup_1us,
	Sup_2us,
	Sup_3us,
	Sup_4us,
	Sup_5us,
	Sup_6us,
	Sup_7us,
	Sup_8us,
	Sup_12us,
	Sup_16us,
	Sup_24us,
	Sup_32us,
	Sup_48us,
	Sup_64us,
	Sup_127us
} ErrorSupTime;

#define TEST_MUX					0x0E	//Test Multiplexer Register
#define OUT_SCAL_125_MASK			0x80	//Output Amplifier Scaling Gain Mask: G5 (1.25 V/V or 1 V/V)
#define CAL_SEL_MASK				0x40	//Calibration Type Configuration Mask
#define CAL_EN_MASK					0x30	//Schedule Calibration Enable and Interval Mask
typedef enum {
	Disabled,			//Disabled
	Enabled_33s,		//Enabled, 33 second Interval
	Enabled_132s,		//Enabled, 132 second Interval
	Enable_495s,		//Enabled, 495 second Interval
} CalENInterval;
#define TEST_MUX_MASK				0x0F	//Input Test Multiplexer Configuration Mask
typedef enum {
	AVSS_AVSS = 0,		//Non-inverting: AVSS; Inverting: AVSS
	DVSS_AVSS = 1,		//Non-inverting: DVSS; Inverting: AVSS
	AVSS_DVSS = 4,		//Non-inverting: AVSS; Inverting: DVSS
	DVSS_DVSS = 5,		//Non-inverting: DVSS; Inverting: DVSS
	Pos_20mV = 10,		//Non-inverting and Inverting: +20mV
	Neg_20mV = 15		//Non-inverting and Inverting: -20mV
} InTestMuxCfg;

#define EX_CURRENT_CFG				0x0F	//Excitation Current Configuration Register
#define EX_CURRENT_SEL_MASK			0xC0	//Excitation Current Connection Configuration Mask
typedef enum {
	None,
	Iout_LV,
	Iout_HV
} CurrentSource;
#define EX_CURRENT_MASK				0x0F	//Excitation Current Value Mask
typedef enum {
	Curr_0uA,
	Curr_100uA,
	Curr_200uA,
	Curr_300uA,
	Curr_400uA,
	Curr_500uA,
	Curr_600uA,
	Curr_700uA,
	Curr_800uA,
	Curr_900uA,
	Curr_1mA,
	Curr_1mA1,
	Curr_1mA2,
	Curr_1mA3,
	Curr_1mA4,
	Curr_1mA5,
} CurrentValue;

#define GAIN_CAL1					0x10	//Gain Calibration 1/16x1V/V Register
#define GAIN_CAL2					0x11	//Gain Calibration 1/8x1V/V Register
#define GAIN_CAL3					0x12	//Gain Calibration 1/4x1V/V Register
#define GAIN_CAL4					0x13	//Gain Calibration 1/2x1V/V Register
#define GAIN_CAL5					0x14	//Gain Calibration 1x1V/V Register
#define GAIN_CAL6					0x15	//Gain Calibration 2x1V/V Register
#define GAIN_CAL7					0x16	//Gain Calibration 4x1V/V Register
#define GAIN_CAL8					0x17	//Gain Calibration 8x1V/V Register
#define GAIN_CAL9					0x18	//Gain Calibration 16x1V/V Register
#define GAIN_CAL10					0x19	//Gain Calibration 32x1V/V Register
#define GAIN_CAL11					0x1A	//Gain Calibration 64x1V/V Register
#define GAIN_CAL12					0x1B	//Gain Calibration 128x1V/V Register
#define GAIN_CAL13					0x1C	//Gain Calibration 1/16x1.375V/V or 1/8x1.375V/V Register
#define GAIN_CAL14					0x1D	//Gain Calibration 1/4x1.375V/V or 1/2x1.375V/V Register
#define GAIN_CAL15					0x1E	//Gain Calibration 1x1.375V/V or 2x1.375V/V Register
#define GAIN_CAL16					0x1F	//Gain Calibration 4x1.375V/V or 8x1.375V/V Register
#define GAIN_CAL17					0x20	//Gain Calibration 16x1.375V/V or 32x1.375V/V Register
#define GAIN_CAL18					0x21	//Gain Calibration 64x1.375V/V or 128x1.375V/V Register
#define GAIN_CAL19					0x22	//Gain Calibration 1/16x1.25V/V or 1/8x1.25V/V Register
#define GAIN_CAL20					0x23	//Gain Calibration 1/4x1.25V/V or 1/2x1.25V/V Register
#define GAIN_CAL21					0x24	//Gain Calibration 1x1.25V/V or 2x1.25V/V Register
#define GAIN_CAL22					0x25	//Gain Calibration 4x1.25V/V or 8x1.25V/V Register
#define GAIN_CAL23					0x26	//Gain Calibration 16x1.25V/V or 32x1.25V/V Register
#define GAIN_CAL24					0x27	//Gain Calibration 64x1.25V/V or 128x1.25V/V Register

#define TRIG_CAL					0x2A	//Trigger Calibration Register
#define TRIG_CAL_MASK				0x01	//Trigger Calibration Bit Mask

#define M_CLK_CNT					0x2E	//Master Clock Count Register

#define DIE_REV_ID					0x2F	//Die Revision Identification Register

#define PART_ID_BYTE_4				0x64	//Device ID [39:32] Register
#define PART_ID_BYTE_3				0x65	//Device ID [31:24] Register
#define PART_ID_BYTE_2				0x66	//Device ID [23:16] Register
#define PART_ID_BYTE_1				0x67	//Device ID [15:8] Register
#define PART_ID_BYTE_0				0x68	//Device ID [7:0] Register

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_ADA4254_REGS_H_ */
