#include "driverlib.h"
#include "Structures/SensorData.h"



/* Define number of sensors. Will need to be updated if more are added. */
#define NUM_PROXIMITY_SENSORS 3
#define NUM_HALLEFFECT_SENSORS 3


/* RTC Module information and pin mappings. */
#define RTC_MODULE_ADDRESS 0b1101000

/* I2C Module Pin Mappings. */
#define I2C_PORT GPIO_PORT_P6
#define I2C_PINS (GPIO_PIN4 + GPIO_PIN5)


