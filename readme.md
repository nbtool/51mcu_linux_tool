#### 1. Brief introduction

The project provides a 51 MCU APP command-line development environment based on Linux system.

You can directly write、build、install APP(HEX/BIN) without using IDE.


#### 2. How to use

If it is the first time to compile, It is recommended to run goto build directly, and then run the 'make tools' to unzip hex2bin、sdcc、stcflash etc.

	cd build
	make tools

Build the project(for example:app_stc51_peri_blinky):

    make build PROJECT=app_stc51_peri_blinky

Install the APP:

    make flash
	

**more：**[https://www.cnblogs.com/zjutlitao/p/9292449.html](https://www.cnblogs.com/zjutlitao/p/9292449.html)


#### 3. Demos

- app_stc51_peri_blinky

