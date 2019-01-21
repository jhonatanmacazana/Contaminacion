/*
 * sensors.c
 *
 * Created: 18/01/2019 08:31:08
 *  Author: Jhonatan
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "sensors.h"
#include "UART_sw.h"

uint16_t CO2getData()
{
	uint8_t gasCommand[9] = {GASCOMMAND1, GASCOMMAND2, GASCOMMAND3, GASCOMMAND4, GASCOMMAND5, GASCOMMAND6, GASCOMMAND7, GASCOMMAND8, GASCOMMAND9};
	uint8_t data[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint16_t gasC = 0;
	for(int i = 0; i<9; i++)
	{
		sendByte1(gasCommand[i]);
	}
	
	for(int i = 0; i<9; i++)
	{
		data[i] = receiveUart1();
	}

	gasC = (data[2]<<8) | (data[3]);
	return gasC;
}