/*
 * AVR_USART.c
 *
 * Created: 15/12/2018 11:47:55
 * Author : Jhonatan
 */ 

/*
 * SOFT_UART_M2.c
 *
 * Created: 25/12/2018 16:41:58
 * Author : Jhonatan
 */ 

#define F_CPU		16000000UL			/* F_CPU = 1 MHz */

#include <avr/io.h>				/* Libreria del uC*/
#include <avr/interrupt.h>		/* Librearia de Delay*/
#include <util/delay.h>			/* Libreria de IRQs*/

#include "UART.h"


/* Sensor de CO */
#define FRAME_SIZE			9
#define START_BYTE			0xFF
#define SWITCH_COMMAND		0x78
#define QA_MODE				0x41
#define INITIATIVE_MODE		0x40
#define COMMAND				0x86

/* Sensor de CO */
void COswitchMode (uint8_t num);
uint16_t COgetData(void);

uint16_t Data_CO;

#define LED_ON()		(PORTD |= (1<<7))
#define LED_OFF()		(PORTD &= ~(1<<7))

int main(void)
{
	USART_Init(MYUBRR);
	DDRD|= (1<<7);
	sei();
	
	COswitchMode(QA_MODE);

	while (1)
	{
		//USART_putString("Mi numero es: ");
		//USART_putNumber(500);
		LED_ON();
		Data_CO = COgetData();
		_delay_ms(1000);
	}
	return 0;
}



/*****************************************************/
/*                  Sensor de CO                     */
/*****************************************************/

void COswitchMode(uint8_t modo)
{
	uint16_t CHECK_SUM = ~(1+SWITCH_COMMAND+modo)+1;
	USART_Transmit(START_BYTE);
	USART_Transmit(0x01);
	USART_Transmit(SWITCH_COMMAND);
	USART_Transmit(modo);
	USART_Transmit(0x00);
	USART_Transmit(0x00);
	USART_Transmit(0x00);
	USART_Transmit(0x00);
	USART_Transmit(CHECK_SUM);
}

uint16_t COgetData(void)
{
	/* Cálculo de bit de error */
	uint16_t CHECK_SUM = ~(1+COMMAND)+1;
	uint8_t Buff_CO[8];
	uint16_t c;
	
	/* Solicitud para recibir datos */
	USART_Transmit(START_BYTE);
	USART_Transmit(0x01);
	USART_Transmit(COMMAND);
	USART_Transmit(0x00);
	USART_Transmit(0x00);
	USART_Transmit(0x00);
	USART_Transmit(0x00);
	USART_Transmit(0x00);
	USART_Transmit(CHECK_SUM);
	
	/* Recibe datos */
	while (USART_Receive() != START_BYTE){}	// Espera el bit de inicio
	LED_OFF();
	for (uint8_t i= 0; i<8; i++)
	{
		Buff_CO[i] = USART_Receive();
	}
	c = 256*Buff_CO[1] + Buff_CO[2];
	return c;	
}
