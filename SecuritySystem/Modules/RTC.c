#include "RTC.h"
#include "driverlib.h"
#include "../Config.h"
#include "../Protocols/I2C.h"
#include "../Structures/SensorData.h"

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
void RTC_Module_Read(SensorData Data) {
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
	/*Data->RTC[0]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[1]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[2]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[3]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[4]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[5]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[6]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[7]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[8]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[9]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[10]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[11]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[12]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[13]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[14]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[15]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[16]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[17]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	Data->RTC[18]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);*/
}
