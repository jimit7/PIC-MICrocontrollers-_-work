
#include<p18f4520.h>

#define LCD PORTD

#define RS PORTCbits.RC4
#define RW PORTCbits.RC5
#define EN PORTCbits.RC6

//***********DELAY LOOP(1ms)****************//


void delay_ms(unsigned int time)
{
	unsigned int i;
	T0CON = 0x08;
	
	for(i = 0; i < time; i++)
	{
		TMR0H = 0xF5;
		TMR0L = 0x32;

		T0CONbits.TMR0ON = 1;	//enable timer0;
		while(INTCONbits.TMR0IF == 0);

		T0CONbits.TMR0ON = 0;	//disable timer0;
		INTCONbits.TMR0IF = 0;	//clear IF flag;
	}
}

//************LCD COMMAND LOOP***********//

void lcd_cmd(unsigned char x)
{
	LCD = x;			//send value on lcd;
	RS = 0;				//select command register;
	RW = 0;				//write data on lcd;
	EN = 1;				//make enable pin high to low;
	delay_ms(1);
	EN = 0;
}

//************LCD DATA LOOP***********//

void lcd_data(unsigned char y)
{
	LCD = y;			//send value on lcd;	
	RS = 1;				//select data register;
	RW = 0;				//write data on lcd;
	EN = 1;				//make enable pin high to low;
	delay_ms(1);
	EN = 0;
}

//************DISPLAY STRING LOOP***********//

void lcd_display(const rom char *buffer)
{
	while(*buffer)
	{
		lcd_data(*buffer);
		delay_ms(1);
		buffer++;
	}
	return;
}

//************LCD INITIALIZATION***********//

void initial_lcd()
{
	lcd_cmd(0X38);			//intialization of 5X7 matrix of lcd;
 	delay_ms(1);
 	lcd_cmd(0X0C);			//display ON,cursor off;
 	delay_ms(1);
 	lcd_cmd(0X01);			//clear display screen;
 	delay_ms(1);
 	lcd_cmd(0X80);			//fource cursor to beginning of 1st line,with 0 position;
 	delay_ms(1);
}
