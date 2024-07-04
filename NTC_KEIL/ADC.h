#ifndef _ADC_H

/*********UART**********/
	#define samplingrate 30000 

	void initAdc(void);
	float adc(void);
	float ReadTemperature(void); 
    int ConvertADCToTemperature(int);
    float log(float);

#endif