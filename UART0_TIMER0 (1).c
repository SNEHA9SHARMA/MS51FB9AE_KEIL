#include "common.h"
#include "MS51_16K.H"
#define BUFFER_SIZE 5
uint8_t received_data;
uint8_t rx_buffer[BUFFER_SIZE];  // Buffer to store received data
uint8_t buffer_index = 0;        // Index to keep track of the buffer position
uint8_t i ;
volatile bit buffer_full = 0;             
void UART0_Init(void) {
    SCON = 0x50;                                                         // UART0 Mode1, REN=1, TI=0
    P06_QUASI_MODE;                                                      // Set P0.6 as UART0_TXD
    P07_QUASI_MODE;                                                      // Set P0.7 as UART0_RXD
    set_SMOD; 
    set_PCON_SMOD;	// Set UART0 Double Rate Enable
    set_T1M;                                                             // Set Timer1 Mode for Baud Rate Generator
    clr_BRCK;
	  CKCON |= 0x10;                                                       //Timer1 as clock source
	  T3CON &= 0xDF;                                                       //Timer1 as UART0 clock source
    PCON|= 0x80;                                                         //UART0 double rate enable
    TMOD |= 0x20;                                                        // Timer1 in Mode 2, 8-bit auto-reload
	  TH1 =0xFB;                                                             // BAUD RATE:200000, CLOCK FREQUENCY:16MHz
    TR1 = 1;         
    TI = 1;            
	  set_ES;
	  set_EA;
	  REN = 1;
    
    // Set UART0 Multiprocessor Communication Mode and Address Detection Mode
    SM2 = 1;        // Enable multiprocessor communication mode
    SM1 = 1;        // Address detection mode
    FE = 0;         // Clear the framing error flag
	     //T3PS2 = 0,T3PS1 = 0,T3PS0 = 0(Prescale = 1)
	
}


void UART_Send(uint8_t dat) {
	  SBUF = dat;	       
    while (!TI);   	
    TI = 0; 
    
}

void Send_Buffer(void) {
	for (i = 0; i < BUFFER_SIZE; i++) {
        UART_Send(rx_buffer[i]);  
    }
}

void UART_ISR(void) interrupt 4 {

    if (RI) {
			  clr_SCON_RI;
        received_data = SBUF; 
        if (received_data == 0x05) {
            P14 = ~P14;  // Toggle LED connected to P1.4
        }			
			
        if (buffer_index < BUFFER_SIZE) {
            rx_buffer[buffer_index] = received_data;
					  ++buffer_index;
					  
				
			 
        }
        if (buffer_index == BUFFER_SIZE) {
            buffer_full = 1; 
        }	
        		
       					
    }
			
	
}
void main(void) {
    UART0_Init();
    P14_PUSHPULL_MODE;   
    P14 = 1;            
    while (1) {
        if (buffer_full) {
            Send_Buffer();
            buffer_index = 0;  
            buffer_full = 0;  
        }
    }
}
