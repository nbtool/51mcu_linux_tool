#ifndef __UART_H__
#define __UART_H__
/*
 * uart.h:
 * Copyright (c) 2014-2021 Rtrobot. <admin@rtrobot.org>
 *  <http://rtrobot.org>
 ***********************************************************************
 * use keil5
 */
#include "main.h"
void Uart_Init(void);
void Send_Char (uint8_t UART_data);
char putchar(char c);
#endif /* __UART_H__ */