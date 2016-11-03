#include "Config.h"


/* Function prototypes. */
void InitializeModules(void);

SensorData SensorReadings;

int main(void) 
{
    WDT_A_holdTimer();

    InitializeModules();



    while(1) {


    }
}

volatile uint32_t MCLKClockSpeed;
volatile uint32_t SMCLKClockSpeed;

void InitializeModules(void) {
	Clock_Init48MHz();

	MCLKClockSpeed = CS_getMCLK();
	SMCLKClockSpeed = CS_getSMCLK();

	SysTick_Init();
	HallEffect_Init();
	ADC_Init();
	UART_Init();
	I2C_Init();

	Display_Init();
}


