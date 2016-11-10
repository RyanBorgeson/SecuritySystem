/**
 * Configure and setup various internal and external clock sources and clock frequencies.
 * @Author Ryan Borgeson & TI MSP432 Technical Manual
 * @Date 11/3/2016
 */
#include "Clock.h"


void Clock_Init48MHz() {

	// Configuring pins for peripheral/crystal usage.
	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_PJ, GPIO_PIN3 | GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
	MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);

	// Sets the external clock source frequency which cna be read using getMCLK, and getSMCLK.
	CS_setExternalClockSourceFrequency(32000,EXTERNAL_CLOCK_SOURCE_FREQUENCY);

	// Starting HFXT in non-bypass mode without a timeout. Before we start
	// we have to change VCORE to 1 to support the 48MHz frequency.
	MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

	MAP_FlashCtl_setWaitState(FLASH_BANK0, 2);
	MAP_FlashCtl_setWaitState(FLASH_BANK1, 2);

	// False means that there are no timeouts set, will return when stable
	CS_startHFXT(false);

	// Initializing MCLK to HFXT (effectively 48MHz).
	MAP_CS_initClockSignal(CS_MCLK, CS_HFXTCLK_SELECT, CS_CLOCK_DIVIDER_1);

}

void SysTick_Init(void)
{
	// Disable SysTick during setup
	SysTick->CTRL = 0;
	// Maximum reload value
	SysTick->LOAD = 0x00FFFFFF;
	// Any write to current value clears it
	SysTick->VAL = 0;
	// Enable SysTick, CPU clk, no interrupts
	SysTick->CTRL = 0x00000005;
}

void SysTick_delay(uint16_t Delay)
{
	// Load value will also depend on MCLK clock frequency.
	SysTick->LOAD = ((Delay*16*3000) - 1);
	 // Any write to CVR clears it and COUNTFLAG in CSR
	SysTick->VAL = 0;
	// Wait for flag to be SET (Timeout happened)
	while((SysTick -> CTRL & 0x00010000) == 0);
}
