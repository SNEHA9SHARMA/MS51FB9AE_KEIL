#ifndef _UART_H
#define _UART_H
#define BUFFER_SIZE 20
/*********UART**********/
	
	void initUart(void);
	void uartTxChar(unsigned char );
	void uartTxStringLength(unsigned char *, int);
	void uartTxString(unsigned char *);
	void printData(uint16_t);
	void Send_Buffer(void);
	void uartTxInt(uint8_t);
    void itoa(int , char*);
#endif