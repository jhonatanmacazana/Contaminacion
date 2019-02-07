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
uint8_t conexion_bt, Flag_Ack, contador_BT;

/* Nivel de bateria */
uint16_t bateria;

/* Prototipos */
void Check_BT(void);

ISR(INT0_vect)
{
	key = 1;
}



int main(void)
{

	_delay_ms(1500);
	/************************************/
	/*  Inicialización de componentes	*/
	/************************************/

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
	//LED_INIT();				// Led como salida
	
	sei();					// Habilita IRQs
	
	/************************************/
	/*        Inicio del programa		*/
	/************************************/

	/* Nivel de Bateria */
	ADC_Start();
	bateria = ADC_GetValue();
	if (bateria >=850){ RGBLed_Color(GREEN);}
	if ((bateria >=200)&(bateria<850)){ RGBLed_Color(YELLOW);}
	if (bateria <200){ RGBLed_Color(RED);}

	
	/* Cambio de modo de sensores */
	MPswitchMode(PASSIVE_MODE);
	COswitchMode(QA_MODE);
	
	/* Mensajes iniciales por LCD */
	LCD_MensajeInicial();		// Inicializando...
	LCD_MensajeTiempo(10);		// Calentando. Tiempo restante en segundos
	
	
	/* Reinicia el control de timers para los dispositivos */
	setTime(TIMER_LCD, 0);
	setTime(TIMER_ADC, 0);
	setTime(TIMER_BT, 0);
	setTime(TIMER_GLOBAL, 0);

	/* Inicialización de variables */
	key = 0;
	conexion_bt = 0;
	
	/* Loop Infinito */
	while (1) 
	{
		/* Revisa la conexion BT */
		Check_BT();
		
		/* Sensores */	
		if(key == 1)
		{
			key = 0;
	
			/* CO2 */
			DATA_CO2 = CO2getData();
			
			/* MP */
			MPgetData(DATA_MP);
			
			/* CO */
			DATA_CO = COgetData();
			
			/* Calibra Sensores */
			//CalibraSensores(DATA_CO2, DATA_MP25, DATA_MP10, DATA_CO);
		
			DATA_CO = DATA_CO/5 -2;
			DATA_CO2 = DATA_CO2 - 340;
			DATA_MP25 = DATA_MP25 + 6;
			DATA_MP10 = DATA_MP10 + 10;

			/* Bluetooth */
			if (conexion_bt == 1)
			{
				Flag_Ack = 1;
				Mux_Channel(CHANNEL_BT);
				USART_putNumber(DATA_CO2);
				USART_putString(",");
				USART_putNumber(DATA_MP25);
				USART_putString(",");
				USART_putNumber(DATA_MP10);
				USART_putString(",");
				USART_putNumber(DATA_CO);
				USART_putString(";");
			}

		}
		
		
		/* Bateria */
		time_adc = getTime(TIMER_ADC);
		if (time_adc >= 60)
		{
			ADC_Start();													// Inicia conversion ADC
			setTime(TIMER_ADC, 0);											// Reinicia el Timer
			bateria = ADC_GetValue();										// Calcula el valor
			if (bateria >=850){ RGBLed_Color(GREEN);}
			if ((bateria >=200)&(bateria<850)){ RGBLed_Color(YELLOW);}
			if (bateria <200){ RGBLed_Color(RED);}
		}
		
		/* LCD */
		DATA_MP25 = (DATA_MP[0]<<8) | (DATA_MP[1]);
		DATA_MP10 = (DATA_MP[2]<<8) | (DATA_MP[3]);
		LCD_MensajePrincipal(DATA_CO2, DATA_MP25, DATA_MP10, DATA_CO);
		
		
		/* Led azul. Conexion BT exitosa */
		if (contador_BT == 1)
		{
			contador_BT++;		// Solo se realiza una vez
			RGBLed_Blink();		// Led parpadea
		}
		
		
	}
	return 0;
}


void Check_BT(void)
{
	uint8_t temp;
	Mux_Channel(CHANNEL_BT);
	temp = USART_ReceiveIf();	// Verifica si hay data nueva. De lo contrario, return 0
	if (temp == 0x41)			// A
	{
		contador_BT++;
		conexion_bt = 1;		// Conexion: E
	}
	if (temp == 0x42)			// B
	{
		key = 1;				// Solicita data
	}
	//if (Flag_Ack == 1)
	//{
		//contador_BT++;
		//if (temp != 0x43)		// C
		//{
			//conexion_bt = 0;	// Conexion: NULL
			//contador_BT = 0;	// Contador reiniciado
		//}
	//}
}



