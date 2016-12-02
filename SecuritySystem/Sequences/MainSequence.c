#include "MainSequence.h"


void Main_Sequence(SensorData * Data) {


	int PreviousSecond = Data->RTC[SECOND];

	Display_Module_MainScreen(&Data);



	while(1) {

		Keypad_Scan();


		// Read startup time from RTC.
		RTC_Module_Read(Data);

		if (Data->RTC[SECOND] != PreviousSecond) {
			Display_Refresh();

			PreviousSecond = Data->RTC[SECOND];
		}


		SysTick_delay(50);
	}


}
