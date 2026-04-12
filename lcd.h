#define D  ((0xf)<<4)  // Configured 4 5 6 7 for data pin
#define RS (1<<10)     // 10 for Register Select
#define E  (1<<11)		 // 11 for Enable

void delay_ms(int);
void lcd_cmd(unsigned char);
void lcd_write(unsigned char);
void lcd_init(void);
void lcd_str(unsigned char *);
void lcd_flt(float);
void lcd_int(int);

void lcd_init()
{
	IODIR0 |= D|RS|E;
	lcd_cmd(0x02);
	lcd_cmd(0x0C);
	lcd_cmd(0x28);
	lcd_cmd(0x01);
}

void lcd_cmd(unsigned char command)
{
		//MSB
    IOCLR0 = D;
    IOSET0 = (command & 0xf0);
    IOCLR0 = RS;
    IOSET0 = E;
    delay_ms(2);
    IOCLR0 = E;
		//LSB
    IOCLR0 = D;
    IOSET0 = ((command << 4) & 0xf0);
    IOCLR0 = RS;
    IOSET0 = E;
    delay_ms(2);
    IOCLR0 = E;
}

void lcd_write(unsigned char data)
{
		//MSB
    IOCLR0 = D;
    IOSET0 = (data & 0xf0);
    IOSET0 = RS;
    IOSET0 = E;
    delay_ms(2);
    IOCLR0 = E;
		//LSB
    IOCLR0 = D;
    IOSET0 = ((data << 4) & 0xf0);
    IOSET0 = RS;
    IOSET0 = E;
    delay_ms(2);
    IOCLR0 = E;
}

void lcd_str(unsigned char *s)
{
	while(*s)
		lcd_write(*s++);
}
   
void delay_ms(int ms)
{
	T0PR  = 15000-1;
	T0TCR = 0x01;
	while(T0TC < ms);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

void lcd_int(int n)
{
	int a[5],i;
	if(n==0)
		lcd_write('0');
	else
	{
		if(n<0)
		{
			lcd_write('-');
			n=-n;
		}
		for(i=0;n!=0;n/=10)
			a[i++]=n%10;
		for(i=i-1;i>=0;i--)
			lcd_write(a[i] + '0');
	}
}

void lcd_flt(float f)
{
	int i = f;
	lcd_int(i);
	lcd_write('.');
	i = (f - i) * 100;
	if(i < 10)
		lcd_write('0');
	lcd_int(i);
}

