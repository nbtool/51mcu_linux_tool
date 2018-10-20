
PROJECT_ROOT := $(shell cd .. && pwd)
TOOLS_PATH := $(PROJECT_ROOT)/tool
BIN_PATH := $(PROJECT_ROOT)/bin
APP_PATH := $(PROJECT_ROOT)/app
HEX2BIN_PATH := $(TOOLS_PATH)/Hex2bin-2.5
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

	if [ ! -d $(BIN_PATH) ]; then \
		mkdir $(BIN_PATH); \
	fi


