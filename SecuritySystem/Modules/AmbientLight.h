/**
 * Ambient light sensor methods for reading ADC values from external photoresistor.
 * @Author Ryan Borgeson
 * @Date 11/3/2016
 */
#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "../Config.h"


#define NORMALIZED_VOLTAGE 3.3
#define AMBIENT_MAX_VOLTAGE 2.4


/**
 * Initialize photoresistor pins and ADC.
 */
void AmbientLight_Module_Init(void);


/**
 * Read ambient light reading from the photoresistor and store the value
 * in a sensor data structure.
 * @param Data Sensor data and readings.
 */
void AmbientLight_Module_Read(SensorData * Data);


#endif
