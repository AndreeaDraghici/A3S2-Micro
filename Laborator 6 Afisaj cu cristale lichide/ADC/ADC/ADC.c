/*
 * ADC.c
 *
 * Created: 4/7/2022
 * Author : user
 */ 

#include <avr/io.h>
#include "LCD.h"

int main(void)
{
    unsigned int val,valoareSute,valoareZeci,valoareUnitati;
    long temp;
    //char buf[20];
    initLCD();
    
    // ADMUX register
    //REFS1 REFS0 ADLAR MUX4 MUX3 MUX2 MUX1 MUX0
    // |      |     |     0    0   0    0    0    Vin = ADC0
    // |      |     1   aliniere la stanga
    // 0      1    VREF = AVCC
    ADMUX =0b01100000;
    
    // ADCSRA register
    // ADEN ADSC ADATE ADIF ADIE ADPS2 ADPS1 ADPS0
    // |      |    |    |     |    1     1     1    factor divizare=128
    // |      |    0    |     0    ADIE si ADATE se seteaza la ‚0’ si nu se mai modifica
    // |      |         0
    // |      0         0
    // 1   enable ADC
    ADCSRA = 0b10000111;
    
    while (1) 
    {
       // daca ADC este in repaus adica nu exists conversie in curs
       if( testbit(ADCSRA , ADSC) == 0 && testbit(ADCSRA , ADIF) == 0)  {
          setbit(ADCSRA, ADSC);   //start conversie
       }
       // daca s-a terminat conversia
       if( testbit(ADCSRA , ADSC) == 0 && testbit(ADCSRA , ADIF)) {
          // sterge bitul care indica sfarsitul conversiei
          clrbit(ADCSRA , ADIF);
          // citeste rezultatul conversiei din portul de date conform setarii ADLAR
          val=ADCH;   //din ce port?
          
          temp=(5*val*100UL)/255;
          
          valoareSute=temp/100%10;
          valoareZeci=temp/10%10;
          valoareUnitati=temp%10;
          
          //buf[0]='0'+valoareSute;
          //buf[1]='0'+valoareZeci;
          //buf[2]='0'+valoareUnitati;
          //buf[3]=0;
         
          gotoLC(1,1);
          putsLCD("V= ");
          putchLCD(valoareSute+'0');
          putchLCD('.');
          putchLCD(valoareZeci+'0');
          putchLCD(valoareUnitati+'0');
          
         // putsLCD(buf);
    }
  }
}

