#include "tcp_server.h"
#include <string.h> 
#if LWIP_NETCONN
#include "App_net.h"
#include "lwip/sys.h"
#include "lwip/api.h"

#include "lwip/tcp.h"
#include "lwip/ip.h"

volatile bool SeverClientFlag = false;

extern TaskHandle_t netled_vTask;
//buff
extern TCP_Data_T TCP_Data;

struct netconn *conn,*newconn;


void Tcp_ReseverDataBuff(void)
{
	if(TCP_Data.TcpSeverBuffFlag)
	{
		static uint16_t length = 0;
		
		TCP_Data.TcpSeverBuffFlag = false;
		
		//��ȡ���ݰ�
		length = RingBuff_GetNumber(&TCP_Data.TCP_R_RingBuff);
		if(length >= 6)
		{
			uint8_t *DataBuff;
			
			DataBuff = pvPortMalloc(length);
			
			if(DataBuff != NULL)
			{
				RingBuff_Read(&TCP_Data.TCP_R_RingBuff,DataBuff, length);
				//����
				RingBuff_Write(&TCP_Data.TCP_T_RingBuff,DataBuff,length);
				Tcp_ServerSendBuff();
				
				vPortFree(DataBuff);
				DataBuff = NULL;
			}
		}			
	}
}




void tcp_server_wait_client_task(void)
{
	err_t err;
	err_t TCP_err;

	struct pbuf *q;		//���յ����ݰ�
//	uint8_t remot_addr[4];	//ip
	static ip_addr_t ipaddr;//��ַ
	static uint16_t port; //�˿�
	
	conn = netconn_new(NETCONN_TCP);      /* ����TCP����  */
	netconn_bind(conn,NULL,8000);           /* �󶨱��ص�ַ�ͼ����Ķ˿ں� */  
	netconn_listen(conn);                 /* �������״̬ */
	conn->recv_timeout = 100;    		/*��ֹ�����̵߳ȴ�1000ms*/
	
	while(1)
	{
		xTaskNotify( netled_vTask, 500, eSetValueWithOverwrite );/* LED��˸Ϊ200mSһ��. */
		
		/*������ǰ���̵������ݽ��� ֱ���ж˿���������*/
		err = netconn_accept(conn,&newconn);    
		newconn->recv_timeout = 100;    //��ʱ���� ��ʱ����û�����������ͱ���ʱ����
		
		if(err == ERR_OK)
		{
			struct netbuf *recvbuf;
			
			netconn_getaddr(newconn,&ipaddr,&port,0);  //��ȡ����������IP��˿ں�
//			remot_addr[3] = (uint8_t)(ipaddr.addr >> 24);
//			remot_addr[2] = (uint8_t)(ipaddr.addr >> 16);
//			remot_addr[1] = (uint8_t)(ipaddr.addr >> 8);
//			remot_addr[0] = (uint8_t)(ipaddr.addr);
			
			xTaskNotify( netled_vTask, 1500, eSetValueWithOverwrite );/* LED��˸Ϊ1000mSһ��. */
			SeverClientFlag = true;
			while(1)
			{				
				//���յ�����
				if((TCP_err = netconn_recv(newconn,&recvbuf)) == ERR_OK)
				{
					//����pbuf����ֱ������
					for(q = recvbuf->p; q != NULL; q = q->next)
					{
						RingBuff_Write(&TCP_Data.TCP_R_RingBuff,q->payload,q->len);
					}  
					netbuf_delete(recvbuf);	//��������Ҫɾ�����ݰ�

					TCP_Data.TcpSeverBuffFlag = true;
				}
				else if((TCP_err != ERR_OK && TCP_err != ERR_TIMEOUT) || SeverClientFlag == false) //�ر�����
				{
					netconn_close(newconn);
					netconn_delete(newconn);
					
					SeverClientFlag = false;
					
					break;
				}
				else
				{
					Tcp_ReseverDataBuff();
					vTaskDelay(100);
				}
			}
		}
	}
	
}




void Tcp_ServerSendBuff(void)
{
	uint16_t length;
	err_t err;
	
	while((length = RingBuff_GetNumber(&TCP_Data.TCP_T_RingBuff)) != 0)
	{
		uint8_t *DataBuff;
		
		if(TCP_Tx_DATA_SIZE <= length)
		{
			length = TCP_Tx_DATA_SIZE;
		}	
		
		DataBuff = pvPortMalloc(length);

		if(DataBuff != NULL)
		{
			RingBuff_Read(&TCP_Data.TCP_T_RingBuff,DataBuff,length);
			err = netconn_write( newconn, DataBuff, length, NETCONN_COPY);
			if(err != ERR_OK)
			{				
				SeverClientFlag = false;
				break;
			}			
			
			vPortFree(DataBuff);
			DataBuff = NULL;
		}
	}
}





#endif


