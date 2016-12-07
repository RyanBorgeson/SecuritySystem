#include "Motor.h"


void Motor_RotateClockwise(void) {
			P4->DIR |= BIT2;
			P4->DIR &= ~(BIT3 | BIT4 | BIT5);
			SysTick_delay(10000);
			P4->DIR |= BIT3;
			P4->DIR &= ~(BIT2 | BIT4 | BIT5);
			SysTick_delay(10000);
			P4->DIR |= BIT4;
			P4->DIR &= ~(BIT2 | BIT3 | BIT5);
			SysTick_delay(10000);
			P4->DIR |= BIT5;
			P4->DIR &= ~(BIT2 | BIT3 | BIT4);
			SysTick_delay(10000);

}
