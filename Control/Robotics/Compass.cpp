// 
// 
// 

#include "Compass.h"
#include "Wire.h"

static float _hmc5883_Gauss_LSB_XY =	1100.0F;		// Varies with gain
static float _hmc5883_Gauss_LSB_Z =		980.0F;			// Varies with gain
#define SENSORS_GAUSS_TO_MICROTESLA     (100)			/**< Gauss to micro-Tesla multiplier */
#define MAGNETIC_DECLINATION			0.04258603
static float offset = 0;
#define X_OFFSET 0	
#define Y_OFFSET -10.5164
void Compass::init(bool withOffset)
{
	Wire.begin();
	Wire.beginTransmission((byte)HMC5883_ADDRESS_MAG);
	Wire.write(COMPASS_MODE_REG);
	Wire.write(0x00);
	Wire.endTransmission();

	Wire.beginTransmission((byte)HMC5883_ADDRESS_MAG);
	Wire.write(COMPASS_CONF_REG_B);
	Wire.write(HMC5883_MAGGAIN_1_3);
	Wire.endTransmission();

	if (withOffset)
	{
		offset = getOrientation()*M_PI/180;
	}
}

float Compass::getOrientation() 
{
	uint8_t xH, xL, yH, yL, zH, zL;
	int16_t x, y, z;
	float magX, magY, magZ;

	Wire.beginTransmission((byte)HMC5883_ADDRESS_MAG);
	Wire.write(COMPASS_X_H);
	Wire.endTransmission();

	Wire.requestFrom((byte)HMC5883_ADDRESS_MAG, (byte)6);
	while (Wire.available() < 6) {};
	xH = Wire.read();
	xL = Wire.read();
	zH = Wire.read();
	zL = Wire.read();
	yH = Wire.read();
	yL = Wire.read();
	x = (int16_t)(xL | ((int16_t)xH << 8));
	y = (int16_t)(yL | ((int16_t)yH << 8));
	z = (int16_t)(zL | ((int16_t)zH << 8));

	magX = (x / _hmc5883_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA) - X_OFFSET;
	magY = (y / _hmc5883_Gauss_LSB_XY * SENSORS_GAUSS_TO_MICROTESLA) - Y_OFFSET;
	magZ = z / _hmc5883_Gauss_LSB_Z * SENSORS_GAUSS_TO_MICROTESLA;

	float heading = atan2(magY, magX);
	heading += MAGNETIC_DECLINATION;
	

	// Correct for when signs are reversed.
	if (heading < 0)
		heading += 2 * PI;

	// Check for wrap due to addition of declination.
	if (heading > 2 * PI)
		heading -= 2 * PI;
	heading -= offset;
	if (heading < 0)
		heading += 2 * PI;

	// Convert radians to degrees for readability.
	float headingDegrees = heading * 180 / M_PI;

	return headingDegrees;
}

