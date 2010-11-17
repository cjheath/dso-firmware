/*******************************************************************************
* File Name: lcd.c
*******************************************************************************/
#include "Lcd.h"
#include "stm32f10x_it.h"
#include "HW_V1_Config.h"
#include "usb_lib.h"
#include "msd.h"

unsigned const short Char_Dot[760] =
{
   0x0000,0x0000,0x0000,0x001C,0x0020,0x0040,0x0040,0x0040,// "
   0x0040,0x0040,0x0020,0x001C,0x0000,0x0000,0x0000,0x0000,// #
   0x0000,0x0000,0x0000,0xE000,0x1000,0x0800,0x0800,0x0800,// $
   0x0C30,0x0C60,0x00C0,0x0180,0x0300,0x0630,0x0C30,0x0000,// %
   0x0800,0x0800,0x1000,0xE000,0x0000,0x0000,0x0000,0x0000,// &
   0x2010,0x2010,0x2010,0x2010,0x2010,0x2010,0x3FF0,0x0000,// ' Empty bottom
   0x0000,0x0000,0x0FC0,0x1FE0,0x3030,0x2010,0x0000,0x0000,// (
   0x0000,0x0000,0x2010,0x3030,0x1FE0,0x0FC0,0x0000,0x0000,// )
   0x0000,0x18C0,0x0D80,0x0700,0x0700,0x0D80,0x18C0,0x0000,// *
   0x0000,0x0100,0x0100,0x07C0,0x07C0,0x0100,0x0100,0x0000,// +
   0x0000,0x0000,0x0000,0xFFFC,0x0000,0x0000,0x0000,0x0000,// ,
   0x0000,0x0100,0x0100,0x0100,0x0100,0x0100,0x0100,0x0000,// -
   0x0000,0x0000,0x0000,0x0030,0x0030,0x0000,0x0000,0x0000,// .
   0x0030,0x0060,0x00C0,0x0180,0x0300,0x0600,0x0C00,0x0000,// /
   0x1FE0,0x3FF0,0x2090,0x2310,0x2410,0x3FF0,0x1FE0,0x0000,// 0
   0x0000,0x0810,0x1810,0x3FF0,0x3FF0,0x0010,0x0010,0x0000,// 1
   0x1070,0x30F0,0x2190,0x2310,0x2610,0x3830,0x1830,0x0000,// 2
   0x1020,0x3030,0x2210,0x2210,0x2210,0x3FF0,0x1DE0,0x0000,// 3
   0x0300,0x0700,0x0D00,0x1910,0x3FF0,0x3FF0,0x0110,0x0000,// 4
   0x3E20,0x3E30,0x2210,0x2210,0x2310,0x23F0,0x21E0,0x0000,// 5
   0x0FE0,0x1FF0,0x3210,0x2210,0x2210,0x03F0,0x01E0,0x0000,// 6
   0x3000,0x3000,0x20F0,0x21F0,0x2300,0x3E00,0x3C00,0x0000,// 7
   0x1DE0,0x3FF0,0x2210,0x2210,0x2210,0x3FF0,0x1DE0,0x0000,// 8
   0x1C00,0x3E10,0x2210,0x2210,0x2230,0x3FE0,0x1FC0,0x0000,// 9
   0x0000,0x0000,0x0000,0x0C60,0x0C60,0x0000,0x0000,0x0000,// :
   0x0040,0x0040,0x0040,0x0040,0x0040,0x0040,0x0040,0x0040,// ;
   0x0000,0x0100,0x0380,0x06C0,0x0C60,0x1830,0x1010,0x0000,// <
   0x0240,0x0240,0x0240,0x0240,0x0240,0x0240,0x0240,0x0000,// =
   0x0000,0x1010,0x1830,0x0C60,0x06C0,0x0380,0x0100,0x0000,// >
   0x1800,0x3800,0x2000,0x23B0,0x27B0,0x3C00,0x1800,0x0000,// ?
   0x0FC0,0x1020,0x2790,0x2490,0x27D0,0x1050,0x0F80,0x0000,// @
   0x07F0,0x0FF0,0x1900,0x3100,0x1900,0x0FF0,0x07F0,0x0000,// A
   0x2010,0x3FF0,0x3FF0,0x2210,0x2210,0x3FF0,0x1DE0,0x0000,// B
   0x0FC0,0x1FE0,0x3030,0x2010,0x2010,0x3030,0x1860,0x0000,// C
   0x2010,0x3FF0,0x3FF0,0x2010,0x3030,0x1FE0,0x0FC0,0x0000,// D
   0x2010,0x3FF0,0x3FF0,0x2210,0x2710,0x3030,0x3870,0x0000,// E
   0x2010,0x3FF0,0x3FF0,0x2210,0x2700,0x3000,0x3800,0x0000,// F
   0x0FC0,0x1FE0,0x3030,0x2110,0x2110,0x31E0,0x19F0,0x0000,// G
   0x3FF0,0x3FF0,0x0200,0x0200,0x0200,0x3FF0,0x3FF0,0x0000,// H
   0x0000,0x0000,0x2010,0x3FF0,0x3FF0,0x2010,0x0000,0x0000,// I
   0x00E0,0x00F0,0x0010,0x2010,0x3FF0,0x3FE0,0x2000,0x0000,// J
   0x2010,0x3FF0,0x3FF0,0x0300,0x0F00,0x3CF0,0x3070,0x0000,// K
   0x2010,0x3FF0,0x3FF0,0x2010,0x0010,0x0030,0x0030,0x0000,// L
   0x3FF0,0x3FF0,0x1C00,0x0E00,0x1C00,0x3FF0,0x3FF0,0x0000,// M
   0x3FF0,0x3FF0,0x1C00,0x0E00,0x0700,0x3FF0,0x3FF0,0x0000,// N
   0x0FC0,0x1FE0,0x3030,0x2010,0x3030,0x1FE0,0x0FC0,0x0000,// O
   0x2010,0x3FF0,0x3FF0,0x2210,0x2200,0x3E00,0x1C00,0x0000,// P
   0x1FE0,0x3FF0,0x2010,0x2070,0x2030,0x3FF8,0x1FE8,0x0000,// Q
   0x2010,0x3FF0,0x3FF0,0x2200,0x2300,0x3FF0,0x1CF0,0x0000,// R
   0x1860,0x3C70,0x2610,0x2210,0x2310,0x39F0,0x18E0,0x0000,// S
   0x0000,0x3800,0x3010,0x3FF0,0x3FF0,0x3010,0x3800,0x0000,// T
   0x3FE0,0x3FF0,0x0010,0x0010,0x0010,0x3FF0,0x3FE0,0x0000,// U
   0x3F80,0x3FC0,0x0060,0x0030,0x0060,0x3FC0,0x3F80,0x0000,// V
   0x3FC0,0x3FF0,0x0070,0x01C0,0x0070,0x3FF0,0x3FC0,0x0000,// W
   0x3030,0x3CF0,0x0FC0,0x0300,0x0FC0,0x3CF0,0x3030,0x0000,// X
   0x0000,0x3C00,0x3E10,0x03F0,0x03F0,0x3E10,0x3C00,0x0000,// Y
   0x3870,0x30F0,0x2190,0x2310,0x2610,0x3C30,0x3870,0x0000,// Z
   0x0010,0x0030,0x0050,0x0190,0x0310,0x0C10,0x3FF0,0x0000,// [ Delta
   0x0800,0x0800,0x0800,0x0800,0x0800,0x0800,0x0800,0x0800,/* \ */
   0x0000,0x0000,0x0000,0xFC7C,0x0280,0x0280,0x0100,0x0100,// ]
   0x0200,0x0400,0x0C00,0x1FF0,0x3FF0,0x0C00,0x0400,0x0200,// ^ Rising edge
   0x0100,0x0080,0x00C0,0x3FE0,0x3FF0,0x00C0,0x0080,0x0100,// _ Falling edge
   0x2010,0x2010,0x2010,0x2010,0x2010,0x2010,0x2010,0x2010,// ` Empty body
   0x00E0,0x05F0,0x0510,0x0510,0x07E0,0x03F0,0x0010,0x0000,// a
   0x2010,0x3FF0,0x3FE0,0x0210,0x0210,0x03F0,0x01E0,0x0000,// b
   0x03E0,0x07F0,0x0410,0x0410,0x0410,0x0630,0x0220,0x0000,// c
   0x01E0,0x03F0,0x0610,0x2410,0x3FF0,0x3FF0,0x0010,0x0000,// d
   0x03E0,0x07F0,0x0510,0x0510,0x0510,0x0730,0x0320,0x0000,// e
   0x0000,0x0210,0x1FF0,0x3FF0,0x2210,0x3000,0x1800,0x0000,// f
   0x03C8,0x07EC,0x0424,0x0424,0x03FC,0x07F8,0x0400,0x0000,// g
   0x2010,0x3FF0,0x3FF0,0x0220,0x0400,0x07F0,0x03F0,0x0000,// h
   0x0000,0x0000,0x0410,0x37F0,0x37F0,0x0010,0x0000,0x0000,// i
   0x0000,0x0018,0x001C,0x0404,0x37FC,0x37F8,0x0400,0x0000,// j
   0x2010,0x3FF0,0x3FF0,0x2180,0x03C0,0x0670,0x0430,0x0000,// k
   0x0000,0x0000,0x2010,0x3FF0,0x3FF0,0x0010,0x0000,0x0000,// l
   0x07F0,0x07F0,0x0600,0x03F0,0x0600,0x07F0,0x07F0,0x0000,// m
   0x0400,0x07F0,0x03F0,0x0400,0x0400,0x07F0,0x03F0,0x0000,// n
   0x03E0,0x07F0,0x0410,0x0410,0x0410,0x07F0,0x03E0,0x0000,// o
   0x0404,0x07FC,0x03FC,0x0444,0x0440,0x07C0,0x0380,0x0000,// p
   0x0380,0x07C0,0x0440,0x0444,0x07FC,0x03FC,0x0404,0x0000,// q
   0x0410,0x07F0,0x03F0,0x0610,0x0400,0x0600,0x0300,0x0000,// r
   0x0000,0x0220,0x0730,0x0590,0x0490,0x06F0,0x0260,0x0000,// s
   0x0400,0x0400,0x1FE0,0x3FF0,0x0410,0x0430,0x0020,0x0000,// t
   0x07E0,0x07F0,0x0010,0x0010,0x07E0,0x07F0,0x0010,0x0000,// u
   0x0000,0x07C0,0x07E0,0x0030,0x0030,0x07E0,0x07C0,0x0000,// v
   0x07E0,0x07F0,0x0030,0x00E0,0x0030,0x07F0,0x07E0,0x0000,// w
   0x0410,0x0630,0x03E0,0x01C0,0x03E0,0x0630,0x0410,0x0000,// x
   0x0780,0x07C4,0x0044,0x0044,0x0044,0x07F8,0x07F0,0x0000,// y
   0x0630,0x0670,0x04D0,0x0590,0x0710,0x0630,0x0430,0x0000,// z
   0x0780,0x0480,0x3CF0,0x2010,0x2FD0,0x2FD0,0x2FD0,0x2FD0,// { Battery head
   0x2FD0,0x2FD0,0x2FD0,0x2FD0,0x2FD0,0x2FD0,0x2FD0,0x2FD0,// | Battery body
   0x2FD0,0x2FD0,0x2FD0,0x2FD0,0x2FD0,0x2010,0x3FF0,0x0000,// } Battery bottom
   0x0780,0x0480,0x3CF0,0x2010,0x2010,0x2010,0x2010,0x2010 // ~ Empty head
};                                            

unsigned const short Logo_Dot[] = {
  7,38,
  0xfc00,0x00ff,0x0000,0x0000,0x0000,0xfffe,0x0001,
  0xff00,0x03ff,0x0000,0x0000,0x0000,0xffff,0x0001,
  0xffc0,0x0fff,0x0000,0x0000,0x8000,0xffff,0x0001,
  0xffe0,0x0fff,0x0000,0x0000,0xc000,0xffff,0x0001,
  0xfff0,0x1fff,0x0000,0x0000,0xc000,0xffff,0x0001,
  0xfff8,0x1ffd,0x0000,0x0000,0xc000,0xffff,0x0000,
  0xfff8,0x1ffc,0x0000,0x0000,0x0000,0x0ffc,0x0000,
  0xfff8,0x1ff8,0x0000,0x0000,0x0000,0x0ffe,0x0000,
  0xfff8,0x1ff8,0x0000,0x0000,0x0000,0x07fe,0x0000,
  0x7fc0,0x1ffc,0xfe00,0x0000,0x0000,0x07fe,0x0000,
  0x7fe0,0x1ffc,0xff80,0x3e01,0x0000,0x07ff,0x0000,
  0x7fe0,0x0ffc,0xffc0,0x3f03,0x0000,0x03ff,0x0000,
  0x7ff0,0x07fe,0xffe0,0x7f83,0x8000,0x03ff,0x0000,
  0x3ff0,0x03ff,0xf7f0,0x7f83,0x81f0,0x03ff,0x0000,
  0x3ff0,0x01ff,0xf3f8,0x3fc3,0x81f8,0x01ff,0x0000,
  0xfff8,0x007f,0xf3fc,0x3fc3,0xc1fc,0xffff,0x0000,
  0xfff8,0x00ff,0xf9fc,0x3fe3,0xc1fe,0xffff,0x0000,
  0xfff8,0x03ff,0xf9fe,0x3fe3,0xc1ff,0xffff,0x0000,
  0xfffc,0x0fff,0xf9ff,0xbfe1,0xe1ff,0xffff,0x0000,
  0x8ffc,0x0fff,0xf8ff,0xdff1,0xe1ff,0x7fff,0x0000,
  0x0ffc,0x1ffe,0xfcff,0xfff0,0xe1ff,0x3fff,0x0000,
  0x0ffe,0x9ffc,0xfcff,0xfff0,0xe1ff,0x007f,0x0000,
  0x07fe,0x9ffc,0x7e7f,0xfff0,0xf1ff,0x007f,0x0000,
  0x07fe,0x9ff8,0x3f7f,0xfff8,0xf1fe,0x003f,0x0000,
  0x07fe,0x9ff8,0xcfff,0x7ffb,0xf1fe,0x003f,0x0000,
  0x03ff,0x9ffc,0xf7ff,0x3ffb,0xf9fe,0x003f,0x0000,
  0x03ff,0x9ffc,0xfcff,0x1ff9,0xfbfe,0x001f,0x0000,
  0x01ff,0x8ffc,0xffff,0x0ff8,0xfbfe,0x001f,0x0000,
  0x01ff,0x87fe,0x7fff,0x07f8,0xfbfe,0x000f,0x0000,
  0x00ff,0x07fe,0x3fff,0x03f8,0xfbfc,0x0007,0x0000,
  0x00ff,0x03ff,0x0fff,0x03f8,0xfbfc,0x0003,0x0000,
  0xc7ff,0x00ff,0x03fc,0x01f0,0xf1f8,0x0001,0x0000,
  0xfff8,0x007f,0x0000,0x0000,0x0000,0x0000,0x0000,
  0xfffc,0x003f,0x0000,0x0000,0x0000,0x0000,0x0000,
  0xfffc,0x000f,0x0000,0x0000,0x0000,0x0000,0x0000,
  0xfffc,0x0003,0x0000,0x0000,0x0000,0x0000,0x0000,
  0xfff8,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
  0x3ff0,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
};

unsigned const char Ref_Buffer[304] = {
   100,116,130,144,157,167,175,181,185,185,184,179,173,164,153,141,128,114,100,86, 73, 60, 49, 40, 33, 27, 24, 24, 25, 29,
   35, 43, 52, 63, 75, 87, 100,112,124,135,145,153,160,164,167,167,166,163,157,150,142,133,122,111,100,89, 79, 70, 61, 54,
   48, 44, 42, 42, 43, 46, 50, 57, 64, 72, 81, 90, 100,109,118,126,133,139,144,147,149,149,148,146,142,137,130,124,116,108,
   100,93, 85, 79, 73, 68, 64, 61, 60, 60, 61, 63, 66, 70, 75, 81, 87, 93, 100,106,112,117,122,125,128,130,131,131,131,129,
   126,123,119,115,110,105,100,96, 91, 88, 84, 81, 79, 78, 77, 78, 78, 80, 82, 84, 87, 90, 93, 97, 100,103,106,108,110,112,
   113,114,114,113,113,112,110,109,107,105,104,102,100,99, 97, 96, 96, 95, 95, 95, 95, 96, 96, 97, 97, 98, 99, 99, 100,100,
   100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
   100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,115,129,141,151,160,165,169,170,169,167,162,156,148,139,130,
   120,110,100,91, 82, 75, 68, 63, 59, 57, 56, 56, 58, 61, 64, 69, 75, 81, 87, 94, 100,106,112,117,121,125,127,129,130,130,
   128,127,124,121,117,113,109,104,100,96, 92, 88, 85, 83, 81, 80, 79, 79, 80, 81, 83, 85, 88, 91, 94, 97, 100,103,106,108,
   108,108,6,8
 };

unsigned short Get_Font_8x14(unsigned char chr, unsigned char row)
{
  unsigned  short idx = (chr - 0x22) * 8;
  
  return Char_Dot[idx + row];
}

unsigned char Get_Ref_Wave(unsigned short idx)
{
  return Ref_Buffer[idx];
}

/*******************************************************************************
 LCD_WR_REG: Set LCD Register  Input: Register addr., Data
*******************************************************************************/
void LCD_WR_REG(unsigned short Reg, unsigned short Data) 
{
  LDC_DATA_OUT=Reg;     //Reg. Addr.
  LCD_RS_LOW();         //RS=0,Piont to Index Reg.
  LCD_nWR_ACT();        //WR Cycle from 1 -> 0 -> 1
  LCD_RS_HIGH();        //RS=1,Piont to object Reg.
  LDC_DATA_OUT=Data;    //Reg. Data 
  LCD_nWR_ACT();        //WR Cycle from 1 -> 0 -> 1
}

/*******************************************************************************
 LCD  initializtion 
*******************************************************************************/
void LCD_Initial(void)
{   
  //------------------------- Reset LCD Driver ---------------------//
  LCD_DATA_BUS_OUT();   //Set LCD Data Bus as Output Mode
  LCD_nWR_HIGH();
  LCD_nRD_HIGH();       
  LCD_RS_HIGH();        //RS=1        
  LCD_nRST_HIGH(); 
  Delayms(1);           //RST=1��Delay 1ms      
  LCD_nRST_LOW(); 
  Delayms(1);          //RST=0 Reset LCD��Delay 1ms      
  LCD_nRST_HIGH(); 
  Delayms(5);          //RST=1��Delay 5 ms  
 //----------------ST7781 Internal Register Initial------------//         
  LCD_WR_REG(0x00FF, 0x0001);  
  LCD_WR_REG(0x00F3, 0x0008);  
  LDC_DATA_OUT=0x00F3;     
  LCD_RS_LOW();         
  LCD_nWR_ACT();       //Read Parameter      
  LCD_RS_HIGH();        
 //-------------------Display Control Setting-----------------//
  LCD_WR_REG(0x0001, 0x0100);    //Output Direct 
  LCD_WR_REG(0x0002, 0x0700);    //Line Inversion
  LCD_WR_REG(0x0003, 0x0030);    //BGR=0,ID=11
  LCD_WR_REG(0x0008, 0x0302);    //Porch Setting
  LCD_WR_REG(0x0009, 0x0000);    //Scan Cycle
  LCD_WR_REG(0x000A, 0x0000);    //FMARK off
 //----------------power Control Register Initial------------//
  LCD_WR_REG(0x0010, 0x0790);    //Power Control1
  LCD_WR_REG(0x0011, 0x0005);    //Power Control2
  LCD_WR_REG(0x0012, 0x0000);    //Power Control3
  LCD_WR_REG(0x0013, 0x0000);    //Power Control4
  Delayms(100);                  //Delay 100ms   
  LCD_WR_REG(0x0010, 0x12B0);    //Power Control1
  Delayms(50);                   //delay 50ms
  LCD_WR_REG(0x0011, 0x0007);    //Power Control2
  Delayms(50);                   //delay 50ms
  LCD_WR_REG(0x0012, 0x008C);    //Power Control3
  LCD_WR_REG(0x0013, 0x1700);    //Power Control4
  LCD_WR_REG(0x0029, 0x001A);    //VCOMH Setting
  Delayms(50);                   //delay 50ms
 //------------------GAMMA Cluster Setting-------------------//
  LCD_WR_REG(0x0030, 0x0000);
  LCD_WR_REG(0x0031, 0x0507);
  LCD_WR_REG(0x0032, 0x0003);
  LCD_WR_REG(0x0035, 0x0200);
  LCD_WR_REG(0x0036, 0x0106);
  LCD_WR_REG(0x0037, 0x0000);
  LCD_WR_REG(0x0038, 0x0507);
  LCD_WR_REG(0x0039, 0x0104);
  LCD_WR_REG(0x003C, 0x0200);
  LCD_WR_REG(0x003D, 0x0005);
 //------------------Display Windows 240*320-----------------//
  LCD_WR_REG(0x0050, 0x0000);
  LCD_WR_REG(0x0051, 0x00EF);
  LCD_WR_REG(0x0052, 0x0000);
  LCD_WR_REG(0x0053, 0x013F);
 //--------------------Frame Rate Setting--------------------//
  LCD_WR_REG(0x0060, 0xA700);
  LCD_WR_REG(0x0061, 0x0001);
  LCD_WR_REG(0x0090, 0x0033);
  LCD_WR_REG(0x0007, 0x0133);
  Delayms(50);                   //delay 50ms
}

/*******************************************************************************
Point_SCR: Set display position   Input: X, Y 
*******************************************************************************/
void Point_SCR(unsigned short x0, unsigned short y0) 
{
  LCD_WR_REG(0x0020,y0);
  LCD_WR_REG(0x0021,x0);
  LDC_DATA_OUT=0x0022;  //DRAM Reg.      
  LCD_RS_LOW();             
  LCD_nWR_ACT();        //WR Cycle from 1 -> 0 -> 1
  LCD_nWR_ACT();        //WR Cycle from 1 -> 0 -> 1
  LCD_RS_HIGH();            
}
/*******************************************************************************
 Set_Pixel: Set a Pixel  Input: Color
*******************************************************************************/
void Set_Pixel(unsigned short Color) 
{
  LDC_DATA_OUT=Color;   //Color Data
  LCD_nWR_ACT();        //WR Cycle from 1 -> 0 -> 1
}
/*******************************************************************************
 Clear Screen 
*******************************************************************************/
void Clear_Screen(unsigned short Color)						
{ 
  unsigned int i; 
  Point_SCR(0, 0);    //X_pos=0, Y_pos=0
  for(i=0;i<240*320;++i) Set_Pixel(Color);
}
/*******************************************************************************
 Display_Str: Display String   Input: x, y , Color, Mode, String  
*******************************************************************************/
void Display_Str(unsigned short x0, unsigned short y0, unsigned short Color, unsigned char Mode, unsigned const char *s)
{ 
  signed short i, j, b; 
  Point_SCR(x0, y0);
  for (j=0; j<14;++j) { 
    Set_Pixel(Mode?Color:BLACK);
  }
  x0++;        
  while (*s!=0) {
    unsigned const short *scanline=Char_Dot+((*s-0x22)*8);
    for(i=0;i<8;++i){
      Point_SCR(x0+i, y0);
      if((*s==0x20)||(*s==0x21)) b=0x0000;
      else                       b=scanline[i];
      if((*s==0x21)&&(i==4)) break;
      for(j=0;j<14;++j){
        if (b&4) {
          Set_Pixel(Mode?BLACK:Color);
        } else {
          Set_Pixel(Mode?Color:BLACK);
        }
        b>>=1;
      }
    }
    if(*s==0x21) x0 +=4;       
    else  x0 += 8;             
    ++s;                           //next character
  }
}
/*******************************************************************************
 Display_Logo: Display Logo   Input: X, Y 
*******************************************************************************/
void Display_Logo(unsigned short Dot_x, unsigned short Dot_y)
{ 
  unsigned short i, j, k, l, Color, b;

  Color = BLUE;
  k = 2;
  for (j=0; j < Logo_Dot[1]; j++) {
    for (i=0; i < Logo_Dot[0]; i++) {
      b = Logo_Dot[k];
      for (l = 0; l < 16; l++) {
        if (b & 1) {
          Point_SCR(Dot_x + i * 16 + l, Dot_y + Logo_Dot[1] - j);
          Set_Pixel(Color);
        }
        b =  b >> 1;
        if (b == 0) break;
      }
      k++;
    }
  }
  
  Color = WHITE;
  for (i=0; i<320; ++i)
  {
    Point_SCR(i, 0);
    Set_Pixel(Color);
    Point_SCR(i, 239);
    Set_Pixel(Color);
  }

  for (i=3; i<317; ++i)
  {
    Point_SCR(i, 3);
    Set_Pixel(Color);
    Point_SCR(i, 236);
    Set_Pixel(Color);
  }

  Point_SCR(0, 0);
  for (j=0; j<240; ++j) Set_Pixel(Color);
  Point_SCR(3, 3);
  for (j=3; j<237; ++j) Set_Pixel(Color);
  Point_SCR(316, 3);
  for (j=3; j<237; ++j) Set_Pixel(Color);
  Point_SCR(319, 0);
  for (j=0; j<240; ++j) Set_Pixel(Color);
}


void Display_Info(unsigned short x0, unsigned short y0, char *Pre, long Num)
{
  char  buf[10], n = 0, k, str[2] = {'-', 0};
  
  if (Pre) {
    char *p = Pre;
    while (*p) p++;
    Display_Str(x0, y0, WHITE, PRN, (unsigned char const *)Pre);
    x0 += (p - Pre) * 8 + 8;
  }

  if (Num < 0) {
    Display_Str(x0, y0, WHITE, PRN, (unsigned char const *)str);
    x0 += 8;
    Num = -Num;
  }

  do {  
    buf[n++] = Num % 10;
    Num /= 10;
  } while (Num > 0);

  k = n;
  
  for (; n > 0; n--) {
    str[0] = '0' + buf[n - 1];
    Display_Str(x0, y0, WHITE, PRN, (unsigned char const *)str);
    x0 += 8;
  }
  
  str[0] = ' ';
  while (k < 10) {
    Display_Str(x0, y0, WHITE, PRN, (unsigned char const *)str);
    x0 += 8;
    k++;
  }
  
}

/******************************** END OF FILE *********************************/
