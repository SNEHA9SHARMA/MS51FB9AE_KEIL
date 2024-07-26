
#include "common.h"
#include "MS51_16K.H"
#include "sevenSeg.h"
#include "delay.h"
#include "tds_adc.h"
#include "tds_uart1.h"
#include "iot_eeprom.h"


const unsigned int digitPattern[10][7] = 
	{		
		// a  b  c  d  e  f  g
		{ 0, 0, 0, 0, 0, 0, 1 }, // 0
		{ 1, 0, 0, 1, 1, 1, 1 }, // 1
		{ 0, 0, 1, 0, 0, 1, 0 }, // 2
		{ 0, 0, 0, 0, 1, 1, 0 }, // 3
		{ 1, 0, 0, 1, 1, 0, 0 }, // 4
		{ 0, 1, 0, 0, 1, 0, 0 }, // 5
		{ 0, 1, 0, 0, 0, 0, 0 }, // 6
		{ 0, 0, 0, 1, 1, 1, 1 }, // 7
		{ 0, 0, 0, 0, 0, 0, 0 }, // 8
		{ 0, 0, 0, 0, 1, 0, 0 }  // 9
	};
	
	
void initSegmentPins()
	{
		P00_PUSHPULL_MODE;
		P01_PUSHPULL_MODE;
		P02_PUSHPULL_MODE;
		P03_PUSHPULL_MODE;
		P04_PUSHPULL_MODE;
		P05_PUSHPULL_MODE;
		P06_PUSHPULL_MODE;
		//P07_PUSHPULL_MODE;
		
		P10_PUSHPULL_MODE;
		P11_PUSHPULL_MODE;
		P12_PUSHPULL_MODE;
		P13_PUSHPULL_MODE;
	}	
	
	
void setSegment(unsigned int value) 
	{
		A = digitPattern[value][0];
		B = digitPattern[value][1];
		C = digitPattern[value][2];
		D = digitPattern[value][3];
		E = digitPattern[value][4];
		F = digitPattern[value][5];
		G = digitPattern[value][6];
		//H = digitPattern[value][7];
	}
															
void displayDigit(int value, int digit) 
	{
		D1 = 0;
		D2 = 0;
		D3 = 0;
		//D4 = 0;
		
		if(digit == 1)
				D1 = 1;
		else if(digit == 2)
				D2 = 1;
		else if(digit == 3)
				D3 = 1;

		setSegment(value);

	}

void displayValue(float value) 
	{
			int intValue = (int)value;

			// Display integer part
			displayDigit(intValue / 100, 3);
			ms_delay(50);
			displayDigit((intValue / 10) % 10, 2);
			ms_delay(50);
			displayDigit((intValue) % 10, 1);
			ms_delay(50);

	}
	
/*void setLED(unsigned int value)
	{	
		RED = 0;	
		GREEN = 0;
		
		if (PUSHBUTTON == 1)
			RED = 1;
	
		else if (value <= TDS_SAFE)
		{	
			//sendString("Safe Water \n");
			GREEN = 1;
			ms_delay(5);
			GREEN = 0;
			ms_delay(5);
		}
		
		else if (value >= TDS_SAFE)
		{	
			//sendString("Unsafe Water \n");
			RED = 1;
			ms_delay(5);
			RED = 0;
			ms_delay(5);
		}
	}
	
	**************************************************
	
	/*switch (channel) 
	{
		case 0:
			adcValue = readADC(TEMP_CHANNEL);
			tempValue = adcToTEMP(adcValue);
			displayValue(tempValue);
			ms_delay(50);
			channel = 2;
			ms_delay(3000);
			break;

		case 2:
			
			adcValue = readADC(TDS_CHANNEL);
			tdsValue = adcToTDS(adcValue);
			displayValue(tdsValue);
			ms_delay(10);
			channel = 0;
			ms_delay(3000);
			break;
		default:
			break;
	}
	
	//setLED(tdsValue);

	
*/