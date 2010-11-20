#
# GNU Makefile for DSO Nano library
# Copyright 2010 Tormod Volden
#

BASE = ../../..
LIB = $(BASE)/DS0201_LIB
USB_LIB = $(BASE)/USBLib

# STM library location
STM_LIB = $(BASE)/library

INCLUDES = -I $(LIB)/include \
           -I $(USB_LIB)/inc \
           -I $(STM_LIB)/inc

# Note that you need to add the toolchain arm-cross/bin to your PATH
# Toolchain setup
CROSS_COMPILE = arm-none-eabi-
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld -v
AR      = $(CROSS_COMPILE)ar
AS      = $(CROSS_COMPILE)as
CP      = $(CROSS_COMPILE)objcopy
OD      = $(CROSS_COMPILE)objdump
  
LNKSCRIPT = stm32f10x_flash_offset.ld
MFLAGS  = -mcpu=cortex-m3 -mthumb
ASFLAGS = $(MFLAGS)
CFLAGS  = $(INCLUDES) -c -fno-common -Os -g $(MFLAGS) -Wp,-DGCC
LFLAGS  = -T $(LNKSCRIPT) -nostartfiles $(MFLAGS)
CPFLAGS = -j .isr_vector -j .flashtext -j .text -j .data
ODFLAGS = -S

CSRC = \
       $(LIB)/source/HW_V1_Config.c \
       $(LIB)/source/Lcd.c \
       $(LIB)/source/main.c \
       $(LIB)/source/memory.c \
       $(LIB)/source/msd.c \
       $(LIB)/source/scsi_data.c \
       $(LIB)/source/stm32f10x_it.c \
       $(LIB)/source/usb_bot.c \
       $(LIB)/source/usb_desc.c \
       $(LIB)/source/usb_endp.c \
       $(LIB)/source/usb_istr.c \
       $(LIB)/source/usb_prop.c \
       $(LIB)/source/usb_pwr.c \
       $(LIB)/source/usb_scsi.c \
       $(USB_LIB)/src/usb_core.c \
       $(USB_LIB)/src/usb_init.c \
       $(USB_LIB)/src/usb_int.c \
       $(USB_LIB)/src/usb_mem.c \
       $(USB_LIB)/src/usb_regs.c

STM32SRCS = $(STM_LIB)/src/stm32f10x_flash.c \
            $(STM_LIB)/src/stm32f10x_nvic.c \
            $(STM_LIB)/src/stm32f10x_spi.c \
            $(STM_LIB)/src/stm32f10x_rcc.c

CSRC += $(STM32SRCS)
COBJ = $(CSRC:.c=.o)

ASRC = ASM_Function-gcc.s \
       cortexm3_macro.s \
       startup_stm32f10x_md.s

AOBJ = $(ASRC:.s=.o)

all: binaries

# The assembly has to be converted from IAR style
ASM_Function-gcc.S: $(LIB)/source/ASM_Function.s
	sed -f iar2gas < $(LIB)/source/ASM_Function.s > ASM_Function-gcc.S

dso-lib.elf: $(COBJ) $(AOBJ) $(LNKSCRIPT)
	$(CC) $(LFLAGS) -o dso-lib.elf $(AOBJ) $(COBJ)

binaries: dso-lib.elf
	$(OD) $(ODFLAGS) dso-lib.elf > dso-lib.lst
	$(CP) $(CPFLAGS) -Obinary dso-lib.elf dso-lib.bin
	$(CP) $(CPFLAGS) -Oihex dso-lib.elf dso-lib.hex

clean:
	rm -f *.o $(LIB)/source/*.o $(STM_LIB)/src/*.o $(USB_LIB)/src/*.o \
	    ASM_Function-gcc.[sS] \
	    dso-lib.elf dso-lib.bin dso-lib.hex dso-lib.lst
