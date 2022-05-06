#include <avr/io.h>
#include "LCD.h"
#include<stdio.h>

#define NOKEY 0x7f
#define DELAY 200
#define K 125

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
  
  unsigned char cycles=0;
  unsigned char secunde=00, minute=29, ore=9;
  
  unsigned int ms8=0;
  unsigned int ts=0, stop_activ;
  DDRA = 0;
  PORTA = 0;
  char buf[17];
  //initializare LCD, kbd, etc.
  initLCD();
  
  //       |  |CTC mode
  TCCR2=0b00011110;
  //        || |||__P=256
  //        ||_____ OC2 toggle
  OCR2=250-1; // N=250;
  //DDRD |= 1<<7;
  while(1){ //bucla principala
     //...
     if(loop_cnt==DELAY){ //citirile se fac din 15 ms in 15 ms
        loop_cnt=0;
        code_ante = code_now;
        code_now = kbscan();
        if( code_ante == NOKEY && code_now != NOKEY){
           kbhit=1;
           kbcode=code_now;
           setbit(DDRD, 7); // seteaza OC2 ca iesire pentru a activa sunetul
           // Aceasta operatie a mai fost facuta la pasul 6
           ts = ms8; // ia o amprenta de timp 
           stop_activ = 1; // activeaza oprire sunet. Defineste aceasta variabila
           // si initializeaz-o cu zero.
        }
        if(stop_activ && ms8 - ts > 100 ){
           clrbit(DDRD, 7); // seteaza OC2 ca intrare pentru a opri sunetul
           stop_activ = 0;
        }
     }
     //......
     //consuma codul
     if(kbhit){
        kbhit=0;
        //prelucreaza kbcode; de exemplu afi?eaza-l
        gotoLC(1, 1);
        putchLCD(kbcode);
     }
     //......
     loop_cnt++;
     
     if( testbit(TIFR, OCF2) ){
        setbit(TIFR, OCF2);
        cycles++;
        ms8+=8;
        
        if(cycles == K){ // k=125
           // a trecut o secunda
           cycles=0;
           
           // actualizeaza secunde, minute, ore
           secunde++;
           if(secunde == 60)
           {
              secunde = 0;
              minute++;
              if(minute == 60)
              {
                 minute = 0;
                 ore++;
                 if(ore == 24)
                 {
                    ore = 0;
                 }
              }
           }
           // afiseaza timpul
           sprintf(buf, "%2d:%02d:%02d", ore, minute, secunde);
           gotoLC(2, 1);
           putsLCD(buf);
           //Verifica incadrarea in timp:
           if(testbit(TIFR, OCF2) ){
              //Afiseaza mesaj de eroare si intra in bucla infinita.
              putsLCD("Eroare");
              while(1){}
           }
        }
     }
  } //end while
} //end main/end main