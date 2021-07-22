#include "Bsp_mpu.h"


//����ĳ�������MPU����
//baseaddr:MPU��������Ļ�ַ(�׵�ַ)
//size:MPU��������Ĵ�С(������32�ı���,��λΪ�ֽ�),�����õ�ֵ�ο�:CORTEX_MPU_Region_Size
//rnum:MPU���������,��Χ:0~7,���֧��8����������,�����õ�ֵ�ο���CORTEX_MPU_Region_Number
//ap:����Ȩ��,���ʹ�ϵ����:�����õ�ֵ�ο���CORTEX_MPU_Region_Permission_Attributes
//MPU_REGION_NO_ACCESS,�޷��ʣ���Ȩ&�û������ɷ��ʣ�
//MPU_REGION_PRIV_RW,��֧����Ȩ��д����
//MPU_REGION_PRIV_RW_URO,��ֹ�û�д���ʣ���Ȩ�ɶ�д���ʣ�
//MPU_REGION_FULL_ACCESS,ȫ���ʣ���Ȩ&�û����ɷ��ʣ�
//MPU_REGION_PRIV_RO,��֧����Ȩ������
//MPU_REGION_PRIV_RO_URO,ֻ������Ȩ&�û���������д��
//���:STM32F7����ֲ�.pdf,4.6��,Table 89.
//sen:�Ƿ�������;MPU_ACCESS_NOT_SHAREABLE,������;MPU_ACCESS_SHAREABLE,����
//cen:�Ƿ�����cache;MPU_ACCESS_NOT_CACHEABLE,������;MPU_ACCESS_CACHEABLE,����
//ben:�Ƿ�������;MPU_ACCESS_NOT_BUFFERABLE,������;MPU_ACCESS_BUFFERABLE,����
//����ֵ;0,�ɹ�.
//    ����,����.
void MPU_Set_Protection(uint32_t baseaddr,uint32_t size,uint32_t rnum,uint8_t ap,uint8_t sen,uint8_t cen,uint8_t ben)
{
	MPU_Region_InitTypeDef MPU_Initure;
	
	HAL_MPU_Disable();								        //����MPU֮ǰ�ȹر�MPU,��������Ժ���ʹ��MPU

	MPU_Initure.Enable = MPU_REGION_ENABLE;			        //ʹ�ܸñ������� 
	MPU_Initure.Number =rnum;			                    //���ñ�������
	MPU_Initure.BaseAddress = baseaddr;	                    //���û�ַ
	MPU_Initure.Size = size;				                    //���ñ��������С
	MPU_Initure.SubRegionDisable = 0X00;                      //��ֹ������
	MPU_Initure.TypeExtField = MPU_TEX_LEVEL0;                //����������չ��Ϊlevel0
	MPU_Initure.AccessPermission = (uint8_t)ap;		            //���÷���Ȩ��,
	MPU_Initure.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;	//����ָ�����(�����ȡָ��)
	MPU_Initure.IsShareable = sen;                            //�Ƿ���?
    MPU_Initure.IsCacheable = cen;                            //�Ƿ�cache?     
	MPU_Initure.IsBufferable = ben;                           //�Ƿ񻺳�?
	HAL_MPU_ConfigRegion(&MPU_Initure);                     //����MPU
	HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);			        //����MPU
}

//������Ҫ�����Ĵ洢��
//����Բ��ִ洢�������MPU����,������ܵ��³��������쳣
void MPU_Memory_Protection(void)
{
    //��������D1 SRAM 512KB �������û�Ӧ�����ݴ洢
    MPU_Set_Protection( 0x24000000,                 //����ַ
                        MPU_REGION_SIZE_512KB,      //����
                        MPU_REGION_NUMBER0,         //NUMER1
                        MPU_REGION_FULL_ACCESS,     //ȫ����
                        MPU_ACCESS_SHAREABLE,       //������
                        MPU_ACCESS_CACHEABLE,       //����cache
                        MPU_ACCESS_NOT_BUFFERABLE); //��ֹ����	
	
	
	
//�˺�ΪD2 SRAM�����SRAM3
  /* Configure the MPU attributes as Device not cacheable 
     for ETH DMA descriptors ��������̫����USB�Ļ��� ��32k*/
    MPU_Set_Protection( 0x30040000,                 //����ַ
                        MPU_REGION_SIZE_256B,      	//����  һ����
                        MPU_REGION_NUMBER1,       
                        MPU_REGION_FULL_ACCESS,    
                        MPU_ACCESS_NOT_SHAREABLE,       
                        MPU_ACCESS_NOT_CACHEABLE,       
                        MPU_ACCESS_BUFFERABLE); 
    
  /* Configure the MPU attributes as Cacheable write through 
     for LwIP RAM heap which contains the Tx buffers  ��������̫����USB�Ļ��� 
	 ��Ϊ0x30044000���ʣ��16k*/
    MPU_Set_Protection( 0x30044000,                 //����ַ
                        MPU_REGION_SIZE_16KB,       //����
                        MPU_REGION_NUMBER2,         //NUMER1
                        MPU_REGION_FULL_ACCESS,     //ȫ����
                        MPU_ACCESS_NOT_SHAREABLE,   //��ֹ����
                        MPU_ACCESS_CACHEABLE,       //����cache
                        MPU_ACCESS_NOT_BUFFERABLE);     //bu������
}

