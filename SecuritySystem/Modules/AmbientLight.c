#include "AmbientLight.h"

volatile uint_fast16_t curADCResult,
			  Duty = 50,
			  CalculatedDuty;
volatile float normalizedADCRes;


void AmbientLight_Module_Read(void) {
	// Get ADC value from ADC memory.
	curADCResult = MAP_ADC14_getResult(ADC_MEM0);
	normalizedADCRes = (curADCResult * 3.3) / 16384;

	// Control the brightness of the LED by settings
	// the calculated duty cycle.
	CalculatedDuty = 100 - (((normalizedADCRes) / 2.4) * 100);

	// Enabling/Toggling Conversion
	MAP_ADC14_enableConversion();
	MAP_ADC14_toggleConversionTrigger();
}
