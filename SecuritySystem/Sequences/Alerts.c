#include "Alerts.h"

#define DOOR 0
#define WINDOW 1
#define PROXIMITY 2


void Alerts(SensorData * Data) {
	static uint8_t ToggleState = 0;
	uint8_t PreviousWarning = 0;

	// Determine the state of the system and activate the alarm if necessary.
	// This will also trigger an intruder alert.
	if (Data->ArmedStatus == ARMED && Data->HallEffect[DOOR] == 1 && (Data->State == MAIN || Data->State == ENTERPIN)) {

		if (Data->AlertStatuses[DOOR] == 0) {
			Flash_Module_PushDateTimeUpTrigger(&Data->FlashStorage.AlarmTriggers, 'D');
			Flash_Module_SaveToFlash(&Data->FlashStorage);

			Data->AlertStatuses[DOOR] = 1;
		}

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


	// Determine the state of the system and activate the alarm if necessary.
	// This will also trigger an intruder alert.
	if (Data->ArmedStatus == ARMED && Data->HallEffect[WINDOW] == 1 && (Data->State == MAIN || Data->State == ENTERPIN)) {


		if (Data->AlertStatuses[WINDOW] == 0) {
			Flash_Module_PushDateTimeUpTrigger(&Data->FlashStorage.AlarmTriggers, 'W');
			Flash_Module_SaveToFlash(&Data->FlashStorage);

			Data->AlertStatuses[WINDOW] = 1;
		}

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

	if (Data->State == MAIN && Data->Proximity[0] == 1) {
			Display_Module_Message("Presents Detected");
		}

	if (Data->State == MAIN && Data->HallEffect[DOOR] == 1 && Data->HallEffect[WINDOW] == 0) {
		Display_Module_Message("Window Open");
	}

	if (Data->State == MAIN && Data->HallEffect[WINDOW] == 1 && Data->HallEffect[DOOR] == 0) {
		Display_Module_Message("Door Open");
	}

	if (Data->State == MAIN && Data->HallEffect[WINDOW] == 1 && Data->HallEffect[DOOR] == 1) {
		Display_Module_Message("Door & Window Open");
	}


	if (Data->State == MAIN && Data->HallEffect[WINDOW] == 0 && Data->HallEffect[DOOR] == 0) {
		Display_Module_Message("Door & Window Closed");
	}



	// Remove previous alarm status and turn off the buzzer.
	if (Data->ArmedStatus == NOTARMED || Data->HallEffect[0] == 0) {
		if (PreviousWarning == 1) {
			Display_Module_RemoveWarning();
		}

		Buzzer_Module_Off();

		RGB_Module_SetColor(Data->ArmedStatus == NOTARMED ? GREEN : RED);
		PreviousWarning = 0;
		Data->AlertStatuses[WINDOW] = 0;
		Data->AlertStatuses[DOOR] = 0;
	}

	if (atoi(ConvertBCDToString(ClockRegisters[TEMPERATURE])) > 43) {
		if (Data->State == MAIN)
			Display_Module_Warning("Fire");

		Buzzer_Module_ToggleTone();

		if (ToggleState) {
			RGB_Module_SetColor(RED);
			ToggleState = !ToggleState;
		} else {
			RGB_Module_SetColor(BLACK);
			ToggleState = !ToggleState;
		}
	}

}
