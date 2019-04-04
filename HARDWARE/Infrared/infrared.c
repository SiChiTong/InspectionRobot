#include "infrared.h" 

//��ʼ��ADC															   
void  Adc_Init(void)
{    
  GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);//ʹ��GPIOAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE);//ʹ��GPIOAʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��

  //�ȳ�ʼ��ADC1ͨ��5 IO��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;//PB0 ADC1_IN8  PB1 ADC1_IN9
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN ;//����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��  
	
	  //�ȳ�ʼ��ADC1ͨ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_4;//PC4  ADC1_IN14   PC5  ADC1_IN15
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��  

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 
 
	
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
  ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
  ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
  ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��
	
 
	ADC_Cmd(ADC1, ENABLE);//����ADת����	

}				  
//���ADCֵ
//ch: @ref ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
u16 Get_Adc(u8 ch)   
{
	  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}
//ð������
void bubble_sort(u32 a[], int n)
{
    int i, j;
		u32 temp;
    for (j = 0; j < n - 1; j++)
        for (i = 0; i < n - 1 - j; i++)
        {
            if(a[i] > a[i + 1])
            {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
}
//��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//ch:ͨ�����
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val[20];
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val[t]=Get_Adc(ch);
		//delay_ms(5);
	}
	//bubble_sort(temp_val,times); //��С��������
	return temp_val[times/2];
}
void Get_Distance_Infrared(u16* dis)
{
	u8 i;
	u16 adcx[4] = {0};
	double temp;
	double Inverse_number;
	
	adcx[0]=Get_Adc_Average(ADC_Channel_8,1);//��ȡͨ��5��ת��ֵ��5��ȡ��λ��
	adcx[1]=Get_Adc_Average(ADC_Channel_9,1);//��ȡͨ��5��ת��ֵ��5��ȡ��λ��
	adcx[2]=Get_Adc_Average(ADC_Channel_14,1);//��ȡͨ��5��ת��ֵ��5��ȡ��λ��
	adcx[3]=Get_Adc_Average(ADC_Channel_15,1);//��ȡͨ��5��ת��ֵ��5��ȡ��λ��
	for(i=0;i<4;i++)
	{
		
		temp=(double)adcx[i]*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111

		if((double)temp<0.393)														//��������
				Inverse_number=0.006666667;
		else if(temp>=0.393&&temp<1.525)					//40-150cm
				Inverse_number=0.0162*temp + 0.0003;	//y=0.0162*x + 0.0003
		else if(temp>=1.525&&temp<1.995)					//30-40cm
				Inverse_number=0.0177*temp - 0.0002;	//y=0.0177*x - 0.0002
		else if(temp>=1.995&&temp<2.525)					//20-30cm
				Inverse_number=0.0314*temp - 0.0294;	//y=0.0314*x - 0.0294
		else if(temp>=2.525&&temp<=3.3)						//15-20cm
				Inverse_number=0.0741*temp - 0.137;	//y=0.0741*x - 0.137
			dis[i]=1/Inverse_number;
	}

}

