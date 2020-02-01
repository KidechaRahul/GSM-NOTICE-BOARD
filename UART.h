#ifndef _UART_H_
	#define _UART_H_
	
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <inttypes.h>
	
	#ifndef F_CPU
		#define F_CPU 16000000		           /* oscillator-frequency in Hz */
	#endif
	
	#define UART_BAUD_RATE 2400
	#define UART_BAUD_CALC(UART_BAUD_RATE,F_CPU) ((F_CPU)/((UART_BAUD_RATE)*16l)-1)
	
	#define UART_ERROR_CODE 0xFF
	
	void uartPutc(unsigned char);
	void uartPuts (char *);
	char receiveByteAsync(int);
	char receiveByte( void );
	char* recieveString(char);
	void uartInit(void);
#endif