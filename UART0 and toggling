#include "common.h"
#include "MS51_16K.H"
#define BUFFER_SIZE 5;
uint8_t received_data;
uint8_t rx_buffer[BUFFER_SIZE];
uint8_t buffer_index =0;
uint8_t i;
volatile bit buffer_full=0;
void UART0_Init(void){
	   SCON=0x50;
	   P06_QUASI_MODE;
	   P07_QUASI_MODE;
	   set_SMOD;
	   set_PCON_SMOD;
	   set_T1M;
	   clr_BRCK;
	   CKCON |=0x10;
	   T3CON &=0xDF;
	   PCON| =0x80;
	   TMOD |=0x20;
	TH1=0xFB;          //BAUD RATE:200000 , clock freq=16MHz
	   TR1= 1;
	   TI=1;
	   set_ES;
	   set_EA;
	   REN=1;
	   SM2=1;
	   SM1=1;
	   FE=0;
}
void UART_Send(int dat){
	SBUF=dat;
	while(!TI);
	TI=0;
}
void Send_Buffer(void){
	for(i=0; i<BUFFER_SIZE;i++){
		UART_Send(rx_buffer[i]);
	}
}

void UART_ISR(void) interrupt 4{
	if(RI){
		clr_SCON_RI;
		received_data =SBUF;
		if(received_data=0x05){
			P14=~P14;
		}
	}
	if(buffer_index<BUFFER_SIZE){
		rx_buffer[buffer_index]=received_data;
		++buffer_index;
	}
	if(buffer_index==BUFFER_SIZE){
		buffer_full=1;
	}
}

void main(void){
	UART0_Init();
	P14_PUSHPULL_MODE;
	P14=1;
	while(1){
		if(buffer_full){
			Send_Buffer();
			buffer_index=0;
			buffer_full=0;
		}
	}
}