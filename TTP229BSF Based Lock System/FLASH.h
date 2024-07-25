#ifndef FLASH_H
#define FLASH_H
#define FLASH_ADDR 0x0200  // Choose an address in APROM
#define FLASH_ADDR1 0x0202
#define FLASH_ADDR2 0x0204
#define FLASH_ADDR3 0x0206
#define FLASH_ADDR4 0x0208
#define FLASH_ADDR5 0x0210
#define FLASH_ADDR6 0x0212
#define FLASH_ADDR7 0x0214
#define FLASH_ADDR8 0x0216
#define FLASH_ADDR9 0x0218
#define FLASH_ADDR10 0x0220

// Define IAP commands
#define PAGE_ERASE_AP 0x22
#define BYTE_PROGRAM_AP 0x21

/*********UART**********/
	
	void Flash_Unlock(void);
	void Flash_Lock(void);
	uint8_t Flash_Read(uint16_t);
	void Write_DATAFLASH(uint16_t , uint8_t );

#endif