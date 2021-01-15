#ifndef _USART_H_
#define _USART_H_

#include "stm32f10x.h"
#include <stdio.h>


extern u8 buff[50];
extern u8 recv_ok ;
void Usart1_Pint_Init(u32 brr);
void Usart1_Send_Str(u8 *str);





#endif

