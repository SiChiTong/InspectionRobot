#ifndef __INFRAED_H
#define __INFRAED_H
#include "sys.h"


void Adc_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  
void Get_Distance_Infrared(u16* dis); 				    
#endif
