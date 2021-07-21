/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/

#include "ER-EPD037-1.h"
#include "Debug.h"

/******************************************************************************
function :	Software reset
parameter:
******************************************************************************/
static void EPD_037_1_Reset(void)
{
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
    DEV_Digital_Write(EPD_RST_PIN, 0);
    DEV_Delay_ms(10);
    DEV_Digital_Write(EPD_RST_PIN, 1);
    DEV_Delay_ms(200);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void EPD_037_1_SendCommand(UBYTE Reg)
{
    DEV_Digital_Write(EPD_DC_PIN, 0);
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_SPI_WriteByte(Reg);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void EPD_037_1_SendData(UBYTE Data)
{ 
    DEV_Digital_Write(EPD_CS_PIN, 0);
    DEV_Digital_Write(EPD_DC_PIN, 1);
    DEV_SPI_WriteByte(Data);
    DEV_Digital_Write(EPD_CS_PIN, 1);
}

/******************************************************************************
function :	Wait until the busy_pin goes LOW
parameter:
******************************************************************************/
void EPD_037_1_WaitUntilIdle(void)
{
    Debug("e-Paper busy\r\n");
    while(DEV_Digital_Read(EPD_BUSY_PIN)==0){
        DEV_Delay_ms(10);
    }
    DEV_Delay_ms(200);      
    Debug("e-Paper busy release\r\n");
}

/******************************************************************************
function :	Turn On Display
parameter:
******************************************************************************/
static void EPD_037_1_TurnOnDisplay(void)
{
  

    EPD_037_1_SendCommand(0x12);
    DEV_Delay_ms(100);        
    EPD_037_1_WaitUntilIdle();       //waiting for the electronic paper IC to release the idle signal

}

/******************************************************************************
function :	Initialize the e-Paper register
parameter:
******************************************************************************/
UBYTE EPD_037_1_Init(void)
{
    EPD_037_1_Reset();

 
   EPD_037_1_SendCommand(0x01);  //vdh 11v vdl -11v vdhr 3.4v
   EPD_037_1_SendData(0x2f);
   EPD_037_1_SendData(0x04);//04=17v   05=18v  06
   EPD_037_1_SendData(0x30);
   EPD_037_1_SendData(0x30);//3F=15V  30=12V
   EPD_037_1_SendData(0x0F); //24=9.6V  1D=8.2V   12=6V  0f=5.4V
   
   EPD_037_1_SendCommand(0x06);
   EPD_037_1_SendData(0x17);
   EPD_037_1_SendData(0x17);
   EPD_037_1_SendData(0x17);
   EPD_037_1_WaitUntilIdle(); 

   
   EPD_037_1_SendCommand(0x00);
   EPD_037_1_SendData(0x0F);     //BWR mode
 

    EPD_037_1_SendCommand(0x61);
    EPD_037_1_SendData(0xF0);  //240
    EPD_037_1_SendData(0x01);
    EPD_037_1_SendData(0xA0);  //416
	
    EPD_037_1_SendCommand(0x04);
    EPD_037_1_WaitUntilIdle(); 
   
    EPD_037_1_SendCommand(0x30);
    EPD_037_1_SendData(0x09); //set 100hz

   
   EPD_037_1_SendCommand(0x82);
   EPD_037_1_SendData(0x26); //vcom -2.0v

    EPD_037_1_WaitUntilIdle();      


    return 0;
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void EPD_037_1_Clear(void)
{
 UWORD Width, Height;
    Width =(EPD_037_1_WIDTH % 8 == 0)?(EPD_037_1_WIDTH / 8 ):(EPD_037_1_WIDTH / 8 + 1);
    Height = EPD_037_1_HEIGHT;

    UWORD i;
    EPD_037_1_SendCommand(0x10);
    for(i=0; i<Width*Height; i++) {
        EPD_037_1_SendData(0xff);

    }
    EPD_037_1_SendCommand(0x13);
    for(i=0; i<Width*Height; i++)	{
        EPD_037_1_SendData(0x00);

    }
    EPD_037_1_TurnOnDisplay();


}




/******************************************************************************
function :	Sends the image buffer in RAM to e-Paper and displays
parameter:
******************************************************************************/
void EPD_037_1_Display(const UBYTE *blackimage, const UBYTE *ryimage)
{
     UDOUBLE Width, Height,j,i;
    Width =(EPD_037_1_WIDTH % 8 == 0)?(EPD_037_1_WIDTH / 8 ):(EPD_037_1_WIDTH / 8 + 1);
    Height = EPD_037_1_HEIGHT;
  
 //send black data
    EPD_037_1_SendCommand(0x10);
    for ( j = 0; j < Height; j++) {
        for ( i = 0; i < Width; i++) {
            EPD_037_1_SendData(blackimage[i + j * Width]);
        }
    }
 

    //send red data
    EPD_037_1_SendCommand(0x13);
    for ( j = 0; j < Height; j++) {
        for ( i = 0; i < Width; i++) {
            EPD_037_1_SendData(~ryimage[i + j * Width]);
        }
    }

    EPD_037_1_TurnOnDisplay();
}



/******************************************************************************
function :	Enter sleep mode
parameter:
******************************************************************************/
void EPD_037_1_Sleep(void)
{
    EPD_037_1_SendCommand(0x02); // POWER OFF
    EPD_037_1_WaitUntilIdle();

    EPD_037_1_SendCommand(0x07);  	//deep sleep
    EPD_037_1_SendData(0xA5);

}
