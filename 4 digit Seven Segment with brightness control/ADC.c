#include "MS51_16K.H"
#include "ADC.h"
#include <stdio.h>
#include <math.h>
unsigned char xdata ADCdataAINH, ADCdataAINL;

unsigned char tempH, tempL;
int adc_value1;
float frac;
float adc_value2;
/****************FUNCTIONS******************/
int mod;
void initAdc(void){
   ENABLE_ADC_CH4;  // Enable ADC on analog input channel 4 (AIN4)

    
}
  

float adc(void){
	
   clr_ADCCON0_ADCF;  // Clear ADC completion flag
    set_ADCCON0_ADCS;  // Start ADC conversion
    while (ADCF == 0);  // Wait for ADC conversion to complete

        // Read ADC result
    tempH = ADCRH;  // Read the high byte of the ADC result
    tempL = ADCRL;  // Read the low byte of the ADC result
    adc_value1 = (tempH << 4) | (tempL & 0x0F);  // Combine high and low bytes to form the full 10-bit result
    adc_value2=(float)(adc_value1);
  frac= adc_value2/4096.0*100;
  if(frac<=20){mod=4;}
  else if( frac>20 && frac<=40){ mod=10;}
  else if(frac>40 && frac<=60){ mod=25;}
  else if(frac>60 && frac<=80){ mod=40;}
  else mod=100;
  return frac;

}

