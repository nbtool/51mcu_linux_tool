/*
 * uart.c:
 * Copyright (c) 2014-2021 Rtrobot. <admin@rtrobot.org>
 *  <http://rtrobot.org>
 ***********************************************************************
 * use keil5
 */

#include <main.H>
#include "uart.h"

/*****************************************************************************
UART初始化
*****************************************************************************/
void Uart_Init(void)		
{
	EA=1;
	ES=1;
	SCON = 0x50;			 
	TMOD = 0x20;
	PCON=0x00; 	
	TH1 = 0xFD;	
	TL1 = 0xfd;
	TR1 = 1;	
	RI = 0;
}

/*****************************************************************************
单字符发送函数
/****************************************************************************/
void Send_Char (uint8_t UART_data)		
{ 		
	SBUF = UART_data;			
	while(TI == 0);			
	TI = 0;					  
}

//重写putchar函数
char putchar(char c)
{
    Send_Char(c);
    return c;
}
