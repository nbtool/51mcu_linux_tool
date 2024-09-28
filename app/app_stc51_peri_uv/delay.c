#include "delay.h"
/*
 * delay.c:
 * Copyright (c) 2014-2021 Rtrobot. <admin@rtrobot.org>
 *  <http://rtrobot.org>
 ***********************************************************************
 * use keil5
 */
#include <main.h>

void Delay1us()		//@12.000MHz
{
	uint8_t i, j;

	_nop_();
	_nop_();
    _nop_();
    _nop_();
	i = 1;
	j = 145;
	do
	{
		while (--j);
	} while (--i);
}

void Delay_Ms (unsigned int a)
{
	unsigned int i;
	while( a-- != 0)
	{
		for(i = 0; i < 600; i++);
	}
}