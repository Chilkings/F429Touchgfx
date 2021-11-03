#include "CTiic.h"
#include "delay.h"	 

//���ݴ�����-IIC ��������	   


void CT_Delay(void)
{
	delay_us(2);
} 

/***************************************************************************************
  * @brief  ���ݴ���оƬIIC�ӿڳ�ʼ��
***************************************************************************************/
void CT_IIC_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TFT_I2C_SCL_GPIO_Port, TFT_I2C_SCL_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(TFT_I2C_SDA_GPIO_Port, TFT_I2C_SDA_Pin, GPIO_PIN_RESET);
	/*Configure GPIO pins : PEPin PEPin */
  GPIO_InitStruct.Pin = TFT_I2C_SCL_Pin|TFT_I2C_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TFT_I2C_SCL_GPIO_Port, &GPIO_InitStruct);
  HAL_GPIO_Init(TFT_I2C_SDA_GPIO_Port, &GPIO_InitStruct);	
	
	CT_IIC_SCL(1);
	CT_IIC_SDA(1);
}

/***************************************************************************************
  * @brief  ����IIC��ʼ�ź�,��SCLΪ���ڼ䣬SDA�ɸߵ��͵�����
***************************************************************************************/
void CT_IIC_Start(void)
{
    CT_SDA_OUT();     //sda�����
    CT_IIC_SCL(1);
    CT_IIC_SDA(1);
    delay_us(30);
    CT_IIC_SDA(0);
	  CT_Delay();
		CT_IIC_SCL(0);
}

/***************************************************************************************
  * @brief  ����IICֹͣ�ź�,��SCLΪ���ڼ䣬SDA�ɵ͵��ߵ�����
***************************************************************************************/
void CT_IIC_Stop(void)
{
    CT_SDA_OUT();//sda�����
		CT_IIC_SCL(0); //STOP:when CLK is high DATA change form low to high
		CT_IIC_SDA(0);
		delay_us(30);
		CT_IIC_SCL(1); 
    CT_Delay();
		CT_IIC_SDA(1);
}



/***************************************************************************************
  * @brief  �ȴ�Ӧ���źŵ���
	*	@retval 1������Ӧ��ʧ�� 0������Ӧ��ɹ�
***************************************************************************************/
uint8_t CT_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	CT_SDA_IN();      //SDA����Ϊ����  
	CT_IIC_SDA(1);	   
	CT_IIC_SCL(1);
	CT_Delay();
	while(CT_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		} 
		CT_Delay();
	}
	CT_IIC_SCL(0);//ʱ�����0 	   
	return 0;  
} 


/***************************************************************************************
  * @brief  ����ACKӦ��
***************************************************************************************/
void CT_IIC_Ack(void)
{
	CT_IIC_SCL(0);
	CT_SDA_OUT(); 
	CT_IIC_SDA(0);
	CT_Delay();
	CT_IIC_SCL(1);
	CT_Delay();
	CT_IIC_SCL(0);
}

/***************************************************************************************
  * @brief  ������ACKӦ��
***************************************************************************************/	    
void CT_IIC_NAck(void)
{
	CT_IIC_SCL(0);
	CT_SDA_OUT(); 
	CT_IIC_SDA(1);
	CT_Delay();
	CT_IIC_SCL(1);
	CT_Delay();
	CT_IIC_SCL(0);
}					 				     


/***************************************************************************************
  * @brief  IIC����һ���ֽ�
  *	@retval ���شӻ�����Ӧ�� 1����Ӧ�� 0����Ӧ��		
***************************************************************************************/
void CT_IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	CT_SDA_OUT(); 	    
    CT_IIC_SCL(0);//����ʱ�ӿ�ʼ���ݴ��� 
	for(t=0;t<8;t++)
    {              
        CT_IIC_SDA((txd&0x80)>>7);
        txd<<=1; 
		CT_Delay();	      
		CT_IIC_SCL(1); 
		CT_Delay();
		CT_IIC_SCL(0);	 
		CT_Delay();
    }	 
} 	    

/***************************************************************************************
  * @brief  ��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
***************************************************************************************/
uint8_t CT_IIC_Read_Byte(unsigned char ack)
{
	uint8_t i,receive=0;
 	CT_SDA_IN();//SDA����Ϊ���� 
	delay_us(30);
	for(i=0;i<8;i++ )
	{ 
		CT_IIC_SCL(0); 	    	   
		CT_Delay();
		CT_IIC_SCL(1);	 
		receive<<=1;
		if(CT_READ_SDA)receive++; 
		CT_Delay();  
	}	  				 
	if (!ack)CT_IIC_NAck();//����nACK
	else CT_IIC_Ack(); //����ACK   
 	return receive;
}




