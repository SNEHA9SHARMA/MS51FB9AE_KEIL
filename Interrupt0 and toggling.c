#include "common.h"
#include "MS51_16K.h"
void INT0_ISR(void) interrupt 0{
	 _push_(SFRS);
	 P10=~P10;
	 clr_TCON_IE0;
	 _pop_(SFRS);
}
void main(){
	P30_QUASI_MODE;
	P30=1;
	P10_PUSHPULL_MODE;
	P10=0;
	INT0_FALLING_EDGE_TRIG;
	set_IE_EX0;
	ENABLE_GLOBAL_INTERRUPT;
	while(1);
	
}
	