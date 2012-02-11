/****************************************************************************
* Copyright (C), 2010 安富莱电子 www.armfly.com
*
* 【本例程在安富莱STM32F103ZE-EK开发板上调试通过             】
* 【QQ: 1295744630, 旺旺：armfly, Email: armfly@qq.com       】
*
* 文件名: main.c
* 内容简述: 	
*	从0开始创建一个工程，实现跑马灯。
*
*	安富莱开发板上有4个LED指示灯，对应的GPIO为 : PF6,PF7,PF8,PF9
*	输出为0点亮LED
*	输出为1关闭LED
*/
#include "stm32f10x.h"

/* 为了使用编程书写方便，我们定义几个控制LED开关的宏 */
#define LED1_ON()	{GPIO_ResetBits(GPIOF, GPIO_Pin_6);}	/* PF6 = 0 点亮LED1 */
#define LED1_OFF()	{GPIO_SetBits(GPIOF, GPIO_Pin_6);}		/* PF6 = 1 熄灭LED1 */

#define LED2_ON()	{GPIO_ResetBits(GPIOF, GPIO_Pin_7);}	/* PF7 = 0 点亮LED2 */
#define LED2_OFF()	{GPIO_SetBits(GPIOF, GPIO_Pin_7);}		/* PF7 = 1 点亮LED2 */

#define LED3_ON()	{GPIO_ResetBits(GPIOF, GPIO_Pin_8);}	/* PF8 = 0 点亮LED3 */
#define LED3_OFF()	{GPIO_SetBits(GPIOF, GPIO_Pin_8);}		/* PF8 = 1 点亮LED3 */

#define LED4_ON()	{GPIO_ResetBits(GPIOF, GPIO_Pin_9);}	/* PF9 = 0 点亮LED4 */
#define LED4_OFF()	{GPIO_SetBits(GPIOF, GPIO_Pin_9);}		/* PF9 = 1 点亮LED4 */

/*
	这是一个延迟函数
*/
void Delay(__IO uint32_t nCount)
{
	/* __IO 就是volatile, 加上这个后可以避免延迟函数被编译器优化掉 */

	for(; nCount != 0; nCount--);
}

/* 主函数 */
int main(void)
{
	/*
		这个函数是ST库中的函数，函数实体在
		Libraries\CMSIS\Core\CM3\system_stm32f10x.c

		配置内部Flash接口，初始化PLL，配置系统时钟的频率
		系统时钟缺省配置为72MHz
	 */
	SystemInit();

	/*
		配置GPIO, 将连接LED1-4的GPIO设置为推挽输出
		为了使程序看起来简洁点，可以将括内代码做成一个函数,比如void GPIO_Configuration(void)
	*/
	{
		GPIO_InitTypeDef GPIO_InitStructure;	/* 定义1个结构体变量 */

		/* 打开GPIOF 时钟 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);

		/* 在将LED设置为输出前先设置输出1，避免一开始就点亮LED */
		GPIO_SetBits(GPIOF, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);

		/* 可以对PF6 - PF9 一起初始化 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7
			| GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	/* 推挽输出模式 */
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF, &GPIO_InitStructure);	/* 调用库函数初始化GPIO */
	}

	/*
		下面这个 while循环实现简单的跑马灯功能。
	*/
	while (1)
	{
		LED1_ON();			/* 点亮LED1 */

		Delay(0xAFFFF);		/* 插入延时 */

		LED2_ON();			/* 点亮LED2 */
		LED3_ON();			/* 点亮LED3 */
		LED1_OFF();			/* 熄灭LED1 */

		Delay(0xAFFFF);		/* 插入延时 */

		/* Turn on LD4 */
		LED4_ON();			/* 点亮LED4 */
		/* Turn off LD2 and LD3 */
		LED2_OFF();			/* 关闭LED2 */
		LED3_OFF();			/* 关闭LED3 */

		Delay(0xAFFFF);		/* 插入延时 */

		LED4_OFF();			/* 关闭LED4 */
	}
}

