#include "RTC.h"

void RTC_Module_Write(uint8_t Year, uint8_t Month, uint8_t DayOfWeek, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second) {
	// Set Master in transmit mode.
	MAP_I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_MODE);
	// Wait for bus release, ready to write.
	while (MAP_I2C_isBusBusy(EUSCI_B1_BASE));
	// Set pointer to beginning of RTC registers.
	MAP_I2C_masterSendMultiByteStart(EUSCI_B1_BASE,0);
	// Write to seconds register.
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, Second);
	// Write to minutes register.
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, Minute);
	// Write to hours register.
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, Hour);
	// Write to day register.
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, Day);
	// Write to date register.
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, DayOfWeek);
	// Write to months register.
	MAP_I2C_masterSendMultiByteNext(EUSCI_B1_BASE, Month);
	// Write to year register and send stop.
	MAP_I2C_masterSendMultiByteFinish(EUSCI_B1_BASE, Year);
}


void RTC_Module_Read(SensorData * Data) {

	// Set Master in transmit mode.
	MAP_I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_TRANSMIT_MODE);
	// Wait for bus release, ready to write.
	while (MAP_I2C_isBusBusy(EUSCI_B1_BASE));
	// Set pointer to beginning of RTC registers.
	MAP_I2C_masterSendSingleByte(EUSCI_B1_BASE,0);
	// Wait for bus release.
	while (MAP_I2C_isBusBusy(EUSCI_B1_BASE));
	// Set Master in receive mode.
	MAP_I2C_setMode(EUSCI_B1_BASE, EUSCI_B_I2C_RECEIVE_MODE);
	// Wait for bus release, ready to receive.
	while (MAP_I2C_isBusBusy(EUSCI_B1_BASE));

/*
	// Read time, date, and temperature from RTC registers.
	// DateTime type definition that holds the returned data.
	DateTime Now;
	int i;

	// Read all results and save RTC register values.
	for (i = 0; i < TOTAL_READINGS; i++) {
		Data->RTC[i] = MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);

		// Save date and time.
		Now.Day = (i == DAY) ? Data->RTC[DAY] : Now.Day;
		Now.Month = (i == MONTH) ? Data->RTC[MONTH] : Now.Month;
		Now.Year = (i == YEAR) ? Data->RTC[YEAR] : Now.Year;
		Now.Hour = (i == HOUR) ? Data->RTC[HOUR] : Now.Hour;
		Now.Minute = (i == MINUTE) ? Data->RTC[MINUTE] : Now.Minute;
		Now.Seconds = (i == SECOND) ? Data->RTC[SECOND] : Now.Seconds;

		// Save temperature information.
		Data->Temperature = (i == TEMPERATURE) ? Data->RTC[TEMPERATURE] : Data->Temperature;
		Data->TempDecimal = (i == TEMP_DECIMAL) ? Data->RTC[TEMP_DECIMAL] : Data->TempDecimal;
	}

	// Add date and time to the data object.
	Data->DateTime = Now;
*/
	ClockRegisters[0]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[1]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[2]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[3]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[4]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[5]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[6]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[7]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[8]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[9]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[10]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[11]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[12]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[13]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[14]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[15]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[16]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[17]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);
	ClockRegisters[18]=MAP_I2C_masterReceiveSingleByte(EUSCI_B1_BASE);

}
