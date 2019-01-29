/*
 * v4_CO2_MP_BT_MUX_ADC.c
 *
 * Created: 23/01/2019 14:25:59
 * Author : Jhonatan
 */ 


#define F_CPU 1000000UL			/* F_CPU = 1 MHz		*/
#include <avr/io.h>				/* Libreria del uC		*/
#include <avr/interrupt.h>		/* Libreria de IRQs		*/
#include <util/delay.h>			/* Libreria de Delay	*/


#include "Perif/sensors.h"
#include "Perif/UART.h"
#include "Perif/ADC.h"
#include "Perif/RGBLED.h"
#include "Perif/LCDI2C.h"
#include "Perif/comps.h"

/************************************/
/*       Variables Globales			*/
/************************************/
/* Habilitador - sensores*/
uint8_t key;

/* Data - sensores */
uint8_t DATA_MP[4];
uint16_t DATA_MP25;
uint16_t DATA_MP10;
uint16_t DATA_CO2;
uint16_t DATA_CO; 

/* Control de timers */
uint16_t time_global, time_lcd, time_adc, time_bt;

/* Bandera de conexion */
uint8_t conexion_bt, Flag_Ack;

/* Nivel de bateria */
uint16_t bateria;

ISR(INT0_vect)
{
	key = 1;
}



int main(void)
{
	/* Comunicación con sensores y BT */
	USART_Init(MYUBRR);		// Configura UART
	MUX_INIT();				// Pines del Mux como salida
	
	/* Interfaz: LCD & boton */
	I2C_Init();				// 10 kHz
	LCD_Init();				// LCD On. Cursor off
	button_Init();			// Int0. Boton como salida
	
	/* Nivel de Batería */
	ADC_Init();				// Conversion ADC
	RGBLed_Init();			// Indicador
	
	/* Control de tiempos */
	Timer_Init();
	/* Debug */
	LED_INIT();				// Led como salida
	
	sei();					// Habilita IRQs

	/* Cambio de modo */
	MPswitchMode(PASSIVE_MODE);
	//COswitchMode(QA_MODE);
	
	/* Mensajes iniciales por LCD */
	LCD_MensajeInicial();		// Inicializando...
	LCD_MensajeTiempo(4);		// Calentando. Tiempo restante en segundos
	
	/* Reinicia el control de timers para los dispositivos */
	setTime(TIMER_LCD, 0);
	setTime(TIMER_ADC, 0);
	setTime(TIMER_BT, 0);
	setTime(TIMER_GLOBAL, 0);

	key = 1;
	DATA_CO = 0;
	conexion_bt = 1;
	while (1) 
	{
		/* Sensores */
		if(key == 1)
		{
			//key = 0;
	
			/* CO2 */
			DATA_CO2 = CO2getData();
			
			/* MP */
			MPgetData(DATA_MP);
			
			/* CO */
			//DATA_CO = COgetData();

			/* Bluetooth */
			if (conexion_bt == 1)
			{
				Flag_Ack = 1;
				Mux_Channel(CHANNEL_BT);
				USART_Transmit(DATA_CO2>>8);
				USART_Transmit(DATA_CO2);
				USART_Transmit(DATA_MP[0]);
				USART_Transmit(DATA_MP[1]);
				USART_Transmit(DATA_MP[2]);
				USART_Transmit(DATA_MP[3]);
				//USART_Transmit(DATA_CO>>8);
				//USART_Transmit(DATA_CO);
			}

		}
		
		
		/* Bateria */
		time_adc = getTime(TIMER_ADC);
		if (time_adc >= 60)
		{
			ADC_Start();
			setTime(TIMER_ADC, 0);
			bateria = ADC_GetValue();
			if (bateria >=850){ RGBLed_Color(GREEN);}
			if ((bateria >=200)&(bateria<850)){ RGBLed_Color(YELLOW);}
			if (bateria <200){ RGBLed_Color(RED);}
		}
		
		/* LCD */
		DATA_MP25 = (DATA_MP[0]<<8) | (DATA_MP[1]);
		DATA_MP10 = (DATA_MP[2]<<8) | (DATA_MP[3]);
		LCD_MensajePrincipal(DATA_CO2, DATA_MP25, DATA_MP10, DATA_CO);
		
		/* Mensaje por desconexion */
		time_bt = getTime(TIMER_BT);
		if (time_bt == 20)
		{
			setTime(TIMER_BT, 0);
			LCD_MensajeConexion(conexion_bt);		// Muestra mensaje por 3 segundos
		}
		
	}
	return 0;
}
