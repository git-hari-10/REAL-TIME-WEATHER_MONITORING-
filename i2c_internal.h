#include "define.h"

void i2c_init()
{
	PINSEL0|=0X50;
	I2SCLL=s_val;
	I2SCLH=s_val;
	I2CONSET=ENABLE;
}

void start()
{
	I2CONSET=START;
	while(!(I2CONSET & SI));
	I2CONCLR=START;
}

void stop()
{
	I2CONSET=STOP;
	I2CONCLR=SI;
}

void write(unsigned char byte)
{
	I2DAT=byte;
	I2CONCLR=SI;
	while(!(I2CONSET & SI));
}

void no_ack()
{
	I2CONCLR=AA;
	I2CONCLR=SI;
	while(!(I2CONSET & SI));
}

void mas_ack()
{
	I2CONSET=AA;
	I2CONCLR=SI;
	while(!(I2CONSET & SI));
}

void restart()
{
	I2CONSET=START;
	I2CONCLR=SI;
	while(!(I2CONSET & SI));
	I2CONCLR=START;	
}

unsigned char read()
{
	while(!(I2CONSET & SI));
	return I2DAT;
}

