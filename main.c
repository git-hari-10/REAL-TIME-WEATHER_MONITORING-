#include <lpc21xx.h>
#include "i2c_external.h"
#include "temperature.h"
#include "uart.h"

int main()
{
	int i;
	float temperature;

	lcd_init();
	i2c_init();
	spi_init();
	uart_init();

	lcd_cmd(0x80);
	lcd_str("REAL TIME WEATHER ");
	lcd_cmd(0XC0);
	lcd_str("MONITORING SYSTEM ");
	lcd_cmd(0X94);
	lcd_str("WITH SMS ALERT  ");
	delay_ms(3000);
	lcd_cmd(0x01);
	
	while(1)
	{
		// I2C  (RTC)
		lcd_cmd(0x80);
	  lcd_str("TIME : ");
    sequential_read();

    for(i=2;i>=0;i--)
    {
        lcd_write((a[i]/10)+'0');
        lcd_write((a[i]%10)+'0');

        if(i!=0)
            lcd_write(':');
    }
    delay_ms(900);

		// SPI  (ADC)
    temperature = temp(0);

    lcd_cmd(0xC0);
    lcd_str("TEMP : ");
    lcd_flt(temperature);

    if((temperature>35.0f)||(temperature<25.0f))
    {
        task(temperature);
    }
    else
    {
        sms = 0;
				IOCLR0 = IN1|IN2|BUZZ;
        lcd_cmd(0x94);
        lcd_str("NORMAL TEMPERATURE");
    }
	}
}


