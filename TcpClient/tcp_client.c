#include "tcp_client.h"

#if LWIP_NETCONN
#include "App_net.h"
#include "lwip/sys.h"
#include "lwip/api.h"

#include "lwip/tcp.h"
#include "lwip/ip.h"

extern TaskHandle_t net1led_vTask;

#define TCP_SERVER_IP   	"192.168.101.30"
#define TCP_SERVER_PORT 	8000

/* 服务器通信使用权信号量  二值信号量*/
SemaphoreHandle_t xServerCommunicationLockSemaphore = NULL;

static struct netconn *tcp_client_server_conn;

void tcp_client_conn_server_task( void )
{
  struct netbuf *buf;
  void *data;
  u16_t len;
  err_t err;
	
	ip_addr_t server_ip;
	u16_t server_port = TCP_SERVER_PORT;				   // 服务器端口号初始化
	ip4addr_aton( TCP_SERVER_IP, &server_ip ); 		 // 服务器IP地址初始化

	xServerCommunicationLockSemaphore = xSemaphoreCreateBinary();  //

	if( NULL == xServerCommunicationLockSemaphore )
	{
			//printf("err:xServerCommunicationLockSemaphore == NULL,while(1).");
			while(1);
	}
	
	for( ;; )
	{
				
		///printf("tcp server connecting %s:%d......", ipaddr_ntoa(&server_ip), server_port );
				
		xTaskNotify( net1led_vTask, 200, eSetValueWithOverwrite );/* 服务器断开连接状态，LED闪烁为200mS一次. */
		
		/* Create a new connection identifier. 连接实列 */
		tcp_client_server_conn = netconn_new( NETCONN_TCP );
				
		if( tcp_client_server_conn != NULL )
		{		
			tcp_client_server_conn->recv_timeout = 100;    		/*禁止阻塞线程等待1000ms*/
			//打开TCP 的保活功能 （客户端不默认打开）
			tcp_client_server_conn->pcb.tcp->so_options |= SOF_KEEPALIVE;

			err = netconn_connect( tcp_client_server_conn, &server_ip, server_port );
					
			if(err == ERR_OK)
			{
				//printf("TCP Server %s:%d connected sucess.", ipaddr_ntoa(&server_ip), server_port );
						
				xSemaphoreGive( xServerCommunicationLockSemaphore ); /* 释放服务器通信使用权 */

				//用于传递修改值
				xTaskNotify( net1led_vTask, 1000, eSetValueWithOverwrite );/* 服务器连接状态，LED闪烁为1000mS一次. */
				
				for( ;; )
				{
					/* receive data until the other host closes the connection */
					if((err = netconn_recv(tcp_client_server_conn, &buf)) == ERR_OK) 
					{
								 //获取一个指向netbuf 结构中的数据的指针
								 if((err = netbuf_data(buf, &data, &len)) == ERR_OK)
								 {
									 //在此获取数据以及数据长度
									  received_server_data_process( data, len );
									  netbuf_delete(buf);
								 }
								 else
								 {
									 //printf("err:netbuf_data(buf, &data, &len):%d.",err);
								 }
								
					}
					else if(err != ERR_OK && err != ERR_TIMEOUT)
					{
						//printf("err:netconn_recv(conn, &buf):%d.",err);
						netbuf_delete(buf);	
						break; //连接发生错误，退出死等数据的循环，重新建立链接
					}
				 }
			 }
			
//			 printf("err:TCP Server %s:%d connect fail,err:%d.", ipaddr_ntoa(&server_ip), server_port, err );
			 netconn_close( tcp_client_server_conn );
			 netconn_delete( tcp_client_server_conn );		
			 vTaskDelay(1000/portTICK_PERIOD_MS);
		}
		else
		{
			//printf("err:Can not create tcp_client_server_conn.");
			vTaskDelay(1000/portTICK_PERIOD_MS);
		}
	}
}


//接收数据
int received_server_data_process( uint8_t *data, uint16_t len )
{
	 return send_server_data( data, len );
}


//发送数据
int send_server_data( uint8_t *data, uint16_t len )
{
												 
	if( tcp_client_server_conn )
	{
		return netconn_write( tcp_client_server_conn, data, len, NETCONN_COPY);
	}
	else
		return ERR_CONN; 

}

#endif /* LWIP_NETCONN */














