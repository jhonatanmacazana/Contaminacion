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


void MPswitchMode(uint8_t t)
{
	uint16_t temp = START_BYTE1+START_BYTE2 +CHANGE_MODE +t;
	uint8_t LRCH = (temp>>8);
	uint8_t LRCL = temp;
	/*Frame*/
	sendByte2(START_BYTE1);
	sendByte2(START_BYTE2);
	sendByte2(CHANGE_MODE);
	sendByte2(0x00);
	sendByte2(t);
	sendByte2(LRCH);
	sendByte2(LRCL);
}


void MPgetData(uint8_t *array)
{
	uint16_t temp = START_BYTE1+START_BYTE2 +READ_DATA;
	uint8_t LRCH = (temp>>8);
	uint8_t LRCL = temp;
	/*Frame*/
	sendByte2(START_BYTE1);
	sendByte2(START_BYTE2);
	sendByte2(READ_DATA);
	sendByte2(0x00);
	sendByte2(0x00);
	sendByte2(LRCH);
	sendByte2(LRCL);
	
	uint8_t Buff_MP[31];
	while (receiveUart2() != START_BYTE1){}
	
	for (uint8_t i= 0; i<31; i++)
	{
		Buff_MP[i] = receiveUart2();
	}
	/* MP 2.5 */
	array[0] = Buff_MP[6];
	array[1] = Buff_MP[7];
	/* MP 10 */
	array[2] = Buff_MP[8];
	array[3] = Buff_MP[9];
}
