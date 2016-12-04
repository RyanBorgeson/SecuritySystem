#include "MainSequence.h"


const Timer_A_ContinuousModeConfig timeraConfig =
{
	TIMER_A_CLOCKSOURCE_ACLK,
	TIMER_A_CLOCKSOURCE_DIVIDER_1,
	TIMER_A_TAIE_INTERRUPT_ENABLE,
	TIMER_A_DO_CLEAR
};

volatile int CurrentDigit = 0;

void Main_Sequence(SensorData * Data) {

	// Main sequence settings.
	Data->State = MAIN;							// Setup the state of the system.
	int PreviousSecond = ClockRegisters[SECOND];		// Keeps track of the previous second.
	Display_Clear_Screen();						// Clears screen.

	// Holds the current digit entered for a pin.

	volatile char PreviousKeyCombo;
	int ClockX = 0;

	while(1) {

		if (RefreshInterrupt) {
			RTC_Module_Read(&Data);
			ClockX+= 1;
			RefreshInterrupt = 0;
		}

		switch(Data->State) {

			case MAIN:
			{
				Keypad_Execute(Data);

				// Only execute ever second.
				if (RefreshInterrupt) {
					Display_Module_MainScreen(&Data, ClockX);
					PreviousSecond = ClockRegisters[SECOND];
				}

				if (Data->KeyCombo[0] == '#') {
					Display_Clear_Screen();
					Data->State = ENTERPIN;
				}

				break;
			}
			case ENTERPIN:
			{

				Keypad_ExecuteForPinEnter(Data, &CurrentDigit);

				// Only execute ever second.
				if (RefreshInterrupt) {
					Display_Module_EnterPIN(&Data, CurrentDigit);
				}

				int KeyComparison = EqualPins(Data->EnteredPIN, Data->SavedPIN);

				if (CurrentDigit == 4 && KeyComparison) {
					Data->EnteredPIN[0] = '\0';
					Data->State = MENU;
					CurrentDigit = 0;
					Display_Clear_Screen();
				}
				if (CurrentDigit == 4 && !KeyComparison) {
					Data->EnteredPIN[0] = '\0';
					Data->State = MAIN;
					CurrentDigit = 0;
					Display_Clear_Screen();
				}



			break;
			}
			case MENU:
			{
				Keypad_Execute(Data);

				if (RefreshInterrupt) {
					Display_Menu(Data);
				}


				if (Data->KeyCombo[0] == '3') {
					// TODO: Toggle unlocking or locking door.
					RGB_Module_SetColor(RED);
				} else if (Data->KeyCombo[0] == '2') {
					// TODO: Set Time & Date
				} else if (Data->KeyCombo[0] == '1') {
					// TODO: Set PIN
				} else {
					RGB_Module_SetColor(GREEN);
				}


				if (Data->KeyCombo[0] == '*') {
					Display_Clear_Screen();
					Data->State = MAIN;
				}

				break;
			}
			case SETPIN:
			{
				// TODO: Set pin state.
				break;
			}
			case SETTIME:
			{
				// TODO: Set time state.
				break;
			}
			case TOGGLELOCK:
			{
				// TODO: Toggle lock state.
				break;
			}

		}

	}
}



void TA0_0_IRQHandler(SensorData * Data) {

	RefreshInterrupt = 1;

    // Clear the compare interrupt flag
    TIMER_A0->CCTL[0] &= ~TIMER_A_CCTLN_CCIFG;
}

int EqualPins(char * SavedPin, char * EnteredPin) {
	return (SavedPin[0] == EnteredPin[0]) && (SavedPin[1] == EnteredPin[1]) && (SavedPin[2] == EnteredPin[2]) && (SavedPin[3] == EnteredPin[3]);
}
