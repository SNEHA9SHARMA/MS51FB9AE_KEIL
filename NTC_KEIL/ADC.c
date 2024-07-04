#include "MS51_16K.H"
#include "ADC.h"
unsigned char xdata ADCdataAINH, ADCdataAINL;

unsigned char tempH, tempL;
float frac;

/**********LOG FUNC**********/
float result;
float term;
int n;
/*******ADC TO TEMP**************/
#define nominal_resistance 10000       //Nominal resistance at 25⁰C
#define nominal_temeprature 25   // temperature for nominal resistance (almost always 25⁰ C)
#define beta 3950  // The beta coefficient or the B value of the thermistor (usually 3000-4000) check the datasheet for the accurate value.
#define Rref 10000   //Value of  resistor used for the voltage divider
float temperature;
float average=0;
float adc1;


void initAdc(void){
	ENABLE_ADC_CH1;
}
  

float adc(void){
	
  register unsigned int adc_value = 0x0000;
  clr_ADCF;
  set_ADCS;                  
  while(ADCF == 0);
  adc_value = ADCRH;
  adc_value <<= 4;
  adc_value |= ADCRL;
  return (float) adc_value;
}
float log(float x) {
    if (x <= 0) return -1;  
    result = 0.0; 
    while (x > 2.0) {
        result += 0.693147; // log(2)
        x /= 2.0;
    }
    while (x < 1.0) {
        result -= 0.693147; // log(2)
        x *= 2.0;
    }
    x -= 1.0;
    term = x;
    for (n = 1; n < 10; n++) {
        if (n % 2 == 0) {
            result -= term / n;
        } else {
            result += term / n;
        }
        term *= x;
    }
    
    return result;
}

int ConvertADCToTemperature(int samples) {
   average      = (float) 4095 / (float) samples - 1 ;
   average  = (float) 1.0/ average;   
   temperature  = log (average);                 
   temperature  = temperature  / beta;                  
   temperature  = temperature + ( 1.0 / (nominal_temeprature + 273.15) ); 
   temperature  = 1.0 / temperature ;                 
   temperature  = temperature - 273.15 ; 
   return temperature;
}
