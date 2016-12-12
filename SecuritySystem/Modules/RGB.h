/**
 * Controls the color of the external RGB LED.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */

#ifndef RGB_H
#define RGB_H

#include "../Config.h"

#define RED 4
#define MAGENTA 2
#define BLUE 3
#define CYAN 1
#define GREEN 5
#define YELLOW 6
#define WHITE 7
#define BLACK 8


/**
 * Initialize and configure the correct pins for the RGB LED.
 */
void RGB_Init(void);

/**
 * Toggles the input/output state of the RGB LED.
 */
void RGB_Module_Toggle(void);

/**
 * Changes the color of the RGB LED.
 * @param Color The color of the LED.
 */
void RGB_Module_SetColor(int Color);

#endif
