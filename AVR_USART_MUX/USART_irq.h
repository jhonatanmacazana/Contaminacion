/*
 * USART_irq.h
 *
 * Created: 15/12/2018 14:32:56
 *  Author: Jhonatan
 */ 


#ifndef USART_IRQ_H_
#define USART_IRQ_H_


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