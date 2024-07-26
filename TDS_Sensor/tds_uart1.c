
#include <stdio.h>
#include "MS51_16K.H"
#include "tds_uart1.h"


void initUART1()
	{
		P16_QUASI_MODE;				//set P1.6 as quasi bidirectional pin
		SCON_1 = 0x40;				//uart0 in mode 1		|START|8-BIT DATA|STOP|
		T3CON = 0xF8;					//timer1 in mode 
		
		RH3 = 0xFF;
		RL3 = 0x98;
		
		T3CON|= 0x08; 

		TI_1 = 1;							//ready to sen	
	}

void sendChar(char c)
	{
		while (TI_1 == 0);			//wait until data is sent 
		SBUF_1 = c;						//write character to be sent to SBUF
		TI_1 = 0;							//reset TI flag--transmission complete
	}

void sendString(char *s)
	{
		 int i;
		 for(i = 0; s[i] != 0; i++)
			 {
					sendChar(s[i]);
			 }
	}
	
void sendNumber(float value)
	{
		char buffer[20];
		sprintf(buffer, "%4.2f", value);
		sendString(buffer);
	}

void sendInteger(int value)
	{
		char buffer[20];
		sprintf(buffer, "%d", value);
		sendString(buffer);
	}


