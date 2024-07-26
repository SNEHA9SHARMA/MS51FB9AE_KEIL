

#define EEPROM_LOWER_BYTE_ADDRESS            0x3800
#define EEPROM_HIGHER_BYTE_ADDRESS           0x3801

void write_EE(unsigned int edata);
unsigned int read_EE(void);