#include "Display.h"
#include "../Assets/MainDisplayBG.h"
#include "../Assets/MenuBG.h"

// TODO: Improve font size for this method for no overlapping.
void Display_Module_DrawString(char String[], uint16_t Color, uint16_t Background, int x, int y, int size, int spacing) {
	int i;

	for (i = 0; i < strlen(String); i++) {
		ST7735_DrawChar(x + (i * spacing), y, String[i], Color, Background, size);
	}
}


void Display_Module_MainScreen(SensorData * Data) {
	char Time[100];
	//volatile char * getseconds = ConvertBCDToString(RTC_registers[0]);

	char * Hours = ConvertBCDToString(ClockRegisters[HOUR]);
	char * Minutes =  ConvertBCDToString(ClockRegisters[MINUTE]);
	char * Seconds =  ConvertBCDToString(ClockRegisters[SECOND]);

	sprintf(Time, "%s:%s:%s", Hours, Minutes, Seconds);

	free(Hours);
	free(Minutes);
	free(Seconds);

	Display_Module_DrawString(Time, ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), 10, 40, 2, 18);
	Display_Module_DrawString("# Menu", ST7735_Color565(255, 255, 255), ST7735_Color565(0, 0, 0), SCREEN_WIDTH - 60, SCREEN_HEIGHT - 20, 1, 7);
}

void Display_Clear_Screen(void) {
	ST7735_FillScreen(0x0000);
}

void Display_Menu(SensorData * Data) {
	Display_Module_DrawString("* BACK", ST7735_Color565(235, 107, 107), ST7735_Color565(32, 36, 39), SCREEN_WIDTH - 60, SCREEN_HEIGHT - 20, 1, 7);
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


char * ConvertBCDToString(uint32_t BCD, char * String) {

	char * str = malloc(sizeof(char) * 3);
	str[0] = (((BCD & 0xF0) >> 4) + 48);
	str[1] = ((BCD & 0x0F) + 48);
	str[2] = '\0';

	return str;
}

void Display_Splash_Screen(void) {

	ST7735_FillRect(0, 32, SCREEN_WIDTH, 64, ST7735_Color565(52, 152, 219));

	Display_Module_DrawString("Loading...", ST7735_Color565(255, 255, 255), ST7735_Color565(52, 152, 219), 30, 60, 1, 7);
	//ST7735_FillRect(0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, 20, ST7735_Color565(46, 204, 113));
}

