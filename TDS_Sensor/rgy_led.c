
#include <stdio.h> 
#include "MS51_16K.H"
#include "rgy_led.h"


void initPWM(){
  P14_PUSHPULL_MODE;
  PWM1_P14_OUTPUT_ENABLE;
  PWM_IMDEPENDENT_MODE;
  PWM_EDGE_TYPE;
  PWM_CLOCK_FSYS;
  PWM_CLOCK_DIV_64;
  set_PWM_period(1023);
  PWM_OUTPUT_ALL_NORMAL;
}

void LED_handle(unsigned int value)
	{
		set_CLRPWM;
		set_PWMRUN; 
		if(value <= 100)
			{
					set_PWM1(900);
			}
		else if(value > 100 && value <= 500)
			{
					set_PWM1(300);
			}
		else
			{ 
					set_PWM1(100);
			}
	}

void set_PWM_period(unsigned int value)
	{
  PWMPL = (value & 0x00FF);
  PWMPH = ((value & 0xFF00) >> 8);
	}

void set_PWM1(unsigned int value)
	{
  PWM1L = (value & 0x00FF);
  PWM1H = ((value & 0xFF00) >> 8);
  set_LOAD;
	}


/*

void initLED_PWM()
{
    P15_PUSHPULL_MODE;      
}

void setPWMValue(uint8_t value, uint8_t channel)
{
    switch(channel)
    {
        case 0: PWMPH = value; break; // Set PWM0 high byte
        case 1: PWM01H = value; break; // Set PWM1 high byte
        case 2: PWM02H = value; break; // Set PWM2 high byte
        default: break;
    }
}

void controlLEDColor(int value)
{
    if(value < TDS_SAFE)
    {
        // Green
        setPWMValue(0, 0); // Set PWM duty cycle for Red to 0
        setPWMValue(255, 1); // Set PWM duty cycle for Green to maximum
        setPWMValue(0, 2); // Set PWM duty cycle for Yellow to 0
    }
    else if(value >= TDS_SAFE && TDS_HAZARDOUS <= 200)
    {
        // Yellow
        setPWMValue(0, 0); // Set PWM duty cycle for Red to 0
        setPWMValue(255, 1); // Set PWM duty cycle for Green to maximum
        setPWMValue(255, 2); // Set PWM duty cycle for Yellow to maximum
    }
    else
    {
        // Red
        setPWMValue(255, 0); // Set PWM duty cycle for Red to maximum
        setPWMValue(0, 1); // Set PWM duty cycle for Green to 0
        setPWMValue(0, 2); // Set PWM duty cycle for Yellow to 0
    }
}


*******************************************************************


void pwm_init()
{
  P15_PUSHPULL_MODE;
  PWM1_P15_OUTPUT_ENABLE;
  PWM_IMDEPENDENT_MODE;
  PWM_EDGE_TYPE;
  PWM_CLOCK_FSYS;
  PWM_CLOCK_DIV_64;
  set_PWM_period(1023);
  PWM_OUTPUT_ALL_NORMAL;
}

void pwm(unsigned int pwm_value)
{
  signed int value = pwm_value;
  set_CLRPWM;
  set_PWMRUN; 
  if(value <= NORMAL_TDS)
	{
  set_PWM1(800);
  }
  else{ 
  set_PWM1(200);
  }
}

void set_PWM_period(unsigned int value)
{
  PWMPL = (value & 0x00FF);
  PWMPH = ((value & 0xFF00) >> 8);
}

void set_PWM1(unsigned int value)
{
  PWM1L = (value & 0x00FF);
  PWM1H = ((value & 0xFF00) >> 8);
  set_LOAD;
}


*/