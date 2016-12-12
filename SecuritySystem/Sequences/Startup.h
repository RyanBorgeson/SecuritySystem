/**
 * Handles starting up and initalizing all modules and components
 * used in the system.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */
#ifndef STARTUP_H
#define STARTUP_H

#include "../Config.h"

#define SPLASH_DELAY 25000

static uint32_t MCLKClockSpeed;
static uint32_t	SMCLKClockSpeed;
static uint32_t	ACLKClockSpeed;

/**
 * Main startup sequence.
 * @param Data The sensor data object.
 */
void Startup_Sequence(SensorData * Data);

#endif
