#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	

#ifdef BEIDA_CODE_V1
//LED�˿ڶ���
#define LED0 PGout(13)	// DS0
#define LED1 PGout(14)	// DS1	 
#endif
#ifdef INSPECTIONROBOT_CODE_V2
//LED׋ࠚ֨ӥ
#define LED0 PAout(11)	// DS0
#define LED1 PAout(12)	// DS1	 
#endif
void LED_Init(void);//��ʼ��		 				    
#endif
