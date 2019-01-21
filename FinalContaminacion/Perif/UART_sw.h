/*
 * UART_sw.h
 *
 * Created: 30/12/2018 17:38:36
 *  Author: Jhonatan
 */ 

#include "config.h"

#ifndef UART_SW_H_
#define UART_SW_H_


#define MYUBRR					F_CPU/UART_BAUD_RATE/8-1

#define UART_PREESCALER			8
#define TICKS2COUNT				F_CPU/UART_BAUD_RATE/UART_PREESCALER-1 /*Ticks entre 2 bits*/
#define TICKS2WAITONE			TICKS2COUNT			/* Espera el periodo de un bit*/
#define TICKS2WAITONE_HALF		TICKS2COUNT*3/2		/* Espera el periodo de un bit y medio*/

#if UART_PREESCALER == 1
#define CS_TIMER	1
#elif UART_PREESCALER == 8
#define CS_TIMER	2
#elif UART_PREESCALER == 64
#define CS_TIMER	3
#elif UART_PREESCALER == 256
#define CS_TIMER	4
#elif UART_PREESCALER == 1024
#define CS_TIMER	5
#endif



#define INTERRUPT_EXEC_CYCL		9



#if PUERTO1 == 'B'
#define TRXDDR1  		DDRB
#define TRXPORT1 		PORTB
#define TRXPIN1  		PINB
#define PC1MSK 			PCMSK0
#define PC1IF			PCIF0
#define PC1INT_vect 	PCINT0_vect
#define MSK1_PORT 		0
#elif PUERTO1 == 'C'
#define TRXDDR1  		DDRC
#define TRXPORT1 		PORTC
#define TRXPIN1  		PINC
#define PC1MSK 			PCMSK1
#define PC1IF			PCIF1
#define PC1INT_vect 	PCINT1_vect
#define MSK1_PORT 		1
#elif PUERTO1 == 'D'
#define TRXDDR1  		DDRD
#define TRXPORT1 		PORTD
#define TRXPIN1  		PIND
#define PC1MSK 			PCMSK2
#define PC1IF			PCIF2
#define PC1INT_vect 	PCINT2_vect
#define MSK1_PORT 		2
#endif

#if PUERTO2 == 'B'
#define TRXDDR2  		DDRB
#define TRXPORT2 		PORTB
#define TRXPIN2  		PINB
#define PC2MSK 			PCMSK0
#define PC2IF			PCIF0
#define PC2INT_vect 	PCINT0_vect
#define MSK2_PORT 		0
#elif PUERTO2 == 'C'
#define TRXDDR2  		DDRC
#define TRXPORT2 		PORTC
#define TRXPIN2  		PINC
#define PC2MSK 			PCMSK1
#define PC2IF			PCIF1
#define PC2INT_vect 	PCINT1_vect
#define MSK2_PORT 		1
#elif PUERTO2 == 'D'
#define TRXDDR2  		DDRD
#define TRXPORT2 		PORTD
#define TRXPIN2  		PIND
#define PC2MSK 			PCMSK2
#define PC2IF			PCIF2
#define PC2INT_vect 	PCINT2_vect
#define MSK2_PORT 		2
#endif

#if PUERTO3 == 'B'
#define TRXDDR3  		DDRB
#define TRXPORT3 		PORTB
#define TRXPIN3  		PINB
#define PC3MSK 			PCMSK0
#define PC3IF			PCIF0
#define PC3INT_vect 	PCINT0_vect
#define MSK3_PORT 		0
#elif PUERTO3 == 'C'
#define TRXDDR3  		DDRC
#define TRXPORT3 		PORTC
#define TRXPIN3  		PINC
#define PC3MSK 			PCMSK1
#define PC3IF			PCIF1
#define PC3INT_vect 	PCINT1_vect
#define MSK3_PORT 		1
#elif PUERTO3 == 'D'
#define TRXDDR3  		DDRD
#define TRXPORT3 		PORTD
#define TRXPIN3  		PIND
#define PC3MSK 			PCMSK2
#define PC3IF			PCIF2
#define PC3INT_vect 	PCINT2_vect
#define MSK3_PORT 		2
#endif

#if PUERTO4 == 'B'
#define TRXDDR4  		DDRB
#define TRXPORT4 		PORTB
#define TRXPIN4  		PINB
#define PC4MSK 			PCMSK0
#define PC4IF			PCIF0
#define PC4INT_vect 	PCINT0_vect
#define MSK4_PORT 		0
#elif PUERTO4 == 'C'
#define TRXDDR4  		DDRC
#define TRXPORT4 		PORTC
#define TRXPIN4  		PINC
#define PC4MSK 			PCMSK1
#define PC4IF			PCIF1
#define PC4INT_vect 	PCINT1_vect
#define MSK4_PORT 		1
#elif PUERTO4 == 'D'
#define TRXDDR4  		DDRD
#define TRXPORT4 		PORTD
#define TRXPIN4  		PIND
#define PC4MSK 			PCMSK2
#define PC4IF			PCIF2
#define PC4INT_vect 	PCINT2_vect
#define MSK4_PORT 		2
#endif



/* Macros - Funciones */
#define sbi(port,bit) 		(port |=  (1 << bit))
#define cbi(port,bit) 		(port &= ~(1 << bit))
#define tog(port,bit) 		(port ^ (1 << bit))

/* Pines de transmisión y recepción */
/* USART Buffer Defines */
#define RX0_BUFFER_MASK (RX0_BUFFER_SIZE - 1)
#define RX1_BUFFER_MASK (RX1_BUFFER_SIZE - 1)
#define RX2_BUFFER_MASK (RX2_BUFFER_SIZE - 1)
#define RX3_BUFFER_MASK (RX3_BUFFER_SIZE - 1)
#define RX4_BUFFER_MASK (RX4_BUFFER_SIZE - 1)

#define TX0_BUFFER_MASK (TX0_BUFFER_SIZE - 1)


#define setTx1()      		sbi(TRXPORT1, TXBIT1)
#define clearTx1()       	cbi(TRXPORT1, TXBIT1)
#define leeRx1() 			( TRXPIN1  & ( 1 << RXBIT1 ))

#define setTx2()      		sbi(TRXPORT2, TXBIT2)
#define clearTx2()       	cbi(TRXPORT2, TXBIT2)
#define leeRx2() 			( TRXPIN2  & ( 1 << RXBIT2 ))

#define setTx3()      		sbi(TRXPORT3, TXBIT3)
#define clearTx3()       	cbi(TRXPORT3, TXBIT3)
#define leeRx3() 			( TRXPIN3  & ( 1 << RXBIT3 ))

#define setTx4()      		sbi(TRXPORT4, TXBIT4)
#define clearTx4()       	cbi(TRXPORT4, TXBIT4)
#define leeRx4() 			( TRXPIN4  & ( 1 << RXBIT4 ))

#define ENABLE_RX1()		sbi(PC1MSK, RXBIT1)
#define ENABLE_RX2()		sbi(PC2MSK, RXBIT2)
#define ENABLE_RX3()		sbi(PC3MSK, RXBIT3)
#define ENABLE_RX4()		sbi(PC4MSK, RXBIT4)

#define DISABLE_RX1()		cbi(PC1MSK, RXBIT1)
#define DISABLE_RX2()		cbi(PC2MSK, RXBIT2)
#define DISABLE_RX3()		cbi(PC3MSK, RXBIT3)
#define DISABLE_RX4()		cbi(PC4MSK, RXBIT4)

#define CLEAN_FLAG_RX1()	sbi(PCIFR, PC1IF)
#define CLEAN_FLAG_RX2()	sbi(PCIFR, PC2IF)
#define CLEAN_FLAG_RX3()	sbi(PCIFR, PC3IF)
#define CLEAN_FLAG_RX4()	sbi(PCIFR, PC4IF)

#define ENABLE_TIMER()		sbi(TIMSK0, OCIE0A)
#define DISABLE_TIMER()		cbi(TIMSK0, OCIE0A)
#define CLEAN_FLAG_TIMER()	sbi(TIFR0, OCF0A)
#define START_TIMER()		(TCCR0B = (CS_TIMER << CS00))
#define STOP_TIMER()		(TCCR0B = 0x00)

/* Prototypes*/

/* Configura el timer0, los puertos y las interrupciones de cambio de estado*/
void uartInit( uint8_t hardware, uint8_t software);

/* Enviar un Byte por cada UART */
void sendByte0(uint8_t c);
void sendByte1(uint8_t c);
void sendByte2(uint8_t c);
void sendByte3(uint8_t c);
void sendByte4(uint8_t c);

/* Enviar un String por cada UART */
void sendString0(char *data);
void sendString1(char *data);
void sendString2(char *data);
void sendString3(char *data);
void sendString4(char *data);

/* Recibir un Byte por cada UART */
uint8_t receiveUart0( void);
uint8_t receiveUart1( void);
uint8_t receiveUart2( void);
uint8_t receiveUart3( void);
uint8_t receiveUart4( void);





#endif /* UART_SW_H_ */