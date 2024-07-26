
#include "MS51_16K.H"
#include "iot_eeprom.h"

void write_EE(unsigned int edata) 
	{
    unsigned char lowByte = 0;
    unsigned char highByte = 0;

		lowByte = (unsigned char)edata;
		highByte = (unsigned char)(edata >> 8);

    Write_DATAFLASH_BYTE(EEPROM_LOWER_BYTE_ADDRESS, lowByte);
    Write_DATAFLASH_BYTE(EEPROM_HIGHER_BYTE_ADDRESS, highByte);
}

unsigned int read_EE(void) 
	{
    unsigned char lowByte = 0;    
    unsigned char highByte = 0;
    unsigned int edata = 0;

    lowByte = Read_APROM_BYTE((unsigned int code *)EEPROM_LOWER_BYTE_ADDRESS);
    highByte = Read_APROM_BYTE((unsigned int code *)EEPROM_HIGHER_BYTE_ADDRESS);

		edata = (highByte << 8) | lowByte;
		
    return edata;
}
