#include "MY_Bm280_Bh1750.h"

unsigned char BUF[8];	  //�������ݻ�����
static bmp280_t p_bmp280; //У׼����
//��ʼ��BIIC
void BIIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOI_CLK_ENABLE();
	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(IIC_SCL_GPIO_Port, IIC_SCL_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(IIC_SDA_GPIO_Port, IIC_SDA_Pin, GPIO_PIN_RESET);
	/*Configure GPIO pins : PEPin PEPin */
	GPIO_InitStruct.Pin = IIC_SCL_Pin | IIC_SDA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(IIC_SCL_GPIO_Port, &GPIO_InitStruct);
	HAL_GPIO_Init(IIC_SDA_GPIO_Port, &GPIO_InitStruct);

	BIIC_SCL(1);
	BIIC_SDA(1);
}
//����AIIC��ʼ�ź�
void BIIC_Start(void)
{
	BSDA_OUT(); //sda�����
	BIIC_SDA(1);
	BIIC_SCL(1);
	delay_us(4);
	BIIC_SDA(0); //START:when CLK is high,DATA change form high to low
	delay_us(4);
	BIIC_SCL(0); //ǯסI2C���ߣ�׼�����ͻ��������
}
//����AIICֹͣ�ź�
void BIIC_Stop(void)
{
	BSDA_OUT(); //sda�����
	BIIC_SCL(0);
	BIIC_SDA(0); //STOP:when CLK is high DATA change form low to high
	delay_us(4);
	BIIC_SCL(1);
	BIIC_SDA(1); //����I2C���߽����ź�
	delay_us(4);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t BIIC_Wait_Ack(void)
{
	uint8_t ucErrTime = 0;
	BSDA_IN(); //SDA����Ϊ����
	BIIC_SDA(1);
	delay_us(1);
	BIIC_SCL(1);
	delay_us(1);
	while (BREAD_SDA)
	{
		ucErrTime++;
		if (ucErrTime > 250)
		{
			BIIC_Stop();
			return 1;
		}
	}
	BIIC_SCL(0); //ʱ�����0
	return 0;
}

//����ACKӦ��
void BIIC_Ack(void)
{
	BIIC_SCL(0);
	BSDA_OUT();
	BIIC_SDA(0);
	delay_us(2);
	BIIC_SCL(1);
	delay_us(2);
	BIIC_SCL(0);
}
//������ACKӦ��
void BIIC_NAck(void)
{
	BIIC_SCL(0);
	BSDA_OUT();
	BIIC_SDA(1);
	delay_us(2);
	BIIC_SCL(1);
	delay_us(2);
	BIIC_SCL(0);
}

//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t IIC_Read_Byte_nask(unsigned char ack)
{
	unsigned char i, receive = 0;
	BSDA_IN(); //SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		BIIC_SCL(0);
		delay_us(2);
		BIIC_SCL(1);
		receive <<= 1;
		if (BREAD_SDA)
			receive++;
		delay_us(1);
	}
	if (!ack)
		BIIC_NAck(); //����nACK
	else
		BIIC_Ack(); //����ACK
	return receive;
}
//AIIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void BIIC_Send_Byte(uint8_t txd)
{
	uint8_t t;
	BSDA_OUT();
	BIIC_SCL(0); //����ʱ�ӿ�ʼ���ݴ���
	for (t = 0; t < 8; t++)
	{
		BIIC_SDA((txd & 0x80) >> 7);
		txd <<= 1;
		delay_us(2); //��TEA5767��������ʱ���Ǳ����
		BIIC_SCL(1);
		delay_us(2);
		BIIC_SCL(0);
		delay_us(2);
	}
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
uint8_t BIIC_Read_Byte(unsigned char ack)
{
	unsigned char i, receive = 0;
	BSDA_IN(); //SDA����Ϊ����
	for (i = 0; i < 8; i++)
	{
		BIIC_SCL(0);
		delay_us(2);
		BIIC_SCL(1);
		receive <<= 1;
		if (BREAD_SDA)
			receive++;
		delay_us(1);
	}
	if (!ack)
		BIIC_NAck(); //����nACK
	else
		BIIC_Ack(); //����ACK
	return receive;
}

uint8_t BMP280_ReadID(void)
{
	return BMP280_Read_Byte(BMP280_CHIPID_REG);
}
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
uint8_t BMP280_Read_Len(uint8_t reg, uint8_t len, uint8_t *buf)
{
	BIIC_Start();
	BIIC_Send_Byte((BMP280_SlaveAddr << 1) | 0); //����������ַ+д����
	BIIC_Wait_Ack();  //�ȴ�Ӧ��
	BIIC_Send_Byte(reg); //д�Ĵ�����ַ
	BIIC_Wait_Ack();	 //�ȴ�Ӧ��
	BIIC_Start();
	BIIC_Send_Byte((BMP280_SlaveAddr << 1) | 1); //����������ַ+������
	BIIC_Wait_Ack();							 //�ȴ�Ӧ��
	while (len)
	{
		if (len == 1)
			*buf = BIIC_Read_Byte(0); //������,����nACK
		else
			*buf = BIIC_Read_Byte(1); //������,����ACK
		len--;
		buf++;
	}
	BIIC_Stop(); //����һ��ֹͣ����
	return 0;
}

//IICдһ���ֽ�
//devaddr:����IIC��ַ
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
uint8_t BMP280_Write_Byte(uint8_t reg, uint8_t data)
{
	BIIC_Start();
	BIIC_Send_Byte((BMP280_SlaveAddr << 1) | 0); //����������ַ+д����
	if (BIIC_Wait_Ack())						 //�ȴ�Ӧ��
	{
		BIIC_Stop();
		return 1;
	}
	BIIC_Send_Byte(reg);  //д�Ĵ�����ַ
	BIIC_Wait_Ack();	  //�ȴ�Ӧ��
	BIIC_Send_Byte(data); //��������
	if (BIIC_Wait_Ack())  //�ȴ�ACK
	{
		BIIC_Stop();
		return 1;
	}
	BIIC_Stop();
	return 0;
}

//IIC��һ���ֽ�
//reg:�Ĵ�����ַ
//����ֵ:����������
uint8_t BMP280_Read_Byte(uint8_t reg)
{
	uint8_t res;
	BIIC_Start();
	BIIC_Send_Byte((BMP280_SlaveAddr << 1) | 0); //����������ַ+д����
	BIIC_Wait_Ack();							 //�ȴ�Ӧ��
	BIIC_Send_Byte(reg);						 //д�Ĵ�����ַ
	BIIC_Wait_Ack();							 //�ȴ�Ӧ��
	BIIC_Start();
	BIIC_Send_Byte((BMP280_SlaveAddr << 1) | 1); //����������ַ+������
	BIIC_Wait_Ack();							 //�ȴ�Ӧ��
	res = BIIC_Read_Byte(0);					 //������,����nACK
	BIIC_Stop();								 //����һ��ֹͣ����
	return res;
}
/**
  * @brief  ���BMP280��������
  * @param  None 
  * @retval 0������
  *         1�����Ӳ�����
  */
uint8_t BMP280_Check(void)
{
	uint16_t time = 0;
	uint8_t chip_ID = 0;
	while (time < 1000)
	{
		chip_ID = BMP280_Read_Byte(BMP280_CHIPID_REG);
		if (chip_ID == 0x57 || chip_ID == 0x58 || chip_ID == 0x59)
			break; //��⵽оƬ
		else
			time++;
		delay_xms(1);
	}
	if (time == 1000)
		return 1; //δ��⵽оƬ
	else
	{
		p_bmp280.chip_id = chip_ID; //��¼оƬID
		return 0;
	}
}
/**
  * @brief  BMP280�����λ��ԭ����������ʹ��֮��оƬ�޷�ʹ�á�
  * @param  None 
  * @retval 0������
  *         1�����Ӳ�����
  */
uint8_t BMP280_SetSoftReset(void)
{
	if (BMP280_Write_Byte(BMP280_RESET_REG, BMP280_RESET_VALUE))
		return 1;
	else
		return 0;
}
/**
  * @brief  BMP280У׼����
  * @param  None 
  * @retval 0������
  *         1�����Ӳ�����
  */
uint8_t BMP280_CalibParam(void)
{
	uint8_t a_data_uint8_t[24], res = 0;
	memset(a_data_uint8_t, 0, 24 * sizeof(uint8_t));
	res = BMP280_Read_Len(BMP280_DIG_T1_LSB_REG, 24, a_data_uint8_t);
	p_bmp280.calib_param.dig_T1 = (uint16_t)((((uint16_t)((uint8_t)a_data_uint8_t[1])) << 8) | a_data_uint8_t[0]);
	p_bmp280.calib_param.dig_T2 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[3])) << 8) | a_data_uint8_t[2]);
	p_bmp280.calib_param.dig_T3 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[5])) << 8) | a_data_uint8_t[4]);
	p_bmp280.calib_param.dig_P1 = (uint16_t)((((uint16_t)((uint8_t)a_data_uint8_t[7])) << 8) | a_data_uint8_t[6]);
	p_bmp280.calib_param.dig_P2 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[9])) << 8) | a_data_uint8_t[8]);
	p_bmp280.calib_param.dig_P3 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[11])) << 8) | a_data_uint8_t[10]);
	p_bmp280.calib_param.dig_P4 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[13])) << 8) | a_data_uint8_t[12]);
	p_bmp280.calib_param.dig_P5 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[15])) << 8) | a_data_uint8_t[14]);
	p_bmp280.calib_param.dig_P6 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[17])) << 8) | a_data_uint8_t[16]);
	p_bmp280.calib_param.dig_P7 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[19])) << 8) | a_data_uint8_t[18]);
	p_bmp280.calib_param.dig_P8 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[21])) << 8) | a_data_uint8_t[20]);
	p_bmp280.calib_param.dig_P9 = (int16_t)((((int16_t)((int8_t)a_data_uint8_t[23])) << 8) | a_data_uint8_t[22]);
	return res;
}
/**
  * @brief  ����BMP280��Դ����ģʽ
  * @param  mode��0,1,2,3 ��
    0��SLEEP_MODE������ģʽ
    1OR2��FORCED_MODE����ȡһ�κ����SLEEP_MODE.
    3����������ģʽ
  * @retval 0������
  *         1�����Ӳ�����
  *         2����������
  */
uint8_t BMP280_SetPowerMode(uint8_t mode)
{
	uint8_t v_mode_uint8_t = 0, res = 0;
	if (mode <= BMP280_NORMAL_MODE)
	{
		v_mode_uint8_t = (p_bmp280.oversamp_temperature << 5) + (p_bmp280.oversamp_pressure << 2) + mode;
		res = BMP280_Write_Byte(BMP280_CTRLMEAS_REG, v_mode_uint8_t);
	}
	else
		res = 2;
	return res;
}
/**
  * @brief  ����BMP280������ģʽ����,�����Լ�����ģʽ
  * @param  mode��
						BMP280_ULTRA_LOW_POWER_MODE    ,
						BMP280_LOW_POWER_MODE          ,
						BMP280_STANDARD_RESOLUTION_MODE,
						BMP280_HIGH_RESOLUTION_MODE    ,
						BMP280_ULTRA_HIGH_RESOLUTION_MODE
  * @retval 0������
  *         1�����Ӳ�����
  */
uint8_t BMP280_SetWorkMode(WORKING_MODE mode)
{
	uint8_t res = 0, v_data_uint8_t = 0;
	if (mode <= 0x04)
	{
		v_data_uint8_t = BMP280_Read_Byte(BMP280_CTRLMEAS_REG); //��ȡ�����ƼĴ�����ֵ
		switch (mode)
		{
		case BMP280_ULTRA_LOW_POWER_MODE:
			p_bmp280.oversamp_temperature = BMP280_P_MODE_x1;
			p_bmp280.oversamp_pressure = BMP280_P_MODE_x1;
			break;
		case BMP280_LOW_POWER_MODE:
			p_bmp280.oversamp_temperature = BMP280_P_MODE_x1;
			p_bmp280.oversamp_pressure = BMP280_P_MODE_x2;
			break;
		case BMP280_STANDARD_RESOLUTION_MODE:
			p_bmp280.oversamp_temperature = BMP280_P_MODE_x1;
			p_bmp280.oversamp_pressure = BMP280_P_MODE_x4;
			break;
		case BMP280_HIGH_RESOLUTION_MODE:
			p_bmp280.oversamp_temperature = BMP280_P_MODE_x1;
			p_bmp280.oversamp_pressure = BMP280_P_MODE_x8;
			break;
		case BMP280_ULTRA_HIGH_RESOLUTION_MODE:
			p_bmp280.oversamp_temperature = BMP280_P_MODE_x2;
			p_bmp280.oversamp_pressure = BMP280_P_MODE_x16;
			break;
		}
		v_data_uint8_t = ((v_data_uint8_t & ~0xE0) | ((p_bmp280.oversamp_temperature << 5) & 0xE0));
		v_data_uint8_t = ((v_data_uint8_t & ~0x1C) | ((p_bmp280.oversamp_pressure << 2) & 0x1C));
		res = BMP280_Write_Byte(BMP280_CTRLMEAS_REG, v_data_uint8_t);
	}
	else
		res = 1;
	return res;
}
/**
  * @brief  ����ʱ�����ã������λ�ȡ�¶Ⱥ���ѹ�ļ��ʱ�䳤��
  * @param  standby_durn��
  *  BMP280_T_SB_0_5MS              ��0.5ms   
  *  BMP280_T_SB_62_5MS             ��62.5ms  
  *  BMP280_T_SB_125MS              ��125ms   
  *  BMP280_T_SB_250MS              ��250ms   
  *  BMP280_T_SB_500MS              ��500ms   
  *  BMP280_T_SB_1000MS             ��1000ms  
  *  BMP280_T_SB_2000MS             ��2000ms  
  *  BMP280_T_SB_4000MS             ��4000ms 
  * @retval 0������
  *         1��������
  */
uint8_t BMP280_SetStandbyDurn(BMP280_T_SB standby_durn)
{
	uint8_t v_data_uint8_t = 0;
	v_data_uint8_t = BMP280_Read_Byte(BMP280_CONFIG_REG);				  //��ȡ���Ĵ�����ֵ
	v_data_uint8_t = ((v_data_uint8_t & ~0xE0) | ((standby_durn << 5) & 0xE0)); //��3λ
	return BMP280_Write_Byte(BMP280_CONFIG_REG, v_data_uint8_t);
}
/**
  * @brief  ��ȡ����ʱ���������λ�ȡ�¶Ⱥ���ѹ�ļ��ʱ�䳤��
  * @param  v_standby_durn_uint8_t��
  *  BMP280_T_SB_0_5MS              ��0.5ms   
  *  BMP280_T_SB_62_5MS             ��62.5ms  
  *  BMP280_T_SB_125MS              ��125ms   
  *  BMP280_T_SB_250MS              ��250ms   
  *  BMP280_T_SB_500MS              ��500ms   
  *  BMP280_T_SB_1000MS             ��1000ms  
  *  BMP280_T_SB_2000MS             ��2000ms  
  *  BMP280_T_SB_4000MS             ��4000ms 
  * @retval 0������
  *         1��������
  */
uint8_t BMP280_GetStandbyDurn(uint8_t *v_standby_durn_uint8_t)
{
	uint8_t res = 0, v_data_uint8_t = 0;
	res = v_data_uint8_t = BMP280_Read_Byte(BMP280_CONFIG_REG);
	*v_standby_durn_uint8_t = (v_data_uint8_t >> 5);
	return res;
}
/**
  * @brief  ��ȡδ�����¶�
  * @param  un_temp������ָ��
  * @retval 0������
  *         1��������
  */
uint8_t BMP280_ReadUncompTemperature(int *un_temp)
{
	uint8_t a_data_uint8_tr[3] = {0, 0, 0}, res = 0;
	res = BMP280_Read_Len(BMP280_TEMPERATURE_MSB_REG, 3, a_data_uint8_tr);
	*un_temp = (int)((((uint32_t)(a_data_uint8_tr[0])) << 12) | (((uint32_t)(a_data_uint8_tr[1])) << 4) | ((uint32_t)a_data_uint8_tr[2] >> 4));
	return res;
}
/**
  * @brief  ��ȡδ������ѹ
  * @param  un_temp������ָ��
  * @retval 0������
  *         1��������
  */
uint8_t BMP280_ReadUncompPressuree(int *un_press)
{
	uint8_t a_data_uint8_tr[3] = {0, 0, 0}, res = 0;
	res = BMP280_Read_Len(BMP280_PRESSURE_MSB_REG, 3, a_data_uint8_tr);
	*un_press = (int)((((uint32_t)(a_data_uint8_tr[0])) << 12) | (((uint32_t)(a_data_uint8_tr[1])) << 4) | ((uint32_t)a_data_uint8_tr[2] >> 4));
	return res;
}
/**
  * @brief  ��ȡδ������ѹ���¶ȣ�һ���ȡ��һ�ζ�ȡ6���ֽ����ݣ��ȷֿ���ȡ�ٶȿ�һ������
  * @param  un_press��δ������ѹ����ָ�룬un_temp��δ�����¶�����ָ��
  * @retval 0������
  *         1��������
  */
uint8_t BMP280_ReadUncompPressureTemperature(int *un_press, int *un_temp)
{
	uint8_t a_data_uint8_t[6] = {0, 0, 0, 0, 0, 0}, res = 0;
	res = BMP280_Read_Len(BMP280_PRESSURE_MSB_REG, 6, a_data_uint8_t);
	*un_press = (int32_t)((((uint32_t)(a_data_uint8_t[0])) << 12) | (((uint32_t)(a_data_uint8_t[1])) << 4) | ((uint32_t)a_data_uint8_t[2] >> 4)); /*��ѹ*/
	*un_temp = (int32_t)((((uint32_t)(a_data_uint8_t[3])) << 12) | (((uint32_t)(a_data_uint8_t[4])) << 4) | ((uint32_t)a_data_uint8_t[5] >> 4));	/* �¶� */
	return res;
}
/**
  * @brief  ��ȡ��ʵ����ѹ
  * @param  un_temp��δ�����¶�����
  * @retval int���¶�ֵ�����磺2255����22.55 DegC
  *        
  */
int BMP280_CompensateTemperatureInt32(int un_temp)
{
	int v_x1_uint32_tr = 0;
	int v_x2_uint32_tr = 0;
	int temperature = 0;
	v_x1_uint32_tr = ((((un_temp >> 3) - ((int)p_bmp280.calib_param.dig_T1 << 1))) * ((int)p_bmp280.calib_param.dig_T2)) >> 11;
	v_x2_uint32_tr = (((((un_temp >> 4) - ((int)p_bmp280.calib_param.dig_T1)) * ((un_temp >> 4) - ((int)p_bmp280.calib_param.dig_T1))) >> 12) * ((int)p_bmp280.calib_param.dig_T3)) >> 14;
	p_bmp280.calib_param.t_fine = v_x1_uint32_tr + v_x2_uint32_tr;
	temperature = (p_bmp280.calib_param.t_fine * 5 + 128) >> 8;
	return temperature;
}
/**
  * @brief  ��ȡ��ʵ��ѹ
  * @param  un_press��δ������ѹ
  * @retval uint32_t����ʵ����ѹֵ   
  */
uint32_t BMP280_CompensatePressureInt32(int un_press)
{
	int v_x1_uint32_tr = 0;
	int v_x2_uint32_tr = 0;
	uint32_t v_pressure_uint32_t = 0;
	v_x1_uint32_tr = (((int)p_bmp280.calib_param.t_fine) >> 1) - (int)64000;
	v_x2_uint32_tr = (((v_x1_uint32_tr >> 2) * (v_x1_uint32_tr >> 2)) >> 11) * ((int)p_bmp280.calib_param.dig_P6);
	v_x2_uint32_tr = v_x2_uint32_tr + ((v_x1_uint32_tr * ((int)p_bmp280.calib_param.dig_P5)) << 1);
	v_x2_uint32_tr = (v_x2_uint32_tr >> 2) + (((int)p_bmp280.calib_param.dig_P4) << 16);
	v_x1_uint32_tr = (((p_bmp280.calib_param.dig_P3 * (((v_x1_uint32_tr >> 2) * (v_x1_uint32_tr >> 2)) >> 13)) >> 3) + ((((int)p_bmp280.calib_param.dig_P2) * v_x1_uint32_tr) >> 1)) >> 18;
	v_x1_uint32_tr = ((((32768 + v_x1_uint32_tr)) * ((int)p_bmp280.calib_param.dig_P1)) >> 15);
	v_pressure_uint32_t = (((uint32_t)(((int)1048576) - un_press) - (v_x2_uint32_tr >> 12))) * 3125;
	if (v_pressure_uint32_t < 0x80000000)
		if (v_x1_uint32_tr != 0)
			v_pressure_uint32_t = (v_pressure_uint32_t << 1) / ((uint32_t)v_x1_uint32_tr);
		else
			return 0;
	else if (v_x1_uint32_tr != 0)
		v_pressure_uint32_t = (v_pressure_uint32_t / (uint32_t)v_x1_uint32_tr) * 2;
	else
		return 0;
	v_x1_uint32_tr = (((int)p_bmp280.calib_param.dig_P9) * ((int)(((v_pressure_uint32_t >> 3) * (v_pressure_uint32_t >> 3)) >> 13))) >> 12;
	v_x2_uint32_tr = (((int)(v_pressure_uint32_t >> 2)) * ((int)p_bmp280.calib_param.dig_P8)) >> 13;
	v_pressure_uint32_t = (uint32_t)((int)v_pressure_uint32_t + ((v_x1_uint32_tr + v_x2_uint32_tr + p_bmp280.calib_param.dig_P7) >> 4));
	return v_pressure_uint32_t;
}
/**
  * @brief  ��ȡ��ʵ��ѹ���¶�
  * @param  press����ʵ����ѹָ�룬temp����ʵ���¶�ָ��
  * @retval 0������
  *         1��������
  */
uint8_t BMP280_ReadPressureTemperature(uint32_t *press, int *temp)
{
	int32_t un_press = 0;
	int32_t un_temp = 0;
	uint8_t res = 0;
	res = BMP280_ReadUncompPressureTemperature(&un_press, &un_temp);
	/* ��ȡ��ʵ���¶�ֵ����ѹֵ*/
	*temp = BMP280_CompensateTemperatureInt32(un_temp);
	*press = BMP280_CompensatePressureInt32(un_press);
	return res;
}
void BMP280_Test(void)
{
	uint32_t bmp280_press;
	int32_t bmp280_temp;
	BMP280_ReadPressureTemperature(&bmp280_press, &bmp280_temp);				   //bmp280��ȡ��ѹֵ���¶�printf("bmp280_press:%d\r\n",bmp280_press);
	printf("\r\nbmp280_temp :%d,bmp280_press :%d\r\n", bmp280_temp, bmp280_press); //��mpu9250���¶ȸ�׼
}

/**
  * @brief  BMP280��ʼ��
  * @param  None 
  * @retval 0������
  *         1�����Ӳ�����
  */
uint8_t BMP280_Init(void)
{
	if (BMP280_Check())
	{
		delay_xms(200);
		BMP280_SetPowerMode(3);
		return 1; //BMP280���оƬ
	}
	else
	{
		if (BMP280_CalibParam())
			return 3;
		if (BMP280_SetPowerMode(BMP280_NORMAL_MODE))
			return 4;
		if (BMP280_SetWorkMode(BMP280_ULTRA_LOW_POWER_MODE))
			return 5;
		if (BMP280_SetStandbyDurn(BMP280_T_SB_0_5MS))
			return 6;
	}
	return 0;
}

void Bh1750_data_send(uint8_t command)
{
	do
	{
		BIIC_Start();				//iic��ʼ�ź�
		BIIC_Send_Byte(BHAddWrite); //����������ַ
	} while (BIIC_Wait_Ack());		//�ȴ��ӻ�Ӧ��
	BIIC_Send_Byte(command);		//����ָ��
	BIIC_Wait_Ack();				//�ȴ��ӻ�Ӧ��
	BIIC_Stop();					//iicֹͣ�ź�
}

uint16_t Bh1750_data_read(void)
{
	uint16_t buf;
	BIIC_Start();					   //iic��ʼ�ź�
	BIIC_Send_Byte(BHAddRead);		   //����������ַ+����־λ
	BIIC_Wait_Ack();				   //�ȴ��ӻ�Ӧ��
	buf = BIIC_Read_Byte(1);		   //��ȡ����
	buf = buf << 8;					   //��ȡ������߰�λ����
	buf += 0x00ff & BIIC_Read_Byte(0); //��ȡ������ڰ�λ����
	BIIC_Stop();					   //����ֹͣ�ź�
	return buf;
}
void Bh1750_Test(void)
{
	float datalx;
	datalx = Bh1750_data_read() / 1.2; //�����ֲ��ȡ�����ݳ���1.2�͵õ���λλlx�Ĺ�ǿ�ȼ��ֵ��
	printf("\n\rBh1750_data:%f\n\r", datalx);
}
void Bh1750_Init(void)
{
	Bh1750_data_send(BHPowOn);	//������������
	Bh1750_data_send(BHReset);	//����Ĵ�������
	Bh1750_data_send(BHModeH2); //���ø߾���Ϊģʽ2
	delay_xms(180);				//������ɺ�Ҫ��һ���ӳ٣��ֲ���˵���180ms�Ϳ�����
}

void PCF8591_Write_Command(unsigned char Addr, unsigned char Command)
{
	BIIC_Start();
	BIIC_Send_Byte(Addr);
	BIIC_Wait_Ack();
	BIIC_Send_Byte(Command);
	BIIC_Wait_Ack();
	BIIC_Stop();
}
//����PCF8591ת�����Ĳ�����ѹֵ
unsigned char ADC_PCF8591(void)
{
	unsigned char temp;
	BIIC_Start();
	BIIC_Send_Byte(0x91);
	BIIC_Wait_Ack();
	temp = IIC_Read_Byte_nask(0);
	BIIC_Stop(); //����һ��ֹͣ����
	return temp;
}
void PCF8591_Init(void)
{
	char i;
	BIIC_Init();
	for (i = 0; i < 4; i++)
	{
		PCF8591_Write_Command(0x90, 0x00 + i);
		delay_xms(10);
	}
}

void PCF8591_Test(void)
{
	int number;
	for (unsigned char i = 0; i < 4; i++)
	{
		PCF8591_Write_Command(0x90, 0x01 + i);
		number = ADC_PCF8591();
		printf("\n\rPCF8591ͨ��%d���ݣ�%d\n\r", i + 1, number);
	}
	printf("\n\r");
	delay_xms(200);
}

uint8_t BMP280_Bh1750_Init(void)
{
	BIIC_Init();
	Bh1750_Init();
	BMP280_Init();
	
	printf("\r\nBMP280 ID:0x%x\n\r", BMP280_ReadID());
	delay_xms(1000);
	return 1;
}
