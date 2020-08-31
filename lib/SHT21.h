#include "main.h"

#define phcode  0xf5;
#define ur  0xe7;
#define tcode 0xf3;
#define rest  0xFE;

float SHT21_get_Ph (void);//return Ph in %
float SHT21_get_Temperature (void);//return temperature in Celsium
uint8_t SHT21_get_UR (void);//read UserRegister
void SHT21_restart(void);//restart sensor
