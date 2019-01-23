/*
 * sensors.h
 *
 * Created: 18/01/2019 08:31:16
 *  Author: Jhonatan
 */ 


#ifndef SENSORS_H_
#define SENSORS_H_


#include "comps.h"			// UART - MUX
#include "USART_irq.h"		// UART - HW

/* Sensor de CO2 */

#define GASCOMMAND1 0xFF
#define GASCOMMAND2 0x01
#define GASCOMMAND3 0x86
#define GASCOMMAND4 0x00
#define GASCOMMAND5 0x00
#define GASCOMMAND6 0x00
#define GASCOMMAND7 0x00
#define GASCOMMAND8 0x00
#define GASCOMMAND9 0x79
#define CO2HIGH 2
#define CO2LOW 3


/* Sensor de Material Particulado */

#define START_BYTE1			0x42
#define START_BYTE2			0x4D
#define READ_DATA			0xE2
#define CHANGE_MODE			0xE1
#define PASSIVE_MODE		0x00
#define ACTIVE_MODE			0x01
#define SLEEP_SET			0xE4
#define SLEEP				0x00
#define WAKE_UP				0x01

/* Prototipos */
uint16_t CO2getData(void);

void MPswitchMode(uint8_t t);

void MPgetData(uint8_t *array);


#endif /* SENSORS_H_ */