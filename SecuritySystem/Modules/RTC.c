#include "RTC.h"

/**
 * I2C Writes a specified date and time to the DS3231 over I2C.
 * Times and Dates must be declared using BCD.
 * Source Code From TI MSP432 Technical Manual.
 * @param Year The Year.
 * @param Month The Month.
 * @param DayOfWeek The day of the week. (Monday - Sunday).
 * @param Day The day of the month.
 * @param Hour The Hour.
 * @param Minute The minute.
 * @param Second The seconds.
 */
void RTC_Module_Write(uint8_t Year, uint8_t Month, uint8_t DayOfWeek, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second) {
	/* Set Master in transmit mode */
	MAP_I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_MODE);
	// Wait for bus release, ready to write
	while (MAP_I2C_isBusBusy(EUSCI_B1_BASE));
	// set pointer to beginning of RTC registers
	MAP_I2C_masterSendMultiByteStart(EUSCI_B1_BASE,0);
	// and write to seconds register
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, Second);
	// write to minutes register
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, Minute);
	// write to hours register
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, Hour);
	// write to day register
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, Day);
	// write to date register
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, DayOfWeek);
	// write to months register
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, Month);
	// write to year register and send stop
	MAP_I2C_masterSendMultiByteFinish(EUSCI_B1_BASE, Year);
}


/**
 * I2C Reads the values from the RTC and stores them in an
 * array byte by byte.
 * Source Code From TI MSP432 Technical Manual.
 */
void RTC_Module_Read(SensorData * Data) {
	// Set Master in transmit mode
	MAP_I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_MODE);
	// Wait for bus release, ready to write
	while (MAP_I2C_isBusBusy(EUSCI_B1_BASE));
	// set pointer to beginning of RTC registers
	MAP_I2C_masterSendSingleByte(EUSCI_B1_BASE,0);
	// Wait for bus release
	while (MAP_I2C_isBusBusy(EUSCI_B1_BASE));
	// Set Master in receive mode
	MAP_I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_RECEIVE_MODE);
	// Wait for bus release, ready to receive
	while (MAP_I2C_isBusBusy(EUSCI_B1_BASE));
	// read from RTC registers (pointer auto increments after each read)


	DateTime Now;

	int i;
	for (i = 0; i < TOTAL_READINGS; i++) {
		Data->RTC[i] = MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);

		Now.Day = (i == DAY) ? Data->RTC[DAY] : Now.Day;
		Now.Month = (i == MONTH) ? Data->RTC[MONTH] : Now.Month;
		Now.Year = (i == YEAR) ? Data->RTC[YEAR] : Now.Year;
		Now.Hour = (i == HOUR) ? Data->RTC[HOUR] : Now.Hour;
		Now.Minute = (i == MINUTE) ? Data->RTC[MINUTE] : Now.Minute;
		Now.Seconds = (i == SECOND) ? Data->RTC[SECOND] : Now.Seconds;

		Data->Temperature = (i == TEMPERATURE) ? Data->RTC[TEMPERATURE] : Data->Temperature;
		Data->TempDecimal = (i == TEMP_DECIMAL) ? Data->RTC[TEMP_DECIMAL] : Data->TempDecimal;
	}

	Data->DateTime = Now;
}
