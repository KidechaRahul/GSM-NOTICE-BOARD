/* vi:set et ts=4 sw=4 ai ft=c ff=dos: */
#include "matrixavr.h"
#include <avr/io.h>
#include <util/delay.h>
#include <compat/deprecated.h>
#include <avr/delay.h>

#define MATRIX_DDR DDRA
#define MATRIX_PORT PORTA
#define storage_clock 0
#define shift_clock 1
#define serial_in 2
#define output_enable 3

/* Global variables */
unsigned int shift_delay=50;
unsigned char look[][5] = {
                            {0x60,0x57,0x37,0x57,0x60},//A
                            {0x00,0x36,0x36,0x36,0x49},//B
							{0x41,0x3E,0x3E,0x3E,0x5D},//C
							{0x00,0x3E,0x3E,0x3E,0x41},//D
							{0x00,0x36,0x36,0x36,0x3E},//E
							{0x00,0x37,0x37,0x37,0x3F},//F
							{0x41,0x3E,0x36,0x36,0x31},//G
							{0x00,0x77,0x77,0x77,0x00},//H
							{0x3E,0x3E,0x00,0x3E,0x3E},//I
							{0x3D,0x3E,0x00,0x3F,0x3F},//J
							{0x00,0x77,0x6B,0x5D,0x3E},//K
							{0x00,0xFE,0xFE,0xFE,0xFE},//L
							{0x00,0x5F,0xE7,0x5F,0x00},//M
							{0x00,0x6F,0x77,0x7B,0x00},//N
							{0x41,0x3E,0x3E,0x3E,0x41},//O
							{0x00,0x37,0x37,0x37,0xCF},//P
							{0x41,0x3E,0x3A,0x3C,0x3F},//Q
                            {0x00,0x37,0x33,0x35,0xCE},//R
							{0x4E,0x36,0x36,0x36,0x39},//S
                            {0x3F,0x3F,0x00,0x3F,0x3F},//T
							{0x01,0x7E,0x7E,0x7E,0x01},//U
                            {0x03,0xFD,0xFE,0xFD,0x03},//V
							{0x00,0x7D,0x73,0x7D,0x00},//W
							{0x1C,0x6B,0x77,0x6B,0x1C},//X
							{0x0F,0xF7,0xF8,0xF7,0x0F},//Y
							{0x3C,0x3A,0x36,0x2E,0x1E},//Z
							{0x00,0x3E,0x3E,0x3E,0x00},//0
							{0x6E,0x5E,0x00,0x7E,0x7E},//1
							{0x4E,0x3C,0x3A,0x36,0x4E},//2
							{0x3C,0x3E,0x36,0x2A,0x1C},//3
							{0x77,0x67,0x57,0x00,0x77},//4
							{0x06,0x36,0x36,0x36,0x31},//5
							{0x00,0x36,0x36,0x36,0x30},//6
							{0x3E,0x3D,0x3B,0x37,0x0F},//7
							{0x00,0x36,0x36,0x36,0x00},//8
							{0x06,0x36,0x36,0x36,0x00},//9
							{0x55,0x63,0x41,0x63,0x55},//*
                            {0xFF,0xF7,0xF7,0xF7,0xFF},// -
                            {0x7F,0x49,0x49,0x7F,0x7F},//:
							{0x7F,0x7F,0x7F,0x72,0x71},//,
							{0x7F,0x7F,0x02,0x7F,0x7F},//!
                           }; 

/* Function prototypes */
void shift_byte(unsigned char x)
{
 unsigned char i;
 for(i=0;i<8;i++)
   {
    if((x & (1<<i))== 0)
	{
	cbi(MATRIX_PORT,serial_in);
	}
	else
	{
	sbi(MATRIX_PORT,serial_in);
	}
	sbi(MATRIX_PORT,shift_clock);
	cbi(MATRIX_PORT,shift_clock);
	
   }
sbi(MATRIX_PORT,storage_clock); 
cbi(MATRIX_PORT,storage_clock); 
 
 _delay_ms(shift_delay);  
}

void shift_alpha(unsigned char a)
{
 unsigned char z;
 for(z=0;z<5;z++)shift_byte(look[a][z]);
 shift_byte(0xFF);
}

void dot(void)
{
 //shift_byte(0xFF);
 shift_byte(0xFE);
 shift_byte(0xFF);
}

void space(void)
{
 shift_byte(0xFF);
 shift_byte(0xFF);
 shift_byte(0xFF);
}


void led_display(char *str,int m)
{
// Declare your local variables here

int i;
      {
     
		  for(i=0;i<=80;i++)
			{
				
				if(str[i]=='a'||str[i]=='A')
				shift_alpha(0);
				else if(str[i]=='b'||str[i]=='B')
				shift_alpha(1);
				else if(str[i]=='c'||str[i]=='C')
				shift_alpha(2);
				else if(str[i]=='d'||str[i]=='D')
				shift_alpha(3);
				else if(str[i]=='e'||str[i]=='E')
				shift_alpha(4);
				else if(str[i]=='f'||str[i]=='F')
				shift_alpha(5);
				else if(str[i]=='g'||str[i]=='G')
				shift_alpha(6);
				else if(str[i]=='h'||str[i]=='H')
				shift_alpha(7);
				else if(str[i]=='i'||str[i]=='I')
				shift_alpha(8);
				else if(str[i]=='j'||str[i]=='J')
				shift_alpha(9);
				else if(str[i]=='k'||str[i]=='K')
				shift_alpha(10);
				else if(str[i]=='l'||str[i]=='G')
				shift_alpha(11);
				else if(str[i]=='m'||str[i]=='M')
				shift_alpha(12);
				else if(str[i]=='n'||str[i]=='N')
				shift_alpha(13);
				else if(str[i]=='o'||str[i]=='O')
				shift_alpha(14);
				else if(str[i]=='p'||str[i]=='P')
				shift_alpha(15);
				else if(str[i]=='q'||str[i]=='Q')
				shift_alpha(16);
				else if(str[i]=='r'||str[i]=='R')
				shift_alpha(17);
				else if(str[i]=='s'||str[i]=='S')
				shift_alpha(18);
				else if(str[i]=='t'||str[i]=='T')
				shift_alpha(19);
				else if(str[i]=='u'||str[i]=='U')
				shift_alpha(20);
				else if(str[i]=='v'||str[i]=='V')
				shift_alpha(21);
				else if(str[i]=='w'||str[i]=='W')
				shift_alpha(22);
				else if(str[i]=='x'||str[i]=='X')
				shift_alpha(23);
				else if(str[i]=='y'||str[i]=='Y')
				shift_alpha(24);
				else if(str[i]=='z'||str[i]=='Z')
				shift_alpha(25);
				else if(str[i]=='0'||str[i]=='O')
				shift_alpha(26);
				else if(str[i]=='1')
				shift_alpha(27);
				else if(str[i]=='2')
				shift_alpha(28);
				else if(str[i]=='3')
				shift_alpha(29);
				else if(str[i]=='4')
				shift_alpha(30);
				else if(str[i]=='5')
				shift_alpha(31);
				else if(str[i]=='6')
				shift_alpha(32);
				else if(str[i]=='7')
				shift_alpha(33);
				else if(str[i]=='8')
				shift_alpha(34);
				else if(str[i]=='9')
				shift_alpha(35);
				else if(str[i]=='*')
				shift_alpha(36);
				else if(str[i]=='_')
				shift_alpha(37);
				else if(str[i]==':')
				shift_alpha(38);
				else if(str[i]==',')
				shift_alpha(39);
				else if(str[i]=='!')
				shift_alpha(40);
				else if(str[i]==' ')
				space();
				else if(str[i]=='.')
				dot();
				else
				break;
			}
			space();
			space();
	}
}

