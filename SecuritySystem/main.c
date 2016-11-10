#include "Config.h"


/* Function prototypes. */
void InitializeModules(void);

SensorData SensorReadings;

int main(void) 
{
    WDT_A_holdTimer();
    InitializeModules();


   // Startup_Sequence(&SensorReadings);

    while(1) {
    	Proximity_Module_Read(&SensorReadings);

    	if (SensorReadings.Proximity[0] > 0) {
    	    RGB_Module_SetColor(RED);
    		Display_Module_DrawString("Movement Detected    ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 30, 50, 1);
    	} else {
    	    RGB_Module_SetColor(GREEN);
    		Display_Module_DrawString("No Movement        ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 30, 50, 1);
    	}
    }
}

volatile uint32_t MCLKClockSpeed;
volatile uint32_t SMCLKClockSpeed;

void InitializeModules(void) {
	Clock_Init48MHz();

	MCLKClockSpeed = CS_getMCLK();
	SMCLKClockSpeed = CS_getSMCLK();

	Display_Init();

	RGB_Init();
	//SysTick_Init();
	//HallEffect_Init();
	Proximity_Init();
	//ADC_Init();
	//UART_Init();
	//I2C_Init();


}


