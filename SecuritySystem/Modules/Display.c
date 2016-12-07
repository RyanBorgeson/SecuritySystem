#include "Display.h"
#include "../Assets/MainDisplayBG.h"
#include "../Assets/MenuBG.h"

// TODO: Improve font size for this method for no overlapping.
void Display_Module_DrawString(char String[], uint16_t Color, uint16_t Background, int x, int y, int size, int spacing) {
	int i;

	for (i = 0; i < strlen(String); i++) {
		ST7735_DrawChar((x + (i * spacing)), y, String[i], Color, Background, size);
	}

}

void Display_Module_DrawStringWithMarquee(char String[], uint16_t Color, uint16_t Background, int x, int y, int size, int spacing) {
	int i;

	for (i = 0; i < strlen(String); i++) {
		ST7735_DrawChar(((x + (i * spacing)) % 145), y, String[i], Color, Background, size);
	}

}

/* MAIN SCREEN */
void Display_Module_MainScreen(SensorData * Data, int ClockX) {
	char Time[15], Date[15], Temperature[11];
	char Hours[3], Minutes[3], Seconds[3], Month[3], Day[3], Year[3], Temp[2];

	ConvertBCDToString(ClockRegisters[HOUR], &Hours);
	ConvertBCDToString(ClockRegisters[MINUTE], &Minutes);
	ConvertBCDToString(ClockRegisters[SECOND], &Seconds);
	ConvertBCDToString(ClockRegisters[MONTH], &Month);
	ConvertBCDToString(ClockRegisters[DAY], &Day);
	ConvertBCDToString(ClockRegisters[YEAR], &Year);
	ConvertBCDToString(ClockRegisters[TEMPERATURE], &Temp);

	sprintf(Time, "  %s:%s:%s  ", Hours, Minutes, Seconds);
	sprintf(Date, "  %s/%s/%s  ", Month, Day, Year);
	sprintf(Temperature, "%s Celsius", Temp);

	Display_Module_DrawStringWithMarquee(Time, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), ClockX, 40, 2, 12);
	Display_Module_DrawStringWithMarquee(Date, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 25 + ClockX, 60, 1, 7);
	Display_Module_DrawString(Temperature, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 40, 90, 1, 7);
	Display_Module_DrawString("# Menu", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);

	free(Time);
	free(Date);
	free(Temperature);
	free(Hours);
	free(Minutes);
	free(Seconds);
	free(Month);
	free(Day);
	free(Year);
	free(Temp);

}

void Display_Clear_Screen(void) {
	ST7735_FillScreen(0x0000);
}

/* MENU */
void Display_Menu(SensorData * Data) {
	Display_Module_DrawString("Options", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 10, 2, 12);

	Display_Module_DrawString("1. Set PIN", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 30, 1, 7);
	Display_Module_DrawString("2. Set Time & Date", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 45, 1, 7);
	Display_Module_DrawString("3. Unlock / Lock", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 60, 1, 7);
	Display_Module_DrawString("4. View Logs", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 75, 1, 7);

	if (Data->ArmedStatus == NOTARMED)
		Display_Module_DrawString("5. Arm System      ", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 90, 1, 7);
	else
		Display_Module_DrawString("5. Disarm System  ", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 90, 1, 7);


	Display_Module_DrawString("* BACK", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);
}

/* ENTER PIN */
void Display_Module_EnterPIN(SensorData * Data, int Digits) {
	Display_Module_DrawString("Enter PIN", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 2, 12);

	if (Digits == 0) {
		ST7735_FillRect(5, 50, 25, 25, ST7735_Color565(255, 255, 255));
		ST7735_FillRect(45, 50, 25, 25, ST7735_Color565(255, 255, 255));
		ST7735_FillRect(85, 50, 25, 25, ST7735_Color565(255, 255, 255));
		ST7735_FillRect(125, 50, 25, 25, ST7735_Color565(255, 255, 255));
	}
	int i;
	for (i = 0; i < Digits; i++) {
		ST7735_DrawChar(12 + (i * 40), 54, '*', ST7735_Color565(0, 0, 0), ST7735_Color565(255, 255, 255), 2);
	}


	Display_Module_DrawString("* BACK", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);

}



/* SET PIN */
void Display_Module_SetPIN(SensorData * Data, int Digits) {
	Display_Module_DrawString("Set PIN", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 2, 12);

	if (Digits == 0) {
		ST7735_FillRect(5, 50, 25, 25, ST7735_Color565(255, 255, 255));
		ST7735_FillRect(45, 50, 25, 25, ST7735_Color565(255, 255, 255));
		ST7735_FillRect(85, 50, 25, 25, ST7735_Color565(255, 255, 255));
		ST7735_FillRect(125, 50, 25, 25, ST7735_Color565(255, 255, 255));
	}
	int i;
	for (i = 0; i < Digits; i++) {
		ST7735_DrawChar(12 + (i * 40), 54, '*', ST7735_Color565(0, 0, 0), ST7735_Color565(255, 255, 255), 2);
	}


	Display_Module_DrawString("* BACK", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);

}


/* Set Time */
void Display_Module_SetTime(SensorData * Data, int Digits, int SetTimeCounter) {
	char EnteredDigits[2];
	sprintf(EnteredDigits, "%c%c", Data->KeyCombo[0], Data->KeyCombo[1]);

	if (Digits == 2)
		sprintf(EnteredDigits, "%c%c", Data->KeyCombo[1], Data->KeyCombo[0]);

	Display_Module_DrawString("Set Time", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 2, 12);

	// This will change based on the set time counter.
	// This will prompt the user for which time/date to enter.
	if (SetTimeCounter == 0)
		Display_Module_DrawString("Enter Seconds     ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 30, 1, 7);
	else if (SetTimeCounter == 1)
			Display_Module_DrawString("Enter Minutes     ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 30, 1, 7);
	else if (SetTimeCounter == 2)
			Display_Module_DrawString("Enter Hours       ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 30, 1, 7);
	else if (SetTimeCounter == 3)
			Display_Module_DrawString("Enter Day of Month ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 30, 1, 7);
	else if (SetTimeCounter == 4)
			Display_Module_DrawString("Enter Month (Ex: 10)", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 30, 1, 7);
	else if (SetTimeCounter == 5)
			Display_Module_DrawString("Enter Year (Ex: 16) ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 30, 1, 7);

	Display_Module_DrawString(EnteredDigits, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 60, 60, 2, 12);

	Display_Module_DrawString("* BACK", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);

	free(EnteredDigits);
}


/* View Logs */
void Display_Module_ViewLogs(SensorData * Data, uint8_t Page) {

	char TimeLog[25];

	char Hours[3], Minutes[3], Seconds[3], Month[3], Day[3], Year[3], Temp[3];
	uint8_t TempLogs[5][6];

	if (Page == 0) {
		Display_Module_DrawString("Arm Logs      ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 1, 7);

		int i = 0;
		for (i = 0; i < 5; i++) {
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][3], &Hours);
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][4], &Minutes);
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][5], &Seconds);
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][0], &Month);
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][1], &Day);
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][2], &Year);

			sprintf(TimeLog, "%s:%s:%s %s/%s/%s", Hours, Minutes, Seconds, Month, Day, Year);

			Display_Module_DrawString(TimeLog, ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 30 + (i * 12), 1, 7);
		}

	} else if (Page == 1) {
		Display_Module_DrawString("Disarm Logs   ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 1, 7);

		int i = 0;
		for (i = 0; i < 5; i++) {
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][3], &Hours);
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][4], &Minutes);
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][5], &Seconds);
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][0], &Month);
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][1], &Day);
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][2], &Year);

			sprintf(TimeLog, "%s:%s:%s %s/%s/%s", Hours, Minutes, Seconds, Month, Day, Year);

			Display_Module_DrawString(TimeLog, ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 30 + (i * 12), 1, 7);
		}

	} else {
		Display_Module_DrawString("Trigger Logs", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 1, 7);
		int i = 0;
		for (i = 0; i < 5; i++) {
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][3], &Hours);
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][4], &Minutes);
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][5], &Seconds);
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][0], &Month);
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][1], &Day);
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][2], &Year);

			sprintf(TimeLog, "%s:%s:%s %s/%s/%s", Hours, Minutes, Seconds, Month, Day, Year);

			Display_Module_DrawString(TimeLog, ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 30 + (i * 12), 1, 7);
		}
	}



	Display_Module_DrawString("1 Next", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, SCREEN_HEIGHT - 20, 1, 7);
	Display_Module_DrawString("* BACK", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);

}

void Display_Init(void) {
	// Setup display with black background.
	ST7735_InitR(INITR_REDTAB);
	ST7735_FillScreen(0x0000);

	// Rotate to landscape mode.
	ST7735_SetRotation(DISPLAY_LANDSCAPE);
}


void ConvertBCDToString(uint8_t BCD, char * String) {

	*String++ = (((BCD & 0xF0) >> 4) + 48);
	*String++ = ((BCD & 0x0F) + 48);
	*String = '\0';
}


void Display_Splash_Screen(void) {
	ST7735_FillRect(0, 32, SCREEN_WIDTH, 64, ST7735_Color565(255, 255, 255));
	Display_Module_DrawString("Loading...", ST7735_Color565(0, 0, 0), ST7735_Color565(255, 255, 255), 30, 60, 1, 7);
}


void Display_Module_Warning(char * Message) {
	ST7735_FillRect(0, 0, SCREEN_WIDTH, 25, ST7735_Color565(223, 65, 65));
	Display_Module_DrawString(Message, ST7735_Color565(255, 255, 255), ST7735_Color565(223, 65, 65), 20, 7, 1, 7);
}

void Display_Module_RemoveWarning() {
	ST7735_FillRect(0, 0, SCREEN_WIDTH, 30, ST7735_Color565(0, 0, 0));
}



/**
 * Sets up PWM output for P7.7 and waveform settings.
 */
void Display_Module_Backlight(void) {
	// Setup up pin directions and non GPIO functions on P7.7.
	P7->DIR |= BIT7;
	P7->SEL0 |= BIT7;
	P7->SEL1 &= ~BIT7;

	// Setup PWM Waveform. CCR1 reset/set.
	TIMER_A1->CCR[0] = 1000 - 1;
	TIMER_A1->CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_CLR;
	TIMER_A1->CCTL[1] = TIMER_A_CCTLN_OUTMOD_7;
}


void Display_Module_UpdateBacklight(SensorData * Data) {

	// Change PWM duty cycle.
	TIMER_A1->CCR[1] = Data->LEDDutyCycle * 10 + 25;
}
