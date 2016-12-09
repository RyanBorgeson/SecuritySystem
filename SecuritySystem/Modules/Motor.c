#include "Motor.h"


void Motor_RotateCounterClockwise(void) {
	Watchdog_Clear();

	int count = 0;

	P4->OUT |= (BIT2 | BIT3 | BIT4 | BIT5);


	while(1) {
		Watchdog_Clear();

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

			/*
			P4->DIR |= BIT5;
			P4->DIR &= ~(BIT2 | BIT3 | BIT4);
			SysTick_delay(4);
			P4->DIR |= BIT4;
			P4->DIR &= ~(BIT2 | BIT3 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT3;
			P4->DIR &= ~(BIT2 | BIT4 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT2;
			P4->DIR &= ~(BIT3 | BIT4 | BIT5);
			SysTick_delay(4);*/

			count++;
		} else {
			break;
		}
	}
	P4->DIR &= ~(BIT2 | BIT3);
	P4->DIR &= ~(BIT4 | BIT5);
}


void Motor_RotateClockwise(void) {
	Watchdog_Clear();

	int count = 0;

	P4->OUT |= (BIT2 | BIT3 | BIT4 | BIT5);

	while(1) {

		Watchdog_Clear();

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

/*
			P4->DIR |= BIT2;
			P4->DIR &= ~(BIT3 | BIT4 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT3;
			P4->DIR &= ~(BIT2 | BIT4 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT4;
			P4->DIR &= ~(BIT2 | BIT3 | BIT5);
			SysTick_delay(4);
			P4->DIR |= BIT5;
			P4->DIR &= ~(BIT2 | BIT3 | BIT4);
			SysTick_delay(4);
*/
			count++;
		} else {
			break;
		}
	}
	P4->DIR &= ~(BIT2 | BIT3);
	P4->DIR &= ~(BIT4 | BIT5);
}
