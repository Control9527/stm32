#ifndef  __TCP_CLIENT_H__
#define  __TCP_CLIENT_H__

#include "RingBuff.h"
#include "lwip/opt.h"
	
void tcp_client_conn_server_task( void );

int send_server_data( uint8_t *data, uint16_t len );
int received_server_data_process( uint8_t *data, uint16_t len );

#endif
