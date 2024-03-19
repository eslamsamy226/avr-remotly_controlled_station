/*
 * remotely_cntrolled_station.c
 *
 * Created: 04/03/2024 11:58:22
 *  Author: Eslam
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include "USART.h"
#include <util/delay.h>
#include "Buzzer.h"
#include "LED.h"

double servo_deg(){
	UART_vSendstring(" Type sign then degree (E.g. -40 or +07)");
	UART_vSendstring("\r\n > ");
	double d=0,s=1;
	char a=UART_u8ReceiveData();
	if (a=='-')
	{
		s=-1;
	}else if(a!='+')
	{
		UART_vSendstring("\r\n > Invalid input");
		return 0xff;
	}
	a=UART_u8ReceiveData();
	if (a>='0' && a<='9')
	{
		d+=(a-'0');
	}else{
	UART_vSendstring("\r\n > Invalid input");
	return 0xff;
	}		
	a=UART_u8ReceiveData();
	if (a>='0' && a<='9')
	{
		d*=10;
		d+=(a-'0');
	}else{
	UART_vSendstring("\r\n > Invalid input");
	return 0xff;
	}	
	d*=s;
	return d;
}
void type_lcd(){

	UART_vSendstring(" Press '`' to quit");
	UART_vSendstring("\r\n > ");
	char cnt=1;
	while(1){
		char x=UART_u8ReceiveData();
		if (x=='`')
		{
		
			break;
		}
		LCD_vSend_char(x);
		cnt++;
		if (cnt==17)
		{
			LCD_movecursor(2,1);
		}
		if (cnt>=33)
		{
			cnt=1;
			LCD_movecursor(1,1);
			LCD_clearscreen();			
		}
	}
}
void sample_temp(){
	long t=0;
	for (char i=0;i<50;i++)
	{
		t+=0.25*(double)ADC_u16Read(0);
		_delay_ms(10);
	}
	t/=50;
	UART_vSendstring(" Current Temperature Is :");
	UART_vSendData('0'+t/10);
	UART_vSendData('0'+t%10);
	UART_vSendstring("C");
}
void send_help_info(){
	UART_vSendstring("\r\n > HI, This is the Remote Station \r\n");
	UART_vSendstring(" > Here Are The Available Commands \r\n");
	UART_vSendstring(" > 0 -> Veiw This Help List \r\n");
	UART_vSendstring(" > 1 -> Current Temperature  \r\n");
	UART_vSendstring(" > 2 -> Type On LCD  \r\n");
	UART_vSendstring(" > 3 -> Clear LCD  \r\n");
	UART_vSendstring(" > 4 -> Move Servo\r\n");
	UART_vSendstring(" > 5 -> Toggel Buzzer");

}
char buz=0;

int main(void)
{
	char temp;
	double c=0xff;
	LCD_vInit();
	ADC_vinit();
	UART_vInit(9600);
	Buzzer_vInit('C',1);
	_delay_ms(1000);
	send_help_info();
	UART_vSendstring("\r\n > ");
	
	while(1)
    {
		TCNT0=ADC_u16Read();
		char command=UART_u8ReceiveData();

		switch(command){
			case '0':
			send_help_info();
			break;
			case '1':
			sample_temp();
			break;
			case '2':
			type_lcd();
			break;
			case '3':
			LCD_clearscreen();
			break;
			case '4':
			c = servo_deg();
			TCNT0=c;
			if (c!=0xff)
			{
			servo_vmove_to(c);
				
			}
			
			break;
			case '5':
			(buz==0?Buzzer_vOn('C',1):Buzzer_vOff('C',1));
			buz=(buz+1)%2;
			break;
			default:
			UART_vSendstring("\r\n > Invalid option");
		}
		UART_vSendstring("\r\n > ");			
    }
}