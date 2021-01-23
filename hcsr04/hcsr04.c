/*
 * Ultrasonic sensor HC-05 interfacing with ATmega16
 * http://www.electronicwings.com
 */ 

//#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "hd44780.h"/* Include LCD header file */

#define  Trigger_pin	PB0	/* Trigger pin */

volatile long long TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;
}

int main(void)
{
	char string[10];
	long count;
	double distance;
	
	DDRB = 0x01;			/* Make trigger pin as output */
	PORTD = 0xFF;			/* Turn on Pull-up */
	
	lcd_init();
	lcd_setpos(0, 0);
	lcd_print("Ultrasonic");
	//_delay_us(2000000);
	lcd_clear();
	
	TIMSK = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = 0;				/* Set all bit to zero Normal operation */
	sei();					/* Enable global interrupt */

    lcd_setpos(0, 1);
	lcd_print("Dist = ");

	while(1)
	{
		PORTB |= (1 << Trigger_pin);/* Give 10us trigger pulse on trig. pin to HC-SR04 */
		_delay_us(10);
		PORTB &= (~(1 << Trigger_pin));
		
		TCNT1 = 0;			/* Clear Timer counter */
		TCCR1B = 0x41;		/* Setting for capture rising edge, No pre-scaler*/
		TIFR = 1<<ICF1;		/* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;		/* Clear Timer Overflow flag */

		/*Calculate width of Echo by Input Capture (ICP) on PortD PD6 */		
		while ((TIFR & (1 << ICF1)) == 0);	/* Wait for rising edge */
		TCNT1 = 0;			/* Clear Timer counter */
		TCCR1B = 0x01;		/* Setting for capture falling edge, No pre-scaler */
		TIFR = 1<<ICF1;		/* Clear ICP flag (Input Capture flag) */
		TIFR = 1<<TOV1;		/* Clear Timer Overflow flag */
		TimerOverflow = 0;	/* Clear Timer overflow count */

		while ((TIFR & (1 << ICF1)) == 0); /* Wait for falling edge */
		count = ICR1 + (65535 * TimerOverflow);	/* Take value of capture register */
		/* 8MHz Timer freq, sound speed =343 m/s, calculation mentioned in doc. */
		distance = (double)count / 466.47; //58.3;

		dtostrf(distance, 2, 2, string);/* Convert distance into string */
		//dtostrf(count, 2, 2, string);
		strcat(string, " cm   ");
		lcd_setpos(7, 1);
		lcd_print(string);	/* Print distance on LDC16x2 */
		_delay_ms(200);
	}
}
