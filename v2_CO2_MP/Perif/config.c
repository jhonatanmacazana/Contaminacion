/*
 * config.c
 *
 * Created: 20/01/2019 22:13:41
 *  Author: Jhonatan
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "config.h"
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