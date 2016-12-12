/**
 * Configures and setups up the I2C module for use with the
 * SMCLK clock source. This allow for communication between the RTC
 * and MSP432.
 */
#ifndef I2C_H
#define I2C_H

#include "../Config.h"



/**
 * Initialize I2C module to be used with DS3231 RTC. Setup
 * Pin output, initiate master, and determine slave address.
 * Source Code From TI MSP432 Technical Manual.
 */
void I2C_Init(void);



#endif
