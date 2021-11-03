/***
	GT1151������������
	INT -----> PH3
	RESET -----> PH8
	SCL -----> PH5
	SDA -----> PH4
**/

#include "gt1151q_iic_driver.h"
#include "ctiic.h"
#include "stdio.h"

#define GT_DEBUG 0

uint16_t touch_x, touch_y;
const uint16_t GT1151_TPX_TBL[5]={GT_TP1_REG,GT_TP2_REG,GT_TP3_REG,GT_TP4_REG,GT_TP5_REG};


const uint8_t GT1151_CFG_TBL[]=
{ 
	0x44,0x20,0x03,0xE0,0x01,0x05,0x35,0x04,0x00,0x08,
	0x09,0x0F,0x55,0x37,0x33,0x11,0x00,0x03,0x08,0x56,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x00,0x00,
	0x3C,0x08,0x0A,0x28,0x1E,0x50,0x00,0x00,0x82,0xB4,
	0xD2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x85,0x25,0x11,0x41,0x43,0x31,
	0x0D,0x00,0xAD,0x22,0x24,0x7D,0x1D,0x1D,0x32,0xDF,
	0x4F,0x44,0x0F,0x80,0x2C,0x50,0x50,0x00,0x00,0x00,
	0x00,0xD3,0x00,0x00,0x00,0x00,0x0F,0x28,0x1E,0xFF,
	0xF0,0x37,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x50,0xB4,0xC0,0x94,0x53,0x2D,
	0x0A,0x02,0xBE,0x60,0xA2,0x71,0x8F,0x82,0x80,0x92,
	0x74,0xA3,0x6B,0x01,0x0F,0x14,0x03,0x1E,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x0C,0x0D,0x0E,0x0F,0x10,
	0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1A,0x1B,
	0x1D,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x19,0x18,0x17,
	0x15,0x14,0x13,0x12,0x0C,0x08,0x06,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
	0xC4,0x09,0x23,0x23,0x50,0x5D,0x54,0x4B,0x3C,0x0F,
	0x32,0xFF,0xE4,0x04,0x40,0x00,0x8A,0x05,0x40,0x00,
	0xAA,0x00,0x22,0x22,0x00,0x00,0xAA,0x05,0x01
};   //�����ṩ�����ò�����ֻ��д��һ��


/***************************************************************************************
  * @brief  ������ò�����У����
***************************************************************************************/
void check_sum(void)	
{	
	uint16_t checksum=0;
	uint8_t checksumH,checksumL;
	uint8_t i=0;	
	for(i=0;i<(sizeof(GT1151_CFG_TBL)-3);i+=2)
	checksum +=((GT1151_CFG_TBL[i]<<8)|GT1151_CFG_TBL[i+1]);//����У���
	checksum =(~checksum)+1;
	checksumH=checksum>>8;
	checksumL=checksum;
	printf("chksum:0x%X,\r\n",checksum);
	printf("chksumH:0x%X,\r\n",checksumH);
	printf("chksumL:0x%X,\r\n",checksumL);			
}



/***************************************************************************************
  * @brief  ����GT1151���ò���
	* @param	mode  0,���������浽flash 1,�������浽flash
	*	@retval none
***************************************************************************************/
uint8_t GT1151_Send_Cfg(uint8_t mode)
{
	uint16_t checksum=0;
	uint8_t buf[3];
	uint8_t i=0;	
	for(i=0;i<(sizeof(GT1151_CFG_TBL)-3);i+=2)
	checksum +=((GT1151_CFG_TBL[i]<<8)|GT1151_CFG_TBL[i+1]);//����У���
	checksum =(~checksum)+1;
	buf[0]= checksum>>8;
	buf[1]= checksum;
	buf[2]= mode;	//�Ƿ�д�뵽GT5688 FLASH?  ���Ƿ���籣��
	
	GT1151_WR_Reg(GT_CFGS_REG,(uint8_t*)GT1151_CFG_TBL,sizeof(GT1151_CFG_TBL)-3);//���ͼĴ�������
	GT1151_WR_Reg(GT_CHECK_REG,buf,3);
	return 0;
}

/***************************************************************************************
  * @brief  ��GT1151д��һ������
	* @param	reg  ��ʼ�Ĵ�����ַ
	* @param	buf  ���ݻ�������
	* @param  len  д���ݳ���
	*	@retval 0,�ɹ�;1,ʧ��.
***************************************************************************************/
uint8_t GT1151_WR_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i=0;
	uint8_t ret=0;
	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   	//����д���� 	 
	CT_IIC_Wait_Ack();
	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
	for(i=0;i<len;i++)
	{	   
    CT_IIC_Send_Byte(buf[i]);  	//������
		ret=CT_IIC_Wait_Ack();
		if(ret)break;  
	}
    CT_IIC_Stop();					//����һ��ֹͣ����	    
	return ret; 
}
	
/***************************************************************************************
  * @brief  ��GT1151����һ������
	* @param	reg  ��ʼ�Ĵ�����ַ
	* @param	buf  ���ݻ�������
	* @param  len  �����ݳ���		
	*	@retval none
***************************************************************************************/
void GT1151_RD_Reg(uint16_t reg,uint8_t *buf,uint8_t len)
{
	uint8_t i; 
 	CT_IIC_Start();	
 	CT_IIC_Send_Byte(GT_CMD_WR);   //����д���� 	 
	CT_IIC_Wait_Ack();
 	CT_IIC_Send_Byte(reg>>8);   	//���͸�8λ��ַ
	CT_IIC_Wait_Ack(); 	 										  		   
 	CT_IIC_Send_Byte(reg&0XFF);   	//���͵�8λ��ַ
	CT_IIC_Wait_Ack();  
 	CT_IIC_Start();  	 	   
	CT_IIC_Send_Byte(GT_CMD_RD);   //���Ͷ�����		   
	CT_IIC_Wait_Ack();	   
	for(i=0;i<len;i++)
	{	   
		buf[i]=CT_IIC_Read_Byte(i==(len-1)?0:1); //������	  
	} 
  CT_IIC_Stop();//����һ��ֹͣ����    
} 


/***************************************************************************************
  * @brief  ��ʼ��GT1151������
	*	@retval ����ֵ:0,��ʼ���ɹ�;1,��ʼ��ʧ�� 
  * @note   ��һ��ʹ��ʱ��Ҫд�����ò���
***************************************************************************************/
uint8_t GT1151_Init(void)
{
	uint8_t temp[5]; 
	uint8_t i=0;
	uint8_t Cfg_Info[239] = {0};
	GPIO_InitTypeDef GPIO_Initure;

	//PH3---INT
	GPIO_Initure.Pin=T_INT_Pin;            //PH3
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
	GPIO_Initure.Pull=GPIO_PULLUP;          //����
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
	HAL_GPIO_Init(T_INT_GPIO_Port,&GPIO_Initure);     //��ʼ��

	//PH8---RST
	GPIO_Initure.Pin=T_RSTH8_Pin;            //PH8
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
	HAL_GPIO_Init(T_RSTH8_GPIO_Port,&GPIO_Initure);     //��ʼ��
	
	CT_IIC_Init();      	//��ʼ����������I2C����  
	GT_RST(0);				    //��λ
	HAL_Delay(12);
	GT_RST(1);				    //�ͷŸ�λ		    
	HAL_Delay(10); 
	
	//PH3---INT
	GPIO_Initure.Pin=T_INT_Pin;            //PH3
	GPIO_Initure.Mode=GPIO_MODE_INPUT;      //����
	GPIO_Initure.Pull=GPIO_NOPULL;          //��������������������
	GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
	HAL_GPIO_Init(T_INT_GPIO_Port,&GPIO_Initure);     //��ʼ��
	HAL_Delay(100);  
	
	#if GT_DEBUG //��ӡ��Ʒ��Ϣ
	GT1151_RD_Reg(GT_PID_REG,temp,4);       //��ȡ��ƷID  
	printf("CTP ID:GT%s\r\n",temp);	        //��ӡID      CTP ID:GT1158
	printf("Default Ver:0x%x\r\n",temp[0]); //��ӡ�汾��  Default Ver:0x31
	#endif  
	
	if(strcmp((char*)temp,"1158")==0)       //�ж�оƬ�Ƿ�ΪGT1151 (CTP ID:GT1158)
	{
		#if GT_DEBUG //д�볧�����ò��������
		GT1151_Send_Cfg(1);
		GT1151_RD_Reg(0x8050,Cfg_Info,239);	
		printf("Config Info:\r\n");
		for( i = 0; i < 239; i++ )
		{
		printf("0x%02X,",Cfg_Info[i]);
		if((i+1)%10==0)
		printf("\r\n");
		}
		printf("\r\n");
		#endif  
		return 0;
	} 
	return 1;
}

uint8_t Touch_Poll(int32_t *x,int32_t *y)
{
	if( touch_x != 0xffff|| touch_y != 0xffff)
	{
		*x = touch_x ;
		*y = touch_y ;
		return 1;
	}
	else
	{
		return 0;
	}
}



/***************************************************************************************
  * @brief   PH7�ж�, �����ж�
  * @input
  * @return
***************************************************************************************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint8_t buf[4];
	uint8_t i = 0, mode = 0, temp = 0;
	uint16_t x[5], y[5];
	if(GPIO_Pin == T_INT_Pin) 									//��ȡ����, �����һֱ��INT����
	{ 
		//printf("enter exit\r\n");
		GT1151_RD_Reg(GT_GSTID_REG, &mode, 1);		//��ȡ�������״̬
		if(mode & 0X80 && ((mode & 0XF) < 6)) 		//������ɶ�ȡ
		{
				temp = 0;
				GT1151_WR_Reg(GT_GSTID_REG, &temp, 1);//����־
		}
		if( (mode & 0xF) && ((mode & 0xF) < 6)) 	//�жϴ��������
		{
				for(i = 0; i < (mode & 0xF); i++)
				{
						GT1151_RD_Reg(GT1151_TPX_TBL[i], buf, 4);	//��ȡXY����ֵ
						x[i] = (((uint16_t)buf[1] << 8) + buf[0]);
						y[i] = (((uint16_t)buf[3] << 8) + buf[2]);
				}
				touch_x = x[0];
				touch_y = y[0];
		}
		if((mode&0x8F)==0x80)//�޴����㰴��,xy��ֵΪ0xffffvv
		{
			touch_x = 0xffff;
			touch_y = 0xffff;
		}
		//printf("x:%d,y:%d\r\n",touch_x,touch_y);
	}
}


