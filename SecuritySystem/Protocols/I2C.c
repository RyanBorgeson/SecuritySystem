/*
 * I2C.c
 *
 *  Created on: Oct 18, 2016
 *      Author: Ryan
 */
#include "I2C.h"

/* I2C Master Configuration Parameter */
const eUSCI_I2C_MasterConfig i2cConfig =
{
	// SMCLK Clock Source
	EUSCI_B_I2C_CLOCKSOURCE_SMCLK,
	// SMCLK = 48MHz
	48000000,
	// Desired I2C Clock of 400khz
	EUSCI_B_I2C_SET_DATA_RATE_400KBPS,
	// No byte counter threshold
	0,
	// No Autostop
	EUSCI_B_I2C_NO_AUTO_STOP
};


/**
 * Initialize I2C module to be used with DS3231 RTC. Setup
 * Pin output, initiate master, and determine slave address.
 * Source Code From TI MSP432 Technical Manual.
 */
void I2C_Init(void) {

	// Select Port 6 for I2C
	// Set Pin 4, 5 to input Primary Module Function,
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(I2C_PORT,
			I2C_PINS, GPIO_PRIMARY_MODULE_FUNCTION);

	/* Initializing I2C Master to SMCLK at 400kbs with no autostop */
	MAP_I2C_initMaster(EUSCI_B1_BASE, &i2cConfig);
	/* Specify slave address */
	MAP_I2C_setSlaveAddress(EUSCI_B1_BASE, RTC_MODULE_ADDRESS);
	/* Set Master in transmit mode */
	MAP_I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_MODE);
	/* Enable I2C Module to start operations */
	MAP_I2C_enableModule(EUSCI_B1_BASE);
}

