/**
 * Proximity sensors detect motion or movement from a 10 foot distance. This
 * initializes pins, pull-up resistors, and reads input from the pins.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */
#include "Proximity.h"


void Proximity_Init(void) {
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN4, GPIO_PRIMARY_MODULE_FUNCTION);
	GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN4);
}

void Proximity_Module_Read(SensorData * Data) {
	Data->Proximity[0] = GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN4);
}
