/**
 * Sets up the watch dog timer. The watchdog timer flag must be cleared
 * throughout the program. If the counter times out the system will reset to
 * its initial state. This is to prevent it from locking up.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */

#ifndef WATCHDOG_H
#define WATCHDOG_H


#include "../Config.h"

/**
 * Initialize and configure the watchdog timer for a
 * 4 second timeout.
 */
void Watchdog_Init(void);

/**
 * Clear the watchdog timer flag so the device does not reset.
 */
void Watchdog_Clear(void);

#endif
