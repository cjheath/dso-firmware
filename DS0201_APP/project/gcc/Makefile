#
# GNU Makefile for DSO Nano
# Copyright 2010 Tormod Volden
#

BASE = ../../..
APP = $(BASE)/DS0201_APP

# STM library location
STM_LIB = $(BASE)/library

INCLUDES = -I $(APP)/include \
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
  
MFLAGS  = -mcpu=cortex-m3 -mthumb
ASFLAGS = $(MFLAGS)
CFLAGS  = $(INCLUDES) -c -fno-common -Os -g $(MFLAGS) -Wp,-DGCC
LFLAGS  = -T stm32f10x_flash_offset.ld -nostartfiles $(MFLAGS)
CPFLAGS = -j .isr_vector -j .flashtext -j .text
ODFLAGS = -S

CSRC = $(APP)/source/Calculate.c \
       $(APP)/source/Files.c \
       $(APP)/source/Function.c \
       $(APP)/source/HW_V1_Config.c \
       $(APP)/source/Lcd.c \
       $(APP)/source/Menu.c \
       $(APP)/source/main.c \
       $(APP)/source/stm32f10x_it.c

STM32SRCS = $(STM_LIB)/src/stm32f10x_flash.c \
            $(STM_LIB)/src/stm32f10x_nvic.c \
            $(STM_LIB)/src/stm32f10x_rcc.c

CSRC += $(STM32SRCS)
COBJ = $(CSRC:.c=.o)

ASRC = ASM_Function-gcc.s \
       cortexm3_macro.s \
       startup_stm32f10x_md.s

AOBJ = $(ASRC:.s=.o)

all: binaries

# The assembly has to be converted from IAR style
ASM_Function-gcc.S: $(APP)/source/ASM_Function.s
	./iar2gas < $(APP)/source/ASM_Function.s > ASM_Function-gcc.S

dso-app.elf: $(COBJ) $(AOBJ)
	$(CC) $(LFLAGS) -o dso-app.elf $(AOBJ) $(COBJ)

binaries: dso-app.elf
	$(OD) $(ODFLAGS) dso-app.elf > dso-app.lst
	$(CP) $(CPFLAGS) -Obinary dso-app.elf dso-app.bin
	$(CP) $(CPFLAGS) -Oihex dso-app.elf dso-app.hex

clean:
	rm -f *.o $(APP)/source/*.o $(STM_LIB)/src/*.o ASM_Function-gcc.[sS] \
	    dso-app.elf dso-app.bin dso-app.hex dso-app.lst
