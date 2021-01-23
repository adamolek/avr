#ifndef LCD_HD44780
#define LCD_HD44780

#define LCD_PORT PORTA
#define LCD_DDR DDRA
#define LCD_PIN PINA

#define RS_PIN PA0
#define RW_PIN PA1
#define E_PIN PA2
#define D4_PIN PA3
#define D5_PIN PA4
#define D6_PIN PA5
#define D7_PIN PA6

/* RS */
#define SET_OUT_LCD_RS  LCD_DDR  |=  _BV(RS_PIN)
#define SET_LCD_RS  LCD_PORT |=  _BV(RS_PIN)
#define CLR_LCD_RS  LCD_PORT &= ~_BV(RS_PIN)

/* RW */
#define SET_OUT_LCD_RW  LCD_DDR  |=  _BV(RW_PIN)
#define SET_LCD_RW  LCD_PORT |=  _BV(RW_PIN)
#define CLR_LCD_RW  LCD_PORT &= ~_BV(RW_PIN)

/* E */
#define SET_OUT_LCD_E   LCD_DDR  |=  _BV(E_PIN)
#define SET_LCD_E   LCD_PORT |=  _BV(E_PIN)
#define CLR_LCD_E   LCD_PORT &= ~_BV(E_PIN)

/* D4 */
#define SET_OUT_LCD_D4  LCD_DDR  |=  _BV(D4_PIN)
#define SET_IN_LCD_D4   LCD_DDR  &= ~_BV(D4_PIN)
#define SET_LCD_D4  LCD_PORT |=  _BV(D4_PIN)
#define CLR_LCD_D4  LCD_PORT &= ~_BV(D4_PIN)
#define IS_SET_LCD_D4   LCD_PIN  &   _BV(D4_PIN)

/* D5 */
#define SET_OUT_LCD_D5  LCD_DDR  |=  _BV(D5_PIN)
#define SET_IN_LCD_D5   LCD_DDR  &= ~_BV(D5_PIN)
#define SET_LCD_D5  LCD_PORT |=  _BV(D5_PIN)
#define CLR_LCD_D5  LCD_PORT &= ~_BV(D5_PIN)
#define IS_SET_LCD_D5   LCD_PIN  &   _BV(D5_PIN)

/* D6 */
#define SET_OUT_LCD_D6  LCD_DDR  |=  _BV(D6_PIN)
#define SET_IN_LCD_D6   LCD_DDR  &= ~_BV(D6_PIN)
#define SET_LCD_D6  LCD_PORT |=  _BV(D6_PIN)
#define CLR_LCD_D6  LCD_PORT &= ~_BV(D6_PIN)
#define IS_SET_LCD_D6   LCD_PIN  &   _BV(D6_PIN)

/* D7 */
#define SET_OUT_LCD_D7  LCD_DDR  |=  _BV(D7_PIN)
#define SET_IN_LCD_D7   LCD_DDR  &= ~_BV(D7_PIN)
#define SET_LCD_D7  LCD_PORT |=  _BV(D7_PIN)
#define CLR_LCD_D7  LCD_PORT &= ~_BV(D7_PIN)
#define IS_SET_LCD_D7   LCD_PIN  &   _BV(D7_PIN)


#define LCD_NOP asm volatile("nop\n\t""nop\n\t" "nop\n\t" "nop\n\t" ::);

#define LCD_ENTRY_MODE(IDS) WriteToLCD(0x04|(IDS), 0)

void lcd_clear();
void lcd_start_display();
void WriteToLCD (unsigned char v, unsigned char  rs);
unsigned char ReadAddressLCD(void);
void lcd_init(void);
void lcd_print(char* str);
void lcd_clear();
void lcd_home();
void lcd_printc(char c);
void lcd_setpos(unsigned char x, unsigned char y);
void lcd_start_display();
void lcd_shift_left();
void lcd_shift_right();
void lcd_print_left();
void lcd_print_right();
void lcd_underline_cursor();
void lcd_blinking_cursor();
void lcd_invisible_cursor();
void lcd_move_cursor_left();
void lcd_move_cursor_right();
void lcd_scroll_display_left();
void lcd_scroll_display_right();
void lcd_blank();
void lcd_define_character(char* c, char addr);
void lcd_print_defined_character(char addr);

#endif
