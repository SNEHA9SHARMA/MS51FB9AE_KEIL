
#include "MS51_16K.H"
#include "tds_uart1.h"
#include "tds_adc.h"
#include "button.h"
#include "delay.h"
#include "rgy_led.h"

//#include "sevenSeg.h"

void main()
	{	
		unsigned int memData = 0;
		initUART1();
		initADC();
		initButton();
		initTimer0();
    init_INT1();
		initPWM();
		
		//initSegmentPins();
		
		while(1)
			{		
				ADC_handle();
				
				//Buttonh_handle();
				
				ms_delay(500);

			}	
	}

