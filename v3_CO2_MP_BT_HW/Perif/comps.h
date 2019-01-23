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



/**************************************/
/*  Configuración del Led para Debug  */
/**************************************/

#define DDR_LED		DDRD
#define PORT_LED	PORTD
#define P_LED		7

#define LED_INIT()	(DDR_LED |= (1<<P_LED))
#define LED_ON()	(PORT_LED |= (1<<P_LED))
#define LED_OFF()	(PORT_LED &= ~(1<<P_LED))
#define sec_to_ms(s)	(s*1000)

/**************************************/
/*	  Configuración del UART - MUX    */
/**************************************/

#define DDR_MUX		DDRD
#define PORT_MUX	PORTD
#define PIN_MUX		PIND
#define MUX_BIT0	5
#define MUX_BIT1	6
#define MUX_BITEN	7


#define CHANNEL_BT		0
#define CHANNEL_CO2		1
#define CHANNEL_MP		2
#define CHANNEL_CO		3

#define DELAY_MUX		500			// Delay para estabilizar el integrado en ms


#define MUX_INIT()		(DDR_MUX |= (1<<MUX_BIT0)|(1<<MUX_BIT1)|(1<<MUX_BITEN))
#define MUX_CLEAR()		(PORT_MUX &= ~((1<<MUX_BIT0)|(1<<MUX_BIT1)))
#define MUX_ENABLE()	(PORT_MUX &= ~(1<<MUX_BITEN))
#define MUX_DISABLE()	(PORT_MUX |= (1<<MUX_BITEN))

#define MUX_SEL0()		(PORT_MUX |= (1<<MUX_BIT0))
#define MUX_SEL1()		(PORT_MUX |= (1<<MUX_BIT1))





/* Funciones Globales */
void button_Init(void);
void led_debug(void);
void Mux_Channel(uint8_t channel);


#endif /* COMPS_H_ */