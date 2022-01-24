#include "24c02.h"
#include "delay.h"

//初始化AIIC
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
//产生AIIC起始信号
void AIIC_Start(void)
{
	ASDA_OUT();     //sda线输出
	AIIC_SDA(1);	  	  
	AIIC_SCL(1);
	delay_us(4);
 	AIIC_SDA(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	AIIC_SCL(0);//钳住I2C总线，准备发送或接收数据 
}	  
//产生AIIC停止信号
void AIIC_Stop(void)
{
	ASDA_OUT();//sda线输出
	AIIC_SCL(0);
	AIIC_SDA(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	AIIC_SCL(1); 
	AIIC_SDA(1);//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t AIIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	ASDA_IN();      //SDA设置为输入  
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
	AIIC_SCL(0);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
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
//不产生ACK应答		    
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
//AIIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void AIIC_Send_Byte(uint8_t txd)
{                        
	uint8_t t;   
	ASDA_OUT(); 	    
	AIIC_SCL(0);//拉低时钟开始数据传输
	for(t=0;t<8;t++)
	{              
		AIIC_SDA((txd&0x80)>>7);
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		AIIC_SCL(1);
		delay_us(2); 
		AIIC_SCL(0);	
		delay_us(2);
	}	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t AIIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	ASDA_IN();//SDA设置为输入
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
		AIIC_NAck();//发送nACK
	else
		AIIC_Ack(); //发送ACK   
	return receive;
}


//初始化AIIC接口
void AT24CXX_Init(void)
{
	AIIC_Init();//AIIC初始化
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{				  
	uint8_t temp=0;		  	    																 
  AIIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		AIIC_Send_Byte(0XA0);	   //发送写命令
		AIIC_Wait_Ack();
		AIIC_Send_Byte(ReadAddr>>8);//发送高地址	    
	}else AIIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	   
	AIIC_Wait_Ack(); 
  AIIC_Send_Byte(ReadAddr%256);   //发送低地址
	AIIC_Wait_Ack();	    
	AIIC_Start();  	 	   
	AIIC_Send_Byte(0XA1);           //进入接收模式			   
	AIIC_Wait_Ack();	 
  temp=AIIC_Read_Byte(0);		   
  AIIC_Stop();//产生一个停止条件	    
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
  AIIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		AIIC_Send_Byte(0XA0);	    //发送写命令
		AIIC_Wait_Ack();
		AIIC_Send_Byte(WriteAddr>>8);//发送高地址	  
	}else AIIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 	 
	AIIC_Wait_Ack();	   
	AIIC_Send_Byte(WriteAddr%256);   //发送低地址
	AIIC_Wait_Ack(); 	 										  		   
	AIIC_Send_Byte(DataToWrite);     //发送字节							   
	AIIC_Wait_Ack();  		    	   
	AIIC_Stop();//产生一个停止条件 
	HAL_Delay(10);	 
}
//在AT24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void AT24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{  	
	uint8_t t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//在AT24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
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
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
uint8_t AT24CXX_Check(void)
{
	uint8_t temp;
	temp=AT24CXX_ReadOneByte(255);//避免每次开机都写AT24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte(255,0X55);
	  temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}



