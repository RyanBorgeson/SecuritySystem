/**
 * Handles the rotation of the stepper motor. This will lock and unlock
 * the door when the user has entered their pin.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */
#include "Motor.h"


void Motor_RotateCounterClockwise(void) {
	Watchdog_Clear();

	// Used to determine how far the motor has rotated.
	int count = 0;

	// Set each port to an output.
	P4->OUT |= (BIT2 | BIT3 | BIT4 | BIT5);

	while(1) {
		// Clear the watchdog timer at each iteration so it does not time out.
		Watchdog_Clear();

		// Stop the rotation at 90 degrees.
		if (count < 8 * 4 * 5) {

			P4->OUT |= BIT2 | BIT5;
			P4->DIR &= ~(BIT3 | BIT4);
			SysTick_delay(4);
			P4->DIR |= BIT4 | BIT5;
			P4->DIR &= ~(BIT2 | BIT3);
			SysTick_delay(4);
			P4->DIR |= BIT3 | BIT4;
			P4->DIR &= ~(BIT2 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT2 | BIT3;
			P4->DIR &= ~(BIT4 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT2 | BIT5;
			P4->DIR &= ~(BIT3 | BIT4);
			SysTick_delay(4);
			P4->DIR |= BIT4 | BIT5;
			P4->DIR &= ~(BIT2 | BIT3);
			SysTick_delay(4);
			P4->DIR |= BIT3 | BIT4;
			P4->DIR &= ~(BIT2 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT2 | BIT3;
			P4->DIR &= ~(BIT4 | BIT5);
			SysTick_delay(4);

			count++;
		} else {
			break;
		}
	}

	// Disable the outputs to conserve power.
	P4->DIR &= ~(BIT2 | BIT3);
	P4->DIR &= ~(BIT4 | BIT5);
}


void Motor_RotateClockwise(void) {
	Watchdog_Clear();

	// Used to determine how far the motor has rotated.
	int count = 0;

	// Set each port to an output.
	P4->OUT |= (BIT2 | BIT3 | BIT4 | BIT5);

	while(1) {
		// Clear the watchdog timer at each iteration so it does not time out.
		Watchdog_Clear();

		// Stop the rotation at 90 degrees.
		if (count < 8 * 4 * 4) {

			P4->DIR |= BIT2 | BIT3;
			P4->DIR &= ~(BIT4 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT3 | BIT4;
			P4->DIR &= ~(BIT2 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT4 | BIT5;
			P4->DIR &= ~(BIT2 | BIT3);
			SysTick_delay(4);
			P4->DIR |= BIT2 | BIT5;
			P4->DIR &= ~(BIT3 | BIT4);
			SysTick_delay(4);
			P4->DIR |= BIT2 | BIT3;
			P4->DIR &= ~(BIT4 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT3 | BIT4;
			P4->DIR &= ~(BIT2 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT4 | BIT5;
			P4->DIR &= ~(BIT2 | BIT3);
			SysTick_delay(4);
			P4->DIR |= BIT2 | BIT5;
			P4->DIR &= ~(BIT3 | BIT4);
			SysTick_delay(4);

			count++;
		} else {
			break;
		}
	}

	// Disable the outputs to conserve power.
	P4->DIR &= ~(BIT2 | BIT3);
	P4->DIR &= ~(BIT4 | BIT5);
}
