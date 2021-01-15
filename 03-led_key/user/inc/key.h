#ifndef _KEY_H_
#define _KEY_H_

#include "stm32f10x.h"

void Key_Init(void);
u8 Key_Scan(void);

#define K1      GPIO_ReadInputDataBit(GPIOA,  GPIO_Pin_0)
#define K2      GPIO_ReadInputDataBit(GPIOA,  GPIO_Pin_8)
#define K3      GPIO_ReadInputDataBit(GPIOB,  GPIO_Pin_10)



#endif

