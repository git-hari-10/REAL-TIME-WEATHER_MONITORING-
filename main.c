#include<lpc21xx.h>
#include "i2c_external.h"
#include "temperature.h"

int main()
{
	int i;
	float temperature;
	
	lcd_init();
	i2c_init();
	spi_init();

	lcd_cmd(0x80);
	lcd_str("REAL TIME WEATHER ");
	lcd_cmd(0XC0);
	lcd_str("MONITORING SYSTEM ");
	lcd_cmd(0X94);
	lcd_str("WITH SMS ALERT  ");
	
	delay_ms(3000);
	lcd_cmd(0x01);lcd_cmd(0x80);
	lcd_str("TIME : ");
	while(1)
	{
		/* ----- REAL TIME CLOCK ----- */
		sequential_read();
		lcd_cmd(0x87);
		for(i=2;i>=0;i--)
		{
				lcd_write((a[i]/10)+'0');
				lcd_write((a[i]%10)+'0');

				if(i!=0)
						lcd_write(':');
		}
		delay_ms(900);
		/* ---- XXXXXXXXXXXXXXXX ---- */
		
		
		/* ------- TEMPERATURE ------ */
		lcd_cmd(0xC0);lcd_str("TEMP : ");
		temperature = temp(0);   					
		lcd_flt(temperature);
		/* ---- XXXXXXXXXXXXXXXX ---- */
	}
}

