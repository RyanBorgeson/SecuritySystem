/**
 * The buzzzer module provides audible feedback by providing options
 * to toggle between tones or play a single tone on the buzzer.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */

#ifndef BUZZER_H
#define BUZZER_H

#include "../Config.h"


/**
 * Setup the buzzer and PWM signal on the correct pins.
 */
void Buzzer_Init(void);


/**
 * Disable the buzzer module so it is unable to produce any sound.
 */
void Buzzer_Module_Off(void);

/**
 * Perform a single tone on the buzzer.
 */
void Buzzer_Module_SingleTone(void);

/**
 * Turn the buzzer module on.
 */
void Buzzer_Module_On(void);

/**
 * Toggle between frequencies. In this case, the buzzer will toggle
 * between high and low frequencies.
 */
void Buzzer_Module_ToggleTone(void);


#endif
