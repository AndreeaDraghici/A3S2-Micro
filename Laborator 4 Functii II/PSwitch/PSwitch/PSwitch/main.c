/*
 * PSwitch.c
 *
 * Created: 3/24/2022
 * Author : user
 */ 

#include <avr/io.h>
#include <avr/pgmspace.h>

int main(void)
{
   unsigned char inputs;

   DDRA = 0xff;
   DDRB = 0x0;
   
   while (1)
   {
      inputs = PINB & 0b00000111;
      
      switch (inputs)
      {
         case 0:
         PORTA = 0b0111111;
         break;
         case 1:
         PORTA = 0b0000110;
         break;
         case 2:
         PORTA = 0b1011011;
         break;
         case 3:
         PORTA =  0b1001111;
         break;
         case 4:
         PORTA = 0b1100110;
         break;
         case 5:
         PORTA = 0b1101101;
         break;
         case 6:
         PORTA =  0b1111101;
         break;
         case 7:
         PORTA = 0b0000111;
         break;
      }
   }
   return 0;
}