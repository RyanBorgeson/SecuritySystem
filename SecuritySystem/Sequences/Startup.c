#include "Startup.h"

// TODO: Startup sequence should contain tests to verify each
// sensor is working correctly.
void Startup_Sequence(SensorData * Data) {

	// Initialize and setup clocks and systick timer.
	Clock_Init();

	I2C_Init();

	SysTick_Init();

	// Determine if clocks have been set up correctly.
	MCLKClockSpeed = CS_getMCLK();
	SMCLKClockSpeed = CS_getSMCLK();
	ACLKClockSpeed = CS_getACLK();



	// Initialize display to show a splash screen while warming up.


	Display_Init();

	// Initialize additional modules.
	RGB_Init();

	//RTC_Init();
	Keypad_Init(Data);

	// Display splash screen on startup.
	Display_Splash_Screen();


	// Attempt to enable master interrupts.
	Interrupt_enableMaster();
	//Interrupt_registerInterrupt(PORT2_IRQn, PORT2_IRQHandler());
	//Interrupt_registerInterrupt(PORT6_IRQn, PORT6_IRQHandler());
	//Interrupt_enableInterrupt(INT_PORT2);
	//Interrupt_registerInterrupt(PORT2_IRQn, PORT2_IRQHandler());
	//Interrupt_enableInterrupt(INT_PORT6);
	Interrupt_enableInterrupt(INT_EUSCIB1);

	// Delay splash screen for at least 2 seconds.
	SysTick_delay(SPLASH_DELAY);




}
