#include "../Config.h"
#include "../Protocols/I2C.h"

#define YEAR 6
#define MONTH 5
#define DAY 4
#define HOUR 2
#define MINUTE 1
#define SECOND 0
#define TEMPERATURE 18
#define TEMP_DECIMAL 19

#define TOTAL_READINGS 19

void RTC_Module_Read(SensorData * Data);
