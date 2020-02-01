/* vi:set et ts=4 sw=4 ai ft=c ff=dos: */
#ifndef _matrixavr_h_
#define _matrixavr_h_

/* Include all system header files here */
#include <avr/io.h>

#define MATRIX_DDR DDRA
#define MATRIX_PORT PORTA
#define storage_clock 0
#define shift_clock 1
#define serial_in 2
#define output_enable 3


/* Structures/Classes ... */
void led_display(char* ,int);
/* Extern declarations, prototypes etc. ... */

#endif /* _matrixavr_h_ */
