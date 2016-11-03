/**
 * Ambient light sensor methods for reading ADC values from external photoresistor.
 * @Author Ryan Borgeson
 * @Date 11/3/2016
 */
#include "AmbientLight.h"


void AmbientLight_Module_Read(SensorData Data) {

	// Reads ADC values for the photoresistor.
	Data.PhotoresistorADC = MAP_ADC14_getResult(ADC_MEM0);

	// Normalized photoresistor value.
	Data.Photoresistor = (Data.PhotoresistorADC * NORMALIZED_VOLTAGE) / 16384;

	// Control the brightness of the LED by settings
	// the calculated duty cycle.
	Data.LEDDutyCycle = 100 - (((Data.Photoresistor) / AMBIENT_MAX_VOLTAGE) * 100);

	// Enabling/Toggling Conversion
	MAP_ADC14_enableConversion();
	MAP_ADC14_toggleConversionTrigger();
}
