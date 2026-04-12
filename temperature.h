#include "lcd.h"

void spi_init(void);
float temp(unsigned char chan);
unsigned char transmit(unsigned char dat);

void spi_init(void)
{
    PINSEL1 |= 0xA8;          // P0.17=SCK1, P0.18=MISO1, P0.19=MOSI1, P0.20=GPIO
    S1SPCR   = 0x20;          // SPI enable, master mode
    S1SPCCR  = 150;           // SPI speed
    IODIR0  |= 1 << 20;       // P0.20 as CS output
    IOSET0   = 1 << 20;       // CS idle HIGH
}

unsigned char transmit(unsigned char dat)
{
    unsigned char data;
    data = S1SPSR;   // dummy read
    S1SPDR = dat;
    while(((1 << 7) & S1SPSR) == 0);
    return S1SPDR;
}

float temp(unsigned char chan)
{
    unsigned char hbyte, lbyte;
    int adc_value;
    float voltage;

    IOCLR0 = 1 << 20;             // CS LOW

    transmit(0x06);               // Start bit + single-ended mode
    hbyte = transmit(chan << 6);  // CH-0 
    lbyte = transmit(0x00);			  // Dummy write

    IOSET0 = 1 << 20;             // CS HIGH

    adc_value = (((0x0F) & hbyte) << 8) | lbyte;

    voltage = (adc_value * 3.3f) / 4096;
    return voltage * 100;
}

