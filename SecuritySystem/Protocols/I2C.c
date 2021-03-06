/**
 * Configures and setups up the I2C module for use with the
 * SMCLK clock source. This allow for communication between the RTC
 * and MSP432.
 */
#include "I2C.h"

/* I2C Master Configuration Parameter */
const eUSCI_I2C_MasterConfig i2cConfig =
{
	EUSCI_B_I2C_CLOCKSOURCE_SMCLK, 		// SMCLK Clock Source
	3000000, 							// SMCLK = 3MHz
	EUSCI_B_I2C_SET_DATA_RATE_400KBPS,  // Desired I2C Clock of 400khz
	0,									// No byte counter threshold
	EUSCI_B_I2C_NO_AUTO_STOP			// No Autostop
};

void I2C_Init(void) {

	// Select Port 6 for I2C
	// Set Pin 4, 5 to input Primary Module Function,
	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6,
	GPIO_PIN4 + GPIO_PIN5, GPIO_PRIMARY_MODULE_FUNCTION);

	/* Initializing I2C Master to SMCLK at 400kbs with no autostop */
	MAP_I2C_initMaster(EUSCI_B1_BASE, &i2cConfig);
	/* Specify slave address */
	MAP_I2C_setSlaveAddress(EUSCI_B1_BASE, RTC_MODULE_ADDRESS);
	/* Set Master in transmit mode */
	MAP_I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_MODE);
	/* Enable I2C Module to start operations */
	MAP_I2C_enableModule(EUSCI_B1_BASE);
}

