/*
 * i2c.c:
 * Copyright (c) 2014-2021 Rtrobot. <admin@rtrobot.org>
 *  <http://rtrobot.org>
 ***********************************************************************
 * use keil5
 */
#include <main.h>
#include "delay.h"
#include "i2c.h"

/*****************************************************************************
引脚定义，扩展板链接引脚号请查阅Bobcats说明
/****************************************************************************/
uint8_t SlaveAddress = 0x00; // 定义I2C地址
sbit SCL = P1 ^ 2;			 //IIC时钟引脚定义
sbit SDA = P1 ^ 3;			 //IIC数据引脚定义

/*****************************************************************************
I2C起始信号
*****************************************************************************/
void I2C_Start(void)
{
	SDA = 1;	//拉高数据线
	SCL = 1;	//拉高时钟线
	Delay1us(); //延时
	SDA = 0;	//产生下降沿
	Delay1us(); //延时
	SCL = 0;	//拉低时钟线
}

/*****************************************************************************
I2C停止信号
*****************************************************************************/
void I2C_Stop(void)
{
	SDA = 0;	//拉低数据线
	SCL = 1;	//拉高时钟线
	Delay1us(); //延时
	SDA = 1;	//产生上升沿
	Delay1us(); //延时
}

/*****************************************************************************
I2C发送应答信号
入口参数:ack (0:ACK 1:NAK)
*****************************************************************************/
void I2C_SendACK(bit ack)
{
	SCL = 0;
	SDA = ack;	//写应答信号
	Delay1us(); //延时
	SCL = 1;	//拉高时钟线
	Delay1us(); //延时
	SCL = 0;	//拉低时钟线
}

/*****************************************************************************
I2C接收应答信号
*****************************************************************************/
bit I2C_RecvACK(void)
{
	uint8_t wait = 0xff;
	SCL = 1;
	while (SDA && wait--)
		;
	if (wait <= 0)
	{
		I2C_Stop();
		return -1;
	}
	SCL = 0;
	Delay1us();
	return 0;
}

/*****************************************************************************
向I2C总线发送一个字节数据
*****************************************************************************/
void I2C_SendByte(uint8_t dat)
{
	uint8_t i;
	for (i = 0; i < 8; i++) //8位计数器
	{
		if (dat & 0x80)
			SDA = 1;
		else
			SDA = 0;
		SCL = 1;	//拉高时钟线
		Delay1us(); //延时
		SCL = 0;	//拉低时钟线
		Delay1us(); //延时
		dat <<= 1;
	}
	//I2C_RecvACK();
}

/*****************************************************************************
从I2C总线接收一个字节数据
*****************************************************************************/
uint8_t I2C_RecvByte()
{
	uint8_t i;
	uint8_t dat = 0;
	SDA = 1;				//使能内部上拉,准备读取数据,
	for (i = 0; i < 8; i++) //8位计数器
	{
		dat <<= 1;
		SCL = 1;	//拉高时钟线
		Delay1us(); //延时
		dat |= SDA; //读数据
		SCL = 0;	//拉低时钟线
		Delay1us(); //延时
	}
	return dat;
}

/*****************************************************************************
从I2C总线接收字符串
*****************************************************************************/
void I2C_ReadCommand(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *rev_data, uint16_t length)
{
	I2C_Start();
	I2C_SendByte((i2c_addr << 1) | 0x00);
	I2C_RecvACK();
	I2C_SendByte(reg_addr);
	I2C_RecvACK();
	I2C_Start();
	Delay_Ms(15);
	I2C_SendByte((i2c_addr << 1) | 0x01);
	I2C_RecvACK();
	while (length)
	{
		*rev_data = I2C_RecvByte();
		if (length == 1)
			I2C_SendACK(1);
		else
			I2C_SendACK(0);
		rev_data++;
		length--;
	}
	I2C_Stop();
}

/*****************************************************************************
向I2C总线发送字符串
*****************************************************************************/
void I2C_WriteCommand(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *send_data, uint16_t length)
{
	I2C_Start();
	I2C_SendByte((i2c_addr << 1) | 0x00);
	I2C_RecvACK();
	I2C_SendByte(reg_addr);
	I2C_RecvACK();
	while (length)
	{
		I2C_SendByte(*send_data);
		I2C_RecvACK();
		send_data++;
		length--;
	}
	I2C_Stop();
}