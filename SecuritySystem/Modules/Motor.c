#include "Motor.h"


void Motor_RotateCounterClockwise(void) {
	Watchdog_Clear();

	int count = 0;

	while(1) {
		Watchdog_Clear();

		if (count < 8 * 4 * 4) {

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
			count++;
		} else {
			break;
		}
	}
}


void Motor_RotateClockwise(void) {
	Watchdog_Clear();

	int count = 0;

	while(1) {
		Watchdog_Clear();

		if (count < 8 * 4 * 4) {


			P4->DIR |= BIT2 | BIT3;
			P4->DIR &= ~(BIT4 | BIT5);
			SysTick_delay(3);
			P4->DIR |= BIT3 | BIT4;
			P4->DIR &= ~(BIT2 | BIT5);
			SysTick_delay(3);
			P4->DIR |= BIT4 | BIT5;
			P4->DIR &= ~(BIT2 | BIT3);
			SysTick_delay(3);
			P4->DIR |= BIT2 | BIT5;
			P4->DIR &= ~(BIT3 | BIT4);
			SysTick_delay(3);
			P4->DIR |= BIT2 | BIT3;
			P4->DIR &= ~(BIT4 | BIT5);
			SysTick_delay(3);
			P4->DIR |= BIT3 | BIT4;
			P4->DIR &= ~(BIT2 | BIT5);
			SysTick_delay(3);
			P4->DIR |= BIT4 | BIT5;
			P4->DIR &= ~(BIT2 | BIT3);
			SysTick_delay(3);
			P4->DIR |= BIT2 | BIT5;
			P4->DIR &= ~(BIT3 | BIT4);

			count++;
		} else {
			break;
		}
	}
}
