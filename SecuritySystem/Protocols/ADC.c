/**
 * Configures and sets up the ADC.
 */

#include "ADC.h"

void ADC_Init(void) {

	// TODO: Ensure the clock divider is set correctly. I think this is for 3Mhz.
	// Initializing ADC (MCLK/1/4)
	MAP_ADC14_enableModule();
	MAP_ADC14_initModule(ADC_CLOCKSOURCE_MCLK, ADC_PREDIVIDER_1, ADC_DIVIDER_4, 0);

	// Configuring GPIOs (5.5 A0)
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(ADC_PORT, ADC_PINS, GPIO_TERTIARY_MODULE_FUNCTION);

	// Configuring ADC Memory
	MAP_ADC14_configureSingleSampleMode(ADC_MEM0, true);
	MAP_ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A0, false);

	// Configuring Sample Timer
	MAP_ADC14_enableSampleTimer(ADC_MANUAL_ITERATION);
}
