#include "App_net.h"

#include "lwip/netif.h"
#include "lwip/tcpip.h"
#include "netif_port.h"

struct netif gnetif; /* network interface structure */

TCP_Data_T TCP_Data;

static void netif_config(void)
{
  ip_addr_t ipaddr;
  ip_addr_t netmask;
  ip_addr_t gw;

  IP_ADDR4(&ipaddr,192,168,101,100);
  IP_ADDR4(&netmask,255,255,255,0);
  IP_ADDR4(&gw,192,168,101,1);

  /* add the network interface ethernetif_init网卡的初始化 并向网卡列表添加网口*/ 
  netif_add(&gnetif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);
  
  /*  Registers the default network interface. */
  netif_set_default(&gnetif);
	
	/* Set the link callback function, this function is called on change of link status*/
  netif_set_link_callback(&gnetif, eth_link_callback); //连接状态改变时回调eth_link_callback
}


void NetInit(void)
{
	/* Create tcp_ip stack thread */
	tcpip_init(NULL, NULL);
	
	/* Initilaize the netif */
	netif_config();
}


void vNetTask(void *pvParameters)
{			
	RingBuff_Init(&TCP_Data.TCP_R_RingBuff,TCP_Data.TCP_RxData,TCP_Rx_DATA_SIZE);
	RingBuff_Init(&TCP_Data.TCP_T_RingBuff,TCP_Data.TCP_TxData,TCP_Tx_DATA_SIZE);
	
	for(;;)
	{
		tcp_client_conn_server_task();		
		vTaskDelay(2000);
	}
}


void vNet1Task(void *pvParameters)
{			
	for(;;)
	{	
		tcp_server_wait_client_task();
		vTaskDelay(2000);
	}
}



