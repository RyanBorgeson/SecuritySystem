/**
 * The buzzzer module provides audible feedback by providing options
 * to toggle between tones or play a single tone on the buzzer.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */
#include "Buzzer.h"


void Buzzer_Init(void) {

	// Setup buzzer output pins.
	P6->DIR |= BIT6;
	P6->SEL0 |= BIT6;
	P6->SEL1 &= ~BIT6;

	// Setup PWM Waveform using SMCLK as the clocksource.
	TIMER_A2->CCR[0] = 1000 - 1;
	TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
	TIMER_A2->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;

	// Initially set the PWM signal to be zero or off.
	TIMER_A2->CCR[3] = 0;
}

void Buzzer_Module_Off(void) {
	// Turn off the buzzer by reversing the pin direction.
	P6->DIR &= ~BIT6;

	// Set PWM to zero.
	TIMER_A2->CCR[3] = 0;
	GPIO_setOutputLowOnPin(GPIO_PORT_P6, GPIO_PIN6);

}

void Buzzer_Module_SingleTone(void) {
	// Perform one tone.
	GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN6);
}

void Buzzer_Module_On(void) {
	// Turn the buzzer on.
	P6->DIR |= BIT6;
}

void Buzzer_Module_ToggleTone(void) {
	// Toggle between a high and low frequency.
	TIMER_A2->CCR[3] = (TIMER_A2->CCR[3] == 100 || TIMER_A2->CCR[3] == 0) ? 500 : 100;
}
