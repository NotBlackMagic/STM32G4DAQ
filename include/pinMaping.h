#ifndef PINMAPING_H_
#define PINMAPING_H_

#ifdef __cplusplus
extern "C" {
#endif

//Fixed Input Pin Mapping

//Fixed Output Pin Mapping
#define GPIO_OUT_ADCA_CS					22		//Output ADC A CS
#define GPIO_OUT_AMPA_CS					23		//Output Amplifier A CS
#define GPIO_OUT_DACA_CS					50		//Output DAC A CS
#define GPIO_OUT_ADCAB_CS					38		//Output ADC B CS
#define GPIO_OUT_AMPB_CS					15		//Output Amplifier B CS
#define GPIO_OUT_DACB_CS					27		//Output DAC B CS
#define GPIO_OUT_STATUS_LED					24		//Output Status LED

//Flexible IO Pin Mapping
#define GPIO_IO_GPIO0						9		//Flexible IO Pin 0
#define GPIO_IO_GPIO1						10		//Flexible IO Pin 1
#define GPIO_IO_GPIO2						26		//Flexible IO Pin 2
#define GPIO_IO_GPIO3						18		//Flexible IO Pin 3
#define GPIO_IO_GPIO4						35		//Flexible IO Pin 4
#define GPIO_IO_GPIO5						32		//Flexible IO Pin 5
#define GPIO_IO_GPIO6						47		//Flexible IO Pin 6
#define GPIO_IO_GPIO7						46		//Flexible IO Pin 7
#define GPIO_IO_GPIO8						39		//Flexible IO Pin 8

//ADC Pin Mapping
#define	GPIO_ADC_A_INP						0		//ADC A Input Positive
#define	GPIO_ADC_A_INN						1		//ADC A Input Negative
#define	GPIO_ADC_B_INP						33		//ADC B Input Positive
#define	GPIO_ADC_B_INN						34		//ADC B Input Negative

//DAC Pin Mapping
#define GPIO_DAC_A_CH1						4		//DAC A Channel 1 Output
#define GPIO_DAC_A_CH2						5		//DAC A Channel 2 Output
#define GPIO_DAC_B_CH1						28		//DAC B Channel 1 Output
#define GPIO_DAC_B_CH2						8		//DAC B Channel 2 Output

#ifdef __cplusplus
}
#endif

#endif /* PINMAPING_H_ */
