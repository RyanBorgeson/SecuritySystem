#include "Keypad.h"


volatile uint8_t Keypressed = 0;
volatile uint8_t TempColumn = 0;
volatile uint8_t SelectedColumn = 0, SelectedRow = 0;

void Keypad_Init(void) {

	GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);

	MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);
	MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
	MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);

}


void Keypad_Scan(void) {
	TempColumn = 0;
	P5->DIR |= BIT0; // Set column C0 to output, and others to remain high Z.(PIN 5.0)
	P5->OUT &= ~BIT0; // Set column C0 to LOW.
	__delay_cycles(50);

	TempColumn = 1;
	P5->DIR &= ~BIT0; // Set column C0 back to input (high Z)
	P5->DIR |= BIT1; // Set column C1 to ouptput, other columns remain high Z.(PIN 5.1)
	P5->OUT &= ~BIT1; // Set column C1 to LOW.
	__delay_cycles(50);

	TempColumn = 2;
	P5->DIR &= ~BIT1; // Set column C1 back to input (high Z).
	P5->DIR |= BIT2; // Set column C2 to output, other columns remain high Z.(PIN 5.2)
	P5->OUT &= ~BIT2; // Set column C2 to LOW.
	__delay_cycles(50);

	P5->DIR &= ~BIT2; // Set column C2 back to input (high Z)
}


/* Port1 ISR */
void PORT2_IRQHandler(void)
{
	static uint8_t DebounceState = 0;

	DebounceState = (DebounceState << 1) | (P2IN & 0x0F) >> 1 | 0xf800;

	if (DebounceState == 0xFC) {
		SelectedColumn = TempColumn;

		if(P2->IFG & BIT4)
			SelectedRow = 0;
		else if (P2->IFG & BIT5)
			SelectedRow = 1;
		else if (P2->IFG & BIT6)
			SelectedRow = 2;
		else if (P2->IFG & BIT7)
			SelectedRow = 3;
	}

    GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
}
