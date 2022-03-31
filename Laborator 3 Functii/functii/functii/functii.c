#include <avr/io.h>

int main(void)
{
   unsigned char inputs;
   unsigned char vx2, vx1, vx0;
   unsigned char outs;
   unsigned char temp;
   
   DDRA = 0b11111111;
   DDRB = 0b00000000;
   
   while(1)
   {
      inputs = PINB;
      inputs &=0b0000111;

      vx0 = inputs & 1<<0;
      vx1 = inputs >>1 & 1<<0;
      vx2 = inputs >>2 & 1<<0;

      outs = 0;

      temp = vx2 ^ vx1 ^ vx0;
      if( temp & 1<<0)
      {
         outs |= 1<<0; //f0
      }

      if(inputs<3)
      {
         outs |= 1<<1; //f1
      }

      temp = (~ vx2 & vx1 ) | ( vx2 & vx0 );
      if( temp & 1<<0)
      {
         outs |= 1<<2 ; //f2
      }
      
      PORTA = outs;
   }
}
