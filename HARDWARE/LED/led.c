#include "led.h" 


//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

#ifdef BEIDA_CODE_V1
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOFʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
	
  GPIO_SetBits(GPIOG,GPIO_Pin_13 | GPIO_Pin_14);//GPIOF9,F10���øߣ�����	
#endif
#ifdef INSPECTIONROBOT_CODE_V2
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹŜGPIOFʱד

  //GPIOF9,F10Եʼۯʨ׃
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//ǕͨˤԶģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//ΆάˤԶ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//ʏ-
  GPIO_Init(GPIOA, &GPIO_InitStructure);//Եʼۯ
	
  GPIO_SetBits(GPIOA,GPIO_Pin_11 | GPIO_Pin_12);//GPIOF9,F10ʨ׃ٟìֆİ	
#endif
	
}






