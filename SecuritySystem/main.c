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

int main(void) {

	// Startup system.
	Startup_Sequence(&SensorReadings);

	// Load main program sequence assuming startup passes all
	// initialization tests.
	Main_Sequence(&SensorReadings);

}
