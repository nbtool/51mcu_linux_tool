#include "LTR390UV.h"
#include <main.h>
#include "delay.h"
#include "i2c.h"


/***************************************************************************************************************
LTR390UV Read Command
****************************************************************************************************************/
void LTR390UV_ReadCommand(uint8_t reg_addr, uint8_t *rev_data, uint8_t length)
{
	I2C_ReadCommand(LTR390UV_I2CADDR, reg_addr, rev_data, length);
}

/***************************************************************************************************************
LTR390UV Write Command
****************************************************************************************************************/
void LTR390UV_WriteCommand(uint8_t reg_addr, uint8_t *send_data, uint16_t length)
{
	I2C_WriteCommand(LTR390UV_I2CADDR, reg_addr, send_data, length);
}

/***************************************************************************************************************
LTR390UV Get Device Identity
****************************************************************************************************************/
bool LTR390UV_Get_Id(void)
{
	uint8_t id = 0x00;
	LTR390UV_ReadCommand(LTR390UV_REG_PART_ID, &id, 1);
	if ((id & 0xf0) != 0xb0)
		return false;
	return true;
}

/***************************************************************************************************************
LTR390UV  Software reset
****************************************************************************************************************/
void LTR390UV_Reset(void)
{
	uint8_t buf = 0x10;
	LTR390UV_WriteCommand(LTR390UV_REG_MAIN_CTRL, &buf, 1);
}

/***************************************************************************************************************
LTR390UV  set low power mode
****************************************************************************************************************/
void LTR390UV_LowPower(bool enable)
{
	uint8_t buf = 0x00;
	LTR390UV_ReadCommand(LTR390UV_REG_MAIN_CTRL, &buf, 1);
	if (enable == true)
		buf &= LTR390UV_LOWPOWER_ENABLE;
	else
		buf |= LTR390UV_LOWPOWER_DISABLE;
	LTR390UV_WriteCommand(LTR390UV_REG_MAIN_CTRL, &buf, 1);
}

/***************************************************************************************************************
LTR390UV  get mode
****************************************************************************************************************/
uint8_t LTR390UV_GetMode(void)
{
	uint8_t buf = 0x00;
	LTR390UV_ReadCommand(LTR390UV_REG_MAIN_CTRL, &buf, 1);
	return (buf >> 3) ? LTR390UV_MODE_UVS : LTR390UV_MODE_ALS;
}

/***************************************************************************************************************
LTR390UV  set mode
****************************************************************************************************************/
void LTR390UV_SetMode(uint8_t mode)
{
	uint8_t buf = 0x00;
	LTR390UV_ReadCommand(LTR390UV_REG_MAIN_CTRL, &buf, 1);
	if (mode == LTR390UV_MODE_ALS)
		buf &= LTR390UV_MODE_ALS;
	else
		buf |= LTR390UV_MODE_UVS;
	LTR390UV_WriteCommand(LTR390UV_REG_MAIN_CTRL, &buf, 1);
}

/***************************************************************************************************************
LTR390UV  set the sensor gain
****************************************************************************************************************/
void LTR390UV_SetGain(uint8_t mode)
{
	LTR390UV_WriteCommand(LTR390UV_REG_ALS_UVS_GAIN, &mode, 1);
}

/***************************************************************************************************************
LTR390UV  get the sensor gain
****************************************************************************************************************/
uint8_t LTR390UV_GetGain(void)
{
	uint8_t buf = 0x00;
	LTR390UV_ReadCommand(LTR390UV_REG_ALS_UVS_GAIN, &buf, 1);
	return buf &= 0x07;
}

/***************************************************************************************************************
this register controls als/uvs measurement resolution,
gain setting and measurement rate.
when the measurement  rate is programmed to be faster than possible for the
programmed adc measurement ,the rate will be lowered than programmed.
****************************************************************************************************************/
void LTR390UV_SetMeasurement(uint8_t mode)
{
	LTR390UV_WriteCommand(LTR390UV_REG_ALS_UVS_MEAS_RATE, &mode, 1);
}

/***************************************************************************************************************
LTR390UV  get the Resolution
****************************************************************************************************************/
uint8_t LTR390UV_GetResolution(void)
{
	uint8_t buf = 0x00;
	LTR390UV_ReadCommand(LTR390UV_REG_ALS_UVS_MEAS_RATE, &buf, 1);
	buf &= 0x70;
	buf = 7 & (buf >> 4);
	return buf;
}

/***************************************************************************************************************
Set the upper and lower interrupt limits
range: 0 - 1048575
****************************************************************************************************************/
void LTR390UV_SetThresholds(uint32_t low, uint32_t up)
{
	uint8_t lower[3] = {0x00};
	uint8_t upper[3] = {0x00};
	lower[0] = low & 0xff;
	lower[1] = (low & 0xff00) >> 8;
	lower[2] = (low & 0xf0000) >> 12;
	LTR390UV_WriteCommand(LTR390UV_REG_ALS_UVS_THRES_LOW_0, lower, 3);

	upper[0] = up & 0xff;
	upper[1] = (up & 0xff00) >> 8;
	upper[2] = (up & 0xf0000) >> 12;
	LTR390UV_WriteCommand(LTR390UV_REG_ALS_UVS_THRES_UP_0, upper, 3);
}

/***************************************************************************************************************
Set the interrupt type and interrupt trigger threshold count
****************************************************************************************************************/
void LTR390UV_SetInterrupt(bool enable, uint8_t mode, uint8_t count)
{
	uint8_t buf = 0x00;
	if (enable)
	{
		buf = mode | 0x04;
		LTR390UV_WriteCommand(LTR390UV_REG_INT_CFG, &buf, 1);
		LTR390UV_WriteCommand(LTR390UV_REG_INT_PST, &count, 1);
	}
	else
		LTR390UV_WriteCommand(LTR390UV_REG_INT_CFG, &buf, 1);
}

/***************************************************************************************************************
LTR390UV  Get Data Statut
****************************************************************************************************************/
bool LTR390UV_GetDataStatus(void)
{
	uint8_t buf = 0x00;
	LTR390UV_ReadCommand(LTR390UV_REG_MAIN_STATUS, &buf, 1);
	if ((buf & 0x08) >> 3)
		return true;
	else
		return false;
}

/***************************************************************************************************************
LTR390UV  Get UV value
****************************************************************************************************************/
uint32_t LTR390UV_GetUVS(void)
{
	uint8_t buf[3] = {0x00};
	LTR390UV_ReadCommand(LTR390UV_REG_UVS_DATA_0, buf, 3);
	return (uint32_t)buf[2] * 65536 + buf[1] * 256 + buf[0];
}

/***************************************************************************************************************
WFAC was window factor. 1 as no window or clear window glass, >1 as tinted windows glass
unit uw/cm2.
****************************************************************************************************************/
float LTR390UV_GetUVI(uint32_t uvs, float WFAC)
{
	xdata float gain_buf[5] = {1, 3, 6, 9, 18};
	xdata float res_buf[6] = {4, 2, 1, 0.5, 0.25, 0.125};
	uint8_t gain = LTR390UV_GetGain();
	uint8_t res = LTR390UV_GetResolution();
	return (float)(uvs) / ((gain_buf[gain] / 18) * (res_buf[res] / 4) * 2300.0) * WFAC;
}

/***************************************************************************************************************
LTR390UV  Get als value
****************************************************************************************************************/
uint32_t LTR390UV_GetALS(void)
{
	uint8_t buf[3] = {0x00};
	LTR390UV_ReadCommand(LTR390UV_REG_ALS_DATA_0, buf, 3);
	return (uint32_t)buf[2] * 65536 + buf[1] * 256 + buf[0];
}

/***************************************************************************************************************
WFAC was window factor. 1 as no window or clear window glass, >1 as tinted windows glass
unit lux.
****************************************************************************************************************/
float LTR390UV_GetLUX(uint32_t als, float WFAC)
{
	xdata float gain_buf[5] = {1, 3, 6, 9, 18};
	xdata float res_buf[6] = {4, 2, 1, 0.5, 0.25, 0.125};
	uint8_t gain = LTR390UV_GetGain();
	uint8_t res = LTR390UV_GetResolution();
	//return 0.6 * (float)(als) / (gain_buf[gain] * res_buf[res]) * WFAC;
}

/***************************************************************************************************************
LTR390UV Initialization
****************************************************************************************************************/
bool LTR390UV_Init(void)
{
	// Get LTR390UV ID
	if (!LTR390UV_Get_Id())
		return false;
	LTR390UV_LowPower(false);
	return true;
}
