/*
 * I2cBus.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: fabien papleux
 */

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "I2cBus.h"

using namespace std;

/**********************************************************/
I2cBus::I2cBus()
{
	currentSlave = -1;
	fd = -1;
	ready = 0;
	init();
}

/**********************************************************/
I2cBus::~I2cBus()
{
	if (fd) close(fd);
}

/**********************************************************/
int I2cBus::init(void)
{
	ready = 0;
	if (piBoardRev() == 1) i2cPath = "/dev/i2c-0";
	else i2cPath = "/dev/i2c-1";
	if ((fd = open (i2cPath, O_RDWR)) >= 0)
		ready = 1;
	return ready;
}

/**********************************************************/
void I2cBus::setSlave (int address)
{
	// cout << "Setting new slave as 0x" << hex << address << dec << endl;
	if (! ready) return;
	if (fd < 0) return;
	if (ioctl (fd, I2C_SLAVE, address) >= 0)
		currentSlave = address;
}

/**********************************************************/
int I2cBus::isReady(void)
{
	return ready;
}

/**********************************************************/
int I2cBus::read8 (int address, int reg)
{
	if (! ready) return -1;
	if (fd < 0) return -1;
	if (address != currentSlave) setSlave(address);
	int data = wiringPiI2CReadReg8 (fd, reg);
	// cout << "Read8 addr=0x" << hex << address << " register=0x" << reg << " value=0x" << data << dec << endl;
	return data;
}

/**********************************************************/
int I2cBus::read16 (int address, int reg)
{
	if (! ready) return -1;
	if (fd < 0) return -1;
	if (address != currentSlave) setSlave(address);
	int data = wiringPiI2CReadReg16 (fd, reg);
	// cout << "Read16 addr=0x" << hex << address << " register=0x" << reg << " value=0x" << data << dec << endl;
	return data;
}

/**********************************************************/
int I2cBus::write8 (int address, int reg, int data)
{
	// cout << "Write8 addr=0x" << hex << address << " register=0x" << reg << " value=0x" << data << dec << endl;
	if (! ready) return -1;
	if (fd < 0) return -1;
	if (address != currentSlave) setSlave(address);
	return wiringPiI2CWriteReg8 (fd, reg, data);
}

/**********************************************************/
int I2cBus::write16 (int address, int reg, int data)
{
	// cout << "Write16 addr=0x" << hex << address << " register=0x" << reg << " value=0x" << data << dec << endl;
	if (! ready) return -1;
	if (fd < 0) return -1;
	if (address != currentSlave) setSlave(address);
	return wiringPiI2CWriteReg8 (fd, reg, data);
}

/**********************************************************/
void I2cBus::printStatus (void)
{
	cout << "I2C BUS Status" << endl;
	cout << "--------------" << endl;
	cout << endl;
	cout << "Is Ready              : " << (isReady() ? "Yes" : "No") << endl;
	cout << "System path           : " << i2cPath << endl;
	cout << "File Descriptor       : " << fd << endl;
	cout << "Current Slave Address : 0x" << hex << currentSlave << dec << endl;
	cout << endl;
}

