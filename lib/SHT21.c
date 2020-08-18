#include "SHT21.h"

uint8_t TXbuff[1],RXbuff[3];
extern I2C_HandleTypeDef hi2c2;

float SHT21_get_Temperature(void)
{
	float T;
	TXbuff [0] = tcode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0x80, TXbuff, 1, (uint32_t)1000);
	HAL_Delay (70);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)0x80, RXbuff, 3, (uint32_t)1000);
	HAL_Delay (1000);
	T=-46.85 + (175.72*(256*RXbuff[0]+RXbuff[1]))/65536;
	return (T);
}

float SHT21_get_Ph(void)
{	float Ph;
	TXbuff [0] = phcode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0x80, TXbuff, 1, (uint32_t)1000);
	HAL_Delay (26);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)0x80, RXbuff, 3, (uint32_t)1000);
	HAL_Delay(1000);
	Ph=-6+((125*((RXbuff[0]*256)+RXbuff[1]))/65536);
	return(Ph);
}
uint8_t SHT21_get_UR(void)
{
	TXbuff [0] = ur;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0x80, TXbuff, 1, (uint32_t)1000);
	HAL_Delay (1);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)0x80, RXbuff, 1, (uint32_t)1000);
	HAL_Delay (1000);
	return(RXbuff[0]);
}

void SHT21_restart(void)
{
	TXbuff [0] = rest;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0x80, TXbuff, 1, (uint32_t)1000);
	HAL_Delay (1);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)0x80, RXbuff, 1, (uint32_t)1000);
	HAL_Delay (1000);
}