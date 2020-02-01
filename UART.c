#include "UART.h"

void uartPutc(unsigned char c) 
{
   // wait until UDR ready
	while(!(UCSR1A & (1 << UDRE)));
	UDR1 = c;    // send character
}

void uartPuts(char *s) 
{
	//  loop until *s != NULL
	while (*s) {
		uartPutc(*s);
		s++;
	}
}

char receiveByte()
{
	while ( !(UCSR1A & (1<<RXC)) ) 	/* Wait for incomming data */
		;			                /* Return the data */
	return UDR1;
}

char receiveByteAsync(int delay_count)
{
	int count;
	count = 0;
	
	while ( !(UCSR1A & (1<<RXC)) ) 	/* Wait for incomming data */
	{
		//(count>=delay_count)?return UART_ERROR_CODE:count++;
		
		count++;
		if(count >= delay_count)
		{
			return UART_ERROR_CODE;
		}
	}
	
	return UDR1;
}

char* recieveString(char stop_char)
{
	char *str;
	int count;
	char recieved_char;
	
	count = 0;
	
	while(1)
	{
		recieved_char = receiveByte();
		if(recieved_char == stop_char)
			break;
		else
		{
			str[count] = recieved_char;
			count++;
		}
	}
	
	str[count] = '\0';
	return str;
}

void uartInit() 
{
	// set baud rate
	UBRR1H = (uint8_t)(UART_BAUD_CALC(UART_BAUD_RATE,F_CPU)>>8);
	UBRR1L = (uint8_t)UART_BAUD_CALC(UART_BAUD_RATE,F_CPU);

	// Enable receiver and transmitter; enable RX interrupt
	UCSR1B = (1 << RXEN) | (1 << TXEN) | (1 << RXCIE);

	//asynchronous 8N1
	UCSR1C = (1 << URSEL) | (3 << UCSZ10);
	
	//sei();
}