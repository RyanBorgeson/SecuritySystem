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

const eUSCI_UART_Config uartConfig =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK,          // SMCLK Clock Source
    78,                                     // BRDIV = 78
    2,                                       // UCxBRF = 2
    0,                                       // UCxBRS = 0
    EUSCI_A_UART_NO_PARITY,                  // No Parity
    EUSCI_A_UART_LSB_FIRST,                  // MSB First
    EUSCI_A_UART_ONE_STOP_BIT,               // One stop bit
    EUSCI_A_UART_MODE,                       // UART mode
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION  // Oversampling
};




volatile uint32_t MCLKClockSpeed;
volatile uint32_t SMCLKClockSpeed;
volatile uint32_t ACLKClockSpeed, PIN, ButtonState;


int main(void) {

	char Seconds[100], NonSeconds[100];
	int TimeCounter = 0;
	int NonWatchDog = 0;


	Clock_Init48MHz();
	Display_Init();
	CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_4);

	Port1_Init();

	GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
	Delay1ms(1000);
	GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN0);


	WDT_A_initWatchdogTimer(WDT_A_CLOCKSOURCE_ACLK, WDT_A_CLOCKITERATIONS_32K);
	WDT_A_setTimeoutReset(WDT_A_SOFT_RESET);
	WDT_A_startTimer();

	while (1) {
		if ((!GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) > 0)) {
			TimeCounter = 0;
			WDT_A_clearTimer();
		} else {

			sprintf(Seconds, "%d", TimeCounter);
			sprintf(NonSeconds, "%d", NonWatchDog);

			Display_Module_DrawString("Counter", ST7735_Color565(255,255,255), ST7735_Color565(0,0,0), 10, 10, 1);
			Display_Module_DrawString(Seconds, ST7735_Color565(255,255,255), ST7735_Color565(0,0,0), 10, 50, 2);
			Display_Module_DrawString(NonSeconds, ST7735_Color565(255,255,255), ST7735_Color565(0,0,0), 10, 70, 2);

			TimeCounter++;
			NonWatchDog++;
			Delay1ms(1000);
		}
	}
}

/**
 * Consolidated all Port 1 initialization and configuration into this
 * method. Sets up button pins and LED pins on Port 1.
 */
void Port1_Init() {
	// Configure P1.4 as a GPIO.
	P1->SEL0 &= ~BIT4;
	P1->SEL1 &= ~BIT4;

	// Enable pull resistor for P1.4.
	P1->REN |= BIT4;

	// Set P1.4 as an input and P1.0 as an output.
	P1->DIR &= ~BIT4;

}


/**
 * Debounce switch determines if P1.4 has been pressed and
 * accounts for any bouncing.
 */
uint8_t DebounceSwitch()
{
	static uint16_t State = 0; // Current debounce status

	// Read switch, upper 5 bits of State are don't cares
	State = (State << 1) | (P1IN & BIT4) >> 1 | 0xf800;

	// Indicates 0 level is stable for 10 consecutive calls
	return (State == 0xfc00);
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


