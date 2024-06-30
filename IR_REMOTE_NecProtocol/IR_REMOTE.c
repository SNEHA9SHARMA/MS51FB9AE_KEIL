#include "MS51_16K.H"
#include "IR_REMOTE.h"
#include "UART.h"
uint32_t keyCode;
uint32_t bitPattern=0,newKey=0;
uint8_t timerValue;
uint8_t msCount=0;
int pulseCount=-1;
int flag=0;
char au;
int it=0;
extern uint8_t rx_buffer[BUFFER_SIZE]; 
void timer0_isr() interrupt 1{
    if(msCount<20) msCount++;
    TF0=0;
    TH0 = 0xF8;   
    TL0 = 0x30;
	  P14=~P14;
   }
           
void externalIntr0_ISR()  interrupt 0{
    _push_(SFRS);
    timerValue = msCount;
    msCount = 0;
	flag=0;
	TH0 = 0xF8;  
    TL0 = 0x30;
    pulseCount++;
	  rx_buffer[it]=pulseCount;
    it++;
      if(timerValue>10){
				pulseCount=-1;
				bitPattern=0;
    }
  
else if((pulseCount>=-1) && (pulseCount<=31)) {  
    if(timerValue>=2){
        bitPattern |=(uint32_t) 1<<(31-pulseCount);
        rx_buffer[it]=71;
        it++;
	} else { 
        
         rx_buffer[it]=70;
         it++;
   }
   
   if(pulseCount == 31){
        newKey = bitPattern;  
        pulseCount = -2; 
        bitPattern=0;		 
        flag=1;

    }
    
}
   clr_TCON_IE0;
    _pop_(SFRS);
 
}
void IR_RemoteInit(void){
    P30_QUASI_MODE;
    P30=1;
    TMOD |= 0x01;  // Timer0 MODE1(16-bit timer)
    TH0 = 0xF8;    // Timer value for 1ms at 24Mhz clock
    TL0 = 0x30;
    TR0 = 1;       // Start the Timer
    ET0 = 1;       // Enable the Timer0 Interrupt
    INT0_FALLING_EDGE_TRIG;
    set_IE_EX0;
    ENABLE_GLOBAL_INTERRUPT;
}

uint32_t IR_RemoteGetKey(void){
    keyCode = newKey;
    newKey = 0x00;
    return keyCode;           
} 
