#include "CCS811.h"

uint8_t ccs_TxBuff[5],ccs_RxBuff[8];
extern I2C_HandleTypeDef hi2c2;

void CCS811_init(void)
{	
	ccs_TxBuff[0]=stat;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
	HAL_I2C_Master_Receive (&hi2c2,	(uint16_t) (0x5a<<1), ccs_RxBuff, 1, (uint32_t) 1000);
	if(ccs_RxBuff[0]>=0x90)
	{
		ccs_TxBuff[0]=0xF4;
		HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
	}
}

uint16_t CCS811_Get_eCO2 (void)
{
	ccs_RxBuff[0]=0x00;
	while(ccs_RxBuff[0]<0x91)
	{
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
	HAL_I2C_Master_Receive (&hi2c2,	(uint16_t) (0x5a<<1), ccs_RxBuff, 1, (uint32_t) 1000);
	}
	ccs_TxBuff[0]=data;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
	HAL_I2C_Master_Receive (&hi2c2,	(uint16_t) (0x5a<<1), ccs_RxBuff, 2, (uint32_t) 1000);
	return(ccs_RxBuff[0]<<8 | ccs_RxBuff[1]);
}

uint16_t CCS811_Get_TVOC (void)
{
	ccs_TxBuff[0]=stat;
	ccs_RxBuff[0]=0x00;
	while(ccs_RxBuff[0]<0x91)
	{
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
	HAL_I2C_Master_Receive (&hi2c2,	(uint16_t) (0x5a<<1), ccs_RxBuff, 1, (uint32_t) 1000);
	}
	ccs_TxBuff[0]=data;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
	HAL_I2C_Master_Receive (&hi2c2,	(uint16_t) (0x5a<<1), ccs_RxBuff, 4, (uint32_t) 1000);
	return(ccs_RxBuff[2]<<8 | ccs_RxBuff[3]);
}


void CCS811_Change_Mode (uint16_t mod)
{
	switch(mod){
	case 1:
		ccs_TxBuff[0]=mode;
		ccs_TxBuff[1]=0x10;
		HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
		HAL_I2C_Master_Receive (&hi2c2,	(uint16_t) (0x5a<<1), ccs_RxBuff, 1, (uint32_t) 1000);
		break;
	case 2:
		ccs_TxBuff[0]=mode;
		ccs_TxBuff[1]=0x20;
		HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
		HAL_I2C_Master_Receive (&hi2c2,	(uint16_t) (0x5a<<1), ccs_RxBuff, 1, (uint32_t) 1000);
		break;
	case 3: 
		ccs_TxBuff[0]=mode;
		ccs_TxBuff[1]=0x30;
		HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
		HAL_I2C_Master_Receive (&hi2c2,	(uint16_t) (0x5a<<1), ccs_RxBuff, 1, (uint32_t) 1000);
		break;
	case 4: 
		ccs_TxBuff[0]=mode;
		ccs_TxBuff[1]=0x40;
		HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
		HAL_I2C_Master_Receive (&hi2c2,	(uint16_t) (0x5a<<1), ccs_RxBuff, 1, (uint32_t) 1000);
		break;
	default:
		ccs_TxBuff[0]=mode;
		ccs_TxBuff[1]=0x00;
		HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 1, (uint32_t) 1000);
		HAL_I2C_Master_Receive (&hi2c2,	(uint16_t) (0x5a<<1), ccs_RxBuff, 1, (uint32_t) 1000);
	}
}

void CCS811_Add_Env_data (uint16_t humidity, uint16_t temperature)
{
	
}
void CCS8811_Restart (void)
{
		ccs_TxBuff[0]=0xFF;
		ccs_TxBuff[1]=0x11; 
		ccs_TxBuff[2]=0xE5;
		ccs_TxBuff[3]=0x72;
		ccs_TxBuff[4]=0x8A;
		HAL_I2C_Master_Transmit(&hi2c2, (uint16_t) (0x5a<<1), ccs_TxBuff, 5, (uint32_t) 1000);
}
