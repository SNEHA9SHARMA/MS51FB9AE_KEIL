#include "MS51_16K.H"
#include "TIMER1.h"
#include "sevenSegment.h"
#include "ADC.h"
/****FunctionS****/
//int start=0;
int msCount=0;
int count=0;
int num;
int a,b,c,dseg;
a=0;
b=0;
c=0;
dseg=0;
int num1;
int a1,b1,c1,dseg1;
int remainder;
//extern int mod;
 void initTimer(void){
 	EA=0;
 	TMOD=0x01;
 	TH0=0xFF;
 	TL0=0xFE;
 	ET0=1;
 	TR0=1;
 	EA=1;
	
 	
 }
 void Timer0_ISR(void) interrupt 1{
 	TF0=0;
 	TH0=0xFF;
 	TL0=0xFE;
 	
	
	msCount++;
 	if(msCount>=500){
	//P17=1;
 	remainder=count%4;
	
	
 	switch(remainder){
	
 	case 0: displayDigit(4,a); break;
 	case 1: displayDigit(3,b); break;
 	case 2: displayDigit(2,c); break;
 	case 3: displayDigit(1,dseg); break;
	/*case 4: DIGIT1=0; break;
		default: break;*/
		
 	}
 	count++;
	if(count%10000==0){/*dseg=c;
	c=b;
	b=a;
	a++; if(a==10) a=0;*/ count=0; }
 	msCount=0;
	//P17=0;
 	}
  
	
   
 	
 }

 