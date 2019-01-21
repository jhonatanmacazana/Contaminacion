/*
 * config.h
 *
 * Created: 30/12/2018 19:00:08
 *  Author: Jhonatan
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

/* Frecuencia del uC*/
#ifndef F_CPU
#define F_CPU 8000000		// 8 MHz
#endif


/* Configuración del UART*/
#define UART_BAUD_RATE			9600

/* Configuración de Puertos de UART*/

#define PUERTO1		'B'
#define TXBIT1		0
#define RXBIT1		1

#define PUERTO2		'D'
#define TXBIT2		3
#define RXBIT2		4

#define PUERTO3		'D'
#define TXBIT3		5
#define RXBIT3		6

#define PUERTO4		'C'
#define TXBIT4		1
#define RXBIT4		0

/* Configuración del Buffer de Recepción. */
#define RX0_BUFFER_SIZE 8     /* 2,4,8,16,32,64,128 or 256 bytes */
#define RX1_BUFFER_SIZE 8     /* 2,4,8,16,32,64,128 or 256 bytes */
#define RX2_BUFFER_SIZE 8     /* 2,4,8,16,32,64,128 or 256 bytes */
#define RX3_BUFFER_SIZE 8     /* 2,4,8,16,32,64,128 or 256 bytes */
#define RX4_BUFFER_SIZE 8     /* 2,4,8,16,32,64,128 or 256 bytes */

#define TX0_BUFFER_SIZE 8     /* 2,4,8,16,32,64,128 or 256 bytes */



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


#endif /* CONFIG_H_ */