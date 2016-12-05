#include "Buzzer.h"


void Buzzer_Init(void) {

	GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN6);
	GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN6);
}
void Buzzer_Module_SingleTone(void) {

	GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN6);


}

void Buzzer_Module_ToggleTone(void) {
	//GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P6, GPIO_PIN6, GPIO_PRIMARY_MODULE_FUNCTION);
	//GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN6);

	GPIO_toggleOutputOnPin(GPIO_PORT_P6, GPIO_PIN6);
}
