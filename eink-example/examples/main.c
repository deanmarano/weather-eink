/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
Examples for ER-EPD037-1Y
Display is Hardward SPI 4-Wire SPI Interface 
Tested and worked with: 
Works with Raspberry pi
****************************************************/
#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "ER-EPD037-1.h"
#include "DEV_Config.h"
#include "GUI_Paint.h"
#include "GUI_BMPfile.h"
#include "ImageData.h"
#include "Debug.h"
#include <time.h> 

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    DEV_Module_Exit();

    exit(0);
}



int main(void)
{
    
    signal(SIGINT, Handler);


  printf("EPD_037_1_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
    EPD_037_1_Init();

    struct timespec start={0,0}, finish={0,0}; 
    clock_gettime(CLOCK_REALTIME,&start);

    EPD_037_1_Clear();

    clock_gettime(CLOCK_REALTIME,&finish);
    printf("%ld S\r\n",finish.tv_sec-start.tv_sec);

    DEV_Delay_ms(500);

    //Create a new image cache named IMAGE_BW and fill it with white
    UBYTE *BlackImage, *RYImage;
    UWORD Imagesize = ((EPD_037_1_WIDTH % 8 == 0)? (EPD_037_1_WIDTH / 8 ): (EPD_037_1_WIDTH / 8 + 1)) * EPD_037_1_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize )) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    if((RYImage = (UBYTE *)malloc(Imagesize )) == NULL) {
        printf("Failed to apply for red memory...\r\n");
        return -1;
    }
    printf("NewImage:BlackImage and RYImage\r\n");
    Paint_NewImage(BlackImage, EPD_037_1_WIDTH, EPD_037_1_HEIGHT , 0, WHITE);
    Paint_NewImage(RYImage, EPD_037_1_WIDTH, EPD_037_1_HEIGHT , 0, WHITE);

    //Select Image
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_SelectImage(RYImage);
    Paint_Clear(WHITE);

#if 1   // show bmp

    printf("show red bmp------------------------\r\n");
    Paint_SelectImage(BlackImage);
    GUI_ReadBmp("./pic/037-1yb1.bmp", 0, 0);
    Paint_SelectImage(RYImage);
    GUI_ReadBmp("./pic/037-1yy1.bmp", 0, 0);
    EPD_037_1_Display(BlackImage, RYImage);

#endif

#if 0
    DEV_Delay_ms(3000);
    printf("show red bmp------------------------\r\n");
    Paint_SelectImage(BlackImage);
    GUI_ReadBmp("./pic/037-1rb2.bmp", 0, 0);
    Paint_SelectImage(RYImage);
    GUI_ReadBmp("./pic/037-1rr2.bmp", 0, 0);
    EPD_037_1_Display(BlackImage, RYImage);
    DEV_Delay_ms(3000);

    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_SelectImage(RYImage);
    Paint_Clear(WHITE);
    printf("show window BMP-----------------\r\n");
    Paint_SelectImage(BlackImage);
    GUI_ReadBmp("./pic/100x100.bmp", 50, 50);
    Paint_SelectImage(RYImage);
    Paint_Clear(WHITE);    
    EPD_037_1_Display(BlackImage, RYImage);
    DEV_Delay_ms(3000);


#endif    
    
#if 0  // show image for array    
    printf("show image for array\r\n");
    EPD_037_1_Display(gImage_037_1_b, gImage_037_1_ry);
    DEV_Delay_ms(3000);
#endif

#if 0   // Drawing on the image
    /*Horizontal screen*/
    //1.Draw black image
    Paint_NewImage(BlackImage, EPD_037_1_WIDTH, EPD_037_1_HEIGHT , 0, WHITE);
    Paint_Clear(WHITE);

   Paint_DrawPoint(25, 50, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 70, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 90, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawPoint(25, 110, BLACK, DOT_PIXEL_4X4, DOT_STYLE_DFT);

    Paint_DrawLine(50, 50, 120, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(120, 50, 50, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(85, 215, 85, 285, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(50, 250, 120, 250, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);

    Paint_DrawString_EN(10, 350, "www.buydisplay.com", &Font16, BLACK, WHITE);
     
    //Draw red/yellow picture
    Paint_NewImage(RYImage, EPD_037_1_WIDTH, EPD_037_1_HEIGHT , 0, WHITE); 
    Paint_Clear(WHITE);
    
    Paint_DrawRectangle(50, 50, 120, 120, RED, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(140, 50, 210, 120, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);

    Paint_DrawCircle(85, 250, 35, RED, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(175, 250, 35, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);


    Paint_DrawString_EN(10, 310, "hello! EPD", &Font24, WHITE, BLACK);
    Paint_DrawString_EN(10, 380, "123456789", &Font24, RED, WHITE);

  
  printf("EPD_Display\r\n");
    EPD_037_1_Display(BlackImage, RYImage);
    DEV_Delay_ms(3000);

    printf("Clear...\r\n");
    EPD_037_1_Clear();
#endif

    printf("Goto Sleep...\r\n");
    EPD_037_1_Sleep();
    free(BlackImage);
    free(RYImage);
    BlackImage = NULL;
    RYImage = NULL;

    DEV_Module_Exit();
    
    return 0;  
    
  
}
