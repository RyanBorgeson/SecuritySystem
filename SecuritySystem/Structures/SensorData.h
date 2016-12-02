/**
 * Global data structure containing information from gathered sensor readings.
 * All sensor readings should be contained within these structures
 * for easy access throughout the program.
 * @Author Ryan Borgeson
 * @Date 10/18/2016
 */

#ifndef SENSORDATA_H
#define SENSORDATA_H

#include "../Config.h"

/**
 * DataTime structure that contains Year, Month, Day, Hour, Minute, and Seconds
 * that are read from the RTC Module.
 */
typedef struct {
	uint16_t Year;
	uint16_t Month;
	uint16_t Day;
	uint16_t Hour;
	uint16_t Minute;
	uint16_t Seconds;
} DateTime;

/**
 * RGB LED information which determines the color of the RGB LED.
 */
typedef struct {
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
} RGB_LED;

/**
 * Main Sensor data structure that combines all nested structures that allow
 * for all sensor readings and data to be access from one globally variable.
 * If additional sensors or readings are required this structure can be added to.
 */
typedef struct {
   double Photoresistor;
   uint16_t PhotoresistorADC;
   uint16_t LEDDutyCycle;

   uint16_t Temperature;
   uint16_t TempDecimal;
   uint16_t Proximity[NUM_PROXIMITY_SENSORS];
   uint8_t HallEffect[NUM_HALLEFFECT_SENSORS];
   char KeyCombo[4];

   uint16_t RTC[19];
   DateTime DateTime;
   RGB_LED LED;
} SensorData;

#endif
