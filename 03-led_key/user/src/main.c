#include "main.h"
#include <string.h>
int main(void)
{
	Led_Init();      //��ʼ��
	//Key_Init();
	Usart1_Pint_Init(115200);
	printf("hello world\r\n");
	Usart1_Send_Str((u8 *)"dkwodkwo\r\n");
	while(1)
	{
		if(recv_ok == 1)
		{
			recv_ok = 0;
			Usart1_Send_Str(buff);
			
			
		}
		switch(Key_Scan())     //��������led����
		{
			case 1:LED1_ON;LED2_OFF;LED3_OFF; break;
			case 2:LED2_ON;LED1_OFF;LED3_OFF; break;
			case 3:LED3_ON;LED1_OFF;LED2_OFF; break;
		}
	}
}

