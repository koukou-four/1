#include "key.h"


/*
	函数名：Key_Init
	函数描述：按键管脚初始化函数
	形参：无
	返回值：无
	PB10 ----   KEY3
	PA8  ----   KEY2
	PA0  ----   KEY1
	浮空输入
*/

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE);	//开时钟
	
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 |GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}


void delay_ms(u32 ms)
{
	while(ms--);
}

/*
	函数名：Key_Scan
	函数描述：按键扫描函数
	形参：无
	返回值：无
	PB10 ----   KEY3	按下后低	
	PA8  ----   KEY2	按下后低
	PA0  ----   KEY1	按下后高
	浮空输入
*/

u8 Key_Scan(void)
{
	static u8 Key_Flag = 0;
	if((K1 == 1 || K2 == 0 || K3 == 0)&&Key_Flag == 0)
	{
		Key_Flag =1;	 	//禁止扫描
		delay_ms(720000);
		if(K1 == 1)
		{
			return 1;
		}
		else if(K2 == 0)
		{
			return 2;
		}
		else if(K3 == 0)
		{
			return 3;
		}
			
	}
	else if(K1 == 0 && K2 == 1 && K3 == 1 && Key_Flag == 1)
	{
		Key_Flag = 0;		//重新允许扫描
	}
	
	return 0;
}