/*
 * kbd.c
 *
 * Created: 4/14/2022 8:21:58 AM
 * Author : user
 */ 

#include <avr/io.h>
#include "LCD.h"

#define NOKEY 0x7f
#define DELAY 200

char kbscan(){
   
   unsigned char temp;
   unsigned char cols=0;
   
   unsigned char lina=0; //linia activa
   unsigned char cola=0; //coloana activa
   
   unsigned char cod_intern;
   char cod_extern;
   
   char tabela_trans[] = "123A456B789C*0#D";
   
   for(DDRA=1<<4; DDRA!=0 ;DDRA<<=1)
   {
      _delay_us(4);
      cols=~PINA;
      cols = cols & 0b00001111; //bitii 7:4 sunt mascati la ‚0’
      
      if(cols!=0) //testam daca exista cel putin un ‚1’ in variabila cols
      {
         break;
      }
   }
   
   if(cols==0) 
   {
     return NOKEY; 
   }
   
   temp=DDRA;
   
   //calculeaza lina
   while((temp & 1<<4)==0)
   {
       lina=lina+1;
       temp>>=1;
   }
   
   //calculeaza cola
   while(cols!=0b00000001)
   {
      cola=cola+1;
      cols>>=1;
   }
   cod_intern = lina * 4 + cola; //calculeaza cod_intern
   cod_extern=tabela_trans[cod_intern];
   return cod_extern;
      
} //end kbscan

//int main(void)
//{
//   unsigned char temp;
//   PORTA=0;
//   initLCD();
    /* Replace with your application code */
//    while (1) 
//    {
//       temp=kbscan();
//       if(NOKEY != temp){
//          clrLCD();
//          putchLCD(temp);
//       }
//    }
  
//}

int main(){
   
   char code_ante = NOKEY;
   char code_now = NOKEY;
   unsigned char kbhit = 0;
   char kbcode;
   unsigned char loop_cnt=0;
   
   //initializare LCD, kbd, etc.
   initLCD();
   
   while(1){ //bucla principala
      //…
      if(loop_cnt==DELAY){ //citirile se fac din 15 ms in 15 ms
         loop_cnt=0;
         code_ante = code_now;
         code_now = kbscan();
         
         if( code_ante == NOKEY && code_now != NOKEY){
            kbhit=1;
            kbcode=code_now;
         }
      }
      //……
      //consuma codul
      if(kbhit){
         kbhit=0;
         //prelucreaza kbcode; de exemplu afi?eaza-l
         putchLCD(kbcode);
      }
      //……
      loop_cnt++;
   } //end while
} //end main