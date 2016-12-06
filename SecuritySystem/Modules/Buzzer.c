#include "Buzzer.h"


void Buzzer_Init(void) {

	// Setup up pin directions and non GPIO functions on P7.7.
	P6->DIR |= BIT6;
	P6->SEL0 |= BIT6;
	P6->SEL1 &= ~BIT6;

	// Setup PWM Waveform. CCR1 reset/set.
	TIMER_A2->CCR[0] = 1000 - 1;
	TIMER_A2->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
	TIMER_A2->CCTL[3] = TIMER_A_CCTLN_OUTMOD_7;

	TIMER_A2->CCR[3] = 0;
}

void Buzzer_Module_Off(void) {
	TIMER_A2->CCR[3] = 0;
}

void Buzzer_Module_SingleTone(void) {

	GPIO_setOutputHighOnPin(GPIO_PORT_P6, GPIO_PIN6);


}

void Buzzer_Module_ToggleTone(void) {

	if (TIMER_A2->CCR[3] == 100 || TIMER_A2->CCR[3] == 0) {
		TIMER_A2->CCR[3] = 500;
	} else {
		TIMER_A2->CCR[3] = 100;
	}

}
