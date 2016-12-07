#include "Flash.h"



/**
 * Reads the date and time information from flash and stores it in the
 * date information array.
 * @param Date Date information array.
 */
void Flash_Module_Read(SavedInformation * Info) {
	 // point to address in flash
	SavedInformation * addr_pointer = CALIBRATION_START + 1;
	*(Info) = *(addr_pointer);
}

/**
 * Save to flash allows the date information to be saved to flash so that
 * when the device is powered down and then back up the date information will
 * be saved.
 * @param Date Date information array to save.
 */
void Flash_Module_SaveToFlash(SavedInformation * Info) {
	/* Setting MCLK to 48MHz for faster programming */
	MAP_PCM_setCoreVoltageLevel(PCM_VCORE1);

	FlashCtl_setWaitState(FLASH_BANK0, 2);
	FlashCtl_setWaitState(FLASH_BANK1, 2);

	/* Unprotecting Info Bank 0, Sector 0 */
	MAP_FlashCtl_unprotectSector(FLASH_INFO_MEMORY_SPACE_BANK0,FLASH_SECTOR0);

	/* Erase the flash sector starting CALIBRATION_START. */
	while(!MAP_FlashCtl_eraseSector(CALIBRATION_START));

	/* Program the flash with the new data. */
	while (!MAP_FlashCtl_programMemory(Info, (void*) CALIBRATION_START + 1, 99)); // Note: leave first byte unprogrammed

	/* Setting the sector back to protected */
	MAP_FlashCtl_protectSector(FLASH_INFO_MEMORY_SPACE_BANK0,FLASH_SECTOR0);
}



/**
 * Push DateTime Up will push older dates up in the date information array.
 * This will allow for older dates to drop off and new dates to be added to
 * the array easily.
 * @param Date Array containing all five dates.
 */
void Flash_Module_PushDateTimeUp(uint8_t * Date) {
	int i, x;
	for (x = 0; x < 6; x++)
		for (i = 30; i > 0; i--) {
			*(Date + i) = *(Date + (i - 1));
		}

	*(Date) = ClockRegisters[5];
	*(Date + 1) = ClockRegisters[4];
	*(Date + 2) = ClockRegisters[6];
	*(Date + 3) = ClockRegisters[2];
	*(Date + 4) = ClockRegisters[1];
	*(Date + 5) = ClockRegisters[0];

}

void Flash_Module_PushDateTimeUpTrigger(uint8_t * Date, char Source) {
	int i, x;
	for (x = 0; x < 7; x++)
		for (i = 35; i > 0; i--) {
			*(Date + i) = *(Date + (i - 1));
		}

	*(Date) = ClockRegisters[5];
	*(Date + 1) = ClockRegisters[4];
	*(Date + 2) = ClockRegisters[6];
	*(Date + 3) = ClockRegisters[2];
	*(Date + 4) = ClockRegisters[1];
	*(Date + 5) = ClockRegisters[0];
	*(Date + 6) = Source;

}
