#include "Display.h"
#include "../Assets/MainDisplayBG.h"
#include "../Assets/MenuBG.h"

// TODO: Improve font size for this method for no overlapping.
void Display_Module_DrawString(char String[], uint16_t Color, uint16_t Background, int x, int y, int size, int spacing) {
	int i;

	for (i = 0; i < strlen(String); i++) {
		ST7735_DrawChar(((x + (i * spacing)) % 145), y, String[i], Color, Background, size);
	}

}

/* MAIN SCREEN */
void Display_Module_MainScreen(SensorData * Data, int ClockX) {
	char Time[15], Date[15], Temperature[15];
	char Hours[3], Minutes[3], Seconds[3], Month[3], Day[3], Year[3], Temp[3];

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

	Display_Module_DrawString(Time, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), ClockX, 30, 2, 12);
	Display_Module_DrawString(Date, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 25 + ClockX, 50, 1, 7);
	Display_Module_DrawString(Temperature, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 50, 80, 1, 7);
	Display_Module_DrawString("# Menu", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);

}

void Display_Clear_Screen(void) {
	ST7735_FillScreen(0x0000);
}

/* MENU */
void Display_Menu(SensorData * Data) {
	Display_Module_DrawString("Options", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 10, 2, 12);

	Display_Module_DrawString("1. Set PIN", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 40, 1, 7);
	Display_Module_DrawString("2. Set Time & Date", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 55, 1, 7);
	Display_Module_DrawString("3. Unlock / Lock", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 70, 1, 7);
	Display_Module_DrawString("4. View Logs", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 85, 1, 7);


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
void Display_Module_ViewLogs(SensorData * Data) {

	char TimeLog[25];

	char Hours[3], Minutes[3], Seconds[3], Month[3], Day[3], Year[3], Temp[3];
	Display_Module_DrawString("View Logs", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 10, 2, 12);


	int i = 0;
	for (i = 0; i < 5; i++) {
		ConvertBCDToString(Data->FlashStorage.DateInformation[i][3], &Hours);
		ConvertBCDToString(Data->FlashStorage.DateInformation[i][4], &Minutes);
		ConvertBCDToString(Data->FlashStorage.DateInformation[i][5], &Seconds);
		ConvertBCDToString(Data->FlashStorage.DateInformation[i][0], &Month);
		ConvertBCDToString(Data->FlashStorage.DateInformation[i][1], &Day);
		ConvertBCDToString(Data->FlashStorage.DateInformation[i][2], &Year);

		sprintf(TimeLog, "%s:%s:%s %s/%s/%s", Hours, Minutes, Seconds, Month, Day, Year);

		Display_Module_DrawString(TimeLog, ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), 10, 30 + (i * 15), 1, 7);
	}


	Display_Module_DrawString("* BACK", ST7735_Color565(255, 255, 255), ST7735_Color565(32, 36, 39), SCREEN_WIDTH - 55, SCREEN_HEIGHT - 20, 1, 7);

}



void Display_Refresh(SensorData * Data) {
	Display_Module_DrawString("test", ST7735_Color565(235, 107, 107), ST7735_Color565(32, 36, 39), 7, SCREEN_HEIGHT - 13, 1, 7);

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


uint8_t ConvertStringToBCD(char * String) {

	uint8_t BCD = 0x00;
	return BCD;
}


void Display_Splash_Screen(void) {
	ST7735_FillRect(0, 32, SCREEN_WIDTH, 64, ST7735_Color565(255, 255, 255));
	Display_Module_DrawString("Loading...", ST7735_Color565(0, 0, 0), ST7735_Color565(255, 255, 255), 30, 60, 1, 7);
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

