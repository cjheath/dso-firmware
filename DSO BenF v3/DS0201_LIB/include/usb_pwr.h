/************************ DS0501USB电源管理程序头文件 **************************
* 文件名  : usb_pwr.c            硬件环境  : DS0501V1.0电路板
* 说明    : USB电源管理程序头文件
* 作者    : ST Team, CXG修改          当前版本  : V0.1  完成日期   : 20008/12/7
*******************************************************************************/

#ifndef __USB_PWR_H
#define __USB_PWR_H

typedef enum _RESUME_STATE
{
  RESUME_EXTERNAL,
  RESUME_INTERNAL,
  RESUME_LATER,
  RESUME_WAIT,
  RESUME_START,
  RESUME_ON,
  RESUME_OFF,
  RESUME_ESOF
} RESUME_STATE;

typedef enum _DEVICE_STATE
{
  UNCONNECTED,
  ATTACHED,
  POWERED,
  DEFAULT,
  ADDRESSED,
  CONFIGURED
} DEVICE_STATE;

void Suspend(void);
void Resume_Init(void);
void Resume(RESUME_STATE eResumeSetVal);

extern  vu8 bDeviceState; /* USB device status */
extern volatile bool fSuspendEnabled;  /* true when suspend is possible */

#endif  /*__USB_PWR_H*/

/******************************* END OF FILE **********************************/
