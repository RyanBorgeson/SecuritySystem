#include "Startup.h"

// TODO: Startup sequence should contain tests to verify each
// sensor is working correctly.
void Startup_Sequence(SensorData * Data) {

	// Initialize and setup clocks and systick timer.
	Clock_Init();
	SysTick_Init();

	// Determine if clocks have been set up correctly.
	MCLKClockSpeed = CS_getMCLK();
	SMCLKClockSpeed = CS_getSMCLK();
	ACLKClockSpeed = CS_getACLK();


	// Initialize display to show a splash screen while warming up.
	Display_Init();

	// Display splash screen on startup.
	Display_Splash_Screen();


	// Delay splash screen for at least 2 seconds.
	SysTick_delay(SPLASH_DELAY);


	// Load main program sequence assuming startup passes all
	// initialization tests.
	Main_Sequence(&Data);

}
