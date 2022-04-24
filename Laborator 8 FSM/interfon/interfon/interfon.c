/*
 * interfon.c
 *
 * Created: 4/21/2022 8:13:40 AM
 * Author : user
 */ 

#include "LCD.h"
#include "string.h"

#define NOKEY 0x7F

#define FMSG   0
#define WAIT   1
#define RING   2
#define OPEN   3
#define COD1   4
#define COD2   5
#define COD3   6
#define ERR    7

char kbscan();

int main(){

   char code_now= NOKEY, code_ante;
   unsigned char kbhit=0;
   char kbcode, cmd=0;
   
   unsigned char loop_cnt=0;
   
   char cod[4]="123";
   char buf[4];
   char stare = FMSG;
   
   initLCD();
   PORTA = 0;
   
   while (1){
      //determina daca este tasta apasata
      if(loop_cnt==100){
         code_ante=code_now;
         code_now = kbscan();
         if(code_now!=NOKEY && code_ante==NOKEY){
            kbhit=1;
            kbcode=code_now;
         }
         loop_cnt=0;
      }
      
      //SFSM
      switch (stare){
         case FMSG:
         clrLCD();
         putsLCD("Suna la 1..8,");
         gotoLC(2,1);
         putsLCD("C pentru cod:");
         stare = WAIT;
         break;
         
         case WAIT:
         if(kbhit){
            kbhit=0;
            if ('C'==kbcode){
               clrLCD();
               putsLCD("Cod=");
               stare = COD1;
            }
            
            if (kbcode>='1' && kbcode <= '8'){
               clrLCD();
               putsLCD("Sun la ");
               putchLCD(kbcode);
               stare = RING;
            } 
         }
         break;
         
         case RING:
         if(cmd==0){
            _delay_ms(5000);//asteapta  5 secunde
            stare=FMSG;
         }
         break;
         
         case COD1:
         if(kbhit){
            kbhit=0;
            if (kbcode>='0' && kbcode <= '9'){
               buf[0]=kbcode;
               putchLCD('*');
               stare = COD2;
            }
            else{
               stare = FMSG;
            }
         }
         break;
         
         case COD2:
         if(kbhit){
            kbhit=0;
            if (kbcode>='0' && kbcode <= '9'){
               buf[1]=kbcode;
               putchLCD('*');
               stare = COD3;
            }
            else{
               stare = FMSG;
            }
         }
         break;
         
         case COD3:
         if(kbhit){
            kbhit=0;
            if (kbcode>='0' && kbcode <= '9' ){
               buf[2]=kbcode;
               putchLCD('*');
               if(strncmp(buf,cod,3)==0){
                  clrLCD();
                  putsLCD("Deschis!");
                  stare = OPEN;
               }
               else{
                  clrLCD();
                  putsLCD("Cod invalid");
                  stare=ERR;
               }
            } 
            else{
               stare = FMSG;
            }
         }
         break;
         
         case OPEN:
         _delay_ms(5000);//asteapta  5 secunde
         stare=FMSG;
         
         break;
         
         case ERR:
         _delay_ms(5000);//asteapta  5 secunde
         stare = FMSG;
         break;
         
      }//end switch
      loop_cnt++;
   }//end while
}//end main

char kbscan(){
   unsigned char temp;
   unsigned char cols=0;
   unsigned char lina=0; //active line
   unsigned char cola=0; //active column
   unsigned char internal_code;
   char cod2return;
   char LUT[] = "123A456B789C*0#D";
   
   for( DDRA = 1<<4; DDRA>0; DDRA=DDRA<<1  ) {
      _delay_us(4);
      cols=~PINA;
      cols &=0b00001111;
      if(cols!=0){
         break;
      }
   }
   
   if(cols==0){
      return NOKEY;
   }
   
   temp=DDRA;
   while(temp!=0b00010000){
      temp >>=1;
      lina++;
   }
   
   while(cols!=0b00000001){
      cols >>=1;
      cola++;
   }
   
   internal_code=lina*4+cola;
   cod2return = LUT[internal_code];
   return cod2return;
}