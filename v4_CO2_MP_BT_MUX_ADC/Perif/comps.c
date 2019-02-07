/*
 * comps.c
 *
 * Created: 20/01/2019 22:13:41
 *  Author: Jhonatan
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "comps.h"
#include "LCDI2C.h"
#include <util/delay.h>


/**************************************/
/*      Boton de cambio de estado     */
/**************************************/
void button_Init(void)
{
	/* Rising Edge */
	EICRA |= (3 << ISC00);
	/* Activa INT0*/
	EIMSK |= (1 << INT0);
}

/**************************************/
/*  		Led para debug  		  */
/**************************************/
void led_debug(void)
{
	LED_ON();
	_delay_ms(3000);
	LED_OFF();
}


/**************************************/
/*  			  Mux 		 		  */
/**************************************/
void Mux_Channel( uint8_t channel)
{
	//MUX_ENABLE();
	MUX_CLEAR();
	switch (channel)
	{
	case 0:
		break;
	case 1:
		MUX_SEL0();
		break;
	case 2:
		MUX_SEL1();
		break;
	case 3:
		MUX_SEL0();
		MUX_SEL1();
		break;
	default:
		break;
	}
}


/**************************************/
/*  			Timer1 		 		  */
/**************************************/


uint16_t segundos, segundosLCD, segundosADC, segundosBT;

void Timer_Init(void)
{
	/* Modo CTC. Prescaler = 1024 */
	TCCR1B = (1 << WGM12) | (5 << CS10);

	/* Reinicia la cuenta */
	TCNT1 = 0;

	/* Comparador = 1 seg */
	OCR1A = 976;

	/* Habilita la interrupción por comparación*/
	TIMSK1 |= (1 << OCIE1A);

	/* Limpia banderas de interrupcion*/
	TIFR1 |= (1 << OCF1A);

}

void setTime(uint8_t type, uint16_t newtime)
{
	switch (type)
	{
	case TIMER_GLOBAL:
		segundos = newtime;
		break;

	case TIMER_LCD:
		segundosLCD = newtime;
		break;

	case TIMER_ADC:
		segundosADC = newtime;
		break;

	case TIMER_BT:
		segundosBT = newtime;
		break;

	default:
		break;
	}
}

uint16_t getTime(uint8_t type)
{
	switch (type)
	{
	case TIMER_GLOBAL:
		return segundos;
		break;

	case TIMER_LCD:
		return segundosLCD;
		break;

	case TIMER_ADC:
		return segundosADC;
		break;

	case TIMER_BT:
		return segundosBT;
		break;

	default:
		return 0;
		break;
	}
}

ISR(TIMER1_COMPA_vect)
{
	segundos++;
	segundosLCD++;
	segundosADC++;
	segundosBT++;
}




/**************************************/
/*  		 Mensajes LCD 	 		  */
/**************************************/
void LCD_MensajeInicial(void)
{
	for (uint8_t i = 0; i < 4; i++)
	{
		LCD_Up();
		LCD_String("Inicializando   ");
		LCD_GotoXY(0, 13);
		_delay_ms(200);
		LCD_String(".");
		_delay_ms(200);
		LCD_String(".");
		_delay_ms(200);
		LCD_String(".");
		_delay_ms(200);
	}

}

void LCD_MensajeTiempo(uint16_t cuenta)
{
	uint16_t tiempo = 0;
	setTime(TIMER_LCD, 0);

	LCD_Up();
	LCD_String("Calentando       ");
	while (tiempo != cuenta)
	{
		tiempo = getTime(TIMER_LCD);
		LCD_Down();
		LCD_Number(cuenta - tiempo);
		LCD_String("        ");
		LCD_GotoXY(1, 3);
		LCD_String(" Seg. Rest.");
	}

}


void LCD_MensajePrincipal(uint16_t co2data, uint16_t mp25data, uint16_t mp10data, uint16_t codata)
{
	uint16_t tiempo = getTime(TIMER_LCD);
	if (tiempo < TIEMPO_SENSORES)
	{
		LCD_Up();
		LCD_String("   Medidor de    ");
		LCD_Down();
		LCD_String("calidad del aire ");
	}
	else if (tiempo < (2 * TIEMPO_SENSORES) )
	{
		LCD_Up();
		LCD_String("CO2             ");
		LCD_Down();
		LCD_Number(co2data);
		LCD_String(" ppm             ");
	}
	else if (tiempo < (3 * TIEMPO_SENSORES) )
	{
		LCD_Up();
		LCD_String("PM 2.5          ");
		LCD_Down();
		LCD_Number(mp25data/1000);
		LCD_String(".");
		LCD_Number(mp25data%1000);
		LCD_String(" ppm            ");
	}
	else if (tiempo < (4 * TIEMPO_SENSORES))
	{
		LCD_Up();
		LCD_String("PM 10           ");
		LCD_Down();
		LCD_Number(mp10data/1000);
		LCD_String(".");
		LCD_Number(mp10data%1000);
		LCD_String(" ppm            ");
	}
	else if (tiempo < (5 * TIEMPO_SENSORES) )
	{
		LCD_Up();
		LCD_String("CO             ");
		LCD_Down();
		LCD_Number(codata);
		LCD_String(" ppm            ");
	}
	else
	{
		setTime(TIMER_LCD, 0);
	}
}

void LCD_MensajeConexion(uint8_t conexion)
{
	if (conexion == 0)
	{
		/* Si no hay conexion */
		LCD_Up();
		LCD_String("Estado:         ");
		LCD_Down();
		LCD_String("Desconectado    ");
	}
	else if (conexion == 1)				// No se muestra nada
	{
		/* Si hay conexion */
		/*LCD_Up();
		LCD_String("Estado:         ");
		LCD_Down();
		LCD_String("Conectado       ");
		*/
	}
	_delay_ms(3000);
}




/**************************************/
/*  		   Sensores				*/
/**************************************/

void CalibraSensores(uint16_t co2data, uint16_t mp25data, uint16_t mp10data, uint16_t codata)
{
	uint16_t temp;
	temp = codata;
	codata = temp/5;
	
	
	temp = co2data;
	co2data = temp - 330;
	
	
}
