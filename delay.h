void delay_ms(int milli)
{
	T0PR  = 15000 - 1;
	T0TCR = 0x01;
	while(T0TC < milli);
	T0TCR = 0x03;
	T0TCR = 0x00;
}

