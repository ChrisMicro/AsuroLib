###############################################################################
# Makefile for the project AsuroLib
###############################################################################

## General Flags
MCU = atmega8
F_CPU = 8000000UL
TARGET = libasuro
CC = avr-gcc.exe
AR = avr-ar
OBJDUMP = avr-objdump

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -Os -I./inc
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += 


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0


## Objects that must be built in order to link
OBJECTS = globals.o adc.o adc_low.o encoder.o encoder_low.o i2c.o lcd.o lcd_bpi216.o\
 	leds.o motor.o motor_low.o my_motor_low.o print.o printf.o rc5.o sound.o switches.o\
  time.o uart.o ultrasonic.o version.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

# Define directories, AtmelAVR.
DIRAVR = "C:/Program Files/Atmel/AVR Tools/AVR Toolchain"
##DIRAVR = /usr/local/avr
#DIRAVRBIN = $(DIRAVR)/bin

## Define directories, WinAVR.
#DIRAVR = C:/WinAVR
##DIRAVR = /usr/local/avr
#DIRAVRUTILS = $(DIRAVR)/utils/bin

DIRAVRBIN = $(DIRAVR)/bin
DIRINC = $(DIRAVR)/avr/include
DIRLIB = $(DIRAVR)/avr/lib

LIB = asuro
LIBFILE = $(TARGET).a
HEADER = asuro.h

## Build
all: $(LIBFILE)
	rm -rf *.o *~

%.o: %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

$(LIBFILE): $(OBJECTS)
	$(AR) cru $(LIBFILE) $(OBJECTS)

## Clean target
clean:
	rm -rf *.o *~ $(LIBFILE)
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)
	rm -rf dep/*.d

install:
	cp $(LIBFILE) $(DIRLIB)/$(LIBFILE)
	cp inc/$(HEADER) $(DIRINC)/$(HEADER)

lst: $(OBJECTS:%.o=%.lst)


%.lst: %.o
	$(OBJDUMP) -h -S $< > $@

## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

