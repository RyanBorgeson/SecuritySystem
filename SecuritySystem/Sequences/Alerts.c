#include "Alerts.h"

#define DOOR 0
#define WINDOW 1
#define PROXIMITY 2


void Alerts(SensorData * Data) {
	static uint8_t ToggleState = 0;
	uint8_t PreviousWarning = 0;



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

	Buzzer_Module_ToggleTone();

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

		Buzzer_Module_On();

		if (ToggleState) {
			RGB_Module_SetColor(RED);
			ToggleState = !ToggleState;
		} else {
			RGB_Module_SetColor(BLACK);
			ToggleState = !ToggleState;
		}


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


		PreviousWarning = 1;
	}

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
