#include "usart.h"


/*
	函数名：Usart1_Pint_Init
	函数描述：串口管脚初始化函数
	形参：brr 波特率
	返回值：无
	备注：
	USART1_TX ----- PA9     推挽复用输出
	USART1_RX ----- PA10    浮空输入
*/
void Usart1_Pint_Init(u32 brr)
{
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);	//开时钟
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1, ENABLE);
	
	USART_InitTypeDef  USART_InitStruct;
	USART_InitStruct.USART_BaudRate = brr;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init( USART1, & USART_InitStruct);
	
	USART_ITConfig( USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig( USART1, USART_IT_IDLE, ENABLE);
	
	
	NVIC_SetPriority(USART1_IRQn,NVIC_EncodePriority(7-2,1,1));
	NVIC_EnableIRQ(USART1_IRQn);
	
	
	USART_Cmd (USART1 , ENABLE);
	
}


/*
	函数名：Usart1_Send_Ch
函数描述：串口发送字符函数
	形参：字符
	返回值：无
	备注：
*/

void Usart1_Send_Str(u8 *str)
{
	while(*str != '\0')
	{
		while((USART1->SR & (0x1<<7)) == 0);
		USART1->DR = *str;
		//USART_SendData( USART1, *str);
		str++;
	}
}

u8 buff[50];
u8 recv_ok ;
void USART1_IRQHandler(void)
{
	static u8 len = 0;
	if(USART_GetITStatus( USART1, USART_IT_RXNE))
	{
		USART_ClearFlag( USART1, USART_FLAG_RXNE);
		buff[len] = USART_ReceiveData( USART1);
		len ++;
		
	}
	if(USART_GetITStatus( USART1, USART_IT_IDLE))
	{
		if(USART1->DR)
		{
			;
		}
		buff[len] = '\0';
		len = 0;
		recv_ok = 1;
		//printf("%s",buff);
	}
}

#pragma import(__use_no_semihosting_swi) //取消半主机状态

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;

int fputc(int ch, FILE *f) {
	while((USART1->SR &(0X01<<7))==0);
		USART1->DR=ch;
  return (ch);
}
int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int ch) {
  while((USART1->SR &(0X01<<7))==0);
		USART1->DR=ch;
}


void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}

