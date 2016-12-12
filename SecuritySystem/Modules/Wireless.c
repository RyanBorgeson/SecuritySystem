/**
 * Handles wireless communication between the MSP432 and the ESP8266
 * using the AT command set. The system can connect to a wireless network
 * and post information to the specified server.
 * @Author Ryan Borgeson
 * @Date 12/12/2016
 */
#include "Wireless.h"

void Wireless_Init(void) {

	// Configure the MSP432 to send information and requests to the
	// ESP8266 over UART. This will take advantage of the ESP8266 AT command
	// set.
	EUSCI_A2->CTLW0 = 0x0001;
	EUSCI_A2->CTLW0 = 0x00C1;
	EUSCI_A2->BRW = 26;
	EUSCI_A2->MCTLW &= ~0xFFF1;

	// Configure pins for UART.
	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
		                GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

	// Enable the USCI module.
	EUSCI_A2->CTLW0 &= ~0x0001;

	// Disable interrupts.
	EUSCI_A2->IE &= ~0x000F;

	// Sends the first command that will connect to a wireless network.
	WireLess_OutString("AT+CWJAP=\"Android\",\"hello123\"\r\n");

	// Delays the system to ensure enough time for connection.
	SysTick_delay(10000);
}

void SendPostRequest(SensorData * Data) {

	// Sensor variables.
	char Temp[3];
	int HallEffect1 = Data->HallEffect[0];
	int HallEffect2 = Data->HallEffect[1];
	int Proximity1 = Data->Proximity[0];

	// Convert the BCD temperature to a character.
	ConvertBCDToString(ClockRegisters[TEMPERATURE], &Temp);

	// Placeholders for the Headers, JSONPayload, and CIPSEND commands.
	char Headers[1000];
	char Payload[1000];
	char CIPSEND[100];

	// Formats the headers and json payload before placing it into the cipsend command.
	// During this time the payload length must be calculated.
	// Sensor information is placed in the payload and posted to a server.
	sprintf(Payload, "Temperature=%s&HallEffect1=%i&HallEffect2=%i&Proximity1=%i", Temp, HallEffect1, HallEffect2, Proximity1);
	sprintf(Headers, "POST /api/sensor HTTP/1.1\r\nHost: ssapi.ryanborgeson.com\r\nConnection: Keep-Alive\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: %i\r\n\r\n%s\r\n\r\n", strlen(Payload), Payload);
	sprintf(CIPSEND, "AT+CIPSEND=4,%i\r\n\r\n", strlen(Headers));

	// Make the post request to the server with the information and headers.
	WireLess_OutString("AT+CIPMUX=1\r\n");
	Delay1ms(20);
	WireLess_OutString("AT+CIPSTART=4,\"TCP\",\"ssapi.ryanborgeson.com\",80\r\n");
	Delay1ms(20);
	WireLess_OutString(CIPSEND);
	Delay1ms(20);
	WireLess_OutString(Headers);
	Delay1ms(20);
}

void PatternCheck(char * Pattern) {
	static char Stream[MAX_PATTERN_BUFFER];
	int i = 0;

	for (i = 0; i < MAX_PATTERN_BUFFER; i++) {
		Stream[i] = UART_receiveData(EUSCI_A2_BASE);
		i = (i < 100) ? i + 1 : 0;
	}

	if (strstr(Stream, Pattern) != 0) {
		SysTick_delay(2000);
	}
}

