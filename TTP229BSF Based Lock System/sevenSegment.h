#define  DIGIT1  P17
#define  DIGIT2  P04
#define  DIGIT3  P03
#define  DIGIT4  P02

// Define the segment pins (assuming P0.0 to P0.6 for segments a to g)
#define SEG_A  P14
#define SEG_B  P13
#define SEG_C  P12
#define SEG_D  P11
#define SEG_E  P10
#define SEG_F  P00
#define SEG_G  P01


void initSevenSegment(void);
void displayDigit(unsigned char , unsigned int );
//void displayNumber(void);
void ms_delay(unsigned int);