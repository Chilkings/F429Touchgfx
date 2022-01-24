#include "CTiic.h"
#include "delay.h"	 

//电容触摸屏-IIC 驱动代码	   


void CT_Delay(void)
{
	delay_us(2);
} 

/***************************************************************************************
  * @brief  电容触摸芯片IIC接口初始化
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
  * @brief  产生IIC起始信号,当SCL为高期间，SDA由高到低的跳变
***************************************************************************************/
void CT_IIC_Start(void)
{
    CT_SDA_OUT();     //sda线输出
    CT_IIC_SCL(1);
    CT_IIC_SDA(1);
    delay_us(30);
    CT_IIC_SDA(0);
	  CT_Delay();
		CT_IIC_SCL(0);
}

/***************************************************************************************
  * @brief  产生IIC停止信号,当SCL为高期间，SDA由低到高的跳变
***************************************************************************************/
void CT_IIC_Stop(void)
{
    CT_SDA_OUT();//sda线输出
		CT_IIC_SCL(0); //STOP:when CLK is high DATA change form low to high
		CT_IIC_SDA(0);
		delay_us(30);
		CT_IIC_SCL(1); 
    CT_Delay();
		CT_IIC_SDA(1);
}



/***************************************************************************************
  * @brief  等待应答信号到来
	*	@retval 1，接收应答失败 0，接收应答成功
***************************************************************************************/
uint8_t CT_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	CT_SDA_IN();      //SDA设置为输入  
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
	CT_IIC_SCL(0);//时钟输出0 	   
	return 0;  
} 


/***************************************************************************************
  * @brief  产生ACK应答
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
  * @brief  不产生ACK应答
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
  * @brief  IIC发送一个字节
  *	@retval 返回从机有无应答 1，有应答 0，无应答		
***************************************************************************************/
void CT_IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	CT_SDA_OUT(); 	    
    CT_IIC_SCL(0);//拉低时钟开始数据传输 
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
  * @brief  读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
***************************************************************************************/
uint8_t CT_IIC_Read_Byte(unsigned char ack)
{
	uint8_t i,receive=0;
 	CT_SDA_IN();//SDA设置为输入 
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
	if (!ack)CT_IIC_NAck();//发送nACK
	else CT_IIC_Ack(); //发送ACK   
 	return receive;
}




