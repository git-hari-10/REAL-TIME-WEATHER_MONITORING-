
void txd(unsigned char);
void uart_str(unsigned char*);
void uart_init(void);
void task(float);

int sms = 0;

void task(float value)
{
    if(sms==0)
    {
        uart_str("AT\r\n");
        delay_ms(500);

        uart_str("AT+CPIN?\r\n");
        delay_ms(500);

        uart_str("AT+CREG?\r\n");
        delay_ms(500);

        uart_str("AT+CMGF=1\r\n");
        delay_ms(500);

        uart_str("AT+CMGS=\"8489593859\"\r\n");
        delay_ms(500);

        if(value>35.0f)
        {
						lcd_cmd(0x01);
            uart_str("HIGH TEMPERATURE");
            lcd_cmd(0x94);
            lcd_str("HIGH TEMPERATURE");
        }
        else if(value<25.0f)
        {
						lcd_cmd(0x01);
            uart_str("LOW TEMPERATURE");
            lcd_cmd(0x94);
            lcd_str("LOW TEMPERATURE ");
        }

        delay_ms(500);
        txd(26);
        sms = 1;
    }
}

void uart_init(void)
{
    PINSEL0 |= 0x05;
    U0LCR   = 0x83;
    U0DLL   = 97;
    U0DLM   = 0;
    U0LCR   = 0x03;
}

void txd(unsigned char data)
{
    while((U0LSR & (1<<5)) == 0);
    U0THR = data;
}

void uart_str(unsigned char *data)
{
    while(*data)
        txd(*data++);
}

