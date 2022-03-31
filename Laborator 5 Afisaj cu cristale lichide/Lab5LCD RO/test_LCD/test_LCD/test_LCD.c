#include "LCD.h"
#include <avr/io.h>

char msg3[] = "0123456789abcdef";
char msg4[] = "ghijklmnopqrstuv";

int main(){
   
   initLCD();

   while(1){
      //write the character
      putchLCD('H');
      _delay_ms(1000);
      
      //clear display
      clrLCD();
      _delay_ms(500);
      
      //print the „Hello micro!” message
      putsLCD("Hello");
      gotoLC(2, 7);
      putsLCD("micro!");
      _delay_ms(1000);
      clrLCD();
      _delay_ms(500);
      
       // din linia 1, coloana 1 scrie caracter cu caracter textul 0123456789abcdef.
       gotoLC(1, 1);
       for(int i = 0; i < 16; ++i){
          putchLCD(msg3[i]);
          gotoLC(1, i + 2);
          // dupa scrierea fiecarui caracter asteapta 0.5 secunde.
          _delay_ms(500);
       }
       
       // din linia 2, coloana 1 scrie mesajul „ghijklmnopqrstuv”
       gotoLC(2, 1);
       putsLCD(msg4);
       
       // muta cursorul pe linia 2, coloana 16.
       gotoLC(2, 16);
       // muta cursorul catre stânga caracter cu caracter pâna pe linia 2, coloana 1.
       for(int i = 16; i > 0; --i){
          gotoLC(2, i);
          //dupa fiecare mutare asteapta 0.5 secunde.
          _delay_ms(500);
       }
       
       //muta cursorul pe linia 1, coloana 16.
       gotoLC(1, 16);
       // muta cursorul catre stânga caracter cu caracter pana pe linia 1, coloana 1.
       for(int i = 16; i > 0; --i){
          gotoLC(1, i);
          // dupa fiecare mutare asteapta 0.5 secunde.
          _delay_ms(500);
       }
       
       // asteapta 0.5 secunde
       _delay_ms(500);       clrLCD();
       _delay_ms(500);
   }
}

