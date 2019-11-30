CC=avrdude
PROGRAMMER=usbasp
PART=m328p
CFLAGS=-Wall -g -Os -mmcu=atmega328p
TARGET=Test
INCLUDE=/Users/whiterabbit/avr8-gnu-toolchain-darwin_x86_64/avr/include
LIBRARY=/Users/whiterabbit/avr8-gnu-toolchain-darwin_x86_64/avr/lib


all:
	avr-gcc ${CFLAGS} -o ${TARGET}.bin ${TARGET}.c -I${INCLUDE} -L${LIBRARY}
	avr-objcopy -j .text -j .data -O ihex ${TARGET}.bin ${TARGET}.hex

flash:
	${CC} -c${PROGRAMMER} -p${PART} -Uflash:w:${TARGET}.hex:i

clean:
	rm *.hex *.bin