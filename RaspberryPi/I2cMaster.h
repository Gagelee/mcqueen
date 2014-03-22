/*
 * I2cBus.h
 *
 *  Created on: Mar 19, 2014
 *      Author: fabien papleux
 */

#ifndef I2CMASTER_H_
#define I2CMASTER_H_

class I2cMaster {

public:
	I2cMaster (const char* address);
	~I2cMaster (void);

	void 	init (const char* address);
	void 	close (void);
	int 	isReady (void);

private:
	int ready;
	int fd;
};

#endif /* I2CBUS_H_ */
