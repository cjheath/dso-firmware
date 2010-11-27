/* ******************************************************************************* */
/*  File name  : ASM_Function.s  */
/*  File description: start addresses for exported functions */
/* ******************************************************************************* */

#ifdef __GNUC__
#define EXPORT .globl
#define EXTERN .extern
#define THUMBFUNC .thumb_func
#else
#define THUMBFUNC
#endif

  EXTERN USB_Istr
  EXTERN CTR_HP
  EXTERN MSD_WriteBlock
  EXTERN MSD_ReadBlock
  EXTERN Get_Font_8x14
  EXTERN Get_Ref_Wave
  EXTERN SD_Set_Changed
  
  EXPORT __BRANCH_TABLE
  
#ifdef __GNUC__
.cpu cortex-m3
.syntax unified
.thumb
.text
#else
  RSEG CODE:CODE(2)
#endif
  
/* ******************************************************************************* */
/*  Table of library function start addresses */
/* ******************************************************************************* */
THUMBFUNC
__BRANCH_TABLE:                /* placeholder */
    B       Reset_Handler
THUMBFUNC
__USB_Istr:                 /*  */
    B       USB_Istr
THUMBFUNC
__CTR_HP:                   /*  */
    B       CTR_HP
THUMBFUNC
__MSD_WriteBlock:           /*  */
    B       MSD_WriteBlock
THUMBFUNC
__MSD_ReadBlock:            /*  */
    B       MSD_ReadBlock
THUMBFUNC
__Get_Font_8x14:            /*  */
    B       Get_Font_8x14
THUMBFUNC
__Get_Ref_Wave:             /*  */
    B       Get_Ref_Wave
THUMBFUNC
__SD_Set_Changed:           /* void SD_Set_Changed(void); */
    B       SD_Set_Changed
#ifdef __GNUC__
  .end
#else
  END
#endif

/* ******************************* END OF FILE *********************************** */
  

