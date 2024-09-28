/*
 * main.c:
 * Copyright (c) 2014-2021 Rtrobot. <admin@rtrobot.org>
 *  <http://rtrobot.org>
 ***********************************************************************
 * use keil5.
 */
#include "delay.h"
#include "uart.h"
#include "i2c.h"
#include "LTR390UV.h"
#include <stdio.h>

void main(void)
{
	uint8_t ltrmode = 0x00;
	Uart_Init();
	Delay_Ms(1000);

	if (LTR390UV_Init() == false)
	{
		printf("LTR390UV initialize error.\r\n");
		while (1)
			;
	}
	else
		printf("LTR390UV initialize register finished.\r\n");
        
	// set mode as als
	// LTR390UV_SetMode(LTR390UV_MODE_ALS);
	// set mode as uvs
	LTR390UV_SetMode(LTR390UV_MODE_UVS);

	ltrmode = LTR390UV_GetMode();
	if (ltrmode == LTR390UV_MODE_ALS)
		printf("mode: ALS\r\n");
	else
		printf("mode: UVS\r\n");
        
    // set gain range as 3
	LTR390UV_SetGain(LTR390UV_GAIN_RANGE_3);

	// set measurement rate as 100ms and set resolution as 18 bit
	LTR390UV_SetMeasurement(LTR390UV_MEASUREMENT_RATE_100MS | LTR390UV_RESOLUTION_18BIT);

	// Set the upper and lower interrupt limits
	// range: 0 - 1048575
	// LTR390UV_SetThresholds(20, 500);

	// Set the interrupt type and interrupt trigger threshold count
	// LTR390UV_SetInterrupt(true, LTR390UV_INT_UVS, LTR390UV_PST_EVERY);
        
	while (true)
	{
		if (LTR390UV_GetDataStatus())
		{
			if (ltrmode == LTR390UV_MODE_ALS)
			{
				uint32_t als = LTR390UV_GetALS();
				printf("ALS: %d,\t", als);
				printf("Lux: %f\r\n", LTR390UV_GetLUX(als, 1));
			}
			else
			{
				uint32_t uvs = LTR390UV_GetUVS();
				printf("UVS: %d,\t", uvs);
				printf("UVI: %f\r\n", LTR390UV_GetUVI(uvs, 1));
			}
		}
		Delay_Ms(100);
	}
}
