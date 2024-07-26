


#define LED P15

#define TDS_SAFE 200	
#define TDS_HAZARDOUS 400	

void initPWM(void);
void set_PWM_period(unsigned int value);
void set_PWM1(unsigned int value);
void LED_handle(unsigned int value);


