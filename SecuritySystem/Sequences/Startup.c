#include "Startup.h"

// TODO: Startup sequence should contain tests to verify each
// sensor is working correctly.
void Startup_Sequence(SensorData * Data) {

	// Initialize and setup clocks and systick timer.
	Clock_Init();
	I2C_Init();
	ADC_Init();

	SysTick_Init();

	// Determine if clocks have been set up correctly.
	MCLKClockSpeed = CS_getMCLK();
	SMCLKClockSpeed = CS_getSMCLK();
	ACLKClockSpeed = CS_getACLK();



	// Attempt to enable master interrupts.
	//Interrupt_enableMaster();


	// Initialize display to show a splash screen while warming up.


	Display_Init();
	Proximity_Init();
	HallEffect_Init();
	Buzzer_Init();
	Wireless_Init();
	AmbientLight_Module_Init();
	Watchdog_Init();

	// Initialize additional modules.
	RGB_Init();
	RGB_Module_SetColor(GREEN);

	Keypad_Init(Data);

	// Display splash screen on startup.
	Display_Module_Backlight();
	Display_Splash_Screen();

	// Change PWM duty cycle.
	TIMER_A1->CCR[1] = 100 * 10;


	/* Setup and reading information from flash. */
	Flash_Module_Read(&Data->FlashStorage);
	strcpy(Data->SavedPIN, Data->FlashStorage.SavedPIN);


	NVIC->ISER[0] = 1 << ((TA0_0_IRQn) & 31);
	TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
	TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // TACCR0 interrupt enabled
	TIMER_A0->CCR[0] = 256;
	TIMER_A0->CTL = TIMER_A_CTL_SSEL__ACLK | TIMER_A_CTL_MC__UP;
	Interrupt_registerInterrupt(TA0_0_IRQn, TA0_0_IRQHandler(Data));

	Data->ArmedStatus = NOTARMED;

	//Interrupt_enableInterrupt(INT_EUSCIB1);


	// Delay splash screen for at least 2 seconds.
	SysTick_delay(SPLASH_DELAY);




}
