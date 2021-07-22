#ifndef APP_NET_H_
#define APP_NET_H_

#include "header.h"

#define TCP_Rx_DATA_SIZE 200
#define TCP_Tx_DATA_SIZE 80

typedef struct
{
	bool TcpSeverBuffFlag;
	uint8_t TCP_RxData[TCP_Rx_DATA_SIZE];
	uint8_t TCP_TxData[TCP_Tx_DATA_SIZE];
	RingBuff TCP_R_RingBuff,TCP_T_RingBuff;
}TCP_Data_T;


void NetInit(void);


void vNetTask(void *pvParameters);
void vNet1Task(void *pvParameters);
#endif
