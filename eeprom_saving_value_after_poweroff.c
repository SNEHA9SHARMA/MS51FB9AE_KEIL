#include "MS51_16K.H"
#include "common.h"

// Define the flash memory address for storing the value
#define FLASH_ADDR 0x0200  // Choose an address in APROM

// Define IAP commands
#define PAGE_ERASE_AP 0x22
#define BYTE_PROGRAM_AP 0x21
int i;
uint8_t value=0x01;


uint8_t val;
void UART_Init(void) {
    // Initialize UART settings
    SCON = 0x50;    // UART0 Mode 1, REN=1, TI=0
    P06_QUASI_MODE; // Set P0.6 as UART0_TXD
    P07_QUASI_MODE; // Set P0.7 as UART0_RXD
    set_SMOD;       // Set UART0 double rate enable
    set_PCON_SMOD;  // Set UART0 double rate enable
    set_T1M;        // Timer1 as baud rate generator
    clr_BRCK;       // Timer1 as clock source
    CKCON |= 0x10;  // Timer1 as clock source
    TMOD |= 0x20;   // Timer1 in Mode 2, 8-bit auto-reload
    TH1 = 0xFB;     // 9600 baud rate with 16MHz system clock
    TR1 = 1;        // Start Timer1
    TI = 1;         // Set TI to send the first character
}

void UART_Send(uint8_t dat) {
    SBUF = dat;
    while (!TI);
    TI = 0;
}

void Flash_Unlock(void) {
    TA = 0xAA;
    TA = 0x55;
    CHPCON |= 0x01; // Enable IAP mode

    TA = 0xAA;
    TA = 0x55;
    IAPUEN |= 0x04; // Enable APROM update
}

void Flash_Lock(void) {
    TA = 0xAA;
    TA = 0x55;
    IAPUEN &= ~0x04; // Disable APROM update

    TA = 0xAA;
    TA = 0x55;
    CHPCON &= ~0x01; // Disable IAP mode
}

uint8_t Flash_Read(uint16_t addr) {
    IAPAL = (uint8_t)addr;
    IAPAH = (uint8_t)(addr >> 8);
    IAPCN = 0x00; // Set IAP command to byte read

    TA = 0xAA;
    TA = 0x55;
    IAPTRG |= SET_BIT0; // Trigger IAP

    return IAPFD;
}

void Flash_Write(uint16_t addr, uint8_t dat) {
    // Erase the page containing the address
    IAPAL = (uint8_t)addr;
    IAPAH = (uint8_t)(addr >> 8);
    IAPCN = PAGE_ERASE_AP; // Set IAP command to page erase

    TA = 0xAA;
    TA = 0x55;
    IAPTRG |= SET_BIT0; // Trigger IAP

    // Write the new data
    IAPAL = (uint8_t)addr;
    IAPAH = (uint8_t)(addr >> 8);
    IAPFD = dat;
    IAPCN = BYTE_PROGRAM_AP; // Set IAP command to byte program

    TA = 0xAA;
    TA = 0x55;
    IAPTRG |= SET_BIT0; // Trigger IAP
}

void main(void) {
	  EA=0;
    UART_Init();

    // Unlock flash for read/write
    Flash_Unlock();

    // Read the last saved value from flash memory
    value = Flash_Read(FLASH_ADDR);

    // Increment the value
    if (value == 0xFF) {
        value = 0x01;
    } else {
        // Increment the value
        value += 1;
    }

    // Save the updated value back to flash memory
    
    Write_DATAFLASH_BYTE(FLASH_ADDR, value);
    // Lock flash after read/write
    Flash_Lock();

    // Print the incremented value via UART
    while (1) {
			 
        UART_Send(value);
        
        for ( i = 0; i < 10000; i++); // Simple delay
    }
}
