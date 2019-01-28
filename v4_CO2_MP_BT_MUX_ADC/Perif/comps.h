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
#define F_CPU 1000000		// 8 MHz
#endif



/**************************************/
/*  Configuración del Led para Debug  */
/**************************************/

#define DDR_LED		DDRB
#define PORT_LED	PORTB
#define P_LED		1

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


/**************************************/
/*	    Configuración del Timer1      */
/**************************************/

#define TIMER_GLOBAL		0
#define TIMER_LCD			1
#define TIMER_ADC			2
#define TIMER_BT			3

#define TIMER_CLEAR()		(TCNT1 = 0)
#define TIMER_ENABLE()		(TIMSK1 |=  (1<<OCIE1A))
#define TIMER_DISABLE()		(TIMSK1 &= ~(1<<OCIE1A))
#define TIMER_START()		(TIMSK1 |=  (5<<CS10))
#define TIMER_STOP()		(TCCR1B &= ~ (5<<CS10))

#define TIEMPO_SENSORES		5		// En segundos



/* Funciones Globales */
void button_Init(void);

void led_debug(void);

void Mux_Channel(uint8_t channel);

void Timer_Init(void);
void setTime(uint8_t type, uint16_t newtime);
uint16_t getTime(uint8_t type);

void LCD_MensajeInicial(void);
void LCD_MensajeTiempo(uint16_t cuenta);
void LCD_MensajePrincipal(void);
void LCD_MensajeConexion(uint8_t conexion);


#endif /* COMPS_H_ */