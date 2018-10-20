-include tools.mk


z_sdcc=${SDCC_PATH}/bin/sdcc
z_packihx=${SDCC_PATH}/bin/packihx
z_hex2bin=${HEX2BIN_PATH}/hex2bin
z_stcflash=${STCFLASH_PATH}/stcflash.py

files_temp=*.asm *.lst *.mem *.rst *.rel *.sym *.ihx *.hex *.map *.lk *.bin


build:
	${z_sdcc} $(APP_PATH)/$(PROJECT)/*.c
	${z_packihx} *.ihx > $(PROJECT).hex
	${z_hex2bin} $(PROJECT).hex

	mv -f $(files_temp) $(BIN_PATH)

clean:
	rm -rf $(BIN_PATH)/*

flash:
	python ${z_stcflash} $(BIN_PATH)/*.bin
