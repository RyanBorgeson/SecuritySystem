/**
 * Handles wireless communication between the MSP432 and the ESP8266
 * using the AT command set. The system can connect to a wireless network
 * and post information to the specified server.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */

#ifndef WIRELESS_H
#define WIRELESS_H
#include "../Config.h"


#define PATTERN_OK "OK"
#define PATTERN_ERROR "ERROR"
#define MAX_PATTERN_BUFFER 30


/**
 * Intialize the wireless module and UART/ESCI module in order to talk
 * with the ESP8266 device.
 */
void Wireless_Init(void);

/**
 * The will send the request using a POST to a remote server. Headers and
 * a payload are created before sending the information.
 * @param Data The sensor data object.
 */
void SendPostRequest(SensorData * Data);

/**
 * Check for a specific pattern within a received bit stream. Takes
 * in an character array and waits until that pattern is receieved.
 * @param Pattern The pattern to look for.
 */
void PatternCheck(char * Pattern);

#endif
