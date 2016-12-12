/**
 * Sets up the watch dog timer. The watchdog timer flag must be cleared
 * throughout the program. If the counter times out the system will reset to
 * its initial state. This is to prevent it from locking up.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */
#include "Watchdog.h"

void Watchdog_Init(void) {
	WDT_A_initWatchdogTimer(WDT_A_CLOCKSOURCE_ACLK, WDT_A_CLOCKITERATIONS_32K);
	WDT_A_setTimeoutReset(WDT_A_SOFT_RESET);
	WDT_A_startTimer();
}

void Watchdog_Clear(void) {
	WDT_A_clearTimer();
}
