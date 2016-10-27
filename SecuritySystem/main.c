#include "Config.h"


/* Function prototypes. */
void InitializeModules(void);

SensorData SensorReadings;

int main(void) 
{
    WDT_A_holdTimer();


    Clock_Init48MHz();
    HallEffect_Init();

    ST7735_InitR(INITR_REDTAB);
    ST7735_FillScreen(0x0000);

    while(1) {

    	HallEffect_Module_Read(&SensorReadings);

    	if (SensorReadings.HallEffect[0])
    		Display_Module_DrawString("Unlocked", ST7735_Color565(255, 0, 0), 20, 50, 1);
    	else
    		Display_Module_DrawString("Secured ", ST7735_Color565(25, 255, 0), 20, 50, 1);

    }
}

volatile uint32_t MCLKClockSpeed;
volatile uint32_t SMCLKClockSpeed;

void InitializeModules(void) {
	Clock_Init48MHz();

	MCLKClockSpeed = CS_getMCLK();
	SMCLKClockSpeed = CS_getSMCLK();

	HallEffect_Init();
	ADC_Init();
	UART_Init();
	I2C_Init();
}
