#include "Keypad.h"


volatile uint8_t Keypressed = 0;


void Keypad_Init(void) {

	GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);

	MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);
	MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
	MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);

	RGB_Init();
}


void Keypad_Scan(void) {
	P5->DIR |= BIT0; // Set column C0 to output, and others to remain high Z.(PIN 5.0)
	P5->OUT &= ~BIT0; // Set column C0 to LOW.
	__delay_cycles(15);

	P5->DIR &= ~BIT0; // Set column C0 back to input (high Z)
	P5->DIR |= BIT1; // Set column C1 to ouptput, other columns remain high Z.(PIN 5.1)
	P5->OUT &= ~BIT1; // Set column C1 to LOW.
	__delay_cycles(15);

	P5->DIR &= ~BIT1; // Set column C1 back to input (high Z).
	P5->DIR |= BIT2; // Set column C2 to output, other columns remain high Z.(PIN 5.2)
	P5->OUT &= ~BIT2; // Set column C2 to LOW.
	__delay_cycles(15);

	P5->DIR &= ~BIT2; // Set column C2 back to input (high Z)
}


/* Port1 ISR */
void PORT2_IRQHandler(void)
{
    volatile uint32_t i;

    // Toggling the output on the LED
   // if(P2->IFG & BIT1)
    	GPIO_toggleOutputOnPin(GPIO_PORT_P2, GPIO_PIN0);

    // Delay for switch debounce
    for(i = 0; i < 10000; i++)

    	GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
}
