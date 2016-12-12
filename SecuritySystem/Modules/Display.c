/**
 * Configures and outputs information, bitmaps, and data to the display
 * over SPI. Handles the layout for each screen or state.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */
#include "Display.h"


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

void Display_Module_MainScreen(SensorData * Data, int ClockX) {
	// Declare variables that will be used to store and format information.
	char Time[15], Date[15], Temperature[11];
	char Hours[3], Minutes[3], Seconds[3], Month[3], Day[3], Year[3], Temp[2];

	// Convert information from the RTC into usable characters.
	// Once the conversion is complete they will be stored in their respective variables.
	ConvertBCDToString(ClockRegisters[HOUR], &Hours);
	ConvertBCDToString(ClockRegisters[MINUTE], &Minutes);
	ConvertBCDToString(ClockRegisters[SECOND], &Seconds);
	ConvertBCDToString(ClockRegisters[MONTH], &Month);
	ConvertBCDToString(ClockRegisters[DAY], &Day);
	ConvertBCDToString(ClockRegisters[YEAR], &Year);
	ConvertBCDToString(ClockRegisters[TEMPERATURE], &Temp);

	// Format string before displaying.
	sprintf(Time, "  %s:%s:%s  ", Hours, Minutes, Seconds);
	sprintf(Date, "  %s/%s/%s  ", Month, Day, Year);
	sprintf(Temperature, "    %s Celsius    ", Temp);

	// Finally display the time, date, temperature, and additional information on the display.
	Display_Module_DrawStringWithMarquee(Time, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), ClockX, 40, 2, 12);
	Display_Module_DrawStringWithMarquee(Date, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 25 + ClockX, 60, 1, 7);
	Display_Module_DrawString(Temperature, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 25, 90, 1, 7);
	Display_Module_DrawString("# Menu", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);

	// Free variables from memory.
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
	// Clears the screen and fills it with all black.
	ST7735_FillScreen(0x0000);
}

void Display_Menu(SensorData * Data) {
	// Display menu options on the display.
	Display_Module_DrawString("Options", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 2, 12);

	Display_Module_DrawString("1. Set PIN", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 30, 1, 7);
	Display_Module_DrawString("2. Set Time & Date", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 45, 1, 7);
	Display_Module_DrawString("3. Unlock / Lock", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 60, 1, 7);
	Display_Module_DrawString("4. View Logs", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 75, 1, 7);

	// Determine the current armed or disarmed state of the system and display
	// update the menu options accordingly.
	if (Data->ArmedStatus == NOTARMED)
		Display_Module_DrawString("5. Arm System      ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 90, 1, 7);
	else
		Display_Module_DrawString("5. Disarm System  ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 90, 1, 7);


	// Back button.
	Display_Module_DrawString("* BACK", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);
}


void Display_Module_EnterPIN(SensorData * Data, int Digits) {
	// Layout for when the user would like to enter the menu.
	// The user will be prompted to enter their pin first.
	Display_Module_DrawString("Enter PIN", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 2, 12);

	// Display rectangles.
	if (Digits == 0) {
		ST7735_FillRect(5, 50, 25, 25, ST7735_Color565(255, 255, 255));
		ST7735_FillRect(45, 50, 25, 25, ST7735_Color565(255, 255, 255));
		ST7735_FillRect(85, 50, 25, 25, ST7735_Color565(255, 255, 255));
		ST7735_FillRect(125, 50, 25, 25, ST7735_Color565(255, 255, 255));
	}

	// For each digit or character the user enters on the keypad, draw another
	// asterisk.
	int i;
	for (i = 0; i < Digits; i++) {
		ST7735_DrawChar(12 + (i * 40), 54, '*', ST7735_Color565(0, 0, 0), ST7735_Color565(255, 255, 255), 2);
	}

	// Back button.
	Display_Module_DrawString("* BACK", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);
}

void Display_Module_SetPIN(SensorData * Data, int Digits) {
	// Allows the user to set or update their pin.
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
}

void Display_Module_SetTime(SensorData * Data, int Digits, int SetTimeCounter) {
	// Variables.
	char EnteredDigits[2];

	// Format entered digits to appear as characters on the display.
	sprintf(EnteredDigits, "%c%c", Data->KeyCombo[0], Data->KeyCombo[1]);

	// If two digits have been entered, format the digits to appear in the correct order.
	if (Digits == 2)
		sprintf(EnteredDigits, "%c%c", Data->KeyCombo[1], Data->KeyCombo[0]);

	// Set time menu.
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

	Display_Module_DrawString("* BACK", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);

	// Free entereddigits variable.
	free(EnteredDigits);
}

void Display_Module_ViewLogs(SensorData * Data, uint8_t Page) {
	// Variables used in the view logs screen.
	char TimeLog[25];
	char Hours[3], Minutes[3], Seconds[3], Month[3], Day[3], Year[3], Temp[3];
	uint8_t TempLogs[5][6];

	// Determine which page the user has currently selected and display it.
	if (Page == 0) {
		Display_Module_DrawString("Arm Logs      ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 1, 7);

		// Format and display the characters on the page.
		int i = 0;
		for (i = 0; i < 5; i++) {
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][3], &Hours);
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][4], &Minutes);
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][5], &Seconds);
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][0], &Month);
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][1], &Day);
			ConvertBCDToString(Data->FlashStorage.ArmTimes[i][2], &Year);

			sprintf(TimeLog, "%s:%s:%s %s/%s/%s", Hours, Minutes, Seconds, Month, Day, Year);

			Display_Module_DrawString(TimeLog, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 30 + (i * 12), 1, 7);
		}

	} else if (Page == 1) {
		Display_Module_DrawString("Disarm Logs   ", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 1, 7);

		// Format and display the characters on the page.
		int i = 0;
		for (i = 0; i < 5; i++) {
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][3], &Hours);
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][4], &Minutes);
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][5], &Seconds);
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][0], &Month);
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][1], &Day);
			ConvertBCDToString(Data->FlashStorage.DisarmTimes[i][2], &Year);

			sprintf(TimeLog, "%s:%s:%s %s/%s/%s", Hours, Minutes, Seconds, Month, Day, Year);

			Display_Module_DrawString(TimeLog, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 30 + (i * 12), 1, 7);
		}

	} else {
		Display_Module_DrawString("Trigger Logs", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 1, 7);

		// Format and display the characters on the page.
		int i = 0;
		for (i = 0; i < 5; i++) {
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][3], &Hours);
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][4], &Minutes);
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][5], &Seconds);
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][0], &Month);
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][1], &Day);
			ConvertBCDToString(Data->FlashStorage.AlarmTriggers[i][2], &Year);

			sprintf(TimeLog, "%s:%s:%s %s/%s/%s %c  ", Hours, Minutes, Seconds, Month, Day, Year, Data->FlashStorage.AlarmTriggers[i][6]);

			Display_Module_DrawString(TimeLog, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 30 + (i * 12), 1, 6);
		}
	}

	Display_Module_DrawString("1 Next", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, SCREEN_HEIGHT - 20, 1, 7);
	Display_Module_DrawString("* BACK", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);
}


void Display_Module_ArmingScreen(SensorData * Data) {
	// Displays a count down when the user goes to set the alarm.
	char Time[3];

	// Format the counter.
	sprintf(Time, "%i", Data->MinuteCounter);

	// Display the count down on the display.
	Display_Module_DrawString("Arming", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 2, 12);
	Display_Module_DrawString(Time, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 60, 60, 2, 12);
}

void Display_Init(void) {
	// Setup display with black background.
	ST7735_InitR(INITR_REDTAB);
	ST7735_FillScreen(0x0000);

	// Rotate to landscape mode.
	ST7735_SetRotation(DISPLAY_LANDSCAPE);
}


void ConvertBCDToString(uint8_t BCD, char * String) {
	// Convert a binary coded decimal (BCD) to a useful string.
	*String++ = (((BCD & 0xF0) >> 4) + 48);
	*String++ = ((BCD & 0x0F) + 48);
	*String = '\0';
}

void Display_Splash_Screen(void) {
	// Draw the splash screen.
	ST7735_FillRect(0, 32, SCREEN_WIDTH, 64, ST7735_Color565(255, 255, 255));
	Display_Module_DrawString("Loading...", ST7735_Color565(0, 0, 0), ST7735_Color565(255, 255, 255), 30, 60, 1, 7);
}

void Display_Module_Warning(char * Message) {
	// Display a warning message at the top of the display.
	ST7735_FillRect(0, 0, SCREEN_WIDTH, 25, ST7735_Color565(223, 65, 65));
	Display_Module_DrawString(Message, ST7735_Color565(255, 255, 255), ST7735_Color565(223, 65, 65), 20, 7, 1, 7);
}

void Display_Module_Message(char * Message) {
	// Display a message at the top of the display.
	ST7735_FillRect(0, 0, SCREEN_WIDTH, 25, ST7735_Color565(81, 156, 163));
	Display_Module_DrawString(Message, ST7735_Color565(255, 255, 255), ST7735_Color565(81, 156, 163), 20, 7, 1, 7);
}

void Display_Module_GreenMessage(char * Message) {
	// Display a message at the top of the display that is green.
	ST7735_FillRect(0, 0, SCREEN_WIDTH, 25, ST7735_Color565(62, 210, 55));
	Display_Module_DrawString(Message, ST7735_Color565(255, 255, 255), ST7735_Color565(62, 210, 55), 20, 7, 1, 7);
}

void Display_Module_RemoveWarning() {
	// Removes the warning by covering it up with a black rectangle.
	ST7735_FillRect(0, 0, SCREEN_WIDTH, 30, ST7735_Color565(0, 0, 0));
}

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
