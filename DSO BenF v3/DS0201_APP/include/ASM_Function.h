/*******************************************************************************
 file name  : ASM_Function.h
 *******************************************************************************/

#ifndef __ASM_FUNCTION_H
#define __ASM_FUNCTION_H

void            __CTR_HP(void);
void            __USB_Istr(void);

u8              __MSD_WriteBlock(u8 * pBuffer, u32 WriteAddr, u16 NumByteToWrite);
u8              __MSD_ReadBlock(u8 * pBuffer, u32 ReadAddr, u16 NumByteToRead);
u16             __Get_Font_8x14(u8 Code, u16 Row);
u8              __Get_Ref_Wave(u16 i);
void            __SD_Set_Changed(void);

void            __Erase_Color(u16 x, u16 y, u16 Color);
void            __Add_Color(u16 x, u16 y, u16 Color);
u16             __Get_Pixel(u16 x0, u16 y0);

#endif
                       
//****************************** END OF FILE ***********************************
