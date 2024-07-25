

#define CLOCK_PIN P15  // Define clock pin (example pin P1.5)
#define DATA_PIN  P16  // Define data pin (example pin P1.6)

void initI2c(void);
unsigned char scan_Kbd(void);
void convertToString(unsigned char );
void Delay_1ms(int);
void initKeyHolder(void);
void setMode(void);
void reading_mode(void);
void writing_mode(void);