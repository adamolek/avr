#include <avr/io.h>
#include <util/delay.h> //define F_CPU in this file upon delay.h inclusion or pass it as compilation argument(-D gcc option)
#include "hd44780.h"

void WriteToLCD (unsigned char v, unsigned char  rs)
{
	unsigned char bf;

	SET_OUT_LCD_D4;
	SET_OUT_LCD_D5;
	SET_OUT_LCD_D6;
	SET_OUT_LCD_D7;

	if(v & 0x10)SET_LCD_D4; else CLR_LCD_D4;
	if(v & 0x20)SET_LCD_D5; else CLR_LCD_D5;
	if(v & 0x40)SET_LCD_D6; else CLR_LCD_D6;
	if(v & 0x80)SET_LCD_D7; else CLR_LCD_D7;

	CLR_LCD_E;
	if(rs)SET_LCD_RS; else CLR_LCD_RS;
	CLR_LCD_RW;

	LCD_NOP;
	SET_LCD_E;
	LCD_NOP; 
	CLR_LCD_E;
	LCD_NOP;

	if(v & 0x01)SET_LCD_D4; else CLR_LCD_D4;
	if(v & 0x02)SET_LCD_D5; else CLR_LCD_D5;
	if(v & 0x04)SET_LCD_D6; else CLR_LCD_D6;
	if(v & 0x08)SET_LCD_D7; else CLR_LCD_D7;

	LCD_NOP;
	SET_LCD_E;
	LCD_NOP; 
	CLR_LCD_E;
	LCD_NOP;

	SET_IN_LCD_D4;
	SET_IN_LCD_D5;
	SET_IN_LCD_D6;
	SET_IN_LCD_D7;

	CLR_LCD_RS;
	SET_LCD_RW;
	SET_LCD_D7;

	do {
		LCD_NOP;
		SET_LCD_E;
		LCD_NOP;
		bf = IS_SET_LCD_D7;
		CLR_LCD_E;
		LCD_NOP;
		SET_LCD_E;
		LCD_NOP;
		LCD_NOP;
		CLR_LCD_E;
	} while(bf);
}

unsigned char ReadAddressLCD ()
{
	unsigned char g = 0 ;

	CLR_LCD_RS;
	SET_LCD_RW; 

	SET_IN_LCD_D4;
	SET_IN_LCD_D5;
	SET_IN_LCD_D6;
	SET_IN_LCD_D7;

	LCD_NOP;
	SET_LCD_E;
	LCD_NOP;

	if(IS_SET_LCD_D4) g+=16;
	if(IS_SET_LCD_D4) g+=32;
	if(IS_SET_LCD_D4) g+=64;
	if(IS_SET_LCD_D4) g+=128;
 
	CLR_LCD_E;
	LCD_NOP;
	SET_LCD_E;  
	LCD_NOP;
  
	if(IS_SET_LCD_D4) g+=8;
	if(IS_SET_LCD_D4) g+=4;
	if(IS_SET_LCD_D4) g+=2;
	if(IS_SET_LCD_D4) g+=1;
  
	CLR_LCD_E; 

	return  g ;
}

void lcd_init(void)
{
	_delay_ms(31);

	SET_OUT_LCD_RS;
	SET_OUT_LCD_RW;
	SET_OUT_LCD_E;
	SET_OUT_LCD_D4;
	SET_OUT_LCD_D5;
	SET_OUT_LCD_D6;
	SET_OUT_LCD_D7;

	CLR_LCD_E;
	CLR_LCD_RS;
	CLR_LCD_RW;
	CLR_LCD_D4;
	CLR_LCD_D5;
	CLR_LCD_D6;
	CLR_LCD_D7;

	LCD_NOP;
	SET_LCD_E;
	LCD_NOP; 
	CLR_LCD_E;
	LCD_NOP;
	_delay_ms(10);

	LCD_NOP;
	SET_LCD_E;
	LCD_NOP; 
	CLR_LCD_E;
	LCD_NOP;
	_delay_ms(2);

	LCD_NOP;
	SET_LCD_E;
	LCD_NOP; 
	CLR_LCD_E;
	LCD_NOP;
	_delay_ms(2);

	CLR_LCD_D4;
	LCD_NOP;
	SET_LCD_E;
	LCD_NOP; 
	CLR_LCD_E;
	LCD_NOP;
	_delay_us(80);

	WriteToLCD (0x28 , 0);
	lcd_start_display();
	lcd_clear();
	LCD_ENTRY_MODE(0x02);
}

void lcd_print(char* str)
{
	unsigned char i = 0;
	while(str[i])WriteToLCD(str[i++], 1);
}

void lcd_clear()
{
	WriteToLCD(1, 0);
}

void lcd_home()
{
	WriteToLCD(2, 0);
}

void lcd_printc(char c)
{
	WriteToLCD(c, 1);
}

void lcd_setpos(unsigned char x, unsigned char y)
{
	WriteToLCD(0x80 | ((x) + ((y) * 0x40)), 0);
}

void lcd_start_display()
{
	WriteToLCD(0x08 | 0x04, 0);
}

void lcd_shift_left()
{
	WriteToLCD(0x07, 0);
}

void lcd_shift_right()
{
	WriteToLCD(0x05, 0);
}

void lcd_print_left()
{
	WriteToLCD(0x04, 0);
}

void lcd_print_right()
{
	WriteToLCD(0x06, 0);
}

void lcd_underline_cursor()
{
	WriteToLCD(0x0E, 0);
}

void lcd_blinking_cursor()
{
	WriteToLCD(0x0F, 0);
}

void lcd_invisible_cursor()
{
	WriteToLCD(0x0C, 0);
}

void lcd_move_cursor_left()
{
	WriteToLCD(0x10, 0);
}

void lcd_move_cursor_right()
{
	WriteToLCD(0x14, 0);
}

void lcd_scroll_display_left()
{
	WriteToLCD(0x18, 0);
}

void lcd_scroll_display_right()
{
	WriteToLCD(0x1E, 0);
}

void lcd_blank()
{
	WriteToLCD(0x08, 0);
}

void lcd_define_character(char* c, char addr)
{
	char i = 0;
	WriteToLCD(0x40 + addr * 8, 0);
	for(i=0; i<=7; i++)	WriteToLCD(c[i], 1);
	WriteToLCD(0x80, 0);
}

void lcd_print_defined_character(char addr)
{
	WriteToLCD(addr, 1);
}
