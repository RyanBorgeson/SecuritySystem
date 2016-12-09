#include "MainSequence.h"



volatile int CurrentDigit = 0;

// Used specifically for handling set time and date.
uint8_t SetDateTime[6] = { 0, 0, 0, 0, 0, 0 };
int SetTimeCounter = 0, PreviousDigit = 0;
char SetTimeDigits[2];

void Main_Sequence(SensorData * Data) {

	// Main sequence settings.
	Data->State = MAIN;									// Setup the state of the system.
	int PreviousSecond = ClockRegisters[SECOND];		// Keeps track of the previous second.
	int MasterPreviousSecond = ClockRegisters[SECOND];
	int SecondsCounter = 0;
	Display_Clear_Screen();								// Clears screen.

	// Current ClockX location.
	static int ClockX = 0;

	// Main loop that executes and handles the main security system functions.
	while(1) {

		// Contains calls that need to be updated only every second.
		// Sensor readings and alerts are updated every second with new warning
		// messages or system alerts.
		if (MasterPreviousSecond != ClockRegisters[SECOND]) {
			GatherSensorData(Data);
			Alerts(Data);
			SecondsCounter++;
			Data->MinuteCounter++;

			MasterPreviousSecond = ClockRegisters[SECOND];
		}



		// Only make an api call every three seconds.
		if (SecondsCounter == 3) {
			SendPostRequest(Data);
			SecondsCounter = 0;

			if (Data->State == MAIN)
				Display_Module_MainScreen(Data, ClockX);
		}

		// Reset to the main screen if there is no input from the user
		// for one minute.
		if (Data->MinuteCounter >= 60 && Data->State != MAIN) {
			Data->State = MAIN;
			Display_Clear_Screen();
			Data->MinuteCounter = 0;
			Data->KeyCombo[LAST_KEY] = 0;
		}

		// Refresh interrupt handles functions that need to be updated frequently.
		// Such as update clock position and reading the new time from the RTC.
		if (RefreshInterrupt) {
			ClockX += 1;
			Display_Module_UpdateBacklight(Data);
			RTC_Module_Read(&Data);


			// Regularly clear the watchdog timer so the system
			// does not reset.
			Watchdog_Clear();

			RefreshInterrupt = 0;
		}

		// Giant state machine that contains all possible states the system
		// will ever be in.
		switch(Data->State) {

			// Main state where the user will be initially brought to upon booting
			// up the security system.
			case MAIN:
			{

				// Check for input from the keypad.
				Keypad_Execute(Data);

				// Update the display on every refresh interrupt.
				if (RefreshInterrupt) {
					Display_Module_MainScreen(Data, ClockX);
				}

				// If the user selects the menu options, change states and
				// clear the screen.
				if (Data->KeyCombo[LAST_KEY] == '#') {
					Display_Clear_Screen();
					Data->State = ENTERPIN;
				}

				break;
			}

			// Enter pin state where the user must enter the pin to continue on to
			// the options menu. Entering the pin here will also disable the alarm.
			case ENTERPIN:
			{
				// Check for user input on the keypad.
				Keypad_ExecuteForPinEnter(Data, &CurrentDigit);

				// Update the display on a refresh interrupt.
				if (RefreshInterrupt) {
					Display_Module_EnterPIN(&Data, CurrentDigit);
				}

				// Check and see if the entered pins match.
				int KeyComparison = EqualPins(Data->EnteredPIN, Data->SavedPIN);

				// If the pin was entered correctly, move onto the menu state.
				if (CurrentDigit == 4 && KeyComparison) {
					Data->KeyCombo[LAST_KEY] = '\0';
					Data->State = MENU;
					CurrentDigit = 0;
					Display_Clear_Screen();
				}

				// If the pin was entered incorrectly move back to the main state.
				if (CurrentDigit == 4 && !KeyComparison) {
					Data->KeyCombo[LAST_KEY] = '\0';
					Data->State = MAIN;
					CurrentDigit = 0;
					Display_Clear_Screen();
				}

				// If the user selects the back option, return the main screen.
				if (Data->KeyCombo[0] == '*') {
					CurrentDigit = 0;
					Display_Clear_Screen();
					Data->State = MAIN;
				}


				break;
			}

			// The menu state where the user will have the option to chance pin,
			// update time, lock and unlock door, and view activity logs.
			case MENU:
			{
				// Determine if an options have already been chosen.
				uint8_t ToggleOptions = 0;

				// This should quite any alarms.
				GatherSensorData(Data);
				Alerts(Data);

				// Just in case, turn of the buzzer...
				Buzzer_Module_Off();

				// Check for user input from the keypad.
				Keypad_Execute(Data);

				// Update display with menu options.
				if (PreviousSecond != ClockRegisters[SECOND]) {
					Display_Menu(Data);
					PreviousSecond = ClockRegisters[SECOND];
				}

				// Check to see which item the user has chosen.
				if (Data->KeyCombo[LAST_KEY] == '3') {
					Data->State = TOGGLELOCK;

					// Ensures that this state does not get toggle again.
					Data->KeyCombo[LAST_KEY] = 0;

				} else if (Data->KeyCombo[LAST_KEY] == '2') {

					// Clears the screen and sends the user to the set time state.
					Display_Clear_Screen();
					Data->State = SETTIME;
					Data->KeyCombo[0] = '-';
					Data->KeyCombo[1] = '-';

				} else if (Data->KeyCombo[LAST_KEY] == '1') {

					Display_Clear_Screen();
					Data->State = SETPIN;

				} else if (Data->KeyCombo[LAST_KEY] == '4') {

					Display_Clear_Screen();
					CurrentDigit = 0;
					Data->State = VIEWLOGS;

				} else if (Data->KeyCombo[LAST_KEY] == '5') {

					Data->ArmedStatus = Data->ArmedStatus == NOTARMED ? ARMED : NOTARMED;
					RGB_Module_SetColor(Data->ArmedStatus == NOTARMED ? GREEN : RED);

					if (Data->ArmedStatus == NOTARMED)
					{
						// Update flash with the time the door was unlocked.
						Flash_Module_PushDateTimeUp(&Data->FlashStorage.DisarmTimes);
						Flash_Module_SaveToFlash(&Data->FlashStorage);
					}
					if (Data->ArmedStatus == ARMED)
					{
						// Set the minute counter to zero.
						Data->MinuteCounter = 0;
						Data->State = ARMING;

						// Update flash with the time the door was unlocked.
						Flash_Module_PushDateTimeUp(&Data->FlashStorage.ArmTimes);
						Flash_Module_SaveToFlash(&Data->FlashStorage);
					}

					Data->KeyCombo[LAST_KEY] = 0;

					Display_Clear_Screen();

				}
				// If the user chooses to go back, bring them back to the main menu.
				if (Data->KeyCombo[LAST_KEY] == '*') {
					Display_Clear_Screen();
					Data->State = MAIN;
				}

				break;
			}

			// The set pin state allows the user to set their pin which will be updated
			// in flash and the next time they disarm the security system they will have to
			// enter the new pin.
			case SETPIN:
			{
				// Check for user input from the keypad.
				Keypad_ExecuteForPinEnter(Data, &CurrentDigit);

				// Update display every refresh interrupt.
				if (RefreshInterrupt) {
					Display_Module_SetPIN(Data, CurrentDigit);
				}

				// If the user has entered all four digits, copy the new pin to ram and update
				// the pin in flash. Navigate back to the main screen when finished.
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

			// Set time state allows the user to update the date and time. This will
			// update the time and date for the system in the RTC module.
			case SETTIME:
			{

				// Check to see if there is user input from the keypad.
				Keypad_ExecuteForPinEnter(Data, &CurrentDigit);

				// Update the display with new content.
				if (RefreshInterrupt) {
					Display_Module_SetTime(Data, CurrentDigit, SetTimeCounter);
				}

				// Determine if the user has entered at least two digits. At least two digits
				// are required to set each time and date options.
				if (CurrentDigit == 2) {
					Display_Module_SetTime(Data, CurrentDigit, SetTimeCounter);
					SetDateTime[SetTimeCounter] = ((Data->KeyCombo[1] - 48) << 4) | (Data->KeyCombo[0] - 48);

					Data->KeyCombo[0] = '-';
					Data->KeyCombo[1] = '-';
					SysTick_delay(20000);

					CurrentDigit = 0;
					SetTimeCounter++;
				}

				// If all time and date options have been set, store the information in the RTC module
				// and continue to the main screen.
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

			// View logs allows the user to see a list of all the activity from the system.
			case VIEWLOGS:
			{
				// Check for input from the keypad.
				Keypad_ExecuteForPinEnter(Data, &CurrentDigit);

				// Update with view logs content.
				if (PreviousSecond != ClockRegisters[SECOND]) {
					Display_Module_ViewLogs(Data, CurrentDigit);
					PreviousSecond = ClockRegisters[SECOND];

					if (CurrentDigit == 3)
						CurrentDigit = 0;
				}

				// Pressing the * will return users to the menu.
				if (Data->KeyCombo[0] == '*') {
					CurrentDigit = 0;
					Display_Clear_Screen();
					Data->KeyCombo[0] = '\0';
					Data->State = MENU;
				}

				break;
			}

			// Toggle lock state will lock and unlock the door.
			case TOGGLELOCK:
			{

				if (Data->MotorStatus == LOCK) {
					Motor_RotateClockwise();
					Data->MotorStatus = UNLOCK;
					Data->State = MENU;
					break;
				}

				if (Data->MotorStatus == UNLOCK) {
					Motor_RotateCounterClockwise();
					Data->MotorStatus = LOCK;
					Data->State = MENU;
					break;
				}

				Data->State = MENU;

				break;
			}

			// Provides a count down before the device is armed.
			case ARMING:
			{
				if (PreviousSecond != ClockRegisters[SECOND]) {
					Display_Module_ArmingScreen(Data);
				}

				if (Data->MinuteCounter >= 15) {
					Display_Clear_Screen();
					Data->MinuteCounter = 0;
					Data->State = MAIN;
				}

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


void GatherSensorData(SensorData * Data) {
	Proximity_Module_Read(Data);
	HallEffect_Module_Read(Data);
	AmbientLight_Module_Read(Data);
}

