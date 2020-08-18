#include "main.h"

#define addr 0xEE;
#define Data 0xF6;
#define test 0xD0;
#define TempCode 0x2E;
#define PressCode 0xF4;
#define CommReg 0xF4;
#define AddrCalib 0xAA;

void BMP180_init(void);
int16_t BMP180_get_UP(void);
int16_t BMP180_get_UT(void);
int16_t BMP180_get_Temperature(void);
uint32_t BMP180_get_Press(void);
