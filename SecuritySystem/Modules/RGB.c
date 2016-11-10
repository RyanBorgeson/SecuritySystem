#include "RGB.h"


void RGB_Init(void) {

	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P2, GPIO_PIN0|GPIO_PIN1|GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
	GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
	GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
	GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);

}


void RGB_Module_SetColor(int Color) {

	switch (Color) {
	case RED:
		GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
		GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
		break;
	case MAGENTA:
		GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
		GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
		break;
	case BLUE:
		GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN2);
		GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1);
		break;
	case CYAN:
		GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1 | GPIO_PIN2);
		GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
		break;
	case GREEN:
		GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);
		GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN2);
		break;
	case YELLOW:
		GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1);
		GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
		break;
	case WHITE:
		GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
		break;
	case BLACK:
		GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
		break;
	}

}
