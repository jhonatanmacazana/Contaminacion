/*
 * UART_sw.c
 *
 * Created: 30/12/2018 17:38:14
 *  Author: Jhonatan
 */ 


#include <avr/io.h>				/* Libreria del uC	*/
#include <avr/interrupt.h>		/* Libreria de IRQs */
#include "UART_sw.h"


typedef enum
{
	IDLE,				// Puede transmitir y recibir.
	TRANSMIT,			// Transmitiendo un byte
	TRANSMIT_STOP_BIT,	// Transmitiendo el stop bit
	RECEIVE,			// Recibiendo un byte
	DATA_PENDING		// Byte listo para leer
} AsynchronousStates_t;


uint8_t Rx =0, Tx = 0;
static volatile AsynchronousStates_t estado;     //!< Holds the state of the UART.
static volatile uint8_t TxData;     //!< Data to be transmitted.
static volatile uint8_t TxBitCount; //!< TX bit counter.
static volatile uint8_t RxData;     //!< Storage for received bits.
static volatile uint8_t RxBitCount; //!< RX bit counter.


static uint8_t BufferRx0[RX0_BUFFER_SIZE];
static uint8_t BufferRx1[RX1_BUFFER_SIZE];
static uint8_t BufferRx2[RX2_BUFFER_SIZE];
static volatile uint8_t Rx0Head,Rx0Tail;
static volatile uint8_t Rx1Head,Rx1Tail;
static volatile uint8_t Rx2Head,Rx2Tail;


static uint8_t BufferTx0[TX0_BUFFER_SIZE];
static volatile uint8_t Tx0Head,Tx0Tail;










void uartInit(void)
{
	
	/*****************************************/
	/*              UART - AVR               */
	/*****************************************/
	
	
	UBRR0H = (MYUBRR>>8);
	UBRR0L = MYUBRR;
	
	/* Activa Modo 2X */
	UCSR0A = (1<<U2X0);
	
	/* Activa el receptor y transmisor del UART */
	UCSR0B = ((1 << RXCIE0) | (1 << RXEN0) | (1 << TXEN0));
	
	/* Frame: 8 bits de datos 1 stop bit */
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	
	
	/*****************************************/
	/*            UART - Sotware             */
	/*****************************************/
	
	/*Puerto*/
	sbi(TRXPORT1, RXBIT1);		// RX como entrada. Alta impedancia
	sbi(TRXDDR1, TXBIT1);		// TX como salida.
	setTx1( );                 	// Set the TX line to idle state.
	sbi(TRXPORT2, RXBIT2);		// RX como entrada. Alta impedancia
	sbi(TRXDDR2, TXBIT2);		// TX como salida.
	setTx2( );                 	// Set the TX line to idle state.

	/* Timer0 en modo CTC */
	TCCR0A = (1<< WGM01);
	/* Define pre escalador*/
	TCCR0B = (CS_TIMER << CS00);
	/* Define el baud rate */
	OCR0A = TICKS2COUNT;

	/* Interrupcion por cambio de estado */
	sbi(PCICR, MSK1_PORT); 			// Interrupciones del puerto
	sbi(PC1MSK, RXBIT1);			// Interrupcion del bit
	sbi(PCICR, MSK2_PORT);			// Interrupciones del puerto
	sbi(PC2MSK, RXBIT2);			// Interrupcion del bit

	/* Estado inicial = IDLE*/
	estado = IDLE;
	
	/* Flush buffers de recepción */
	Rx0Tail = 0;
	Rx0Head = 0;
	Rx1Tail = 0;
	Rx1Head = 0;
	Rx2Tail = 0;
	Rx2Head = 0;
	
}





/*****************************************/
/*           Interrupciones              */
/*****************************************/

/* Subrutina de interrupción para el pin RX */
ISR(PC1INT_vect)
{
	/* Cambia de estado*/
	estado = RECEIVE;
	
	if (leeRx1() == 0){
		Rx = 1;
		DISABLE_RX1();
	}
	else if (leeRx2() == 0){
		Rx = 2;
		DISABLE_RX2();
	}

	DISABLE_TIMER();
	STOP_TIMER();

	TCNT0 = INTERRUPT_EXEC_CYCL;	// Limpia la cuenta. Incluye tiempo para ejecutar la rutina de interrupción.

	START_TIMER();
	OCR0A = TICKS2WAITONE_HALF;		// Cuenta un periodo y medio para el muestreo.

	RxBitCount = 0;			// Limpia el contador de bits recibidos.
	CLEAN_FLAG_TIMER();
	ENABLE_TIMER();

	return;
}

#if (PUERTO1 != PUERTO2)
ISR(PC2INT_vect)
{
	/* Cambia de estado*/
	estado = RECEIVE;
	
	if (leeRx1() == 0){
		Rx = 1;
		DISABLE_RX1();
	}
	else if (leeRx2() == 0){
		Rx = 2;
		DISABLE_RX2();
	}

	DISABLE_TIMER();
	STOP_TIMER();

	TCNT0 = INTERRUPT_EXEC_CYCL;	// Limpia la cuenta. Incluye tiempo para ejecutar la rutina de interrupción.

	START_TIMER();
	OCR0A = TICKS2WAITONE_HALF;		// Cuenta un periodo y medio para el muestreo.

	RxBitCount = 0;			// Limpia el contador de bits recibidos.
	CLEAN_FLAG_TIMER();
	ENABLE_TIMER();

	return;
}
#endif


/* Timer. Mapeo de transmisión y recepción. */
ISR(TIMER0_COMPA_vect)
{
	uint8_t tmphead;
	switch(estado)
	{
		case TRANSMIT:
		if (TxBitCount < 8)
		{
			switch(Tx)
			{
				case 1:
				if (TxData & 0x01)		// Si el LSB del TX buffer es 1:
					setTx1();			// Enviar un 1 por el pin TX
				else					// De lo contrario:
					clearTx1();			// Enviar un 0 por el pin TX
				break;
				case 2:
				if (TxData & 0x01)		// Si el LSB del TX buffer es 1:
					setTx2();			// Enviar un 1 por el pin TX
				else					// De lo contrario:
					clearTx2();			// Enviar un 0 por el pin TX
				break;
				default:
				break;
			}
			
			TxData = TxData >> 1; // Shift para evaluar siguiente bit.
			TxBitCount++;			// Incrementa el contador de bits transmitidos.
		}
		else
		{
			switch(Tx)
			{
				case 1:
				setTx1();					// Enviar un 1 por el pin TX.
				break;
				case 2:
				setTx2();					// Enviar un 1 por el pin TX.
				break;
				default:
				break;
			}
			Tx = 0;
			estado = TRANSMIT_STOP_BIT;		// Cambia el estado.
		}
		break;

		case TRANSMIT_STOP_BIT:
		DISABLE_TIMER();
		/* Activa interrupción para RX*/
		ENABLE_RX1();
		ENABLE_RX2();
		estado = IDLE;				// Cambia de estado
		break;

		case RECEIVE:
		OCR0A = TICKS2WAITONE; 		//Cuenta un periodo despues de que se active la interrupción de RX.
		if (RxBitCount < 8)
		{
			RxBitCount++;					// Incrementa el contador de bits recibidos.
			RxData = (RxData>>1); 	// Shift para ordenar de LSB a MSB.
			switch (Rx)
			{
				case 1:
				if (leeRx1() != 0)		// Si lee un 1
				RxData |= 0x80;	// Se ubicará un 1 en el extremo izquierdo. (Mirror)
				break;
				case 2:
				if (leeRx2() != 0)		// Si lee un 1
				RxData |= 0x80;	// Se ubicará un 1 en el extremo izquierdo. (Mirror)
				break;
				default:
				break;
			}
		}
		else
		{
			switch(Rx)
			{
				case 1:
				tmphead = (Rx1Head +1)&RX1_BUFFER_MASK;
				Rx1Head = tmphead;
				BufferRx1[tmphead] = RxData;
				CLEAN_FLAG_RX1();			// Limpia la bandera de interrupción del pin RX.
				break;
				case 2:
				tmphead = (Rx2Head +1)&RX2_BUFFER_MASK;
				Rx2Head = tmphead;
				BufferRx2[tmphead] = RxData;
				CLEAN_FLAG_RX2();			// Limpia la bandera de interrupción del pin RX.
				break;
				default:
				break;
			}
			Rx = 0;						// Limpia bandera
			estado = DATA_PENDING;		// Cambia de estado
			DISABLE_TIMER();
			ENABLE_RX1();
			ENABLE_RX2();
		}
		break;
		default:
		estado = IDLE;			// Estado por defecto es IDLE.
	}

}

/* Buffer vacío. Empieza transmisión */
ISR(USART_UDRE_vect)
{
	uint8_t tmptail;
	if (Tx0Head != Tx0Tail) {			// Verifica si existe algun dato nuevo
		tmptail = (Tx0Tail+1) & TX0_BUFFER_MASK;	// Calcula la nueva posicion
		Tx0Tail = tmptail;				// Almacena la posición del buffer
		UDR0 = BufferTx0[tmptail];		// Transmite 
	} else {
		/* Deshabilita interrupción UDRE */
		cbi(UCSR0B, UDRIE0);
	}
	
}

/* Data nueva. Lee recepción */
ISR(USART_RX_vect)
{
	uint8_t tmphead;

	RxData = UDR0;					// Lee y almacena la data
	tmphead = (Rx0Head + 1) & RX0_BUFFER_MASK;
	Rx0Head = tmphead;
	BufferRx0[tmphead] = RxData;	// Guarda en buffer
}




/*****************************************/
/*              UART - AVR               */
/*****************************************/

uint8_t receiveUart0( void)
{
	uint8_t tmptail;
	while(Rx0Head == Rx0Tail){;};	// Espera a nueva data
	tmptail = (Rx0Tail+1) & RX0_BUFFER_MASK;
	Rx0Tail = tmptail;
	estado = IDLE;
	return BufferRx0[tmptail];
}
void sendByte0(uint8_t c)
{
	uint8_t tmphead;
	tmphead = (Tx0Head +1) & TX0_BUFFER_MASK;	// Calculo del indice
	while (tmphead == Tx0Tail){;};	// Espera a que haya espacio en el buffer
	BufferTx0[tmphead] = c;			// Almacena el dato a enviar
	Tx0Head = tmphead;				// Guarda el indice
	/* Activa Interrupcion de UART */
	sbi(UCSR0B, UDRIE0);			// Activa la interrupcion UDRE
	
}
void sendString0( char* data )
{
	while( *data != '\0' )	// Mientras exista alguna letra que no se ha enviado
	{
		sendByte0( *data );	// Envia letra por letra
		data++;					// Cambia de letra a enviar
	}
}


/*****************************************/
/*            UART - Sotware             */
/*****************************************/

uint8_t receiveUart1( void)
{
	uint8_t tmptail;
	while(Rx1Head == Rx1Tail){;};	// Espera a nueva data
	tmptail = (Rx1Tail+1) & RX1_BUFFER_MASK;
	Rx1Tail = tmptail;
	estado = IDLE;
	return BufferRx1[tmptail];
}
void sendByte1(uint8_t c)
{
	while(estado != IDLE){;} 	//Espera si esta recibiendo o transmitiendo.

	estado = TRANSMIT;			// Cambia de estado
	cbi(PC1MSK, RXBIT1);			// Desactiva interrupcion de RX
	TxData = c;           // Coloca el byte en el buffer
	TxBitCount = 0;       // Reinicia el conteo

	/* Reinicio del contador */
	TCCR0B &= ~( 1 << CS01 );		// Detiene el timer
	TCNT0 = 0;						// Limpia el registro
	sbi(TIFR0, OCF0A);					// Limpia bandera de interrupción del timer
	TCCR0B |= ( 1 << CS01 ); 		// Inicia el timer de nuevo

	/* Start Bit*/
	clearTx1();               	// TX en bajo
	Tx = 1;						// Habilita la comunicación para el UART1
	/* Activa Timer0 */
	sbi(TIMSK0, OCIE0A);       	// Activa la interrupcion por timer
}
void sendString1( char* data )
{
	while( *data != '\0' )	// Mientras exista alguna letra que no se ha enviado
	{
		sendByte1( *data );	// Envia letra por letra
		data++;					// Cambia de letra a enviar
	}
}

uint8_t receiveUart2( void)
{
	uint8_t tmptail;
	while(Rx2Head == Rx2Tail){;};	// Espera a nueva data
	tmptail = (Rx2Tail+1) & RX2_BUFFER_MASK;
	Rx2Tail = tmptail;
	estado = IDLE;
	return BufferRx2[tmptail];
}
void sendByte2(uint8_t c)
{
	while(estado != IDLE){;} 	//Espera si esta recibiendo o transmitiendo.

	estado = TRANSMIT;			// Cambia de estado
	cbi(PC2MSK, RXBIT2);			// Desactiva interrupcion de RX
	TxData = c;           // Coloca el byte en el buffer
	TxBitCount = 0;       // Reinicia el conteo

	/* Reinicio del contador */
	TCCR0B &= ~( 1 << CS01 );		// Detiene el timer
	TCNT0 = 0;						// Limpia el registro
	sbi(TIFR0, OCF0A);					// Limpia bandera de interrupción del timer
	TCCR0B |= ( 1 << CS01 ); 		// Inicia el timer de nuevo

	/* Start Bit*/
	clearTx2();               	// TX en bajo
	Tx = 2;						// Habilita la comunicación para el UART1
	/* Activa Timer0 */
	sbi(TIMSK0, OCIE0A);       	// Activa la interrupcion por timer
}
void sendString2( char* data )
{
	while( *data != '\0' )	// Mientras exista alguna letra que no se ha enviado
	{
		sendByte2( *data );	// Envia letra por letra
		data++;					// Cambia de letra a enviar
	}
}
