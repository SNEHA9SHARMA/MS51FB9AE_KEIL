#include "MS51_16K.H"
#include "I2C.h"
#include "FLASH.h"
#include "UART.h"
#include "sevenSegment.h"
#include "TIMER1.h"
int databit;

extern bit pend;          // Character Pending flag
unsigned char Key = 0;  // Store the key value
unsigned char button;
int iterat;

/*===============================SevenSegmentPrinting==================*/
extern int a,b,c,dseg;

/*========================SetMode==================================*/
int iterato;
int travelCount=0;
int keyHolder[10];
int keyHolder_it=0;
int written=0;

int v=0;
bit pend = 0; 
unsigned char oldKey = 0; // Store the previous key value
unsigned char New_Key = 0; // Store the new key value
unsigned int keyCount=0;
int writing_flag=0;
unsigned int iterate=0;
uint8_t newKey;
uint8_t newi;
uint16_t addr;
int reading_flag=0;
int write=0;
/*=================================================================*/
void initI2c() {
    P15_PUSHPULL_MODE;  // Set CLOCK_PIN as push-pull output
    P16_INPUT_MODE;     // Set DATA_PIN as input
    P17_PUSHPULL_MODE;  // Set DEBUG_PIN as push-pull output for debugging
    
    P15 = 1;  // Set CLOCK_PIN high initially
}

unsigned char scan_Kbd(void) {
    Key = 0;  // Reset Key
    
    for (button = 1; button <= 16; button++) {
        P15 = 0;  // Set CLOCK_PIN low
        databit = P16;  // Read DATA_PIN (assuming it gives the bit state)
        P15 = 1;  // Set CLOCK_PIN high
        
        if (databit == 0) {
            Key = button+'0';  // Save button number (1 to 16)
        }
    }
    
    pend = (Key > 0) ? 1 : 0;  // Set pend flag if Key is greater than 0
    
    return Key;  // Return the key value
}

void convertToString(unsigned char key){
   
    if(key=='1' || key=='2' || key=='3' || key=='4' || key=='5' || key=='6' || key=='7' || key=='8' || key=='9' ){

     uartTxString("key:  "); uartTxChar(key); uartTxString("  ");
    }
    else if(key==':'){uartTxString("key:  10  ");}
    else if(key==';'){uartTxString("key:  11  ");}
    else if(key=='<'){uartTxString("key:  12  ");}
    else if(key=='='){uartTxString("key:  13  ");}
    else if(key=='>'){uartTxString("key:  14  ");}
    else if(key=='?'){uartTxString("key:  15  ");}
    else if(key=='@'){uartTxString("key:  16  ");}
    else {uartTxString("key:  NA  ");}
  
   
    return;
}

void Delay_1ms(int a){
    for( iterat=0;iterat<a;iterat++){
        _nop_();
    }
}

void initKeyHolder(void){
    int i;
    for(i=0;i<10;i++){
       keyHolder[i] = 0;
    }
}

void writing_mode(){
    uartTxString("    Wait, We are Writing............\n");
    EA=0;
    for(keyCount=0;keyCount<10;keyCount++){
    addr=FLASH_ADDR + 2*keyCount;
	
    Flash_Unlock();
    Write_DATAFLASH(addr, keyHolder[keyCount]);
    Flash_Lock();
	
    writing_flag=1;
    if(writing_flag){
    uartTxString("Now we are writing: "); 
    uartTxChar(keyHolder[keyCount]);
    uartTxString(" \n");
    uartTxString("Writing Successful"); 
    uartTxString(" \n");
    writing_flag=0;}
    }
    travelCount=0;
    initKeyHolder();
    Flash_Unlock();
    Write_DATAFLASH(FLASH_ADDR10, 0x01);
    Flash_Lock();
    written=1;
    EA=1;
}


void reading_mode(){
uartTxString("         Wait We are reading.................\n ");
EA=0;
for(iterate=0;iterate<10;iterate++){

            reading_flag=1;
            addr=FLASH_ADDR + 2*iterate;
	        
            Flash_Unlock();
            newKey=Flash_Read(addr);
            Flash_Lock();
	        
            newi=keyHolder[iterate];
            if(reading_flag){
            uartTxString("Now We are Reading:   ");
            uartTxChar(newKey);
            uartTxChar(newi);
            uartTxString("\n");
            reading_flag = 0;}
            if( newKey==keyHolder[iterate] ) { v++; } 
}
            if(v==10)  {uartTxString("Ok!\n"); a=9; b=0; c=0; dseg=10;}   // to print "good" in sevenSegment
            else       {uartTxString("Not Ok!\n"); a=11; b=12; c=1; dseg=13;}    // to print "FAIL" in sevenSegment      
            v=0;
            travelCount=0;
            initKeyHolder();
            EA=1;
}


void setMode(void){

        Delay_1ms(10);  // Delay to allow the keyboard to recover (if needed)
        New_Key = scan_Kbd();  // Get key press
        
        if (oldKey != New_Key) {
        oldKey = New_Key;  // Update oldKey
        
        if (New_Key != 0) {
	    a=0;b=0;c=0;dseg=0;
            // Serial.print(F(" "));
            // Serial.println(New_Key, HEX);
            uartTxChar(' ');
            uartTxChar(New_Key);
            uartTxString("\n");
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////           
            if(New_Key=='?' && travelCount>=10 && written==0){
                 writing_mode();}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            else if(New_Key=='@' && travelCount>=10 && written==1){
                reading_mode();
            }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            else{
                 if(keyHolder_it==10){
                 for( iterato=0;iterato<9;iterato++){
                    keyHolder[iterato]=keyHolder[iterato+1];
                }
                    keyHolder[9]=New_Key;
                }
                else{
                    keyHolder[ keyHolder_it++ ]=New_Key;
                }
                travelCount++;
            }
           
            
            }
    pend = 0;  // Reset pend flag
  }
      
}
