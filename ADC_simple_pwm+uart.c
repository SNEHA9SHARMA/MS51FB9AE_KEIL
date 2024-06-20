#include "MS51_16K.H"
#include "common.h"
float d;
int d1;
int d2;
int d3;
float p;
int p1;
int i;
unsigned char xdata ADCdataAINH, ADCdataAINL;
unsigned int adc_value;
unsigned char tempH, tempL;
float frac;
float adc;
int pw(float freq, float duty){
	p=2000000/freq-1;
	p1=(int)(p);
	PWMPH=(p1 >> 8) & 0xFF;
	PWMPL=p1 & 0xFF;
	d=duty*p/100;
	d1=(int)(d);
	return d1;
	
}
void UART0_Init(void)
{
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

void UART0_SendChar(char c)
{
    SBUF = c;
    while (TI == 0);
    TI = 0;
}

void UART0_SendString(char* str)
{
    while (*str)
    {
        UART0_SendChar(*str++);
    }
}

void main(void) 
{   P14_QUASI_MODE;
	  P12_QUASI_MODE;
	  P10_QUASI_MODE;
	  PWM_IMDEPENDENT_MODE;
	  PWM_CLOCK_DIV_8;
	  PWM1_P14_OUTPUT_ENABLE;
	  PWM0_P12_OUTPUT_ENABLE;
	  PWM2_P10_OUTPUT_ENABLE;
    UART0_Init();  // Initialize UART0 for printf
  
    ENABLE_ADC_AIN4;  // Enable ADC on analog input channel 4 (AIN4)

    /* ADC Low speed initial configuration */
    ADCCON1 |= 0x30;  // Set clock divider to divide ADC clock
    ADCCON2 |= 0x0E;  // Set ADC acquisition time
    AUXR1 |= SET_BIT4;  // Set ADC clock to low speed
    
    P12_PUSHPULL_MODE;  // Set P1.2 pin to push-pull mode

    while (1)
    {
        clr_ADCCON0_ADCF;  // Clear ADC completion flag
        set_ADCCON0_ADCS;  // Start ADC conversion
        while (ADCF == 0);  // Wait for ADC conversion to complete

        // Read ADC result
        tempH = ADCRH;  // Read the high byte of the ADC result
        tempL = ADCRL;  // Read the low byte of the ADC result
        adc_value = (tempH << 4) | (tempL & 0x0F);  // Combine high and low bytes to form the full 10-bit result
			  adc=(float)(adc_value);
        frac=adc/4095*100;
			  d1=pw(162.54,frac);            //function of pwm
	      PWM1H=(d1 >> 8) & 0xFF;;
	      PWM1L=d1 & 0xFF;
	      set_PWMCON0_LOAD;
        set_PWMCON0_PWMRUN;
        // Print ADC result for debugging
        UART0_SendString("ADC Value: ");
        UART0_SendChar(adc_value / 1000 + '0');
        UART0_SendChar((adc_value % 1000) / 100 + '0');
        UART0_SendChar((adc_value % 100) / 10 + '0');
        UART0_SendChar(adc_value % 10 + '0');
        UART0_SendString("\n");

        // Toggle P12 based on some condition (optional)
        P12 ^= 1;

        // Small delay to observe the toggling (adjust as necessary)
        // This delay may be removed if the toggling frequency is a concern
     
    }
}
