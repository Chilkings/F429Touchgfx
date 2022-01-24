#include "24c02.h"
#include "delay.h"

//��ʼ��AIIC
void AIIC_Init(void)
{	
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(AIIC_SCL_GPIO_Port, AIIC_SDA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIIC_SDA_GPIO_Port, AIIC_SCL_Pin, GPIO_PIN_RESET);
	/*Configure GPIO pins : PEPin PEPin */
  GPIO_InitStruct.Pin = AIIC_SDA_Pin|AIIC_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(AIIC_SCL_GPIO_Port, &GPIO_InitStruct);
  HAL_GPIO_Init(AIIC_SDA_GPIO_Port, &GPIO_InitStruct);
	
	AIIC_SCL(1);
	AIIC_SDA(1);
}
//����AIIC��ʼ�ź�
void AIIC_Start(void)
{
	ASDA_OUT();     //sda�����
	AIIC_SDA(1);	  	  
	AIIC_SCL(1);
	delay_us(4);
 	AIIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	AIIC_SCL(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����AIICֹͣ�ź�
void AIIC_Stop(void)
{
	ASDA_OUT();//sda�����
	AIIC_SCL(0);
	AIIC_SDA(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	AIIC_SCL(1); 
	AIIC_SDA(1);//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t AIIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	ASDA_IN();      //SDA����Ϊ����  
	AIIC_SDA(1);delay_us(1);	   
	AIIC_SCL(1);delay_us(1);	 
	while(AREAD_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			AIIC_Stop();
			return 1;
		}
	}
	AIIC_SCL(0);//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void AIIC_Ack(void)
{
	AIIC_SCL(0);
	ASDA_OUT();
	AIIC_SDA(0);
	delay_us(2);
	AIIC_SCL(1);
	delay_us(2);
	AIIC_SCL(0);
}
//������ACKӦ��		    
void AIIC_NAck(void)
{
	AIIC_SCL(0);
	ASDA_OUT();
	AIIC_SDA(1);
	delay_us(2);
	AIIC_SCL(1);
	delay_us(2);
	AIIC_SCL(0);
}					 				     
//AIIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void AIIC_Send_Byte(uint8_t txd)
{                        
	uint8_t t;   
	ASDA_OUT(); 	    
	AIIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ���
	for(t=0;t<8;t++)
	{              
		AIIC_SDA((txd&0x80)>>7);
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		AIIC_SCL(1);
		delay_us(2); 
		AIIC_SCL(0);	
		delay_us(2);
	}	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t AIIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	ASDA_IN();//SDA����Ϊ����
	for(i=0;i<8;i++ )
	{
		AIIC_SCL(0); 
		delay_us(2);
		AIIC_SCL(1);
		receive<<=1;
		if(AREAD_SDA)receive++;   
		delay_us(1); 
	}					 
	if (!ack)
		AIIC_NAck();//����nACK
	else
		AIIC_Ack(); //����ACK   
	return receive;
}


//��ʼ��AIIC�ӿ�
void AT24CXX_Init(void)
{
	AIIC_Init();//AIIC��ʼ��
}
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t temp=0;		  	    																 
  AIIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		AIIC_Send_Byte(0XA0);	   //����д����
		AIIC_Wait_Ack();
		AIIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ	    
	}else AIIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	   
	AIIC_Wait_Ack(); 
  AIIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	AIIC_Wait_Ack();	    
	AIIC_Start();  	 	   
	AIIC_Send_Byte(0XA1);           //�������ģʽ			   
	AIIC_Wait_Ack();	 
  temp=AIIC_Read_Byte(0);		   
  AIIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
  AIIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		AIIC_Send_Byte(0XA0);	    //����д����
		AIIC_Wait_Ack();
		AIIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ	  
	}else AIIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 	 
	AIIC_Wait_Ack();	   
	AIIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	AIIC_Wait_Ack(); 	 										  		   
	AIIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	AIIC_Wait_Ack();  		    	   
	AIIC_Stop();//����һ��ֹͣ���� 
	HAL_Delay(10);	 
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{  	
	uint8_t t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len)
{  	
	uint8_t t; 
	uint32_t temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
uint8_t AT24CXX_Check(void)
{
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(255);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(255,0X55);
	  temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}



