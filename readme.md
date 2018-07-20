## 在Linux下搭建51单片机的开发烧写环境（makefile版）
星期二, 10. 七月 2018 01:01上午 - beautifulzzzz
![][#bar]

### 一、SDCC（Small Device C Compiler）编译环境搭建

SDCC是一个小型设备的C语言编译器，该编译器是标准C语言，可以编译Intel MCS51架构的微处理器，也可以编译STM8等常见MCU。我们要在linux上搭建51开发环境，首先要搭建SDCC编译环境。

其主页是：[http://sdcc.sourceforge.net/][#2] ，下面是SDCC的首页简介：
> SDCC is a retargettable, optimizing Standard C (ANSI C89, ISO C99, ISO C11) compiler suite that targets the Intel MCS51 based microprocessors (8031, 8032, 8051, 8052, etc.), Maxim (formerly Dallas) DS80C390 variants, Freescale (formerly Motorola) HC08 based (hc08, s08), Zilog Z80 based MCUs (z80, z180, gbz80, Rabbit 2000/3000, Rabbit 3000A, TLCS-90) and STMicroelectronics STM8. Work is in progress on supporting the Microchip PIC16 and PIC18 targets. It can be retargeted for other microprocessors.

![][#bar]
#### 1.1、下载
有两个可供下载的： 

- 1） [https://sourceforge.net/projects/sdcc/files/][#3]   <-- 需要自己编译，有一定难度
- 2） [http://sdcc.sourceforge.net/snap.php][#4]  <-- 编译好的，拿来即用

**注：** 对于选择拿来即用的兄弟，可以直接跳过1.2节

![][#bar]
#### 1.2、编译
如何编译：

	./config
	
可能会出现下面几种错误（我也给出了解决办法）：

- **错误 1** 、缺少bison :

		configure: error: Cannot find required program bison.
	
	解决方法：	

		sudo apt-get install flex bison

- **错误 2** 、找不到adjacency_list.hpp

		configure: error: boost library not found (boost/graph/adjacency_list.hpp).
	
	解决方法：
	
		sudo apt-get install libboost-date-time-dev libboost-program-options-dev libboost-system-dev libboost-filesystem-dev libboost-iostreams-dev

- **错误 3** 、 没有PIC14、PIC16设备

		failed for device/lib/pic14
	
	解决方法：
	
		./configure --disable-pic14-port --disable-pic16-port

![][#bar]
#### 1.3、测试

直接下载编译好的需要将其按照说明放入系统bin等文件中，采用编译的会自动将其放入系统bin中。而我比较喜欢不让其和系统的各种东西纠缠在一起，单独放在工程下的一个叫tool的文件里，大不了用的时候输全路径！

如下，我在example目录下建一个makefile和a.c文件，将直接编译好的sdcc文件放在tool下面：

	➜  SDCC_WS  tree -L 2
	.
	├── example
	│   ├── a.c
	│   └── makefile
	├── readme.md
	└── tool
	    └── sdcc

其中a.c为51闪灯程序：

	#include <8052.h>
	 
	void delay(void);
	 
	void main(void){
	    while(1){
		 P1 = 0xFF; // Turn ON all LED's connected to Port1
		 delay();
		 P1 = 0x00; // Turn OFF all LED's connected to Port1
		 delay();
	    }
	}
	 
	void delay(void){
	    int i,j;
	    for(i=0;i<0xff;i++)
		 for(j=0;j<0xff;j++);
	}

makefile为：

	SDCC_PATH=../tool/sdcc

	z_sdcc=${SDCC_PATH}/bin/sdcc
	z_packihx=${SDCC_PATH}/bin/packihx


	a.hex:a.c
		${z_sdcc} a.c
		${z_packihx} a.ihx > a.hex

	clean:
		rm -rf *.asm *.lst *.mem *.rst *.lnk *.rel *.sym *.ihx *.hex *.map *.lk *.bin

![][#bar]
### 二、Hex2Bin+命令行烧写工具配置使用
#### 2.1、下载工具安装配置
理论上hex也能烧写，但是hex比bin要大一些，所以我们用这里用bin烧写。hex转bin要用到一个[Hex2Bin][#7]工具，将其下载下来解压到tool目录下；stc单片机烧写工具需要用一个github开源软件[stcflash][#8]，也将其下载到tool目录下：

	➜  SDCC_WS  tree -L 2
	.
	├── example
	│   ├── a.c
	│   └── makefile
	├── readme.md
	└── tool
	    ├── Hex2bin-2.5
	    ├── sdcc
	    ├── software
	    └── stcflash

将makefile改为：

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

![][#bar]
#### 2.2、编译+烧写

进入example目录运行make，自动编译：

![][#9]

输入make flash，给51单片机重新上电（冷启动）进行烧写：

![][#10]


![][#bar]

### 链接
- 8051 PROGRAMMING USING SMALL DEVICE C COMPILER (SDCC)：[GO][#5]
- SDCC WiKi：[https://sourceforge.net/p/sdcc/wiki/Home/][#6]
- 在Linux下搭建51单片机的开发烧写环境：[GO][#11]


![][#bar]
```
@beautifulzzzz
智能硬件、物联网，热爱技术，关注产品
博客：http://blog.beautifulzzzz.com
园友交流群：414948975
```


[#bar]:https://btfzmd.oss-cn-shanghai.aliyuncs.com/base/bar.png
[#1]:http://odff1d90v.bkt.clouddn.com/20180708/sdcc_download.png
[#2]:http://sdcc.sourceforge.net/
[#3]:https://sourceforge.net/projects/sdcc/files/ 
[#4]:http://sdcc.sourceforge.net/snap.php 
[#5]:http://www.instructables.com/id/8051-Programming-Using-Small-Device-C-Compiler-SDC/
[#6]:https://sourceforge.net/p/sdcc/wiki/Home/
[#7]:https://sourceforge.net/projects/hex2bin/files/latest/download
[#8]:https://github.com/laborer/stcflash
[#9]:http://odff1d90v.bkt.clouddn.com/20180711/make_sdcc.png
[#10]:http://odff1d90v.bkt.clouddn.com/20180711/make_flash.png
[#11]:https://blog.csdn.net/thinkerleo1997/article/details/53145972


