#ifndef __TCS3471_H__
#define __TCS3471_H__

	#include "stm32f3xx_hal.h"
	#include "i2c.h"
	void get_CRGB(uint16_t *c, uint16_t *r, uint16_t *g, uint16_t *b);
	void TCS3471_PrintReg(void);
	void TCS3471_SetCurrent(uint8_t id);
	void TCS3471_powerOn(void);
	uint8_t TCS3471_detect(void);
	void TCS3471_enable(void);
	void TCS3471_disable(void);
	void TCS3471_setGain(uint8_t gain);
	void TCS3471_setIntegrationTime(uint8_t time);
	void TCS3471_setWaitTime(uint8_t waitTime);
	void TCS3471_enableInt(void);
	void TCS3471_disableInt(void);
	void TCS3471_clearInt(void);
	void TCS3471_highInt(uint16_t highThreshold);
	void TCS3471_lowInt(uint16_t lowThreshold);
	void TCS3471_Persistence(uint8_t persistence);
	uint8_t TCS3471_isValid(void);
	uint16_t TCS3471_getClear(void);
	uint16_t TCS3471_getRed(void);
	uint16_t TCS3471_getGreen(void);
	uint16_t TCS3471_getBlue(void);

#endif  // __TCS3471_H__