#include "Wireless.h"



void Wireless_Init(void) {

	EUSCI_A2->CTLW0 = 0x0001;
	EUSCI_A2->CTLW0 = 0x00C1;
	EUSCI_A2->BRW = 26;
	EUSCI_A2->MCTLW &= ~0xFFF1;

	GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,
		                GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

	//P1SEL0 |= 0x0C;
	//P1SEL1 &= ~0x0C; // configure P1.3 and P1.2 as primary module function
	EUSCI_A2->CTLW0 &= ~0x0001; // enable the USCI module
	EUSCI_A2->IE &= ~0x000F; // disable interrupts


	SysTick_delay(10000);


	//GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN1);
	//GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN1);
}



void SendPostRequest(SensorData * Data) {
	static uint8_t RequestsSent = 0;

	// Sensor variables.
	char Temp[3];

	ConvertBCDToString(ClockRegisters[TEMPERATURE], &Temp);

	char Headers[1000];
	char JSONPayload[1000];
	char CIPSEND[100];


	//sprintf(JSONPayload, "{\"Temperature\":\"%s\",\"AmbientLight\":\"0.7\"}", Temp);
	//sprintf(JSONPayload, "{\"Temperature\":\"22\",\"AmbientLight\":\"%.5f\"}", SensorReadings->Photoresistor);
	//sprintf(Headers, "POST /api/sensor HTTP/1.1\r\nHost: ssapi.ryanborgeson.com\r\nConnection: Keep-Alive\r\nContent-Type: application/json\r\nContent-Length: %i\r\n\r\n%s\r\n\r\n", strlen(JSONPayload), JSONPayload);
	//sprintf(CIPSEND, "AT+CIPSEND=4,%i\r\n\r\n", (strlen(Headers) + strlen(JSONPayload) - 28));

	sprintf(JSONPayload, "Temperature=%s&AmbientLight=0.7", Temp);
	//sprintf(Headers, "POST http://ssapi.ryanborgeson.com/api/sensor HTTP/1.1\r\nAccept: */*\r\nAccept-Encoding: gzip, deflate\r\nConnection: Keep-Alive\r\nContent-Length: %i\r\nContent-Type: application/x-www-form-urlencoded\r\nHost: ssapi.ryanborgeson.com\r\nUser-Agent: runscope/0.1\r\n\r\n%s\r\n\r\n", strlen(JSONPayload) - 1, JSONPayload);
	sprintf(Headers, "POST /api/sensor HTTP/1.1\r\nHost: ssapi.ryanborgeson.com\r\nConnection: Keep-Alive\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: %i\r\n\r\n%s\r\n\r\n", strlen(JSONPayload) - 1, JSONPayload);

	sprintf(CIPSEND, "AT+CIPSEND=4,%i\r\n\r\n", strlen(Headers));


	WireLess_OutString("AT+CIPMUX=1\r\n");
	//PatternCheck("OK");
	Delay1ms(100);
	WireLess_OutString("AT+CIPSTART=4,\"TCP\",\"ssapi.ryanborgeson.com\",80\r\n");
	//PatternCheck("OK");
	Delay1ms(100);


	WireLess_OutString(CIPSEND);
	//PatternCheck("OK");
	Delay1ms(100);
	WireLess_OutString(Headers);
	//WireLess_OutString("\r\n\r\n");
	//PatternCheck("OK");
	Delay1ms(100);

	//WireLess_OutString("AT+CIPCLOSE\r\n");
	//Delay1ms(50);
	//PatternCheck("OK");

	// Reset wireless device just incase it has any issues.
	//if (RequestsSent > 20) {
	//	WireLess_OutString("AT+RST\r\n");
	//	RequestsSent = 0;
	//}
	//RequestsSent++;
}



/**
 * Check for a specific pattern within a received bit stream. Takes
 * in an character array and waits until that pattern is receieved.
 */
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

