/**
 * Initializes and executes the home security system modules, 
 * protocols, and sequences. Startup procedures will be executed
 * here.
 * @Author Ryan Borgeson, Nick Borchardt, Chris Gaigalas
 * @Date 11/14/2016
 */
#include "Config.h"
#include <stdio.h>

SensorData SensorReadings;



volatile uint32_t MCLKClockSpeed;
volatile uint32_t SMCLKClockSpeed;
volatile uint32_t ACLKClockSpeed, PIN, ButtonState;


int main(void) {


}

void InitializeModules(void) {
	Clock_Init48MHz();
		Display_Init();
	MCLKClockSpeed = CS_getMCLK();
	SMCLKClockSpeed = CS_getSMCLK();
	ACLKClockSpeed = CS_getACLK();


		SysTick_Init();
	//RGB_Init();

	//HallEffect_Init();
	//Proximity_Init();
	//ADC_Init();
	//UART_Init();
	//I2C_Init();


}


