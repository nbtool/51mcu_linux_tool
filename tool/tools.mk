
PROJECT_ROOT := ~/Downloads/51mcu_linux_tool/example
TOOLS_PATH := $(PROJECT_ROOT)/../tool
HEX2BIN_PATH := $(TOOLS_PATH)/hex2bin-2.5
SDCC_PATH := $(TOOLS_PATH)/sdcc
STCFLASH_PATH := $(TOOLS_PATH)/stcflash

tools:
	if [ ! -d $(HEX2BIN_PATH) ]; then \
		unzip $(HEX2BIN_PATH).zip -d $(TOOLS_PATH) ; \
	fi

	if [ ! -d $(SDCC_PATH) ]; then \
		unzip $(SDCC_PATH).zip -d $(TOOLS_PATH) ; \
	fi

	if [ ! -d $(STCFLASH_PATH) ]; then \
		unzip $(STCFLASH_PATH).zip -d $(TOOLS_PATH) ; \
	fi


