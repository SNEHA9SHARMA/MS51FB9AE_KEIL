#include "MS51_16K.H"
#include "FLASH.h"

volatile unsigned char xdata page_buff[128];

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


void Write_DATAFLASH(unsigned int u16EPAddr, unsigned char u8EPData)
{
    unsigned char looptmp = 0;
    unsigned int u16_addrl_r;
    unsigned int RAMtmp;

    //Check page start address
    u16_addrl_r = (u16EPAddr / 128) * 128;

    //Save APROM data to XRAM0
    for (looptmp = 0; looptmp < 0x80; looptmp++)
    {
        RAMtmp = Read_APROM_BYTE((unsigned int code *)(u16_addrl_r + looptmp));
        page_buff[looptmp] = RAMtmp;
    }

    // Modify customer data in XRAM
    page_buff[u16EPAddr & 0x7f] = u8EPData;

    //Erase APROM DATAFLASH page
    IAPAL = u16_addrl_r & 0xff;
    IAPAH = (u16_addrl_r >> 8) & 0xff;
    IAPFD = 0xFF;
    set_CHPCON_IAPEN;
    set_IAPUEN_APUEN;
    IAPCN = 0x22;
    set_IAPTRG_IAPGO;

    //Save changed RAM data to APROM DATAFLASH
    set_CHPCON_IAPEN;
    set_IAPUEN_APUEN;
    IAPCN = 0x21;

    for (looptmp = 0; looptmp < 0x80; looptmp++)
    {
        IAPAL = (u16_addrl_r & 0xff) + looptmp;
        IAPAH = (u16_addrl_r >> 8) & 0xff;
        IAPFD = page_buff[looptmp];
        set_IAPTRG_IAPGO;
    }

    clr_IAPUEN_APUEN;
    clr_CHPCON_IAPEN;
}

