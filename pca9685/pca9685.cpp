#ifndef __PCA9685_CPP_
#define __PCA9685_CPP_

#include "pca9685.h"

using namespace std;

pca9685::pca9685 (void)
{
	address = DEFAULT_ADDRESS;
	pwmFrequency = DEFAULT_PWM_FREQ;
	gpio = new Gpio();
};

pca9685::~pca9685 (void)
{
	delete gpio;
};

int pca9685::init ()
{
	gpio->init();
	gpio->i2cInit();
	return setPwmFrequency(pwmFrequency);
};

int pca9685::init (int newAddress)
{
	setAddress(newAddress);
	return init();
};

int pca9685::setPwmFrequency (int newFrequency)
{
	pwmFrequency = newFrequency;
	if (! gpio) return 0;
	if (! gpio->isReady()) return 0;
	if (! gpio->i2cIsReady()) return 0;
	sleep();
	gpio->delay(5);
	int prescale = (OSC_CLOCK / ( SCALE * pwmFrequency )) - 1;
	int returnValue = gpio->i2cWriteReg8 (address, PRESCALE_REG, prescale);
	gpio->delay(5);
	awaken();
	gpio->delay(5);
	return returnValue;
};

void pca9685::setAddress (int newAddress)
{
	address = newAddress;
};

int pca9685::sleep ()
{
	if (! gpio) return 0;
	if (! gpio->isReady()) return 0;
	if (! gpio->i2cIsReady()) return 0;
	mode1Reg = gpio->i2cReadReg8 (address, MODE1);
	return gpio->i2cWriteReg8 (address, MODE1, MODE1_SLEEP);
};

int pca9685::awaken ()
{
	if (! gpio) return 0;
	if (! gpio->isReady()) return 0;
	if (! gpio->i2cIsReady()) return 0;
	mode1Reg = gpio->i2cReadReg8 (address, MODE1);
	return gpio->i2cWriteReg8 (address, MODE1, MODE1_AI);
};

int pca9685::setPwm (int channel, int start, int stop)
{
	if (! gpio) return 0;
	if (! gpio->isReady()) return 0;
	if (! gpio->i2cIsReady()) return 0;
	
	int baseReg = (channel * 4) + 6; // converting channel number into register number
	int hiStart = start >> 8;
	int loStart = start << 8 >> 8;
	int hiStop = stop >> 8;
	int loStop = stop << 8 >> 8;
	gpio->i2cWriteReg8 (address, baseReg, loStart);
	gpio->i2cWriteReg8 (address, baseReg + 1, hiStart);
	gpio->i2cWriteReg8 (address, baseReg + 2, loStop);
	gpio->i2cWriteReg8 (address, baseReg + 4, hiStop);
	return 1;
};

#endif
