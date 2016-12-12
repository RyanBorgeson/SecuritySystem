/**
 * Alerts determines when the alarm should sound based on certain events.
 * Each event that should trigger the alarm will be specified below.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */
#include "Alerts.h"

void Alerts(SensorData * Data) {
	// Variables used to toggle certain states.
	static uint8_t ToggleState = 0;
	uint8_t PreviousWarning = 0;

	// Always attempt to toggle the buzzer whether or not
	// it is on.
	Buzzer_Module_ToggleTone();

	// If the system exceeds a temperature of 43 degrees celsius
	// an alarm will sound and message will be displayed indicating the
	// system is too hot.
	if (ClockRegisters[TEMPERATURE] > 0x43) {

		if (Data->State == MAIN)
			Display_Module_Warning("Fire");

		Buzzer_Module_On();

		if (ToggleState) {
			RGB_Module_SetColor(RED);
			ToggleState = !ToggleState;
		} else {
			RGB_Module_SetColor(BLACK);
			ToggleState = !ToggleState;
		}
	}

	// Trigger an alarm if the door, window, or proximity sensor goes off in the main system state.
	// This will trigger a blinking LED and alarming sound.
	if (Data->ArmedStatus == ARMED && (Data->Proximity[0] == 1 || Data->HallEffect[WINDOW] == 1 || Data->HallEffect[DOOR] == 1) && (Data->State == MAIN || Data->State == ENTERPIN)) {

		// Set which alarm was trigger in flash.
		if (Data->AlertStatuses[WINDOW] == 0 && Data->HallEffect[WINDOW] == 1) {
			Flash_Module_PushDateTimeUpTrigger(&Data->FlashStorage.AlarmTriggers, 'W');
			Flash_Module_SaveToFlash(&Data->FlashStorage);

			Data->AlertStatuses[WINDOW] = 1;
		}
		if (Data->AlertStatuses[DOOR] == 0 && Data->HallEffect[DOOR] == 1) {
			Flash_Module_PushDateTimeUpTrigger(&Data->FlashStorage.AlarmTriggers, 'D');
			Flash_Module_SaveToFlash(&Data->FlashStorage);

			Data->AlertStatuses[DOOR] = 1;
		}
		if (Data->AlertStatuses[PROXIMITY] == 0 && Data->Proximity[0] == 1) {
			Flash_Module_PushDateTimeUpTrigger(&Data->FlashStorage.AlarmTriggers, 'P');
			Flash_Module_SaveToFlash(&Data->FlashStorage);

			Data->AlertStatuses[PROXIMITY] = 1;
		}

		// Turn on the buzzer module.
		Buzzer_Module_On();

		// Toggle between RED and off LED states.
		if (ToggleState) {
			RGB_Module_SetColor(RED);
			ToggleState = !ToggleState;
		} else {
			RGB_Module_SetColor(BLACK);
			ToggleState = !ToggleState;
		}

		// Display the appropriate message on the display depending on the state
		// of each sensor.
		if (Data->State == MAIN && Data->Proximity[0] == 1 && Data->AlertStatuses[PROXIMITY] == 1) {
			Display_Module_Message("Intruder Detected");
		} else {
			if (Data->State == MAIN && Data->HallEffect[DOOR] == 1 && Data->HallEffect[WINDOW] == 0)
				Display_Module_Message("Window Open");

			if (Data->State == MAIN && Data->HallEffect[WINDOW] == 1 && Data->HallEffect[DOOR] == 0)
				Display_Module_Message("Door Open");

			if (Data->State == MAIN && Data->HallEffect[WINDOW] == 1 && Data->HallEffect[DOOR] == 1)
				Display_Module_Message("Door & Window Open");

			if (Data->State == MAIN && Data->HallEffect[WINDOW] == 0 && Data->HallEffect[DOOR] == 0)
				Display_Module_Message("Door & Window Closed");
		}

		// Is true if the previous state of the system was in a warning state.
		PreviousWarning = 1;
	}

	// Display a message indicating if the door, window, or proximity sensor
	// is being trigger. This will only display a message and not alarm the user.
	// Must be in the disarmed state.
	if (Data->State == MAIN && Data->ArmedStatus == NOTARMED) {
		if (Data->State == MAIN && Data->HallEffect[DOOR] == 1 && Data->HallEffect[WINDOW] == 0)
			Display_Module_Message("Window Open");

		if (Data->State == MAIN && Data->HallEffect[WINDOW] == 1 && Data->HallEffect[DOOR] == 0)
			Display_Module_Message("Door Open");

		if (Data->State == MAIN && Data->HallEffect[WINDOW] == 1 && Data->HallEffect[DOOR] == 1)
			Display_Module_Message("Door & Window Open");

		if (Data->State == MAIN && Data->HallEffect[WINDOW] == 0 && Data->HallEffect[DOOR] == 0)
			Display_Module_Message("Door & Window Closed");
	}

	// Toggles the LED if the status of an alarm is set to true.
	if (Data->ArmedStatus == ARMED && (Data->AlertStatuses[WINDOW] == 1 || Data->AlertStatuses[DOOR] == 1 || Data->AlertStatuses[PROXIMITY] == 1)) {
		if (ToggleState) {
			RGB_Module_SetColor(RED);
			ToggleState = !ToggleState;
		} else {
			RGB_Module_SetColor(BLACK);
			ToggleState = !ToggleState;
		}
	}

	// Remove previous alarm status and turn off the buzzer.
	// This returns everything to its none armed state. Turns off buzzer,
	// resets LED, and resets alert statuses.
	if (Data->ArmedStatus == NOTARMED) {
		if (PreviousWarning == 1) {
			Display_Module_RemoveWarning();
		}

		if (ClockRegisters[TEMPERATURE] <= 0x43) {
			Buzzer_Module_Off();
			RGB_Module_SetColor(Data->ArmedStatus == NOTARMED ? GREEN : RED);
		}
		Data->AlertStatuses[WINDOW] = 0;
		Data->AlertStatuses[DOOR] = 0;
		Data->AlertStatuses[PROXIMITY] = 0;
	}


}
