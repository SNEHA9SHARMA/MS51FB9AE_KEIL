#ifndef _ADC_H

/*********UART**********/
	#define samplingrate 30000 

	#define TDS_ALT_PIN        P04
	#define TDS_EN_PIN         P11
	#define TDS_ADC_PIN        P03

	void initAdc(void);
	float adc(void);
	float ReadTemperature(void);
	float log(float); 
    int ConvertADCToTemperature(int);
    float tds(float);
    void print(void);
    float pow(float,float);

#endif