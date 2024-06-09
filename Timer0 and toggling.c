#include "common.h"
#include "MS51_16K.h"
void Timer0_Init(void){
	EA=0;
	TMOD=0x01;
	TH0=0xFA;
	ET0=1;
	TR0=1;
	EA=1;
}

void Timer0_ISR(void) interrupt 1{
	TF0=0;
	TH0=0xFA;
	TL0=0xCB;
	P10=~P10;
}
void main(void){
	
	Timer0_Init();
	P10_PUSHPULL_MODE;
	while(1);
}