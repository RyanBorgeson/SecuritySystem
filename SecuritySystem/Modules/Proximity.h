/**
 * Proximity sensors detect motion or movement from a 10 foot distance. This
 * initializes pins, pull-up resistors, and reads input from the pins.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */

#ifndef PROXIMITY_H
#define PROXIMITY_H

#include "../Config.h"

#define PROXIMITY_PORTS GPIO_PORT_P5
#define PROXIMITY_PINS GPIO_PIN4

/**
 * Initialize and configure pins for the proximity sensor.
 */
void Proximity_Init(void);

/**
 * Read and store the value read from the proximity sensor.
 * @param Data The sensor data object.
 */
void Proximity_Module_Read(SensorData * Data);

#endif
