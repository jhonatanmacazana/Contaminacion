/*
 * USART_irq.h
 *
 * Created: 15/12/2018 14:32:56
 *  Author: Jhonatan
 */ 


#ifndef USART_IRQ_H_
#define USART_IRQ_H_


#ifndef F_CPU
#define F_CPU	8000000UL		// 8MHz
#endif

/* Configuración del UART*/
#define UART_BAUD_RATE			9600
#define MYUBRR					F_CPU/8/UART_BAUD_RATE-1


/* USART Buffer Defines */
#define USART_RX_BUFFER_SIZE 8     /* 2,4,8,16,32,64,128 or 256 bytes */
#define USART_TX_BUFFER_SIZE 8     /* 2,4,8,16,32,64,128 or 256 bytes */
#define USART_RX_BUFFER_MASK (USART_RX_BUFFER_SIZE - 1)
#define USART_TX_BUFFER_MASK (USART_TX_BUFFER_SIZE - 1)


/* Prototypes */
void USART_Init(unsigned int ubrr_val);
unsigned char USART_Receive(void);
void USART_Transmit(unsigned char data);
void USART_putString(char* StringPtr);
void USART_putInt(uint8_t val);


#endif /* USART_IRQ_H_ */