#include "MS51_16K.H"
#include "UART.h"
#include "ADC.h"
#include "TIMER.h"
float key=0;
int temp;
float adc2;
int adc3;
float samples = 0;
int flag=0;
int cnt=0;
extern int msCount;
int abd;
void main()
{   FsysSelect(FSYS_HIRC);
    MODIFY_HIRC(HIRC_24);
    P14_PUSHPULL_MODE;
    P14=1;
    initUart();
    initAdc();
    ENABLE_GLOBAL_INTERRUPT;
    initTimer();
	  uartTxChar(0x88);
   
    while(1)
{ 
//    if(msCount>900){
//			key = adc();
//			uartTxString("ADC Value: ");
//			uartTxChar((uint16_t ) key / 1000 + '0');
//			uartTxChar(( (uint16_t )key % 1000) / 100 + '0');
//			uartTxChar(((uint16_t )key % 100) / 10 + '0');
//			uartTxChar((uint16_t )key % 10 + '0');
//			uartTxString("\n");
//		  msCount=0;}
		  

//		adc3=(int) key;
//		uartTxChar(adc3);
//	  printData(adc3);
    
   
     
		    key = adc();
        samples+= key;
        cnt++;

      if(cnt==30000){
				abd =(int) (samples/30000);
				temp=ConvertADCToTemperature(abd);
				
			  uartTxString("ADC value: ");
      	uartTxChar((uint16_t ) abd / 1000 + '0');
			  uartTxChar(( (uint16_t )abd % 1000) / 100 + '0');
		    uartTxChar(((uint16_t )abd % 100) / 10 + '0');
		    uartTxChar((uint16_t )abd % 10 + '0');
				uartTxString(" ---Temp: ");
				uartTxChar(((uint8_t )temp % 100) / 10 + '0');
		    uartTxChar((uint8_t )temp % 10 + '0');
			  uartTxString("\n");
				
				cnt=0;
		    samples=0;
				 
		 }
  
      
   

}
}     
 