#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define clrbit(var,bit) ( (var) &= ~(1 << (bit)) )
#define setbit(var,bit) ( (var) |=  1 << (bit) )
#define testbit(var,bit)( (var) &   1 << (bit) )

void initLCD();
void putchLCD(char ch);
void putsLCD( char ch[]);
void clrLCD();
void gotoLC(unsigned char line, unsigned char col);
