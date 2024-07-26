

#define A  P00
#define B  P01
#define C  P02
#define D  P03
#define E  P04
#define F  P05
#define G  P06
//#define DP P14			//note P14 is selected for Decimal 

#define D1 P10
#define D2 P11
#define D3 P12

//#define D4 P16		

void initSegmentPins(void);

void setSegment(unsigned int value);
	
void displayDigit(int value, int digit);
	
void displayValue(float value);	

//void setLED(unsigned int value);
	