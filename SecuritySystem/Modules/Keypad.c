#include "Keypad.h"


void Keypad_Init(SensorData * Data) {

	P2->DIR &= ~0xF0;


//	GPIO_setAsInputPin(GPIO_PORT_P2, GPIO_PIN4 | GPIO_PIN5 | GPIO_PIN6 | GPIO_PIN7);
	//GPIO_setAsInputPin(GPIO_PORT_P5, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2);

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

uint8_t Keypad_Debounce(void) {
	static uint16_t KeypadDebounceState = 0;
	KeypadDebounceState = (KeypadDebounceState << 1) |  ((P5IN & (BIT0 | BIT1 | BIT2)) != 0x00) << 1 | 0xf800;
	if (KeypadDebounceState == 0xFFFC) return 1;
	return 0;
}



int Keypad_SaveButtonPress(uint16_t PressedKey, SensorData * Data) {

	switch (PressedKey) {
		case ONE:
			Keypad_InsertKeyCombo('1', Data);
			return 1;
		case TWO:
			Keypad_InsertKeyCombo('2', Data);
			return 1;
		case THREE:
			Keypad_InsertKeyCombo(0x33, Data);
			return 1;
		case FOUR:
			Keypad_InsertKeyCombo(0x34, Data);
			return 1;
		case FIVE:
			Keypad_InsertKeyCombo(0x35, Data);
			return 1;
		case SIX:
			Keypad_InsertKeyCombo(0x36, Data);
			return 1;
		case SEVEN:
			Keypad_InsertKeyCombo(0x37, Data);
			return 1;
		case EIGHT:
			Keypad_InsertKeyCombo(0x38, Data);
			return 1;
		case NINE:
			Keypad_InsertKeyCombo(0x39, Data);
			return 1;
		case ZERO:
			Keypad_InsertKeyCombo(0x30, Data);
			return 1;
		case ASTERISK:
			Keypad_InsertKeyCombo(0x2A, Data);
			return 1;
		case POUND:
			Keypad_InsertKeyCombo(0x23, Data);
			return 1;
	}
	return 0;
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
		if (Keypad_SaveButtonPress(*KeypadState, Data))
			Data->MinuteCounter = 0;
	}
}

void Keypad_ExecuteForPinEnter(SensorData * Data, int * Count) {
	Keypad_Scan();

		if (Keypad_Debounce()) {
			if (Keypad_SaveButtonPress(*KeypadState, Data)) {
				if (Data->KeyCombo[0] != '#') {
					if (Data->State == SETPIN && Data->KeyCombo[LAST_KEY] == '*') {

					} else {
						Data->EnteredPIN[*Count] = Data->KeyCombo[0];
						(*Count)++;
						Data->MinuteCounter = 0;
					}
				}
			}
		}
}

