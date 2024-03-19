/*
 * ADC.c
 *
 * Created: 20/02/2024 13:49:49
 *  Author: Eslam
 */ 


#include <avr/io.h>
#include "ADC.h"

void ADC_vinit(void){

	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
	SET_BIT(ADCSRA,ADEN);
	
	SET_BIT(ADCSRA,ADPS2);
	SET_BIT(ADCSRA,ADPS1);
	
	//SET_BIT(ADCSRA,ADATE);
	//CLR_BIT(SFIOR,0);
	//CLR_BIT(SFIOR,1);
	//CLR_BIT(SFIOR,2);
	//SET_BIT(ADCSRA,ADSC);
}

unsigned short ADC_u16Read(char channel){
		ADMUX|=channel;
	unsigned short read_val;
	
	SET_BIT(ADCSRA,ADSC);
	while(IS_BIT_SET(ADCSRA,ADSC));//stay in your position till ADIF become 1
	
	read_val=(ADCL);
	read_val|=(ADCH<<8);
	return read_val ;
}