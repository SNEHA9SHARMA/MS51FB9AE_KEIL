

#define REF_TEMPERATURE 298   					// temperature for nominal resistance (almost always 25° C)
    									
#define BETA 3900											// The beta coefficient or the B value of the thermistor (usually 3000-4000) check the datasheet for the accurate value.
#define REF_R 9800   											//Value of  resistor used for the voltage divider
#define NOMINAL_R 10000
#define TDS_EN	P07						//Set P07 as TDS_EN
#define TDS_ALT	P01						//Set P01 as TDS_ALT

#define TDS_CHANNEL 4					//ADC channel for TDS sensor
#define TEMP_CHANNEL 3					//ADC channel for temperature sensor

#define SAMPLING_START_DELAY 0

#define SAMPLES 16


void initADC();
unsigned int readTDS_ADC(void);
unsigned int readTemp_ADC(void);
float adcToTDS(unsigned int adcValue,float temp);
float adcToTEMP(unsigned int adcValue);
void ADC_handle(void);