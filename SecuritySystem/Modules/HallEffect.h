/**
 * Hall Effect file header that contains an outline of the methods
 * used to gather sensor readings from the hall effect sensors.
 * @Author Ryan Borgeson
 * @Date 10/27/2016
 */

#ifndef HALLEFFECT_H
#define HALLEFFECT_H

#include "../Config.h"

/**
 * Initializes Hall Effect sensors by setting their pins as inputs.
 * Also, pull-up resistor are used to ensure the initial value is high.
 */
void HallEffect_Init(void);

/**
 * Reads the data from the Hall Effect sensors and stores it along with
 * the rest of the sensor data. Gathers data from any and all hall effect
 * sensors. Will return HIGH if no magnetic field is detected and will
 * return LOW if a magnetic field is detected.
 * @param Data Sensor data object.
 */
void HallEffect_Module_Read(SensorData * Data);

#endif
