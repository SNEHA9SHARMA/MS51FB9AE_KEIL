
#include "MS51_16K.H"
#include "button.h"
#include "tds_uart1.h"
#include "tds_adc.h"
#include "iot_eeprom.h"

volatile bit buttonPressed = 0;
volatile unsigned int buttonPressTime = 0;

unsigned int value = 0;

 bit shortPressFlag = 0;
 bit longPressFlag = 0;

void initButton(void)
{
    P17_PUSHPULL_MODE;
    BUTTON = 1;
}

void init_INT1(void)
{
    ENABLE_GLOBAL_INTERRUPT;       // Enable global interrupt
    ENABLE_INT1_INTERRUPT;        // Enable interrupt 1
    INT1_LOW_LEVEL_TRIG;       
}

void Timer0_ISR(void) interrupt 1
{
    TH0 = 0x3C;                 // For 1ms delay with 24MHz crystal frequency
    TL0 = 0xB0;
    buttonPressTime++;
}

void INT1_ISR(void) interrupt 2
	{
    if (BUTTON == 0)        // Button pressed
    {
        buttonPressed = 1;
        TH0 = 0x3C;             // Load Timer0 with initial value for 1ms delay
        TL0 = 0xB0;
        set_TCON_TR0;           // Start Timer0
				//buttonPressTime++;
    }
    else                        // Button released
    {
			if (buttonPressed)
			{
					clr_TCON_TR0;       // Stop Timer0
					if (buttonPressTime > 100) // Short press threshold (less than 3 seconds)
					{
						//sendString("\nLong Press: ");
						//sendNumber(buttonPressTime);
						shortPressFlag = 1;
						longPressFlag = 0;
					}
					else                        // Long press
					{
						//sendString("\nShort Press: ");
						//sendNumber(buttonPressTime);
						shortPressFlag = 0;
						longPressFlag = 1;
					}
					buttonPressed = 0;
					buttonPressTime = 0;
			}
    }
	}

void initTimer0(void)
{
    TMOD &= 0xF0;       
    TMOD |= 0x01;      
    TH0 = 0x3C;         
    TL0 = 0xB0;
    ENABLE_TIMER0_INTERRUPT;    // Enable Timer0 interrupt
    set_TCON_TR0;               // Start Timer0
}

void Buttonh_handle()
{
	if(shortPressFlag)
		{
			shortPressFlag = 0;
			value = read_EE();
			sendString("\n TDS value : ");
			sendString("\n");
			sendNumber(value);
		}
	else if(longPressFlag)
		{
			longPressFlag = 0;
			value = readTDS_ADC();
			value = ((float)value * 5) / 4095;
			write_EE(value);
			//sendNumber(123);
			sendString("\n TDS value Stored in Memory \n");
		}
}



/*********************************************************
	

volatile int value_update_counter = 0;

extern int one_sec_counter;
extern int is_btn_pressed;
extern int value_tds;
extern int value_temp;

long unsigned int value_pressed = 0;
char short_pressed = 0;
char long_pressed = 0;
int value = 0;

void Timer0_ISR(void) interrupt 1{
    push(SFRS);
    
    if(is_btn_pressed)
    {
        value_update_counter = 0;
        one_sec_counter = 0;
        value_tds = read_EE();
        is_btn_pressed = 0;
    }
    
    value_update_counter++;
    if(value_update_counter == 1000)
    {
        value_tds = adc_read(0);
        uartTxString("ADC VALUE_tds =  ");
        printData(value_tds);
        uartTxChar(0x0D);
        pwm_generator(value_tds);
        
        value_temp = adc_read(1);
        uartTxString("ADC VALUE_temp =  ");
        printData(value_temp);
        uartTxChar(0x0D);
        
        value_update_counter = 0;
        
    }
    
    TH0 = TH0_INIT;
    TL0 = TL0_INIT;
    
    pop(SFRS);
}


void EXT_INT1(void) interrupt 2{
    push(SFRS);
    IE1 = 0;
    value_pressed++;
        if(value_pressed > 5000 && value_pressed < 35000) {
            short_pressed = 1;
            long_pressed = 0;
        }
                
        else if(value_pressed > 50000){                
            short_pressed = 0;
            long_pressed = 1;
        }
    pop(SFRS);
}


*/
