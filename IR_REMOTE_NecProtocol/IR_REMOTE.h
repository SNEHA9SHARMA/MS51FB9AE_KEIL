#ifndef _IR_REMOTE_H_
#define _IR_REMOTE_H_

/********************************************
        NEC IR Remote Codes- ACTUAL
*********************************************/  
#define IR_POWER      0x1AE5A857
#define IR_1          0x1AE5F00F
#define IR_2          0x1AE528D7
#define IR_3          0x1AE5708F
#define IR_4          0x1AE504FB
#define IR_5          0x1AE508F7
#define IR_REVERSE    0x1AE540BF
#define IR_ECO        0x1AE520DF
#define IR_BREEZE     0x1AE5E01F
#define IR_TURBO      0x1AE5906F
#define IR_1H         0x1AE541BE
#define IR_2H         0x1AE5C13E
#define IR_4H         0x1AE5B14E
#define IR_8H         0x1AE549B6
/*********************************************/

/***************************************************************************************************
                             Function prototypes
***************************************************************************************************/
void IR_RemoteInit(void);
uint32_t IR_RemoteGetKey(void);
/**************************************************************************************************/
#endif