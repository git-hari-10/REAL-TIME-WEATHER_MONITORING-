#define pclk       15000000
#define i2cspeed    100000
#define s_val  (pclk/i2cspeed)/2

#define AA 			1<<2
#define SI 			1<<3
#define STOP 		1<<4
#define START 	1<<5
#define ENABLE 	1<<6

#define s_write (0x68<<1)
#define d_add   0x00
#define s_read  ((0x68<<1)|1)

