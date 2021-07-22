#include "Bsp_mpu.h"


//设置某个区域的MPU保护
//baseaddr:MPU保护区域的基址(首地址)
//size:MPU保护区域的大小(必须是32的倍数,单位为字节),可设置的值参考:CORTEX_MPU_Region_Size
//rnum:MPU保护区编号,范围:0~7,最大支持8个保护区域,可设置的值参考：CORTEX_MPU_Region_Number
//ap:访问权限,访问关系如下:可设置的值参考：CORTEX_MPU_Region_Permission_Attributes
//MPU_REGION_NO_ACCESS,无访问（特权&用户都不可访问）
//MPU_REGION_PRIV_RW,仅支持特权读写访问
//MPU_REGION_PRIV_RW_URO,禁止用户写访问（特权可读写访问）
//MPU_REGION_FULL_ACCESS,全访问（特权&用户都可访问）
//MPU_REGION_PRIV_RO,仅支持特权读访问
//MPU_REGION_PRIV_RO_URO,只读（特权&用户都不可以写）
//详见:STM32F7编程手册.pdf,4.6节,Table 89.
//sen:是否允许共用;MPU_ACCESS_NOT_SHAREABLE,不允许;MPU_ACCESS_SHAREABLE,允许
//cen:是否允许cache;MPU_ACCESS_NOT_CACHEABLE,不允许;MPU_ACCESS_CACHEABLE,允许
//ben:是否允许缓冲;MPU_ACCESS_NOT_BUFFERABLE,不允许;MPU_ACCESS_BUFFERABLE,允许
//返回值;0,成功.
//    其他,错误.
void MPU_Set_Protection(uint32_t baseaddr,uint32_t size,uint32_t rnum,uint8_t ap,uint8_t sen,uint8_t cen,uint8_t ben)
{
	MPU_Region_InitTypeDef MPU_Initure;
	
	HAL_MPU_Disable();								        //配置MPU之前先关闭MPU,配置完成以后在使能MPU

	MPU_Initure.Enable = MPU_REGION_ENABLE;			        //使能该保护区域 
	MPU_Initure.Number =rnum;			                    //设置保护区域
	MPU_Initure.BaseAddress = baseaddr;	                    //设置基址
	MPU_Initure.Size = size;				                    //设置保护区域大小
	MPU_Initure.SubRegionDisable = 0X00;                      //禁止子区域
	MPU_Initure.TypeExtField = MPU_TEX_LEVEL0;                //设置类型扩展域为level0
	MPU_Initure.AccessPermission = (uint8_t)ap;		            //设置访问权限,
	MPU_Initure.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;	//允许指令访问(允许读取指令)
	MPU_Initure.IsShareable = sen;                            //是否共用?
    MPU_Initure.IsCacheable = cen;                            //是否cache?     
	MPU_Initure.IsBufferable = ben;                           //是否缓冲?
	HAL_MPU_ConfigRegion(&MPU_Initure);                     //配置MPU
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);			        //开启MPU
}

//设置需要保护的存储块
//必须对部分存储区域进行MPU保护,否则可能导致程序运行异常
void MPU_Memory_Protection(void)
{
    //保护整个D1 SRAM 512KB 此用于用户应用数据存储
    MPU_Set_Protection( 0x24000000,                 //基地址
                        MPU_REGION_SIZE_512KB,      //长度
                        MPU_REGION_NUMBER0,         //NUMER1
                        MPU_REGION_FULL_ACCESS,     //全访问
                        MPU_ACCESS_SHAREABLE,       //允许共享
                        MPU_ACCESS_CACHEABLE,       //允许cache
                        MPU_ACCESS_NOT_BUFFERABLE); //禁止缓冲	
	
	
	
//此后为D2 SRAM区域的SRAM3
  /* Configure the MPU attributes as Device not cacheable 
     for ETH DMA descriptors 此用于以太网和USB的缓冲 到32k*/
    MPU_Set_Protection( 0x30040000,                 //基地址
                        MPU_REGION_SIZE_256B,      	//长度  一部分
                        MPU_REGION_NUMBER1,       
                        MPU_REGION_FULL_ACCESS,    
                        MPU_ACCESS_NOT_SHAREABLE,       
                        MPU_ACCESS_NOT_CACHEABLE,       
                        MPU_ACCESS_BUFFERABLE); 
    
  /* Configure the MPU attributes as Cacheable write through 
     for LwIP RAM heap which contains the Tx buffers  此用于以太网和USB的缓冲 
	 此为0x30044000起的剩下16k*/
    MPU_Set_Protection( 0x30044000,                 //基地址
                        MPU_REGION_SIZE_16KB,       //长度
                        MPU_REGION_NUMBER2,         //NUMER1
                        MPU_REGION_FULL_ACCESS,     //全访问
                        MPU_ACCESS_NOT_SHAREABLE,   //禁止共享
                        MPU_ACCESS_CACHEABLE,       //允许cache
                        MPU_ACCESS_NOT_BUFFERABLE);     //bu允许缓冲
}

