/*
 * comps.h
 *
 * Created: 30/12/2018 19:00:08
 *  Author: Jhonatan
 */ 


#ifndef COMPS_H_
#define COMPS_H_

/* Frecuencia del uC*/
#ifndef F_CPU
#define F_CPU 8000000		// 8 MHz
#endif


/* Configuración del UART*/
#define UART_BAUD_RATE			9600
#define MYUBRR					F_CPU/8/UART_BAUD_RATE-1


/* Configuración del Led para Debug */

#define DDR_LED		DDRD
#define PORT_LED	PORTD
#define P_LED		7

#define LED_INIT()	(DDR_LED |= (1<<P_LED))
#define LED_ON()	(PORT_LED |= (1<<P_LED))
#define LED_OFF()	(PORT_LED &= ~(1<<P_LED))
#define sec_to_ms(s)	(s*1000)

/* Funciones Globales */
void button_Init(void);
void led_debug(void);


#endif /* COMPS_H_ */