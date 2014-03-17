#include <iostream>
#include <wiringPi.h>
#include "pca9685/pca9685.h"

using namespace std;

int main (int argv, char** args)
{
	pca9685 i2c;
	
	i2c.init();
	
	int chServo = 8;
	int chEsc = 9;
	
	i2c.setPwm(chServo, 0, 330);
	delay(500);
	i2c.setPwm(chServo, 0, 400);
	delay(500);
	i2c.setPwm(chServo, 0, 330);
	
	return 0;
}
