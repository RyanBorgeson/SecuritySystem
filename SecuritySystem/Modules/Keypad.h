/**
 * Handles keypad interaction and debounce for the keypad. Also, saves the
 * current button press.
 * @Date 12/12/2016
 */

#ifndef KEYPAD_H
#define KEYPAD_H

#include "../Config.h"


/**
 * Initialize and setup keypad on the correct pins.
 * @param Data The sensor data object.
 */
void Keypad_Init(SensorData * Data);


/**
 * Scan keys looks at each column to determine if it has been pressed.
 * If so, the row will then be checked. When a column is not being check
 * it is set to a high impedance to protect the I/O.
 */
void Keypad_Scan(void);


/**
 * Handles keypad debounce and returns true if the keypad
 * was successfully debounced. Otherwise, a successful debounce has not
 * occured.
 * @return The state of the debounce.
 */
uint8_t Keypad_Debounce(void);

/**
 * Saves the button press in the data object and returns true if the
 * key was successfully determined.
 * @param PressedKey The key that was pressed.
 * @param Data The sensor data object.
 * @return Return true if valid key press or false if invalid.
 */
int Keypad_SaveButtonPress(uint16_t PressedKey, SensorData * Data);

/**
 * Inserts the selected key into the sensor data object where the
 * value is stored.
 * @param Key The pressed key.
 * @param Data The sensor data object.
 */
void Keypad_InsertKeyCombo(char Key, SensorData * Data);

/**
 * Checks the state of the keypad and then continues on the debounce
 * and store the key press if there is a valid press.
 * @param Data The sensor data object.
 */
void Keypad_Execute(SensorData * Data);


/**
 * Checks the state of the keypad and then continues on the debounce
 * and store the key press if there is a valid press. This is used when
 * the user is entering their pin.
 * @param Data The sensor data object.
 * @param Count the number of digits that have been entered.
 */
void Keypad_ExecuteForPinEnter(SensorData * Data, int * Count);

#endif
