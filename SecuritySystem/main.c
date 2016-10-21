#include "driverlib.h"
#include "Protocols/I2C.h"
#include "Modules/RTC.h"


/* Function prototypes. */
void InitializeModules(void);

SensorData SensorReadings;


int main(void) 
{
    WDT_A_holdTimer();

    InitializeModules();

    while(1) {
    	RTC_Module_Read(&SensorReadings);

    	__delay_cycles(50);
    }
}

void InitializeModules(void) {
	I2C_Init();
}
