#include "MS51_16K.H"
#include "I2C.h"
#include "UART.h"
#include "FLASH.h"
#include "sevenSegment.h"
#include "TIMER1.h"
/*#include "PWM.h"
#include "ADC.h"*/
// Define the segments for each digit (assuming common cathode display)

extern int written;
//float duty1;

// Main function

void main() {
    // Configure the GPIO pins as output
    FsysSelect(FSYS_HIRC);
    MODIFY_HIRC(HIRC_24);
    initUart();
    initI2c();
    initSevenSegment();
    initTimer();

    Flash_Unlock();
    written=Flash_Read(FLASH_ADDR10);
    Flash_Lock();
    ENABLE_GLOBAL_INTERRUPT;
   
    if(written==1){written=1;}
    else {written=0;}
    uartTxString("\n\n\tHi Gil!, I will be back in about 5 seconds!\n\n\tRunning: CapKbd_8229BSF - 10/19/2019\n");
    Delay_1ms(5000);  // Delay 5 seconds
    // Serial.print(F("\tGetting Key Presses...\n"));
    uartTxString("\tGetting Key Presses...\n");
    initKeyHolder();
    while (1) {
    	
    setMode();
}
}

