#include "Config.h"


/* Function prototypes. */
void InitializeModules(void);

SensorData SensorReadings;


int main(void) 
{
    WDT_A_holdTimer();

    InitializeModules();

    while(1) {
    	RTC_Module_Read(&SensorReadings);
    	AmbientLight_Module_Read();

    	__delay_cycles(50);
    }
}

volatile uint32_t MCLKClockSpeed;
volatile uint32_t SMCLKClockSpeed;

void InitializeModules(void) {
	Clock_Init48MHz();

	MCLKClockSpeed = CS_getMCLK();
	SMCLKClockSpeed = CS_getSMCLK();

	I2C_Init();
	ADC_Init();
}
