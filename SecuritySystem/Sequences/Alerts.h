/**
 * Alerts determines when the alarm should sound based on certain events.
 * Each event that should trigger the alarm will be specified below.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */

#ifndef ALERT_H
#define ALERT_H

#include "../Config.h"

#define DOOR 0
#define WINDOW 1
#define PROXIMITY 2

/**
 * Alerts the user either audibly or visually using the display. Based on certain
 * sensor readings or environmental triggers the system will alert the user.
 * @param Data The sensor data object.
 */
void Alerts(SensorData * Data);

#endif
