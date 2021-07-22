#ifndef _RING_BUFF_H_
#define _RING_BUFF_H_

#include "stm32h7xx.h"
#include "stdbool.h"

typedef struct 
{
  uint16_t buff_in;
  uint16_t buff_out;
  uint16_t buff_size;
  uint8_t *buff_ring;
}RingBuff;

void RingBuff_Init(RingBuff *ringbuff,uint8_t *buff,uint16_t size);
void RingBuff_Write(RingBuff *ringbuff,uint8_t *buff,uint16_t size);
uint16_t RingBuff_Read(RingBuff *ringbuff,uint8_t *buff, uint16_t num);
uint16_t RingBuff_GetNumber(RingBuff *ringbuff);
void RingBuff_LoseBuff(RingBuff *ringbuff);

#endif


