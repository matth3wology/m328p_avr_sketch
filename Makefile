CC=avrdude
PROGRAMMER=usbasp
PART=m328p
CFLAGS=-Wall -g -Os -mmcu=atmega328p
TARGET=Test
INCLUDE=C:/WinAVR-20100110/avr/include
LIBRARY=C:/WinAVR-20100110/avr/lib


all:
	avr-gcc ${CFLAGS} -o ${TARGET}.bin ${TARGET}.c -I${INCLUDE} -L${LIBRARY}
	avr-objcopy -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	${CC} -c${PROGRAMMER} -p${PART} -Uflash:w:${TARGET}.hex:i

.PHONY: clean

clean:
	del *.bin *.hex