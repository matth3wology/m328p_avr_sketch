CC=avrdude
PROGRAMMER=usbasp
PART=m328p
CFLAGS=-g -Os -mmcu=atmega328p -Wno-redundant-decls
TARGET=gpio_servo
INCLUDE=C:/avr8-gnu-toolchain-win32_x86_64/avr/include
LIBRARY=C:/avr8-gnu-toolchain-win32_x86_64/avr/lib

all:
	avr-gcc $(CFLAGS) -o $(TARGET).bin $(TARGET).c -I$(INCLUDE) -L$(LIBRARY)
	avr-objcopy -j .text -j .data -O ihex $(TARGET).bin $(TARGET).hex

flash:
	$(CC) -c$(PROGRAMMER) -p$(PART)  -Uflash:w:$(TARGET).hex:i

.PHONY: clean

clean:
	del *.bin *.hex
