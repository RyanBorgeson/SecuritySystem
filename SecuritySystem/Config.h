#include "driverlib.h"

#include "Protocols/I2C.h"
#include "Protocols/ADC.h"
#include "Protocols/UART.h"
#include "Modules/Clock.h"
#include "Modules/RTC.h"
#include "Modules/AmbientLight.h"
#include "Modules/HallEffect.h"
#include "Modules/ST7735.h"

#include "Structures/SensorData.h"


/* Define number of sensors. Will need to be updated if more are added. */
#define NUM_PROXIMITY_SENSORS 3
#define NUM_HALLEFFECT_SENSORS 3

/* RTC Module information and pin mappings. */
#define RTC_MODULE_ADDRESS 0b1101000

/* I2C Module Pin Mappings. */
/* Modify this if more I2C pins need to be specified. */
#define I2C_PORT GPIO_PORT_P6
#define I2C_PINS (GPIO_PIN4 + GPIO_PIN5)

/* ADC Module Pin Mappings. */
/* Modify this to add additional pins and ports to use for ADC. */
#define ADC_PORT GPIO_PORT_P5
#define ADC_PINS GPIO_PIN5

/* Define Port and Pin mappings for Hall effect sensors. */
#define HALL_EFFECT_PORT_1 GPIO_PORT_P4
#define HALL_EFFECT_PORT_2 GPIO_PORT_P6
#define HALL_EFFECT_PIN_1 GPIO_PIN0
#define HALL_EFFECT_PIN_2 GPIO_PIN1
