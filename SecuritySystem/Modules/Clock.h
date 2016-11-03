/**
 * Configure and setup various internal and external clock sources and clock frequencies.
 * @Author Ryan Borgeson & TI MSP432 Technical Manual
 * @Date 11/3/2016
 */
#ifndef CLOCK_H
#define CLOCK_H

#include "../Config.h"


#define EXTERNAL_CLOCK_SOURCE_FREQUENCY 48000000


/**
 * Initialize clock to 48MHz using external oscillator. Values for MCLK and SMCLK and be
 * determined using the getMCLK() and getSMCLK() methods.
 */
void Clock_Init48MHz();

/**
* Initilizes SysTick timer, but must be configured to work with the
* selected master clock frequency.
*/
void SysTick_Init(void);

/**
* Sets up SysTick timer delay which provides a accurate delay using the
* system clock. Waits for a flag to be thrown before continuing.
* @param delay Delay in milliseconds to wait.
*/
void SysTick_delay(uint16_t Delay);

#endif
