/*******************************************************************************
File Name: HW_V1_config.c 
*******************************************************************************/
#include "Function.h"
#include "Menu.h"
#include "stm32f10x_it.h"
#include "stm32f10x_systick.h"
#include "HW_V1_Config.h"

volatile unsigned short Refresh_Counter, Delay_Counter;
volatile unsigned char Key_Buffer;

/*******************************************************************************
Function Name : NVIC_Configuration
Description : Configure DMA inbterrupt channel priority
*******************************************************************************/
void      NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = DMAChannel1_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
Function Name : Set_Range
Description : set the range of the voltage 
*******************************************************************************/
void     Set_Range(char Range)
{

   switch (Range)
   {
   case 0: // 10mV

   case 1: // 20mV

   case 2: // 50mV

   case 3: // 100mV

      RANGE_A_HIGH();
      RANGE_B_HIGH();
      RANGE_C_HIGH();
      RANGE_D_HIGH();
      break;
   case 4: // 200mV

   case 5: // 500mV

   case 6: // 1V

      RANGE_A_HIGH();
      RANGE_B_HIGH();
      RANGE_C_HIGH();
      RANGE_D_LOW();
      break;
   case 7: // 2V

   case 8: // 5V

   case 9: // 10V

      RANGE_A_LOW();
      RANGE_B_HIGH();
      RANGE_C_HIGH();
      RANGE_D_LOW();
      break;
   case 10: // 0.2V/Div £¨20mV ¡Á10/Div£© 

   case 11: // 0.5V/Div £¨50mV ¡Á10/Div£©

   case 12: // 1V/Div £¨0.1V ¡Á10/Div£©

      RANGE_A_HIGH();
      RANGE_B_LOW();
      RANGE_C_HIGH();
      RANGE_D_LOW();
      break;
   case 13: // 2V/Div £¨0.2V ¡Á10/Div£©

   case 14: // 5V/Div £¨0.5V ¡Á10/Div£©

   case 15: // 10V/Div £¨  1V ¡Á10/Div£©

      RANGE_A_LOW();
      RANGE_B_LOW();
      RANGE_C_HIGH();
      RANGE_D_LOW();
      break;
   case 16: // 20V/Div £¨ 2V ¡Á10/Div£©

   case 17: // 50V/Div £¨ 5V ¡Á10/Div£©

   case 18: // 100V/Div £¨10V ¡Á10/Div£©

      RANGE_A_HIGH();
      RANGE_B_HIGH();
      RANGE_C_LOW();
      RANGE_D_LOW();
      break;
   default: // Connected To GND

      RANGE_A_LOW();
      RANGE_B_LOW();
      RANGE_C_LOW();
      RANGE_D_LOW();
      break;
   }
}

/*******************************************************************************
Function Name : Set_Base
Description : set the base level of the Horizontal scan
Para : Base is the index of the Scan_PSC&Scan_ARR
*******************************************************************************/
void     Set_Base(char Base)
{
   TIM1_PSC = Scan_PSC[Base];
   TIM1_ARR = Scan_ARR[Base];
   TIM1_CCR1 = (Scan_ARR[Base] + 1) / 2;
}

void    ADC_Stop(void)
{
   DMA_CCR1 = 0x00000000; // disable DMA1
   ScanMode = 0;     // 0=idle, 1=pre-fetch, 2=trig-fetch, 3=post-fetch
}
/*******************************************************************************
Function Name : ADC_Start
Description : start the ADC sampling scan
*******************************************************************************/
void     ADC_Start(void)
{
   ADC_Stop(); // disable DMA1
   ScanSegment = 0;   // scan buffer has three virtual segments (pre-fetch, trig-seek and post-fetch)
   ScanMode = 1;     // 0=idle, 1=pre-fetch, 2=trig-seek, 3=post-fetch
   DMA_CPAR1 = ADC1_DR_ADDR; // base address of the peripheral's data register for DMA1
   DMA_CMAR1 = (u32)Scan_Buffer;
   DMA_CNDTR1 = SEGMENT_SIZE;
   DMA_CCR1 = 0x00003583; // enable DMA1
}
/*******************************************************************************
Function Name : Set_Y_Pos
Description : set the baseline of the no-voltage
Para : i is the index of the array, Y0 is the voltage 
*******************************************************************************/
void    Set_Y_Pos(unsigned short i, unsigned short Y0)
{
   TIM2_CCR4 = ((240 - Y0) * Y_POSm[i]) / 32 + Y_POSn[i];

}
/*******************************************************************************
Function Name : Test_USB_ON
Description : detect the USB status
Return:	 1: USB plug in, 0:USB plug out
*******************************************************************************/
char            Test_USB_ON(void)
{
   if (GPIOB_IDR & 0x0400)
      return 1;
   else
      return 0;
}

/*******************************************************************************
Function Name : SD_Card_ON
Description : detect the SD card status
Return:	 1: SD card plug in, 0:SD card plug out
*******************************************************************************/
char            SD_Card_ON(void)
{
   if (GPIOD_IDR & 0x0400)
      return 0;
   else
      return 1; // SD_Card_ON

}

/*******************************************************************************
 Delay ms
*******************************************************************************/
void Delayms(unsigned short delay)
{
  Delay_Counter = delay;
  while (Delay_Counter);
}

/*******************************************************************************
 wait for keypress
*******************************************************************************/
void WaitForKey(void)
{
  Key_Buffer = 0;
  while (!Key_Buffer);
}

/******************************** END OF FILE *********************************/
