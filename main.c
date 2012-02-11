/****************************************************************************
* Copyright (C), 2010 ���������� www.armfly.com
*
* ���������ڰ�����STM32F103ZE-EK�������ϵ���ͨ��             ��
* ��QQ: 1295744630, ������armfly, Email: armfly@qq.com       ��
*
* �ļ���: main.c
* ���ݼ���: 	
*	��0��ʼ����һ�����̣�ʵ������ơ�
*
*	����������������4��LEDָʾ�ƣ���Ӧ��GPIOΪ : PF6,PF7,PF8,PF9
*	���Ϊ0����LED
*	���Ϊ1�ر�LED
*/
#include "stm32f10x.h"

/* Ϊ��ʹ�ñ����д���㣬���Ƕ��弸������LED���صĺ� */
#define LED1_ON()	{GPIO_ResetBits(GPIOF, GPIO_Pin_6);}	/* PF6 = 0 ����LED1 */
#define LED1_OFF()	{GPIO_SetBits(GPIOF, GPIO_Pin_6);}		/* PF6 = 1 Ϩ��LED1 */

#define LED2_ON()	{GPIO_ResetBits(GPIOF, GPIO_Pin_7);}	/* PF7 = 0 ����LED2 */
#define LED2_OFF()	{GPIO_SetBits(GPIOF, GPIO_Pin_7);}		/* PF7 = 1 ����LED2 */

#define LED3_ON()	{GPIO_ResetBits(GPIOF, GPIO_Pin_8);}	/* PF8 = 0 ����LED3 */
#define LED3_OFF()	{GPIO_SetBits(GPIOF, GPIO_Pin_8);}		/* PF8 = 1 ����LED3 */

#define LED4_ON()	{GPIO_ResetBits(GPIOF, GPIO_Pin_9);}	/* PF9 = 0 ����LED4 */
#define LED4_OFF()	{GPIO_SetBits(GPIOF, GPIO_Pin_9);}		/* PF9 = 1 ����LED4 */

/*
	����һ���ӳٺ���
*/
void Delay(__IO uint32_t nCount)
{
	/* __IO ����volatile, �����������Ա����ӳٺ������������Ż��� */

	for(; nCount != 0; nCount--);
}

/* ������ */
int main(void)
{
	/*
		���������ST���еĺ���������ʵ����
		Libraries\CMSIS\Core\CM3\system_stm32f10x.c

		�����ڲ�Flash�ӿڣ���ʼ��PLL������ϵͳʱ�ӵ�Ƶ��
		ϵͳʱ��ȱʡ����Ϊ72MHz
	 */
	SystemInit();

	/*
		����GPIO, ������LED1-4��GPIO����Ϊ�������
		Ϊ��ʹ�����������㣬���Խ����ڴ�������һ������,����void GPIO_Configuration(void)
	*/
	{
		GPIO_InitTypeDef GPIO_InitStructure;	/* ����1���ṹ����� */

		/* ��GPIOF ʱ�� */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);

		/* �ڽ�LED����Ϊ���ǰ���������1������һ��ʼ�͵���LED */
		GPIO_SetBits(GPIOF, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);

		/* ���Զ�PF6 - PF9 һ���ʼ�� */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7
			| GPIO_Pin_8 | GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	/* �������ģʽ */
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOF, &GPIO_InitStructure);	/* ���ÿ⺯����ʼ��GPIO */
	}

	/*
		������� whileѭ��ʵ�ּ򵥵�����ƹ��ܡ�
	*/
	while (1)
	{
		LED1_ON();			/* ����LED1 */

		Delay(0xAFFFF);		/* ������ʱ */

		LED2_ON();			/* ����LED2 */
		LED3_ON();			/* ����LED3 */
		LED1_OFF();			/* Ϩ��LED1 */

		Delay(0xAFFFF);		/* ������ʱ */

		/* Turn on LD4 */
		LED4_ON();			/* ����LED4 */
		/* Turn off LD2 and LD3 */
		LED2_OFF();			/* �ر�LED2 */
		LED3_OFF();			/* �ر�LED3 */

		Delay(0xAFFFF);		/* ������ʱ */

		LED4_OFF();			/* �ر�LED4 */
	}
}

