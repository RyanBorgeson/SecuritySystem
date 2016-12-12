/**
 * Configures and outputs information, bitmaps, and data to the display
 * over SPI. Handles the layout for each screen or state.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#include "../Config.h"


#define DISPLAY_LANDSCAPE 1
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 128

/**
 * Initialize the display for the initial screen and set the correct
 * orientation of the display.
 */
void Display_Init(void);

/**
 * Draw a string on the display with the specified properties.
 * @param String The string to display.
 * @param Color The color of the text.
 * @param Background The background color of the text.
 * @param x The x position of the text.
 * @param y The y position of the text.
 * @param size The size of the text.
 * @param spacing The spacing between each letter.
 */
void Display_Module_DrawString(char String[], uint16_t Color, uint16_t Background, int x, int y, int size, int spacing);

/**
 * Similar to the DrawString method, but this draws a string on the display with the specified properties
 * and allows the text to scroll across the screen.
 * @param String The string to display.
 * @param Color The color of the text.
 * @param Background The background color of the text.
 * @param x The x position of the text.
 * @param y The y position of the text.
 * @param size The size of the text.
 * @param spacing The spacing between each letter.
 */

void Display_Module_DrawStringWithMarquee(char String[], uint16_t Color, uint16_t Background, int x, int y, int size, int spacing);

/**
 * Clears the screen.
 */
void Display_Clear_Screen(void);

/**
 * Sets up the main screen with date, time, and temperature. Also handles
 * scrolling text.
 * @param Data The sensor data object containing system information.
 * @param ClockX The x position of the time and date.
 */
void Display_Module_MainScreen(SensorData * Data, int ClockX);

/**
 * Displays the menu with selectable menu options.
 * @param Data A sensor data object containing system information.
 */
void Display_Menu(SensorData * Data);


/**
 * Displays the layout for the user to enter their pin. This is necessary
 * before moving to the next menu.
 * @param Data The sensor data object.
 * @param Digits Number of digits the user has already entered.
 */
void Display_Module_EnterPIN(SensorData * Data, int Digits);

/**
 * Prompts the user to enter a new pin.
 * @param Data The sensor data object.
 * @param Digits The number of digits entered by the user.
 */
void Display_Module_SetPIN(SensorData * Data, int Digits);


/**
 * Prompts the user to set the time and date.
 * @param Data The sensor data object.
 * @param Digits Number of digits the user has already entered.
 * @param SetTimeCounter
 */
void Display_Module_SetTime(SensorData * Data, int Digits, int SetTimeCounter);

/**
 * Display the arm, disarm, and triggered alarms. This will also display
 * the source of the alarm (window, door, proximity) and what time it was triggered.
 * The user can navigation through each page.
 * @param Data The sensor data object.
 * @param Page The page to display (1 = Arm times, 2 = Disarm times, 3 = Trigger times).
 */
void Display_Module_ViewLogs(SensorData * Data, uint8_t Page);

/**
 * Converts a BCD value into a string. This is used before an RTC value
 * can be displayed on the screen.
 * @param BCD The BCD value.
 * @param Sting Pointer to a string where the value will be saved.
 */
void ConvertBCDToString(uint8_t BCD, char * String);

/**
 * Display the splash screen on system startup.
 */
void Display_Splash_Screen(void);

/**
 * Displays the arming screen with a countdown.
 * @param Date The sensor data object.
 */
void Display_Module_ArmingScreen(SensorData * Data);

/**
 * Displays a warning message on the top of the display.
 * @param Message The message to display.
 */
void Display_Module_Warning(char * Message);

/**
 * Displays a message on the top of the display.
 * @param Message The message to display.
 */
void Display_Module_Message(char * Message);

/**
 * Displays a "success" message at the top of the screen.
 * @param Message The message to display.
 */
void Display_Module_GreenMessage(char * Message);

/**
 * Remove the message from the top of the display.
 */
void Display_Module_RemoveWarning();

/**
 * Sets up PWM output for the display backlight.
 */
void Display_Module_Backlight(void);

/**
 * Update the backlight on the display. The value will be updated based
 * on the specified duty cycle provided in the sensor data object.
 * @param Data The sensor data object.
 */
void Display_Module_UpdateBacklight(SensorData * Data);


#endif
