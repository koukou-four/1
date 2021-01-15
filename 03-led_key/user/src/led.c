#include "led.h"
/*
	函数名：Led_Init
	函数描述：LED管教初始化函数
	形参：无
	返回值：无
	PA11 ----   LED3
	PB14 ----   LED2
	PB11 ----   LED1
	推挽输出
*/
void Led_Init(void)
{
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	//开时钟
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 |GPIO_Pin_14; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}

