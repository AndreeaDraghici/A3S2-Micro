#include "LCD.h"

#define E  5
#define RS 4

#define IReg 0
#define DReg 1

void wr_LCDreg(unsigned char vRS, unsigned char data){

   static volatile unsigned char cnt8;

#define wait125   cnt8++

   static unsigned char first=1;
   
   PORTD = (data>>4) & 0x0f;  

   if(vRS==0)
      clrbit(PORTD,RS);	//RS=0
   else
      setbit(PORTD,RS);	//RS=1

   wait125;

   setbit(PORTD,E);	//E=1
   wait125;
   wait125;
      
   clrbit(PORTD,E);	//E=0
   wait125;
   
   if(first){
      first=0;
      return;
   }
   
   PORTD &=0xf0;
   PORTD = PORTD | (data & 0x0f);

   wait125;

   setbit(PORTD,E);	//E=1
   wait125;
   wait125;

   clrbit(PORTD,E);	//E=0
   wait125;
}

void initLCD(){
    PORTD = 0;
    DDRD  = 0xff;
    _delay_ms(1000);
   // Function set
	//bit 7 6 5 4   3 2 1 0
	//    0 0 1 DL  N F - - 
	//    0 0 1  0  1 1 0 0  0x3c
	wr_LCDreg(IReg, 0b00101100);
   _delay_us(50);
   
	wr_LCDreg(IReg, 0b00101100);
   _delay_us(50);
   
   // Display on/off control
   // Display on/off control
	//bit 7 6 5 4   3 2 1 0
	wr_LCDreg(IReg, 0x0e);
   _delay_us(50);
   
   // Entry mode set
   //bit 7 6 5 4   3 2 1 0
	wr_LCDreg(IReg, 0x06);
   _delay_us(50);
   
   // Clear display
   //bit 7 6 5 4   3 2 1 0
	wr_LCDreg(IReg, 0x01);
   _delay_ms(3);
}

void clrLCD(){
	wr_LCDreg(IReg, 0x01);
    _delay_ms(2);
}

void gotoLC(unsigned char line, unsigned char col){
   if(line>=1 && line<=2 && col>=1 && col <= 16){
      wr_LCDreg(IReg, 0x80 + 0x40 * --line + --col); //set DDRAM address
      _delay_us(50);
   }
}

void putchLCD(char ch){
	wr_LCDreg(DReg,ch);
   _delay_us(50);
}

void putsLCD( char ch[]){
	while(*ch)
		putchLCD(*ch++);
}
 