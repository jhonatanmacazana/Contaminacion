/*
 * v3_CO2_MP_BT_HW.c
 *
 * Created: 22/01/2019 12:46:58
 * Author : Jhonatan
 */ 


#define F_CPU 1000000UL			/* F_CPU = 1 MHz		*/
#include <avr/io.h>				/* Libreria del uC		*/
#include <avr/interrupt.h>		/* Libreria de IRQs		*/
#include <util/delay.h>			/* Libreria de Delay	*/

#include "Perif/USART_irq.h"
#include "Perif/sensors.h"

/* Variables Globales */
uint8_t key;
uint8_t DATA_MP[4];
uint16_t DATA_CO;


ISR(INT0_vect)
{
	key = 1;
}


int main(void)
{
	USART_Init(MYUBRR);
	button_Init();
	sei();

	//MPswitchMode(PASSIVE_MODE);
	
	// Led de debug
	//led_debug();

	while (1) 
	{
		/* Sensores */
		if(key == 1)
		{
			key = 0;
	
			/* CO2 */
			//DATA_CO = CO2getData();
			
			//MPgetData(DATA_MP);
			
			
			//LED_ON();

			/* Debug */
			
			//sendByte0(DATA_CO>>8);
			//sendByte0(DATA_CO);
			//sendByte0(DATA_MP[0]);
			//sendByte0(DATA_MP[1]);
			//sendByte0(DATA_MP[2]);
			//sendByte0(DATA_MP[3]);
			
			
			//_delay_ms(500);
		}
		//LED_OFF();
		
	}
	return 0;
}
