#include "main.h"

#define addr 0x5A; // or 5b if addr pin pull-up
#define stat 0x00;
#define mode 0x01;
#define data 0x02;
#define env_data 0x05;
#define app_start 0xF4;

void CCS811_init(void);
uint16_t CCS811_Get_eCO2 (void);// eCO2 in ppm
uint16_t CCS811_Get_TVOC (void);// TVOC in ppb
void CCS811_Change_Mode (uint8_t mod);
void CCS811_Add_Env_data (uint8_t humidity, uint8_t temperature);//first humidity, second temperature;
void CCS8811_Restart (void);
