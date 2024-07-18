#include "MS51_16K.H"
#include "PWM.h"
float d;
int d1;
int d2;
int d3;
float p;
int p1;

void initPwm(void){
     P14_QUASI_MODE;
     PWM_IMDEPENDENT_MODE;
	PWM_CLOCK_DIV_8;
	   
}
void pw(float duty){
	PWM1_P14_OUTPUT_ENABLE;
	p=2000000/162.54-1;
	p1=(int)(p);
	PWMPH=(p1 >> 8) & 0xFF;
	PWMPL=p1 & 0xFF;
	d=duty*p/100;
	d1=(int)(d);
	PWM1H=(d1 >> 8) & 0xFF;;
	PWM1L=d1 & 0xFF;
  set_PWMCON0_LOAD;
  set_PWMCON0_PWMRUN;
}