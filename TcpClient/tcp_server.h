#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "RingBuff.h"
#include "lwip/opt.h"

void tcp_server_wait_client_task(void);

void Tcp_ServerSendBuff(void);

extern volatile bool SeverClientFlag;


#endif



