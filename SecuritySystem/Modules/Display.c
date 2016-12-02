#include "Display.h"
#include "../Assets/MainDisplayBG.h"


// TODO: Improve font size for this method for no overlapping.
void Display_Module_DrawString(char String[], uint16_t Color, uint16_t Background, int x, int y, int size) {
	int i;

	for (i = 0; i < strlen(String); i++) {
		ST7735_DrawChar(x + (i * 10), y, String[i], Color, Background, size);
	}
}

void Display_Module_MainScreen(SensorData * Data) {
	char Time[100];
	sprintf(Time, "Time: ");

	ST7735_FillScreen(0x0000);
	ST7735_DrawBitmap(0, SCREEN_HEIGHT, MainMenuDesign, SCREEN_WIDTH, SCREEN_HEIGHT);
}


void Display_Module_MainScreen2(SensorData * Data) {
	static uint8_t PreviousHallEffect;
	static uint8_t PreviousHallEffect2;

	if (PreviousHallEffect != Data->HallEffect[0] || PreviousHallEffect2 != Data->HallEffect[1])
		if (!Data->HallEffect[0] || !Data->HallEffect[1]) {
			//ST7735_DrawBitmap(0, SCREEN_HEIGHT - 1, MainMenuDesign, SCREEN_WIDTH, SCREEN_HEIGHT);
			Display_Module_DrawString("SECURED           # MENU", ST7735_Color565(147, 200, 70), ST7735_Color565(32, 36, 39), 7, SCREEN_HEIGHT - 13, 1);
		} else {
			//ST7735_DrawBitmap(0, SCREEN_HEIGHT - 48, Armed, SCREEN_WIDTH, 48);
			Display_Module_DrawString("UNSECURED         # MENU", ST7735_Color565(235, 107, 107), ST7735_Color565(32, 36, 39), 7, SCREEN_HEIGHT - 13, 1);
		}

	PreviousHallEffect = Data->HallEffect[0];
	PreviousHallEffect = Data->HallEffect[1];
}


void Display_Refresh(SensorData * Data) {
	Display_Module_DrawString("test", ST7735_Color565(235, 107, 107), ST7735_Color565(32, 36, 39), 7, SCREEN_HEIGHT - 13, 1);

}


void Display_Init(void) {
	// Setup display with black background.
	ST7735_InitR(INITR_REDTAB);
	ST7735_FillScreen(0x0000);

	// Rotate to landscape mode.
	ST7735_SetRotation(DISPLAY_LANDSCAPE);
}



void Display_Splash_Screen(void) {

	ST7735_FillRect(0, 32, SCREEN_WIDTH, 64, ST7735_Color565(52, 152, 219));

	Display_Module_DrawString("Loading...", ST7735_Color565(255, 255, 255), ST7735_Color565(52, 152, 219), 30, 60, 1);
	//ST7735_FillRect(0, SCREEN_HEIGHT - 20, SCREEN_WIDTH, 20, ST7735_Color565(46, 204, 113));
}

