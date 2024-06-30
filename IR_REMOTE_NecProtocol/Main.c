#include "MS51_16K.H"
#include "IR_REMOTE.h"
#include "UART.h"
#include "PWM.h"
uint32_t key;
extern uint8_t timerValue;
int m;
extern int flag;
extern char buffer[256];
float a=0;
int v=1;
int pow=0;
void main()
{   FsysSelect(FSYS_HIRC);
    MODIFY_HIRC(HIRC_24);
    P14_PUSHPULL_MODE;
    P14=1;
    initUart();
    initPwm();
    IR_RemoteInit();  
    ENABLE_GLOBAL_INTERRUPT;
    while(1)
    {   
        if(flag==1){
        key=IR_RemoteGetKey();
        printData(key);
        //Send_Buffer();
        
/***********************************************FUNCTIONS*************************************************/
			 /* if(key==IR_REVERSE) { PWM1_P14_OUTPUT_DISABLE; P14=0; v=0; a=0; pow=1;}
              if(key==IR_POWER){PWM1_P14_OUTPUT_DISABLE; P14=1; v=1; a=0; pow=0;}
              if(pow==1){
              if(key==IR_1){pw(99.00); a=99.00; v=1;}
              if(key==IR_2){pw(98.00); a=98.00; v=1;}
              if(key==IR_3){pw(97.00); a=97.00; v=1;}
              if(key==IR_4){pw(96.00); a=96.00; v=1;}
              if(key==IR_5){pw(95.00); a=95.00; v=1;}
              if(key==IR_ECO){pw(94.00); a=94.00; v=1;}
              if(key==IR_BREEZE){pw(93.00); a=93.00; v=1;}
              if(key==IR_TURBO){pw(92.00); a=92.00; v=1;}
              if(key==IR_1H || key==IR_2H || key==IR_4H || key==IR_8H){
                if(v==1){v=0; PWM1_P14_OUTPUT_DISABLE; P14=1;}
                else if(v==0){
                    if (a!=0){if(a<10){a=a+10; pw(a);} else{a=a-10; pw(a);}}
                    else{P14=0;}
										v=1;
                }
      } }     
    */
/*******************************************************************************************************/


    }
}     
 }  