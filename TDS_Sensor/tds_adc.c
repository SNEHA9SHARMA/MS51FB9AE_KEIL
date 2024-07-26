
#include <math.h>
#include <stdio.h>
#include "MS51_16K.H"
#include "delay.h"
#include "tds_adc.h"
#include "tds_uart1.h"
#include "rgy_led.h"



void initADC()
	{
		P05_INPUT_MODE;				 
		P06_INPUT_MODE; 			
		P07_PUSHPULL_MODE;			
		P01_PUSHPULL_MODE;	
	}

unsigned int readTemp_ADC(void) 	
	{
		unsigned int adcValue = 0;
		unsigned int adcSum = 0;	
		unsigned int i;
		
		ENABLE_ADC_AIN3;
		clr_ADCF;
		set_ADCS;  
		for(i = 0; i < SAMPLES; i++)
			{
				while(ADCF == 0); 
				adcSum += (ADCRH << 4) | (ADCRL >> 4);
				ADCRH =0;
				ADCRL=0;
			}
		adcSum = adcSum / SAMPLES;
		adcValue = (unsigned int)adcSum;
		return adcValue;
	}
	
	
unsigned int readTDS_ADC(void)
	{
		float adcAverage = 0;
		float adcValue_1 = 0;
		float adcAverage_1 = 0;
		float adcValue = 0;
		unsigned int i;
		
		for(i = 0; i < SAMPLES; i++)
		{	
			TDS_ALT = 1;			
			TDS_EN = 0;					// following values are not used in final calculation
			us_delay(SAMPLING_START_DELAY);
			ENABLE_ADC_AIN4;
			clr_ADCF;
			set_ADCS; 
			while(ADCF == 0);
			adcValue_1 = (ADCRH << 4) | (ADCRL >> 4);
			adcAverage_1 += adcValue_1;
			ADCRH = 0;
			ADCRL = 0;
			
			/****************************************************/
			
			TDS_ALT = 0;								
			TDS_EN = 1;					//Actual Sampling starts from here
			us_delay(SAMPLING_START_DELAY);
			ENABLE_ADC_AIN4;
			clr_ADCF;
			set_ADCS; 
			while(ADCF == 0);
			adcValue = (ADCRH << 4) | (ADCRL >> 4);
			adcAverage += adcValue;
			ADCRH = 0;
			ADCRL = 0;

		}
					
		TDS_ALT = 0;
		TDS_EN = 0;
		
		adcAverage_1 = 0;		
		adcAverage = adcAverage / SAMPLES;
		
		return adcAverage;
	}
			
float adcToTEMP(unsigned int adcValue)
	{	
		float temp =0;
		
		temp = 4095 /(float) adcValue - 1;
    temp = REF_R/ temp;               
    temp = temp / NOMINAL_R;
		temp = log(temp); 		
		temp /= BETA;
		temp += 1.0/(REF_TEMPERATURE);
		temp = 1.0/temp;
		temp -= 273.15;
		
		return temp;
	}
	
float adcToTDS(unsigned int  adcValue, float temp)
	{
		double conpensated_adcValue = 0;
		double tds = 0;
		double A = 1000000;
		double B = 1.23755;
		float C = (1.0 + 0.02*(temp - 25));
		
		//float tdsV = ((float)adcValue)*5/4095;

		conpensated_adcValue = adcValue/C;
		
		//formula for calculating TDS values

		tds = A /(pow(adcValue,B));
		
		tds = tds/C;
		
		if(tds < 60)
			tds = 0;
		
		//tds = A /(pow(adcValue,B));
		
		return tds;
	}
	
	
void ADC_handle(void)
	{
		unsigned int tempADC = 0;
		float tempValue = 0.0;
		unsigned int tdsADC = 0;
		float tdsValue = 0.0;
		
		//Temperature
		
		tempADC = readTemp_ADC();
		tempValue = adcToTEMP(tempADC);
		
		tdsADC = readTDS_ADC();
		tdsValue = adcToTDS(tdsADC,tempValue);

		sendString("\nTEMP: ");
		sendNumber(tempValue);
		sendString("°C ");
		
		sendString("\t TDS: ");
		sendInteger(tdsValue);
		sendString(" ppm @ ");

		//sendString("\tTDS_ADC: ");
		sendInteger(tdsADC);
		sendString(" \n");

		//LED_handle(tdsValue);							//set LED intensity

	}
	