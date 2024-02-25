#include "TCS3471.h"
#include <stdio.h>
// Slave address
//TCS34727FN 0x44 = TCS34725  0x4D = TCS34727
//TCS34717FN 0x14 = TCS34711 & TCS34715  0x1D = TCS34713 & TCS34717
#define ADDRESS_0 (0x29 << 1)
//#define ADDRESS_1 (0x29 << 1)
// Registers
#define TCS3471_ENABLE_REG  0x00
#define TCS3471_ATIME_REG   0x01
#define TCS3471_WTIME_REG   0x03
#define TCS3471_AILTL_REG   0x04
#define TCS3471_AILTH_REG   0x05
#define TCS3471_AIHTL_REG   0x06
#define TCS3471_AIHTH_REG   0x07
#define TCS3471_PERS_REG    0x0C
#define TCS3471_CONFIG_REG  0x0D
#define TCS3471_CONTROL_REG 0x0F
#define TCS3471_ID_REG      0x12
#define TCS3471_STATUS_REG  0x13
#define TCS3471_CDATA_REG   0x14
#define TCS3471_CDATAH_REG  0x15
#define TCS3471_RDATA_REG   0x16
#define TCS3471_RDATAH_REG  0x17
#define TCS3471_GDATA_REG   0x18
#define TCS3471_GDATAH_REG  0x19
#define TCS3471_BDATA_REG   0x1A
#define TCS3471_BDATAH_REG  0x1B

// Custom Enable Register value
// Reserved 7..5
// AIEN = 1 RGBC interrupt enable
// WEN  = 0 Wait enable
// Reserved
// AEN = 1 RGBC enable
// PON = 1 Power ON
#define TCS3471_EnableByte	0x13

// Command register bits
#define TCS3471_COMMAND_BIT  0x80
#define TCS3471_AUTOINCR_BIT 0x20
#define TCS3471_SPECIAL_BIT  0x60
#define TCS3471_INTCLEAR_BIT 0x06

// Enable register bits
#define TCS3471_AIEN_BIT     0x10
#define TCS3471_WEN_BIT      0x08
#define TCS3471_AEN_BIT      0x02
#define TCS3471_PON_BIT      0x01

// Configuration register bits
#define TCS3471_WLONG_BIT    0x02

// Control register bits

#define TCS3471_GAIN_1X			0x00
#define TCS3471_GAIN_4X			0x01
#define TCS3471_GAIN_16X		0x02
#define TCS3471_GAIN_60X		0x03

// ID register values
#define TCS3471_1_5_VALUE    0x14
#define TCS3471_3_7_VALUE    0x1D

// Status register bits
#define TCS3471_AINT_BIT     0x10
#define TCS3471_AVALID_BIT   0x01

#define TCS3471_RESPONCE_TIME   500

const uint8_t TCS3471_GET_ALL = TCS3471_COMMAND_BIT | TCS3471_AUTOINCR_BIT | TCS3471_CDATA_REG;
const uint8_t TCS3471_INT_CLR = TCS3471_COMMAND_BIT | TCS3471_SPECIAL_BIT | TCS3471_INTCLEAR_BIT;

static I2C_HandleTypeDef crtI2C;

static uint16_t read_16(uint8_t addr) {
	uint8_t rx_buff[2];
	if (HAL_I2C_Mem_Read(&crtI2C, ADDRESS_0, TCS3471_COMMAND_BIT | TCS3471_AUTOINCR_BIT | addr, 1, rx_buff, 2, TCS3471_RESPONCE_TIME) == HAL_OK) 
		return (uint16_t) ((rx_buff[1] << 8) | rx_buff[0]);
	 else
		return 0;
}

static uint8_t read_8(uint8_t addr, uint8_t *value) {
	if(HAL_I2C_Mem_Read(&crtI2C, ADDRESS_0, TCS3471_COMMAND_BIT | addr, 1, value, 1, TCS3471_RESPONCE_TIME) == HAL_OK) {
		return 1;
	} else
		return 0;
}

static uint8_t write_8(uint8_t addr, uint8_t value) {
	if (HAL_I2C_Mem_Write(&crtI2C, ADDRESS_0, TCS3471_COMMAND_BIT | addr, 1, &value, 1, TCS3471_RESPONCE_TIME) == HAL_OK)
		return 1;
	else
		return 0;
}

static uint8_t write_16(uint8_t addr, uint16_t value) {
	if (HAL_I2C_Mem_Write(&crtI2C, ADDRESS_0, TCS3471_COMMAND_BIT | TCS3471_AUTOINCR_BIT | addr, 1, (uint8_t*)(&value), 2, TCS3471_RESPONCE_TIME) == HAL_OK)
		return 1;
	else
		return 0;
}

void TCS3471_SetCurrent(uint8_t id){
	if(id){
		crtI2C = hi2c2;
	} else {
		crtI2C = hi2c1;
	}
}

void TCS3471_PrintReg(void){
		uint8_t tmpaddr, result;
		result = read_8(TCS3471_ENABLE_REG, &tmpaddr);
		printf("TCS3471_ENABLE_REG r %d a %d\r\n", result, tmpaddr);
		result = read_8(TCS3471_ATIME_REG, &tmpaddr);
		printf("TCS3471_ATIME_REG r %d a %d\r\n", result, tmpaddr);
		result = read_8(TCS3471_WTIME_REG, &tmpaddr);
		printf("TCS3471_WTIME_REG r %d a %d\r\n", result, tmpaddr);
		result = read_8(TCS3471_AILTL_REG, &tmpaddr);
		printf("TCS3471_AILTL_REG r %d a %d\r\n", result, tmpaddr);
		result = read_8(TCS3471_AILTH_REG, &tmpaddr);
		printf("TCS3471_AILTH_REG r %d a %d\r\n", result, tmpaddr);
		result = read_8(TCS3471_AIHTL_REG, &tmpaddr);
		printf("TCS3471_AIHTL_REG r %d a %d\r\n", result, tmpaddr);		
		result = read_8(TCS3471_AIHTH_REG, &tmpaddr);
		printf("TCS3471_AIHTH_REG r %d a %d\r\n", result, tmpaddr);			
		result = read_8(TCS3471_PERS_REG, &tmpaddr);
		printf("TCS3471_PERS_REG r %d a %d\r\n", result, tmpaddr);	
		result = read_8(TCS3471_CONFIG_REG, &tmpaddr);
		printf("TCS3471_CONFIG_REG r %d a %d\r\n", result, tmpaddr);
		result = read_8(TCS3471_CONTROL_REG, &tmpaddr);
		printf("TCS3471_CONTROL_REG r %d a %d\r\n", result, tmpaddr);
		result = read_8(TCS3471_ID_REG, &tmpaddr);
		printf("TCS3471_ID_REG r %d a %d\r\n", result, tmpaddr);
		result = read_8(TCS3471_STATUS_REG, &tmpaddr);
		printf("TCS3471_STATUS_REG r %d a %d\r\n", result, tmpaddr);
		printf("----------------------------\r\n");
}

void get_CRGB(uint16_t *c, uint16_t *r, uint16_t *g, uint16_t *b) {
	uint8_t rx_buff[8];
	if (HAL_I2C_Mem_Read(&crtI2C, ADDRESS_0, TCS3471_GET_ALL, 1, rx_buff, 8, TCS3471_RESPONCE_TIME) == HAL_OK) 
	*c = (uint16_t) ((rx_buff[1] << 8) | rx_buff[0]);
	*r = (uint16_t) ((rx_buff[3] << 8) | rx_buff[2]);
	*g = (uint16_t) ((rx_buff[5] << 8) | rx_buff[4]);
	*b = (uint16_t) ((rx_buff[7] << 8) | rx_buff[6]);
	HAL_I2C_Master_Transmit(&crtI2C, ADDRESS_0, (uint8_t*)(&TCS3471_INT_CLR), 1, TCS3471_RESPONCE_TIME);
}

uint8_t TCS3471_detect(void) {
	uint8_t tmpaddr, result;
	result = read_8(TCS3471_ID_REG, &tmpaddr);
	//printf("r %d a %d\r\n", result, tmpaddr);
	if(result){
		if(tmpaddr == TCS3471_3_7_VALUE)	
			return 1;
		else
			return 0;
	} else
		return 0;
}

void TCS3471_powerOn(void){
	//Power on the sensor and wait 2.4ms
	write_8(TCS3471_ENABLE_REG, TCS3471_PON_BIT);
	HAL_Delay(3);
}

void TCS3471_enable(void) {
	// WLONG = 0x02
	//Wait Long. When asserted, the wait cycles are increased by a factor 12x from that programmed in the WTIME register.
	write_8(TCS3471_CONFIG_REG, 0x00);
	// Reserved 7..5
	// AIEN = 1 RGBC interrupt enable
	// WEN  = 0 Wait enable
	// Reserved
	// AEN = 1 RGBC enable
	// PON = 1 Power ON
	write_8(TCS3471_ENABLE_REG, TCS3471_EnableByte);
}

void TCS3471_disable(void) {
	uint8_t tmpVal;
	read_8(TCS3471_ENABLE_REG, &tmpVal);
	write_8(TCS3471_ENABLE_REG, tmpVal & ~(TCS3471_PON_BIT | TCS3471_AEN_BIT));
}

void TCS3471_setGain(uint8_t gain) {
	uint8_t sGain = TCS3471_GAIN_1X;
	if(gain > 37)
		sGain = TCS3471_GAIN_60X;
	else if(gain > 9)
		sGain = TCS3471_GAIN_16X;
	else if(gain > 2)
		sGain = TCS3471_GAIN_4X;
	write_8(TCS3471_CONTROL_REG, sGain);
}


void TCS3471_setIntegrationTime(uint8_t time) {
	write_8(TCS3471_ATIME_REG, time);
}

void TCS3471_setWaitTime(uint8_t waitTime) {
	write_8(TCS3471_WTIME_REG, waitTime);
}

void TCS3471_enableInt(void) {
	uint8_t tmpVal, result;
	result = read_8(TCS3471_ENABLE_REG, &tmpVal);  
	write_8(TCS3471_ENABLE_REG, tmpVal | TCS3471_AIEN_BIT);
}

void TCS3471_disableInt(void) {
	uint8_t tmpVal, result;
	result = read_8(TCS3471_ENABLE_REG, &tmpVal);  
	write_8(TCS3471_ENABLE_REG, tmpVal & ~TCS3471_AIEN_BIT);
}

void TCS3471_clearInt(void) {
	//uint8_t cmd = TCS3471_COMMAND_BIT | TCS3471_SPECIAL_BIT | TCS3471_INTCLEAR_BIT;
	HAL_I2C_Master_Transmit(&crtI2C, ADDRESS_0, (uint8_t*)(&TCS3471_INT_CLR), 1, TCS3471_RESPONCE_TIME);
}

void TCS3471_highInt(uint16_t highThreshold) {
	write_16(TCS3471_AIHTL_REG, highThreshold);
}

void TCS3471_lowInt(uint16_t lowThreshold) {
	write_16(TCS3471_AILTL_REG, lowThreshold);
}

void TCS3471_Persistence(uint8_t persistence) {
	uint8_t valueToWrite = persistence;
	if (valueToWrite > 60)
		valueToWrite = 60;
	if (valueToWrite > 3)
		valueToWrite = valueToWrite / 5 + 3;
	write_8(TCS3471_PERS_REG,valueToWrite & 0x0F);
}

uint8_t TCS3471_isValid(void) {
	uint8_t tmpVal;
	read_8(TCS3471_STATUS_REG, &tmpVal);
	return (tmpVal & TCS3471_AVALID_BIT) == TCS3471_AVALID_BIT;
}

uint16_t TCS3471_getClear(void) {
	return read_16(TCS3471_CDATA_REG);
}

uint16_t TCS3471_getRed(void) {
	return read_16(TCS3471_RDATA_REG);
}

uint16_t TCS3471_getGreen(void) {
	return read_16(TCS3471_GDATA_REG);
}

uint16_t TCS3471_getBlue(void) {
	return read_16(TCS3471_BDATA_REG);
}