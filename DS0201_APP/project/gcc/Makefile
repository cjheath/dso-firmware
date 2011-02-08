#
# GNU Makefile for DSO Nano application
# Copyright 2010 Tormod Volden
#

NAME = dso-app

# Directory layout
BASE    = ../../..
PRJ     = $(BASE)/DS0201_APP
STM_LIB = $(BASE)/library

INCLUDES = -I $(PRJ)/include \
           -I $(STM_LIB)/inc

# Toolchain setup
CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld -v
AR = $(CROSS_COMPILE)ar
AS = $(CROSS_COMPILE)as
CP = $(CROSS_COMPILE)objcopy
OD = $(CROSS_COMPILE)objdump
  
LNKSCRIPT = stm32f10x_flash_offset.ld
MFLAGS  = -mcpu=cortex-m3 -mthumb
ASFLAGS = $(MFLAGS)
CFLAGS  = $(MFLAGS) $(INCLUDES) -c -fno-common -Os -g
LFLAGS  = $(MFLAGS) -T $(LNKSCRIPT) -nostartfiles

CSRC = \
       $(PRJ)/source/stm32f10x_vector.c \
       $(PRJ)/source/stm32f10x_it.c \
       $(PRJ)/source/main.c \
       $(PRJ)/source/HW_V1_Config.c \
       $(PRJ)/source/Lcd.c \
       $(PRJ)/source/Calculate.c \
       $(PRJ)/source/Files.c \
       $(PRJ)/source/Function.c \
       $(PRJ)/source/Menu.c
CSRC += \
       $(STM_LIB)/src/stm32f10x_flash.c \
       $(STM_LIB)/src/stm32f10x_nvic.c \
       $(STM_LIB)/src/stm32f10x_rcc.c

COBJ = $(CSRC:.c=.o)

ASRC = ASM_Function-gcc.s \
       cortexm3_macro.s \
       startup_stm32f10x_md.s

AOBJ = $(ASRC:.s=.o)

all: binaries

# The assembly has to be converted from IAR style
#ASM_Function-gcc.S: $(PRJ)/source/ASM_Function.s
#	sed -f iar2gas < $(PRJ)/source/ASM_Function.s > ASM_Function-gcc.S

$(NAME).elf: $(AOBJ) $(COBJ) $(LNKSCRIPT)
	$(CC) $(LFLAGS) -o $(NAME).elf $(AOBJ) $(COBJ)

binaries: $(NAME).elf
	$(OD) -S $(NAME).elf > $(NAME).lst
	$(CP) -O binary $(NAME).elf $(NAME).bin
	$(CP) -O ihex $(NAME).elf $(NAME).hex

clean:
	rm -f *.o $(PRJ)/source/*.o $(STM_LIB)/src/*.o \
	    $(NAME).elf $(NAME).bin $(NAME).hex $(NAME).lst
#	    ASM_Function-gcc.[sS] \
