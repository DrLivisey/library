#include "BMP180.h"

uint8_t tRXBuff[3];
uint8_t TXBuff[2];
uint16_t  AC4,AC5,AC6;
int16_t MC,MD,AC1,AC2,AC3,B1,B2,MB;
extern I2C_HandleTypeDef hi2c2;

void BMP180_init (void)
{	
	uint8_t Calibr[22]; 
	TXBuff[0]=AddrCalib;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)0xEE, Calibr, 22, (uint32_t)1000);
	AC1=((Calibr[0])<<8)|Calibr[1];
	AC2=((Calibr[2])<<8)|Calibr[3];
	AC3=((Calibr[4])<<8)|Calibr[5];
	AC4=((Calibr[6])<<8)|Calibr[7];
	AC5=((Calibr[8])<<8)|Calibr[9];
	AC6=((Calibr[10])<<8)|Calibr[11];
	B1=((Calibr[12])<<8)|Calibr[13];
	B2=((Calibr[14])<<8)|Calibr[15];
	MB=((Calibr[16])<<8)|Calibr[17];
	MC=((Calibr[18])<<8)|Calibr[19];
	MD=((Calibr[20])<<8)|Calibr[21];
}

int16_t BMP180_get_UT (void)
{
	uint16_t UT=0;
	TXBuff[0]=CommReg;
	TXBuff[1]=TempCode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 2, (uint32_t)1000);
	TXBuff[0]=Data;
	HAL_Delay(5);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)0xEE, tRXBuff, 3, (uint32_t)1000);
	UT=(tRXBuff[0]<<8)|tRXBuff[1];
	return(UT);
}

int16_t BMP180_get_Temperature(void)
{	
	int16_t UT,Temperature,X1,X2;
	TXBuff[0]=CommReg;
	TXBuff[1]=TempCode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 2, (uint32_t)1000);
	TXBuff[0]=Data;
	HAL_Delay(5);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)0xEE, tRXBuff, 3, (uint32_t)1000);
	UT=(tRXBuff[0]<<8)+tRXBuff[1];
	X1=((UT-AC6)*AC5)>>15;
	X2=(MC<<11)/(X1+MD);
	Temperature=(X1+X2+8)>>4;
	return(Temperature);
}

int16_t BMP180_get_UP(void)
{
	int16_t UP=0;
	TXBuff[0]=CommReg;
	TXBuff[1]=PressCode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 2, (uint32_t)1000);
	TXBuff[0]=Data;
	HAL_Delay(5);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)0xEE, tRXBuff, 3, (uint32_t)1000);
	UP=(tRXBuff[0]<<8)|tRXBuff[1];
	return(UP);
}

uint32_t BMP180_get_Press(void)
{
	int32_t UT,UP=0,X1,X2,X3,B3,B6,B5;
	uint32_t B4,B7,p; 
	TXBuff[0]=CommReg;
	TXBuff[1]=TempCode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 2, (uint32_t)1000);
	TXBuff[0]=Data;
	HAL_Delay(5);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)0xEE, tRXBuff, 3, (uint32_t)1000);
	UT=(tRXBuff[0]<<8)+tRXBuff[1];
	X1=((UT-AC6)*AC5)>>15;
	X2=(MC<<11)/(X1+MD);
	B5=X1+X2;
	TXBuff[0]=CommReg;
	TXBuff[1]=PressCode;
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 2, (uint32_t)1000);
	TXBuff[0]=Data;
	HAL_Delay(26);
	HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)0xEE, TXBuff, 1, (uint32_t)1000);
	HAL_I2C_Master_Receive(&hi2c2, (uint16_t)0xEE, tRXBuff, 3, (uint32_t)1000);
	UP=((tRXBuff[0]<<16)|(tRXBuff[1]<<8)|tRXBuff[2])>>5;
	B6 = B5 - 4000;
	X1 = (B2 * ((B6 * B6) >> 12)) >> 11;
	X2 = (AC2 * B6) >> 11;
	X3 = X1 + X2;
	B3 = (((AC1 * 4 + X3)<<3) + 2) >> 2;
	X1 = (AC3 * B6) >> 13;
	X2 = (B1 * ((B6 * B6) >> 12)) >> 16;
	X3 = ((X1 + X2) + 2) >> 2;
	B4 = (AC4 * (unsigned long)(X3 + 32768)) >> 15;
	B7 = ((unsigned long)UP - B3) * (50000>>3);
	if (B7 < 0x80000000) {p = (B7 * 2) / B4;}
		else {p = (B7 / B4) * 2;}
	X1 = (p >> 8) * (p >> 8);
	X1 = (X1 * 3038) >> 16;
	X2 = (-7357 * (p)) >> 16;
	p = p + ((X1 + X2 + 3791) >> 4);
	return (p);
}
