#include "MainSequence.h"


const Timer_A_ContinuousModeConfig timeraConfig =
{
	TIMER_A_CLOCKSOURCE_ACLK,
	TIMER_A_CLOCKSOURCE_DIVIDER_1,
	TIMER_A_TAIE_INTERRUPT_ENABLE,
	TIMER_A_DO_CLEAR
};


void Main_Sequence(SensorData * Data) {

	// Main sequence settings.
	Data->State = MAIN;							// Setup the state of the system.
	int PreviousSecond = ClockRegisters[SECOND];		// Keeps track of the previous second.
	Display_Clear_Screen();						// Clears screen.


	while(1) {

		if (RefreshInterrupt) {
			RTC_Module_Read(&Data);
			RefreshInterrupt = 0;
		}

		switch(Data->State) {

			case MAIN:

				// Only execute ever second.
				if (PreviousSecond != ClockRegisters[SECOND]) {
					Display_Module_MainScreen(&Data);
					PreviousSecond = ClockRegisters[SECOND];
				}

				Keypad_Execute(Data);

				if (Data->KeyCombo[0] == '#') {
					Display_Clear_Screen();
					Data->State = MENU;
				}

				break;

			case MENU:

				Keypad_Execute(Data);

				if (PreviousSecond != ClockRegisters[SECOND]) {
					Display_Menu(Data);

					PreviousSecond = ClockRegisters[SECOND];
				}

				if (Data->KeyCombo[0] == '*') {
					Display_Clear_Screen();
					Data->State = MAIN;
				}

				break;

		}

	}
}



void TA0_0_IRQHandler(SensorData * Data) {

	RefreshInterrupt = 1;

    // Clear the compare interrupt flag
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
}
