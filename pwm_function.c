#include "common.h"
#include "MS51_16K.H"
float d;
int d1;
int d2;
int d3;
float p;
int p1;
int i;
int pw(float freq, float duty){
	p=2000000/freq-1;
	p1=(int)(p);
	PWMPH=(p1 >> 8) & 0xFF;
	PWMPL=p1 & 0xFF;
	d=duty*p/100;
	d1=(int)(d);
	return d1;
	
}
void main(void)
{

    P14_QUASI_MODE;
	  P12_QUASI_MODE;
	  P10_QUASI_MODE;
	  PWM_IMDEPENDENT_MODE;
	  PWM_CLOCK_DIV_8;
	  PWM1_P14_OUTPUT_ENABLE;
	  PWM0_P12_OUTPUT_ENABLE;
	  PWM2_P10_OUTPUT_ENABLE;
	  d1=pw(162.54,50.00);            //function of pwm
	  PWM1H=(d1 >> 8) & 0xFF;;
	  PWM1L=d1 & 0xFF;
	  set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
	  d2=pw(162.54,75.00);
	  PWM0H=(d2 >> 8) & 0xFF;;
	  PWM0L=d2 & 0xFF;
	  set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
	  d3=pw(162.54,33.00);
	  PWM2H=(d3 >> 8) & 0xFF;;
	  PWM2L=d3 & 0xFF;
	  set_PWMCON0_LOAD;
    set_PWMCON0_PWMRUN;
    while (1)
    {
         
             
    }
}
