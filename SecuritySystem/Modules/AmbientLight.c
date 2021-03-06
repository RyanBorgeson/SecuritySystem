/**
 * Ambient light sensor methods for reading ADC values from external photoresistor.
 * @Author Ryan Borgeson
 * @Date 11/3/2016
 */
#include "AmbientLight.h"

void AmbientLight_Module_Init(void) {
	// Setup photoresistor pins to work with the ADC.
	GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);
	GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN5);
}


void AmbientLight_Module_Read(SensorData * Data) {

	// Reads ADC values for the photoresistor.
	Data->PhotoresistorADC = MAP_ADC14_getResult(ADC_MEM0);

	// Normalized photoresistor value.
	Data->Photoresistor = (Data->PhotoresistorADC * NORMALIZED_VOLTAGE) / 16384;

	// Control the brightness of the LED by settings
	// the calculated duty cycle.
	Data->LEDDutyCycle = (((Data->Photoresistor) / AMBIENT_MAX_VOLTAGE) * 100);

	// Enabling/Toggling Conversion
	MAP_ADC14_enableConversion();
	MAP_ADC14_toggleConversionTrigger();
}
