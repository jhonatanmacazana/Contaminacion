/*
 * AVR_USART_MUX.c
 *
 * Created: 14/01/2019 11:40:51
 * Author : Jhonatan
 */ 

#define F_CPU	16000000UL			/* F_CPU = 1 MHz */
#define BAUD	9600
#define MYUBRR F_CPU/8/BAUD-1


/* UART - MUX */
#define DDR_MUX		DDRD
#define PORT_MUX	PORTD
#define PIN_MUX		PIND
#define MUX_BIT0	5
#define MUX_BIT1	6
#define MUX_BITEN	7

#define MUX_INIT()		(DDR_MUX |= (1<<MUX_BIT0)|(1<<MUX_BIT1)|(1<<MUX_BITEN))
#define MUX_CLEAR()		(PORT_MUX &= ~((1<<MUX_BIT0)|(1<<MUX_BIT1)))
#define MUX_ENABLE()	(PORT_MUX &= ~(1<<MUX_BITEN))
#define MUX_DISABLE()	(PORT_MUX |= (1<<MUX_BITEN))

#define MUX_SEL0()		(PORT_MUX |= (1<<MUX_BIT0))
#define MUX_SEL1()		(PORT_MUX |= (1<<MUX_BIT1))

#include <avr/io.h>				/* Libreria del uC */
#include <avr/interrupt.h>		/* Libreria de IRQs */
#include <util/delay.h>			/* Libreria de Delay */

#include "USART_irq.h"

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

#define sbi(port, pin)		(port |= (1<<pin))
#define cbi(port, pin)		(port &= ~(1<<pin))

uint8_t canal_mux;

int main(void)
{
	USART_Init(MYUBRR);
	MUX_INIT();
	sei();

	while (1) 
	{
		/* Cambia de canal */
		Mux_Channel(canal_mux);
		
		/* Tiempo para estailizar el mux */
		_delay_ms(1000);
		
		/* Echo de los caracteres recibidos */
		USART_Transmit(USART_Receive());
		
		/* Envia el canal actual*/
		USART_putString(" Canal ");
		USART_putInt(canal_mux);
		
		/* Modifica el canal ascendentemente */
		canal_mux++;
		if (canal_mux == 4)
		{
			canal_mux = 0;
		}
	}
	return 0;
}
