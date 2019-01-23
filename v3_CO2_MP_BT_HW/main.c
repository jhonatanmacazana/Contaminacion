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


#include "Perif/sensors.h"

/* Variables Globales */
uint8_t key;
uint8_t DATA_MP[4];
uint16_t DATA_CO2;


ISR(INT0_vect)
{
	key = 1;
}


int main(void)
{
	USART_Init(MYUBRR);		// Configura UART
	button_Init();			// Int0. Boton como salida
	LED_INIT();				// Led como salida
	MUX_INIT();				// Pines del Mux como salida
	
	sei();					// Habilita IRQs

	MPswitchMode(PASSIVE_MODE);
	
	// Led de debug
	led_debug();

	while (1) 
	{
		/* Sensores */
		if(key == 1)
		{
			key = 0;
	
			/* CO2 */
			DATA_CO2 = CO2getData();
			
			/* MP */
			MPgetData(DATA_MP);
			
			
			LED_ON();	// Led de debug

			/* Bluetooth */
			Mux_Channel(CHANNEL_BT);
			_delay_ms(DELAY_MUX);
			USART_Transmit(DATA_CO2>>8);
			USART_Transmit(DATA_CO2);
			USART_Transmit(DATA_MP[0]);
			USART_Transmit(DATA_MP[1]);
			USART_Transmit(DATA_MP[2]);
			USART_Transmit(DATA_MP[3]);
		}
		LED_OFF();
		
	}
	return 0;
}
