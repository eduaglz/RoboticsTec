// Compass.h

#ifndef _COMPASS_h
#define _COMPASS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#define HMC5883_ADDRESS_MAG (0x3C >> 1)  
#define COMPASS_I2C_READ	0x3D
#define COMPASS_I2C_WRITE	0x3C

#define COMPASS_CONF_REG_A	0x00
#define COMPASS_CONF_REG_B	0x01
#define COMPASS_MODE_REG	0x02
#define COMPASS_X_H			0x03
#define COMPASS_X_L			0x04
#define COMPASS_Z_H			0x05
#define COMPASS_Z_L			0x06
#define COMPASS_Y_H			0x07
#define COMPASS_Y_L			0x08
#define COMPASS_STATUS_REG	0x09
#define COMPASS_ID_REG_A	0x0A
#define COMPASS_ID_REG_B	0x0B
#define COMPASS_ID_REG_C	0x0C

/*=========================================================================
MAGNETOMETER GAIN SETTINGS
-----------------------------------------------------------------------*/
typedef enum
{
	HMC5883_MAGGAIN_1_3 = 0x20,  // +/- 1.3
	HMC5883_MAGGAIN_1_9 = 0x40,  // +/- 1.9
	HMC5883_MAGGAIN_2_5 = 0x60,  // +/- 2.5
	HMC5883_MAGGAIN_4_0 = 0x80,  // +/- 4.0
	HMC5883_MAGGAIN_4_7 = 0xA0,  // +/- 4.7
	HMC5883_MAGGAIN_5_6 = 0xC0,  // +/- 5.6
	HMC5883_MAGGAIN_8_1 = 0xE0   // +/- 8.1
} hmc5883MagGain;
/*=========================================================================*/

class Compass
{
 protected:


 public:
	void init(bool withOffset);
	float getOrientation();
};

#endif

