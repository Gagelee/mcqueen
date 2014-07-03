/*
 * PwmLvSonarEz2.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: fabien papleux
 *
 */

#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <wiringPi.h>
#include "PCA9685.h"
#include "PwmLvSonarEz2.h"

using namespace std;

/**
 * -----------------------------------------------------------------------------------------------------
 * CONSTRUCTOR
 * - Initializes unit
 * -----------------------------------------------------------------------------------------------------
 */

PwmLvSonarEz2::PwmLvSonarEz2 (PCA9685* controller, int myChannel, Pin* onPin)
{
	ready = 0;
	lastPwm = -1;
	pwm = controller;
	pin = onPin;
	channel = myChannel;
	init();
}


/**
 * -----------------------------------------------------------------------------------------------------
 * DESTRUCTOR
 * -
 * -----------------------------------------------------------------------------------------------------
 */

PwmLvSonarEz2::~PwmLvSonarEz2 (void)
{
}




/**
 * -----------------------------------------------------------------------------------------------------
 * init (void)
 * Initializes the ESC and ensures that it can communicate with it
 * -----------------------------------------------------------------------------------------------------
 */

int PwmLvSonarEz2::init (void)
{
	int success;

	// start by voiding the readiness of the object
	ready = 0;


	// check if the PWM controller is ready.  If it isn't, try to reset it once.  If it still isn't
	// ready, abort initialization and return 0 (failed)
	if (! pwm->isReady()) pwm->reset();
	if (! pwm->isReady()) return 0;


	ready = 1;
	return ready;
}




/**
 * -----------------------------------------------------------------------------------------------------
 * isReady (void)
 * returns the value of 'ready'.
 * Ready is set to 1 when the unit has been successfully initialized or is generally available to
 * receive commands.
 * -----------------------------------------------------------------------------------------------------
 */

int PwmLvSonarEz2::isReady (void) { return ready; }




/**
 * -----------------------------------------------------------------------------------------------------
 * printStatus (void)
 * Sends detailed object status to the standard output.  Use for debugging when necessary.
 * -----------------------------------------------------------------------------------------------------
 */

void PwmLvSonarEz2::printStatus (void)
{
	cout << "PWM LV MaxSonar EZ2 STATUS" << endl;
	cout << "--------------" << endl << endl;
	cout << "Is Ready      : " << (isReady() ? "Yes" : "No") << endl;
	cout << endl;
}



/**
 * -----------------------------------------------------------------------------------------------------
 * getPwm (void)
 * returns the current PWM stop value.
 *
 * Note: depending on controllers, it seems that start values are either always 0 or they can be set
 * by the user.  If I remember correctly, an Arduino only takes 1 value while the PCA9685 16-channel
 * PWM controller can receive both a start and a stop value.  To simplify things, I only use one and
 * always use 0 as a start value
 * -----------------------------------------------------------------------------------------------------
 */

int PwmEsc::getPwm (void)
{
	// if the ESC is not ready or if the PWM controller is not ready, return 0 (failed)
	if ((! ready) || (! pwm->isReady())) return 0;

	// return the PWM value collected from the PWM controller
	return pwm->getPwm(channel);
}

/**
 * int on (void)
 * Turns the sensor on to get a read.
 */

int PwmLvSonarEz2::on (void) {
	return 1;
}

/**
 * int off (void)
 * Turns the sensor off when not needed for a read.
 */

int PwmLvSonarEz2::off (void) {
	return 1;
}
