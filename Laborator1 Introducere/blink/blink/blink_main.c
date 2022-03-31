#include <avr/io.h>
#define F_CPU 8000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

//period
#define T 10UL

//duty factor
#define DF 25UL
#define THIGH (T*DF/100)
#define TLOW (T*(100-DF)/100)

int main(){
   DDRA=0xff;

   while(1){
      PORTA=1; //turn on LED
      _delay_ms(THIGH);

      PORTA=0; //turn off LED
      _delay_ms(TLOW);
   }
}