/**
 * Global data structure containing information from gathered sensor readings.
 * All sensor readings should be contained within these structures
 * for easy access throughout the program.
 * @Author Ryan Borgeson
 * @Date 10/18/2016
 */

/* Define number of sensors. Will need to be updated if more are added. */
#define NUM_PROXIMITY_SENSORS 3
#define NUM_HALLEFFECT_SENSORS 3

/**
 * DataTime structure that contains Year, Month, Day, Hour, Minute, and Seconds
 * that are read from the RTC Module.
 */
struct DateTime {
	uint16_t Year;
	uint16_t Month;
	uint16_t Day;
	uint16_t Hour;
	uint16_t Minute;
	uint16_t Seconds;
};

/**
 * RGB LED information which determines the color of the RGB LED.
 */
struct RGB_LED {
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
};

/**
 * Main Sensor data structure that combines all nested structures that allow
 * for all sensor readings and data to be access from one globally variable.
 * If additional sensors or readings are required this structure can be added to.
 */
struct SensorData {
   uint16_t Photoresistor;
   uint16_t Temperature;
   uint16_t Proximity[NUM_PROXIMITY_SENSORS];
   uint16_t HallEffect[NUM_HALLEFFECT_SENSORS];

   struct DateTime DateTime;
   struct RGB_LED LED;

} SensorData;


