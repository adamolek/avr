#include <avr/io.h>
#include <math.h>
#include <stdio.h>

#define PHR_R 4
#define PHR_L 5
#define MOTOR_L OCR1A
#define MOTOR_R OCR1B

int adc_measurement(uint8_t channel)
{
	ADMUX = (ADMUX & 0xF8) | channel;
	ADCSRA |= _BV(ADSC);
	while(ADCSRA & _BV(ADSC));
	return ADCW;
}

int main()
{
	int phr_l, phr_r;
	int limit, diff;

	/* PWM init */
	DDRB |= _BV(PB1) | _BV(PB2);
	TCCR1A |= _BV(WGM11);					/* fast PWM */
	TCCR1B |= _BV(WGM12) | _BV(WGM13);
	TCCR1A |= _BV(COM1A1) | _BV(COM1B1);	/* CTC channel A and B */
	TCCR1B |= _BV(CS10);					/* prescaler = 1 */
	ICR1 = 200;								/* PWM 40kHz */
	MOTOR_L = 0;							/* left motor, OCR1A */
	MOTOR_R = 0;							/* right motor, OCR1B */

	/* ADC init */
	ADMUX |= _BV(REFS0);
	ADCSRA |= _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
	
	phr_l = adc_measurement(PHR_L);
	phr_r = adc_measurement(PHR_R);
	limit = fmax(phr_l, phr_r);				/* minimal voltage on photoresistor to move motors */
	diff = 1023 - limit;					/* difference between maximal voltage and voltage on
											   photoresistor during start-up */
	
	while(1)
	{
		phr_l = adc_measurement(PHR_L);
		phr_r = adc_measurement(PHR_R);
		
		if(phr_r <= limit && phr_l <= limit)
		{
			/* stop motors */
			MOTOR_R = 0;
			MOTOR_L = 0;
		}
		else
		{
			/* calculate appropriate pwm value for each motor */
			phr_r -= limit;
			if(phr_r < 0)phr_r = 0;
			phr_l -= limit;
			if(phr_l < 0)phr_l = 0;
			MOTOR_L = 200 * (float)phr_l / (float)diff;
			MOTOR_L = 200 * (float)phr_r / (float)diff;
		}
	}
}
