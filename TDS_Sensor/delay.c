
#include "MS51_16K.H"
#include "sevenSeg.h"
#include "delay.h"
#include "tds_adc.h"
#include "tds_uart1.h"
#include "iot_eeprom.h"


void ms_delay(unsigned int delay)
	{
		unsigned int i, j;
		for(i = 0; i < delay; i++)
		{
			for(j = 0; j < 2000; j++){}   // random delay
		}
	}	
	
void us_delay(unsigned int delay)
	{
		unsigned int i;
    while (delay--) 
		{
      for (i = 0; i < 12; i++); 
    }
	}