/*
 * lcd.h
 *
 * Created: 23-2-2016 16:15:38
 *  Author: titat_000
 */ 

extern void lcd_command(unsigned char);
extern void lcd_writeChar(unsigned char);
extern void display_text(char[], int);
extern void lcd_setLine(int);
extern void set_cursor(int);
extern void lcd_scrollLeft();
extern void lcd_scrollRight();
extern void lcd_init();

 #define arraySize(x)  (sizeof(x) / sizeof((x)[0]))
 #define shiftCursor 0b00000110
