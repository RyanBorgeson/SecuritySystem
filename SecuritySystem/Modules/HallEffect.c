/**
 * Hall Effect sensor modules and functions.
 * These methods are used to gather sensor information from the
 * hall effect sensors.
 * @Author Ryan Borgeson
 * @Date 10/27/2016
 */
#include "HallEffect.h"



void HallEffect_Init(void) {
	// Set peripheral as primary module function.
	GPIO_setAsPeripheralModuleFunctionInputPin(HALL_EFFECT_PORT_1, HALL_EFFECT_PIN_1, GPIO_PRIMARY_MODULE_FUNCTION);
	GPIO_setAsPeripheralModuleFunctionInputPin(HALL_EFFECT_PORT_2, HALL_EFFECT_PIN_2, GPIO_PRIMARY_MODULE_FUNCTION);

	// Set as input with pull up resistor so the default value is HIGH.
	GPIO_setAsInputPinWithPullUpResistor(HALL_EFFECT_PORT_1, HALL_EFFECT_PIN_1);
	GPIO_setAsInputPinWithPullUpResistor(HALL_EFFECT_PORT_2, HALL_EFFECT_PIN_2);
}


void HallEffect_Module_Read(SensorData * Data) {
	// Store hall effect sensor data in the sensor data structure.
	Data->HallEffect[0] = GPIO_getInputPinValue(HALL_EFFECT_PORT_1, HALL_EFFECT_PIN_1);
	Data->HallEffect[1] = GPIO_getInputPinValue(HALL_EFFECT_PORT_2, HALL_EFFECT_PIN_2);
}
