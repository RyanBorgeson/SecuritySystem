/**
 * RTC Module handles date, time, and temperature information. Below are
 * is the configuration and method calls associated with the RTC Module.
 * @Author Ryan Borgeson
 * @Date 10/21/2016
 */

#ifndef RTC_H
#define RTC_H

#include "../Config.h"

/* Define RTC register indexes. */
#define YEAR 6
#define MONTH 5
#define DAY 4
#define HOUR 2
#define MINUTE 1
#define SECOND 0
#define TEMPERATURE 17
#define TEMP_DECIMAL 18

/* Totals readings from the RTC Module. */
#define TOTAL_READINGS 19


/**
 * I2C Writes a specified date and time to the DS3231 over I2C.
 * Times and Dates must be declared using BCD.
 * Source Code From TI MSP432 Technical Manual.
 * @param Year The Year.
 * @param Month The Month.
 * @param DayOfWeek The day of the week. (Monday - Sunday).
 * @param Day The day of the month.
 * @param Hour The Hour.
 * @param Minute The minute.
 * @param Second The seconds.
 */
void RTC_Module_Write(uint8_t Year, uint8_t Month, uint8_t DayOfWeek, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second);


/**
 * I2C Reads the values from the RTC and stores the results for
 * date, time, and temperature readings.
 * @param Data Expects sensor data type to write results to.
 */
void RTC_Module_Read(SensorData * Data);


#endif
