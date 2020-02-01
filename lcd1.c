#include<avr/io.h>
#include<util/delay.h>

#define RS PA0
#define EN PA1
#define D4 PA4
#define D5 PA5
#define D6 PA6
#define D7 PA7

void init_lcd(void);
void lcd_cmd_4(unsigned char);
void lcd_cmd_8(unsigned char);
void lcd_data_4(unsigned char);
void lcd_data_8(unsigned char);
void lcd_display(unsigned char*);
void delay_ms(unsigned int);

//-------------------------------------

void init_lcd(void)
{
DDRC = 0XFF;
delay_ms(15);

lcd_cmd_4(0x30);
delay_ms(15);

lcd_cmd_4(0x30);
delay_ms(15);

lcd_cmd_4(0x30);
delay_ms(15);

lcd_cmd_4(0x20);
delay_ms(15);

lcd_cmd_8(0x28);
lcd_cmd_8(0x10);
lcd_cmd_8(0x0C);
lcd_cmd_8(0x04);
lcd_cmd_8(0x01);
}

//-------------------------------------

void lcd_cmd_4(unsigned char value)
{
PORTC &=~(1<<RS);
PORTC = (value & 0XF0)|(PORTC & 0X0F);
PORTC |= (1<<EN);
delay_ms(2);
PORTC &=~(1<<EN);
}

//-------------------------------------

void lcd_cmd_8(unsigned char value)
{
lcd_cmd_4(value);
lcd_cmd_4(value<<4);
}

//-------------------------------------

void lcd_data_4(unsigned char value)
{
PORTC |= (1<<RS);
PORTC = (value & 0XF0)|(PORTC & 0X0F);
PORTC |= (1<<EN);
delay_ms(2);
PORTC &=~(1<<EN);
}

//-------------------------------------

void lcd_data_8(unsigned char value)
{
lcd_data_4(value);
lcd_data_4(value<<4);
}

//-------------------------------------

void lcd_display(unsigned char *str)
{
char i=0;
//lcd_cmd_8(0X80);
	while(*str !='\0')
	{
	i++;
	lcd_data_8(*str++);
		if(i==16)
		{
		lcd_cmd_8(0XC0);
		}
		if(i==32)
		{
		lcd_cmd_8(0X80);
		}
	}
}

//-------------------------------------

void delay_ms(unsigned int time)
{
volatile unsigned int i,j;
for(i=0; i<time; i++)
for(j=0; j<1000; j++);
}

//-------------------------------------
