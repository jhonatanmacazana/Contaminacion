/*
 * comps.c
 *
 * Created: 20/01/2019 22:13:41
 *  Author: Jhonatan
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "comps.h"
#include <util/delay.h>

/* Funciones e interrupciones */
void button_Init(void)
{
	/* Rising Edge */
	EICRA |= (2<<ISC00);
	/* Activa INT0*/
	EIMSK |= (1<< INT0);
}

void led_debug(void)
{
	LED_ON();
	_delay_ms(3000);
	LED_OFF();
}

void Mux_Channel( uint8_t channel)
{
	MUX_ENABLE();
	MUX_CLEAR();
	switch (channel)
	{
		case 0:
		break;
		case 1:
		MUX_SEL0();
		break;
		case 2:
		MUX_SEL1();
		break;
		case 3:
		MUX_SEL0();
		MUX_SEL1();
		break;
		default:
		break;
	}
}