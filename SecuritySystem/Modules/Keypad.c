#include "Keypad.h"




void Keypad_Init(SensorData * Data) {


	GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);

	//MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7, GPIO_HIGH_TO_LOW_TRANSITION);
	////MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
	//MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);


	//Interrupt_registerInterrupt(PORT2_IRQn, PORT2_IRQHandler(Data));
	//Interrupt_enableInterrupt(INT_PORT2);

	//MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P5, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2, GPIO_HIGH_TO_LOW_TRANSITION);
	//MAP_GPIO_enableInterrupt(GPIO_PORT_P5, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);
	//MAP_GPIO_clearInterruptFlag(GPIO_PORT_P5, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);

}

/**
 * Scan keys looks at each column to determine if it has been pressed.
 * If so, the row will then be checked. When a column is not being check
 * it is set to a high impedance to protect the I/O.
 */
void Keypad_Scan(void) {
	static uint8_t idx = 0;

	P5->DIR |= BIT0;		// Set column C0 to output, and others to remain high Z. (PIN 5.0)
	P5->OUT &= ~BIT0;		// Set column C0 to LOW.
	__delay_cycles(10);

	KeypadState[idx] = (P2IN & 0xF0) >> 4;	// Read all row pins (P2.7, P2.6, P2.5, P2.4) when C0 is LOW.

	P5->DIR &= ~BIT0;		// Set column C0 back to input (high Z)
	P5->DIR |= BIT1;		// Set column C1 to ouptput, other columns remain high Z. (PIN 5.1)
	P5->OUT &= ~BIT1;		// Set column C1 to LOW.
	__delay_cycles(10);

	KeypadState[idx] = (KeypadState[idx] << 4) | (P2IN & 0xF0) >> 4; 	// Read all row pins when C1 is LOW.

	P5->DIR &= ~BIT1;		// Set column C1 back to input (high Z).
	P5->DIR |= BIT2;		// Set column C2 to output, other columns remain high Z. (PIN 5.2)
	P5->OUT &= ~BIT2;		// Set column C2 to LOW.
	__delay_cycles(10);

	KeypadState[idx] = (KeypadState[idx] << 4) | (P2IN & 0xF0) >> 4;

	P5->DIR &= ~BIT2;		// Set column C2 back to input (high Z)
	if (++idx >= 10) idx = 0;
}

int Keypad_Debounce(void) {
	static uint16_t DebounceState = 0; // Current debounce status
	DebounceState = (DebounceState << 1) | ((P5IN & 0xF0) >> 1) | 0xf800;
	if(DebounceState == 0xfc00) return 1;
	return 0;
}



void Keypad_SaveButtonPress(uint16_t PressedKey, SensorData * Data) {

	switch (PressedKey) {
		case ONE:
			Keypad_InsertKeyCombo('1', Data);
			break;
		case TWO:
			Keypad_InsertKeyCombo('2', Data);
			break;
		case THREE:
			Keypad_InsertKeyCombo(0x33, Data);
			break;
		case FOUR:
			Keypad_InsertKeyCombo(0x34, Data);
			break;
		case FIVE:
			Keypad_InsertKeyCombo(0x35, Data);
			break;
		case SIX:
			Keypad_InsertKeyCombo(0x36, Data);
			break;
		case SEVEN:
			Keypad_InsertKeyCombo(0x37, Data);
			break;
		case EIGHT:
			Keypad_InsertKeyCombo(0x38, Data);
			break;
		case NINE:
			Keypad_InsertKeyCombo(0x39, Data);
			break;
		case ZERO:
			Keypad_InsertKeyCombo(0x30, Data);
			break;
		case ASTERISK:
			Keypad_InsertKeyCombo(0x2A, Data);
			break;
		case POUND:
			Keypad_InsertKeyCombo(0x23, Data);
			break;
	}
}




void Keypad_InsertKeyCombo(char Key, SensorData * Data) {
	uint8_t KeyCombinations[4][3] = {
			{ 0x2A, 0x30, 0x23 },
			{ 0x37, 0x38, 0x39 },
			{ 0x34, 0x35, 0x36 },
			{ 0x31, 0x32, 0x33 }
	};

	Data->KeyCombo[3] = Data->KeyCombo[2];
	Data->KeyCombo[2] = Data->KeyCombo[1];
	Data->KeyCombo[1] = Data->KeyCombo[0];
	Data->KeyCombo[0] = Key;

}


void Keypad_Execute(SensorData * Data) {
	Keypad_Scan();

	if (Keypad_Debounce()) {
		Keypad_SaveButtonPress(*KeypadState, Data);
	}
}
