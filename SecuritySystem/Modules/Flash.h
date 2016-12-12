/**
 * Methods that handle interaction between ram and flash. Allows
 * information to be stored in flash and read again once the system
 * boots up.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */
#ifndef FLASH_H
#define FLASH_H

#include "../Config.h"


/**
 * Reads the date and time information from flash and stores it in the
 * date information array.
 * @param Date Date information array.
 */
void Flash_Module_Read(SavedInformation * Info);


/**
 * Save to flash allows the date information to be saved to flash so that
 * when the device is powered down and then back up the date information will
 * be saved.
 * @param Date Date information array to save.
 */
void Flash_Module_SaveToFlash(SavedInformation * Info);


/**
 * Push DateTime Up will push older dates up in the date information array.
 * This will allow for older dates to drop off and new dates to be added to
 * the array easily.
 * @param Date Array containing all five dates.
 */
void Flash_Module_PushDateTimeUp(uint8_t * Date);


/**
 * Similar to the push date timeup method, however, this takes into account the
 * source of the trigger and also saves that information.
 * @param Date Date of the trigger.
 * @param Source Source that triggered the alarm.
 */
void Flash_Module_PushDateTimeUpTrigger(uint8_t * Date, char Source);


#endif
