#include "MS51_16K.H"
#include "sevenSegment.h"
#include "TIMER1.h"
#include "PWM.h"
#include "ADC.h"
// Define the segments for each digit (assuming common cathode display)

float duty1;

// Main function
void main() {
    // Configure the GPIO pins as output
    FsysSelect(FSYS_HIRC);
    MODIFY_HIRC(HIRC_24);
    ENABLE_GLOBAL_INTERRUPT;
    initSevenSegment();
	  initTimer();
	  initAdc();
	  initPwm();
	  PWM1_P14_OUTPUT_ENABLE;
	  P17_PUSHPULL_MODE;
	while(1){
		 
     duty1=adc();
     pw(duty1);

     

	  }
}

