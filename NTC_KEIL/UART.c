#include "MS51_16K.H"
#include "UART.h"

volatile unsigned char RecivedData = 0;
uint8_t received_data;
uint8_t rx_buffer[BUFFER_SIZE];  // Buffer to store received data
uint8_t buffer_index = 0;        // Index to keep track of the buffer position
uint8_t i=0 ;
int start;
int end;
int f;
int isNegative;
unsigned char buffer_full = 0;
void SerialPort0_ISR(void) interrupt 4 {     // Vector @  0x23  
    _push_(SFRS);

    if(RI) {
        RecivedData = SBUF;
        clr_SCON_RI;
               if (buffer_index < BUFFER_SIZE) {
            rx_buffer[buffer_index] = RecivedData;
                      ++buffer_index;
                      
                
             
        }
        if (buffer_index == BUFFER_SIZE) {
            buffer_full = 1; 
        }   
    }
    
    if(TI == 1) {
        clr_SCON_TI;
    }
    _pop_(SFRS);
}
void Send_Buffer(void) {
  for (i = 0; i < BUFFER_SIZE; i++) {
        uartTxChar(rx_buffer[i]);  
    }
}
void itoa(int num, char* str)
{
    f = 0;
    isNegative = 0;
    
    // Handle 0 explicitly, otherwise empty string is printed for 0
    if (num == 0)
    {
        str[f++] = '0';
        str[f] = '\0';
        return;
    }
    
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise, numbers are considered unsigned.
    if (num < 0)
    {
        isNegative = 1;
        num = -num;
    }
    
    // Process individual digits
    while (num != 0)
    {
        int rem = num % 10;
        str[f++] = rem + '0';
        num = num / 10;
    }
    
    // If number is negative, append '-'
    if (isNegative)
        str[f++] = '-';
    
    str[f] = '\0'; // Append string terminator
    
    // Reverse the string
    start = 0;
    end = f - 1;
    while (start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

void initUart(void) {
    
    P06_QUASI_MODE;
    P07_INPUT_MODE;
    SCON = 0x50;    
    
    set_PCON_SMOD;      //UART0 Double Rate Enable
    T3CON &= 0xF8;      //T3PS2 = 0,T3PS1 = 0,T3PS0 = 0(Prescale = 1)
    set_T3CON_BRCK;     //UART0 baud rate clock source = Timer3
    
    RH3    = HIBYTE(65536 - (24000000/16/115200));  
    RL3    = LOBYTE(65536 - (24000000/16/115200));     
    
    set_T3CON_TR3;
    ENABLE_UART0_INTERRUPT;
}

void uartTxChar(unsigned char a) {
    TI = 0;  
    SBUF = a;
    while(TI == 0);
}

void uartTxStringLength(unsigned char *a , int l) {
    unsigned int i = 0;
    while(i<l) {
        uartTxChar(a[i]);
        i++;
    }
}

void uartTxInt(uint8_t a){
    TI = 0;  
    SBUF = a;
    while(TI == 0);
}

void uartTxString(unsigned char *a) {
    unsigned int i= 0;
    while(a[i]!= '\0') {
        uartTxChar(a[i]);
        i++;
    }
}

void printData(uint16_t prtData) {//print 4 bytes of Data
    uint8_t temp1, temp2;
    
    DISABLE_UART0_INTERRUPT;
    temp1 = (prtData &0x000000FF);
    temp2 = (prtData &0x0000FF00)>>8;
    
    temp1 = (unsigned char) temp1;
    temp2 = (unsigned char) temp2;
       
    uartTxChar((unsigned char)temp2);
    uartTxChar((unsigned char)temp1);
    uartTxChar('\n');    
    ENABLE_UART0_INTERRUPT;
}