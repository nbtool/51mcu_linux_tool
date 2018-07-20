-include ../tool/tools.mk

SDCC_PATH=../tool/sdcc
HEX2BIN_PATH=../tool/Hex2bin-2.5
STCFLASH=../tool/stcflash

z_sdcc=${SDCC_PATH}/bin/sdcc
z_packihx=${SDCC_PATH}/bin/packihx
z_hex2bin=${HEX2BIN_PATH}/hex2bin
z_stcflash=${STCFLASH}/stcflash.py

a.hex:a.c
	${z_sdcc} a.c
	${z_packihx} a.ihx > a.hex
	${z_hex2bin} a.hex

clean:
	rm -rf *.asm *.lst *.mem *.rst *.lnk *.rel *.sym *.ihx *.hex *.map *.lk *.bin

flash:
	python ${z_stcflash} a.bin
