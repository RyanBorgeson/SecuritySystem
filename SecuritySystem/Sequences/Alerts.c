#include "Alerts.h"




void Alerts(SensorData * Data) {
	static uint8_t ToggleState = 0;
	uint8_t PreviousWarning = 0;

	// Determine the state of the system and activate the alarm if necessary.
	// This will also trigger an intruder alert.
	if (Data->ArmedStatus == ARMED && Data->HallEffect[0] == 1 && (Data->State == MAIN || Data->State == ENTERPIN)) {
		if (Data->State == MAIN)
			Display_Module_Warning("Intruder Alert");

		Buzzer_Module_ToggleTone();

		if (ToggleState) {
			RGB_Module_SetColor(RED);
			ToggleState = !ToggleState;
		} else {
			RGB_Module_SetColor(BLACK);
			ToggleState = !ToggleState;
		}

		PreviousWarning = 1;

	}

	// Remove previous alarm status and turn off the buzzer.
	if (Data->ArmedStatus == NOTARMED || Data->HallEffect[0] == 0) {
		if (PreviousWarning == 1) {
			Display_Module_RemoveWarning();
		}

		Buzzer_Module_Off();
		RGB_Module_SetColor(GREEN);
		PreviousWarning = 0;
	}

	if (atoi(ConvertBCDToString(ClockRegisters[TEMPERATURE])) > 43) {

	}

}
