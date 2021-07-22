#include "RingBuff.h"

void RingBuff_Init(RingBuff *ringbuff,uint8_t *buff,uint16_t size)
{
  ringbuff->buff_in = 0;
  ringbuff->buff_out = 0;
  ringbuff->buff_size = size;
  ringbuff->buff_ring = buff;
}


void RingBuff_Write(RingBuff *ringbuff,uint8_t *buff,uint16_t num)
{
  uint16_t i;
  for(i = 0; i < num; i++)
  {
    ringbuff->buff_ring[ringbuff->buff_in++] = buff[i];
    if(ringbuff->buff_in >= ringbuff->buff_size)
    {
      ringbuff->buff_in = 0;
    }
  }
}


uint16_t RingBuff_Read(RingBuff *ringbuff,uint8_t *buff, uint16_t num)
{
  uint16_t i;
  for(i = 0; i < num; i++)
  {
    if(ringbuff->buff_out != ringbuff->buff_in)
    {
      buff[i] = ringbuff->buff_ring[ringbuff->buff_out++];
      if(ringbuff->buff_out >= ringbuff->buff_size)
      {
        ringbuff->buff_out = 0;
      }
    }
    else
    {
      break;
    }
  }
  
  return i;
}


uint16_t RingBuff_GetNumber(RingBuff *ringbuff)
{
  uint16_t num;
  if(ringbuff->buff_in < ringbuff->buff_out)
  {
    num = ringbuff->buff_in + ringbuff->buff_size - ringbuff->buff_out;
  }
  else
  {
    num = ringbuff->buff_in - ringbuff->buff_out;
  }
  
  return num;
}


void RingBuff_LoseBuff(RingBuff *ringbuff)
{
   ringbuff->buff_out = 0;
   ringbuff->buff_in  = 0;
}


















