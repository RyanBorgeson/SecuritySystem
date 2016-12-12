/**
 * Initialize UART in order to communicate with host computer or other
 * device over UART.
 * Required in order to send and receive commands through terminal.
 * Source Code From Lecture
 */

#ifndef UART_H
#define UART_H

#include "../Config.h"

/**
 * Initialize and setup the UART module.
 */
void UART_Init(void);

/**
 * Output character by placing in trasmit buffer.
 * Source Code From Lecture.
 * @param Data Information to output to terminal.
 */
void UART_OutChar(char data);


/**
 * Output character by placing in trasmit buffer.
 * Source Code From Lecture.
 * @param Data Information to output to terminal.
 */
void WireLess_Out(char data);


/**
 * Send character over UART to host computer.
 * Source Code From Lecture.
 * @return Return the character received over UART.
 */
char WireLess_In(void);

/**
 * Output a string of characters one at a time through UART
 * to the host computer.
 * @param OutputString String to output to terminal.
 */
void UART_OutString(char * OutputString);

/**
 * Output a string command used to talk with the ESP8266.
 * @param OutputString Command to send.
 */
void WireLess_OutString(char * OutputString);


#endif
