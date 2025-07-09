/*
Author: 	J.F. van der Bent
			W Pielage & E Helmond

Date:		24-11-2021
Revision:	5

    uart.c:
          UART2 driver for ARM-board V5

    pin-info:
           PA2 - TX
           PA3 - RX

To enable UART use the following line:
	UART_init();
To use UART on interrupt base use:
	UART_INT_init();

This file initialize the UART on the ARM-board v5.
To send data to the UART use:
	UART_printf(*string);


In the interrupt routine the char is send back to the terminal
07-07-2014 Aanpassen Uart routine om compatibel te zijn met void UART_put(char *c)
24011-2021 aanpassen van de Uart lib naar HAL

*/

#define CRETURN     13
#define LFEED       10


void UART_init(void);
signed int UART_printf(size_t length, const char *pFormat, ...);
void UART_INT_init(void);
void UART_putchar(unsigned char c);
void UART_puts(const char *s);
void UART_putnum(unsigned int num, unsigned char deel);
void UART_putint(unsigned int num);
char UART_get(void);
void UART_gets(char *s, int size, int echo);
