#ifndef MAINSEQUENCE_H
#define MAINSEQUENCE_H

#include "../Config.h"

/**
 * Main sequence performs and executes each state and determines
 * which state it should be in. Almost everything happens within the
 * main sequence.
 * @param Data Sensor data object.
 */
void Main_Sequence(SensorData * Data);

/**
 * Timer interrupt handler that executes based on the specified Timer A0.
 * This provides an interrupt that triggers multiple times a second and updates
 * various parts of the program.
 */
void TA0_0_IRQHandler();

/**
 * Equal pins determines if the saved pin and the entered pin match when
 * being entered on the keypad.
 */
int EqualPins(char * SavedPin, char * EnteredPin);

/**
 * Gather sensor data grabs readings from each sensor and updates
 * it throughout the rest of the application.
 */
void GatherSensorData(SensorData * Data);


#endif
