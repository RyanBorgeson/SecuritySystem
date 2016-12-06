#include "Alerts.h"


void Alerts(SensorData * Data) {
	static uint8_t ToggleState = 0;

	// Determine the state of the system and activate the alarm if necessary.
	if (Data->ArmedStatus == ARMED && Data->HallEffect[0] == 1) {
		Buzzer_Module_ToggleTone();

		if (ToggleState) {
			RGB_Module_SetColor(RED);
			ToggleState = !ToggleState;
		} else {
			RGB_Module_SetColor(BLACK);
			ToggleState = !ToggleState;
		}

	}
	if (Data->ArmedStatus == NOTARMED || Data->HallEffect[0] == 0) {
		Buzzer_Module_Off();
		RGB_Module_SetColor(GREEN);
	}

	if (atoi(ConvertBCDToString(ClockRegisters[TEMPERATURE])) > 43) {

	}

}
