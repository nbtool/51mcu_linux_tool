/*
 * i2c.h:
 * Copyright (c) 2014-2021 Rtrobot. <admin@rtrobot.org>
 *  <http://rtrobot.org>
 ***********************************************************************
 * use keil5
 */
 
#ifndef __I2C_H__
#define __I2C_H__

#include "main.h"

void I2C_Start(void);
void I2C_Stop(void);
bit I2C_RecvACK(void);
uint8_t I2C_RecvByte(void);
void I2C_SendByte(uint8_t  dat);
void I2C_SendACK(bit ack);
void I2C_ReadCommand(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *rev_data, uint16_t length);
void I2C_WriteCommand(uint8_t i2c_addr, uint8_t reg_addr, uint8_t *send_data, uint16_t length);
#endif /* __I2C_H__ */