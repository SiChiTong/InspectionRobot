#ifndef __RS485_H
#define __RS485_H			 
#include "sys.h"	 								  
#include "bms.h"


//ģʽ����
#define RS485_TX_EN			PGout(8)	//485ģʽ����.0,����;1,����.
#define MYRS485_TX_EN		{PCout(12)=1;PDout(0)=1;}	//485ģʽ����.0,����;1,����.
#define MYRS485_RX_EN		{PCout(12)=0;PDout(0)=0;}	//485ģʽ����.0,����;1,����.

//����봮���жϽ��գ�����EN_USART2_RXΪ1����������Ϊ0
#define EN_USART2_RX 	1			//0,������;1,����.


extern u8 RS485_RX_BUF[64]; 		//���ջ���,���64���ֽ�
extern u8 RS485_RX_CNT;   			//���յ������ݳ���
extern u8 rs485buf[35];

void RS485_Init(u32 bound);
void RS485_Send_Data(u8 *buf,u8 len);
void RS485_Receive_Data(u8 *buf,u8 *len);	
void MYRS485_Init(u32 bound);
//void Get_BattaryMsg(void);

#endif	   
















