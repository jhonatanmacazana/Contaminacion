/*
 * sensors.c
 *
 * Created: 18/01/2019 08:31:08
 *  Author: Jhonatan
 */ 

#include <avr/io.h>				// AVR
#include <avr/interrupt.h>		// IRQs
#include "sensors.h"			// Mnemonics
#include "UART.h"				// UART-HW
#include "comps.h"				// MUX 
#include <util/delay.h>			// Delay

uint16_t CO2getData()
{
	/* Declaracion de variables */
	uint8_t gasCommand[9] = {GASCOMMAND1, GASCOMMAND2, GASCOMMAND3, GASCOMMAND4, GASCOMMAND5, GASCOMMAND6, GASCOMMAND7, GASCOMMAND8, GASCOMMAND9};
	uint8_t data[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint16_t gasC = 0;
	
	/* Habilita el mux para el CO2 */
	Mux_Channel(CHANNEL_CO2);
		
	/* Envia solicitud para recibir datos */
	for(int i = 0; i<9; i++)
	{
		USART_Transmit(gasCommand[i]);
	}
	
	/* Recibe datos*/
	for(int i = 0; i<9; i++)
	{
		data[i] = USART_Receive();
	}

	/* Mascara para concetración de CO2 */
	gasC = (data[2]<<8) | (data[3]);
	
	/* Regresa la concentración de CO2*/
	return gasC;
}


void MPswitchMode(uint8_t t)
{
	/* Declaración de variables */
	uint16_t temp = START_BYTE1+START_BYTE2 +CHANGE_MODE +t;
	uint8_t LRCH = (temp>>8);
	uint8_t LRCL = temp;
	
	/* Habilita el mux para el MP */
	Mux_Channel(CHANNEL_MP);
		
	/* Solicitud para cambiar de modo */
	USART_Transmit(START_BYTE1);
	USART_Transmit(START_BYTE2);
	USART_Transmit(CHANGE_MODE);
	USART_Transmit(0x00);
	USART_Transmit(t);
	USART_Transmit(LRCH);
	USART_Transmit(LRCL);
}


void MPgetData(uint8_t *array)
{
	/* Declaración de variables */
	uint16_t temp = START_BYTE1+START_BYTE2 +READ_DATA;
	uint8_t LRCH = (temp>>8);
	uint8_t LRCL = temp;
	uint8_t Buff_MP[31];
	
	/* Habilita el mux para el MP */
	Mux_Channel(CHANNEL_MP);
		
	/* Solicitud para recibir datos */
	USART_Transmit(START_BYTE1);
	USART_Transmit(START_BYTE2);
	USART_Transmit(READ_DATA);
	USART_Transmit(0x00);
	USART_Transmit(0x00);
	USART_Transmit(LRCH);
	USART_Transmit(LRCL);
	
	/* Espera el bit de inicio */
	while (USART_Receive() != START_BYTE1){}
	
	/* Recibe datos */
	for (uint8_t i= 0; i<31; i++)
	{
		Buff_MP[i] = USART_Receive();
	}
	/* MP 2.5 */
	array[0] = Buff_MP[6];
	array[1] = Buff_MP[7];
	/* MP 10 */
	array[2] = Buff_MP[8];
	array[3] = Buff_MP[9];
}


void COswitchMode(uint8_t modo)
{
	/* Cálculo de bit de error */
	uint16_t CHECK_SUM = ~(1+SWITCH_COMMAND+modo)+1;
	
	/* Habilita el mux para el CO */
	Mux_Channel(CHANNEL_CO);
	
	/* Solicitud para cambiar de modo */
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
	
	/* Habilita el mux para el CO */
	Mux_Channel(CHANNEL_CO);
	
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
	for (uint8_t i= 0; i<8; i++)
	{
		Buff_CO[i] = USART_Receive();
	}
	
	/* Concentracion de CO */
	c = 256*Buff_CO[1] + Buff_CO[2];
	return c;
}
