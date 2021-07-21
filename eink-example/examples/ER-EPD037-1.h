/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/

#ifndef __EPD_037_1_H_
#define __EPD_037_1_H_

#include "DEV_Config.h"

// Display resolution
#define EPD_037_1_WIDTH       240
#define EPD_037_1_HEIGHT      416
UBYTE EPD_037_1_Init(void);
void EPD_037_1_Clear(void);
void EPD_037_1_Display(const UBYTE *blackimage, const UBYTE *ryimage);
void EPD_037_1_Sleep(void);

#endif
