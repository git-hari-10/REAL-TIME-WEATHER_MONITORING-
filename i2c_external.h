#include "i2c_internal.h"

unsigned char BCDtoDEC(unsigned char num)
{
    return ((num >> 4) * 10) + (num & 0x0F);
}

void byte_write(unsigned char data)
{
	start();
	write(s_write);
	write(d_add);
	write(data);
	stop();
}

void page_write(unsigned char *p, unsigned char byte)
{
	int i;
	start();
	write(s_write);
	write(d_add);
	for(i=0;i<byte;i++)
		write(p[i]);
	stop();
}

unsigned char random_read()
{
	unsigned char ch;
	start();
	write(s_write);
	write(d_add);
	restart();
	write(s_read);
	no_ack();
	ch=read();
	stop();
	return ch;
}

void sequential_read()
{
	int i;
	unsigned char temp;
	start();
	write(s_write);
	write(d_add);
	restart();
	write(s_read);
	for(i=0;i<3;i++)
    {
        if(i == 2)
            no_ack();  
        else
            mas_ack();
				temp = read();
				a[i] = BCDtoDEC(temp);				
    }
	stop();
}



