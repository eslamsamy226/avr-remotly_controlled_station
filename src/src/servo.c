/*
 * servo.c
 *
 * Created: 25/02/2024 13:50:27
 *  Author: Eslam
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include "std_macros.h"
#include <util/delay.h>
void servo_vmove_to(double degree){
	if(degree>=(-90) && degree<=90)
	{
		double step=1.5+(0.5/90)*degree;
			// for sg90
			/*double step=1.38;
				if (degree<0)
				{
						step+=(0.9/90.0)*degree;
				}else if(degree>0)
				{
						step+=(1.0/90.0)*degree;
				}*/
		SET_BIT(DDRD,5);
		TCCR1A|=0x82;
		TCCR1B|=0x18;
		ICR1=19999;
		OCR1A=1000*step;
		//start
		SET_BIT(TCCR1B,CS11);
		_delay_ms(65);
		
	}
//	TCCR1A=0;
//	TCCR1B=0;
//	TCNT1=0;
//	OCR1A=0;
//	ICR1=0;
}