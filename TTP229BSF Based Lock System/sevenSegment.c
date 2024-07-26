#include "MS51_16K.H"
#include "sevenSegment.h"
#include "math.h"



void initSevenSegment(){

      P17_PUSHPULL_MODE;
      P04_PUSHPULL_MODE;
      P03_PUSHPULL_MODE;
      P02_PUSHPULL_MODE;
      P14_PUSHPULL_MODE;
      P13_PUSHPULL_MODE;
      P12_PUSHPULL_MODE;
      P10_PUSHPULL_MODE;
      P00_PUSHPULL_MODE;
      P01_PUSHPULL_MODE;
	  P11_PUSHPULL_MODE;
	    
}


const unsigned int bits[14][7]={
	
     {0,0,0,0,0,0,1},
     {1,0,0,1,1,1,1},
     {0,0,1,0,0,1,0},
     {0,0,0,0,1,1,0},
     {1,0,0,1,1,0,0},
     {0,1,0,0,1,0,0},
     {0,1,0,0,0,0,0},
     {0,0,0,1,1,1,1},
     {0,0,0,0,0,0,0},
     {0,0,0,0,1,0,0},
     {1,0,0,0,0,1,0},
     {0,1,1,1,0,0,0},
     {0,0,0,1,0,0,0},
     {1,1,1,0,0,0,1}
	 
};

// Define the digit pins (assuming P1.0 to P1.3 for digit control)


// Function to display a digit
void displayDigit(unsigned char digit, unsigned int value) {
    // Turn off all digits
    if(DIGIT1==1) DIGIT1 = 0;
    if(DIGIT2==1) DIGIT2 = 0;
    if(DIGIT3==1) DIGIT3 = 0;
    if(DIGIT4==1) DIGIT4 = 0;
   
    // Set the segments for the digit
    SEG_A = bits[value][0];
    SEG_B = bits[value][1];
    SEG_C = bits[value][2];
    SEG_D = bits[value][3];
    SEG_E = bits[value][4];
    SEG_F = bits[value][5];
    SEG_G = bits[value][6];
    
    // Turn on the appropriate digit
    switch(digit) {
        case 1: DIGIT1 = 1; break;
        case 2: DIGIT2 = 1; break;
        case 3: DIGIT3 = 1; break;
        case 4: DIGIT4 = 1; break;
    }
}

/*void displayNumber(void) {
	  
	
        displayDigit(4, 3);
        ms_delay(5);
			  
        displayDigit(3, 4);
        ms_delay(5);
			  
        displayDigit(2, 5);
        ms_delay(5);
			  
        displayDigit(1, 6);
			  ms_delay(5);
			  
} */

void ms_delay(unsigned int delay)
    {
        unsigned int i, j;
        for(i = 0; i < delay; i++)
        {
            for(j = 0; j < 2000; j++){}   // random delay
        }
    }   
