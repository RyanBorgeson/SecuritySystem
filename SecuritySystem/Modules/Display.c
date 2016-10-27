#include "Display.h"


// TODO: Improve font size for this method for no overlapping.
void Display_Module_DrawString(char String[], uint16_t Color, int x, int y, int size) {
	int i;

	for (i = 0; i < strlen(String); i++) {
		ST7735_DrawCharS(x + (i * (7 + size)), y, String[i], Color, 0, size);
	}
}
