/*
 * FinalContaminacion.c
 *
 * Created: 17/01/2019 16:21:53
 * Author : Jhonatan
 */ 

#define F_CPU 8000000UL			/* F_CPU = 1 MHz */
#include <avr/io.h>				/* Libreria del uC*/
#include <avr/interrupt.h>		/* Librearia de Delay*/
#include <util/delay.h>			/* Libreria de IRQs*/

#include "Perif/UART_sw.h"
#include "Perif/sensors.h"

/* Variables Globales */
uint8_t key;
uint16_t DATA_CO;


int main(void)
{
	uartInit(1,0);		// Software UART
	button_Init();		// Boton para muestrear
	LED_INIT();			// Led debug
	sei();

	/* Debug */
	led_debug();		// 3 segundos encendido

	while (1) 
	{
		/* Sensores */
		if(key == 1)
		{
			key = 0;
	
			/* CO2 */
			DATA_CO = CO2getData();
			LED_ON();

			/* Debug */
			sendByte0(DATA_CO>>8);
			sendByte0(DATA_CO);

		}
		LED_OFF();
		
	}
	return 0;
}


ISR(INT0_vect)
{
	key = 1;
}
