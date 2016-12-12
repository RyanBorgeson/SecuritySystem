/**
 * Initialize UART in order to communicate with host computer or other
 * device over UART.
 * Required in order to send and receive commands through terminal.
 * Source Code From Lecture
 */

#include "UART.h"

void UART_Init(void) {
	EUSCI_A0->CTLW0 = 0x0001; // hold the USCI module in reset mode
	// bit15=0, no parity bits
	// bit14=x, not used when parity is disabled
	// bit13=0, LSB first
	// bit12=0, 8-bit data length
	// bit11=0, 1 stop bit
	// bits10-8=000, asynchronous UART mode
	// bits7-6=11, clock source to SMCLK
	// bit5=0, reject erroneous characters and do not set flag
	// bit4=0, do not set flag for break characters
	// bit3=0, not dormant
	// bit2=0, transmit data, not address (not used here)
	// bit1=0, do not transmit break (not used here)
	// bit0=1, hold logic in reset state while configuring
	EUSCI_A0->CTLW0 = 0x00C1;
	EUSCI_A0->BRW = 26; // UCBR = baud rate = int(N) =26 = clock/baud rate = 26.0417
	EUSCI_A0->MCTLW &= ~0xFFF1; // clear first and second modulation stage bit fields,
	P1SEL0 |= 0x0C;
	P1SEL1 &= ~0x0C; // configure P1.3 and P1.2 as primary module function
	EUSCI_A0->CTLW0 &= ~0x0001; // enable the USCI module
	EUSCI_A0->IE &= ~0x000F; // disable interrupts
}

void UART_OutChar(char data) {
	while((EUSCI_A0->IFG&0x02) == 0);
	EUSCI_A0->TXBUF = data;
}

void WireLess_Out(char data) {
	while((EUSCI_A2->IFG&0x02) == 0);
	EUSCI_A2->TXBUF = data;
}

char WireLess_In(void) {
	while ((EUSCI_A2->IFG&0x01) == 0);
	return ((char)(EUSCI_A2->RXBUF));
}

void UART_OutString(char * OutputString) {
	uint8_t i;
	for (i = 0; i < (int)strlen(OutputString); i++) {
		UART_OutChar(OutputString[i]);
	}
}

void WireLess_OutString(char * OutputString) {
	uint8_t i;
	for (i = 0; i < (int)strlen(OutputString); i++) {
		WireLess_Out(OutputString[i]);
	}
}





