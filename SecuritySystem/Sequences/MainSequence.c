#include "MainSequence.h"


const Timer_A_ContinuousModeConfig timeraConfig =
{
	TIMER_A_CLOCKSOURCE_ACLK,
	TIMER_A_CLOCKSOURCE_DIVIDER_1,
	TIMER_A_TAIE_INTERRUPT_ENABLE,
	TIMER_A_DO_CLEAR
};

volatile int CurrentDigit = 0;

// Used specifically for handling set time and date.
uint8_t SetDateTime[6] = { 0, 0, 0, 0, 0, 0 };
int SetTimeCounter = 0, PreviousDigit = 0;
char SetTimeDigits[2];

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

				if (Data->KeyCombo[0] == '*') {
					CurrentDigit = 0;
					Display_Clear_Screen();
					Data->State = MAIN;
				}

			break;
			}
			case MENU:
			{
				// Determine if an options have already been chosen.
				uint8_t ToggleOptions = 0;

				Keypad_Execute(Data);

				if (RefreshInterrupt) {
					Display_Menu(Data);
				}


				if (Data->KeyCombo[0] == '3') {
					// TODO: Toggle unlocking or locking door.
					RGB_Module_SetColor(RED);

					Flash_Module_PushDateTimeUp(&Data->FlashStorage.DateInformation);
					Flash_Module_SaveToFlash(&Data->FlashStorage);

					// Ensures that this state does not get toggle again.
					Data->KeyCombo[0] = '\0;';

				} else if (Data->KeyCombo[0] == '2') {
					// TODO: Set Time & Date
					Display_Clear_Screen();
					Data->State = SETTIME;
					Data->KeyCombo[0] = '0';
					Data->KeyCombo[1] = '0';
				} else if (Data->KeyCombo[0] == '1') {
					// TODO: Set PIN
					Display_Clear_Screen();
					Data->State = SETPIN;
				} else if (Data->KeyCombo[0] == '4') {
					Display_Clear_Screen();
					Data->State = VIEWLOGS;
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
				Keypad_ExecuteForPinEnter(Data, &CurrentDigit);

				if (RefreshInterrupt) {
					Display_Module_SetPIN(Data, CurrentDigit);
				}

				if (CurrentDigit == 4) {
					strncpy(Data->SavedPIN, Data->EnteredPIN, sizeof(Data->SavedPIN));
					strncpy(Data->FlashStorage.SavedPIN, Data->EnteredPIN, sizeof(Data->SavedPIN));
					Flash_Module_SaveToFlash(&Data->FlashStorage);
					CurrentDigit = 0;
					Display_Clear_Screen();
					Data->State = MAIN;
				}

				break;
			}
			case SETTIME:
			{



				// TODO: Set time state.
				Keypad_ExecuteForPinEnter(Data, &CurrentDigit);

				if (RefreshInterrupt) {
					Display_Module_SetTime(Data, CurrentDigit, SetTimeCounter);
				}

				if (CurrentDigit == 2) {
					Display_Module_SetTime(Data, CurrentDigit, SetTimeCounter);
					SetDateTime[SetTimeCounter] = ((Data->KeyCombo[1] - 48) << 4) | (Data->KeyCombo[0] - 48);

					Data->KeyCombo[0] = '0';
					Data->KeyCombo[1] = '0';
					SysTick_delay(20000);

					CurrentDigit = 0;
					SetTimeCounter++;
				}

				if (SetTimeCounter == 6) {
					RTC_Module_Write(SetDateTime[5], SetDateTime[4], SetDateTime[3], SetDateTime[2], SetDateTime[1], SetDateTime[0]);
					SetTimeCounter = 0;
					Data->KeyCombo[0] = '\0';
					CurrentDigit = 0;
					Display_Clear_Screen();
					Data->State = MAIN;
				}


				// Pressing the * will return users to the menu.
				if (Data->KeyCombo[0] == '*') {
					SetTimeCounter = 0;
					Data->KeyCombo[0] = '\0';
					CurrentDigit = 0;
					Display_Clear_Screen();
					Data->State = MENU;
				}

				break;
			}
			case VIEWLOGS:
			{
				// TODO: Set time state.
				Keypad_Execute(Data);

				if (PreviousSecond != ClockRegisters[SECOND]) {
					Display_Module_ViewLogs(Data);
					PreviousSecond = ClockRegisters[SECOND];
				}

				// Pressing the * will return users to the menu.
				if (Data->KeyCombo[0] == '*') {
					Display_Clear_Screen();
					Data->KeyCombo[0] = '\0';
					Data->State = MENU;
				}

				break;
			}
			case TOGGLELOCK:
			{
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
