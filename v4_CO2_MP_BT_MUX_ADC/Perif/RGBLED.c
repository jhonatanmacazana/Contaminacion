/*************************************************************************
 Title	:   RGB-Led library (RGBLED.c)
 Author:    Jhonatan Macazana <jhonatan.macazana@utec.edu.pe> 
 Software:  AVR-GCC 4.x
 Hardware:  Designed for ATmega328P, similar AVR devices

 DESCRIPTION
       Basic library for use a RGB Led.

       This Library uses macro definitions for the port, 
       the pin and the type of the Led. The values are only dominant colors.
       This Library does not include a function to change the brightness of
       the Led.

 USAGE
       See the C include RGBLED.h file for a description of each function
       
*****************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "RGBLED.h"


/*
**	functions
*/

/*************************************************************************
Low-level function to initialize the LED.
Input:    none
Returns:  none
*************************************************************************/
void RGBLed_Init(void)
{
	DDR_RGB |= (1<<PIN_R)|(1<<PIN_G)|(1<<PIN_B);		// Pins as output
	RGB_CLEAR();										// Turn off the pins
}

/*************************************************************************
Change the color of the RGB Led.
Input:    color 	color the led will shown
Returns:  none
*************************************************************************/
void RGBLed_Color(uint8_t color)
{
	RGB_CLEAR();
	switch(color)
	{
		case RED:
			RGB_RED();
			break;
		case GREEN:
			RGB_GREEN();
			break;
		case BLUE:
			RGB_BLUE();
			break;
		case YELLOW:
			RGB_GREEN();
			RGB_RED();
			break;
		case CYAN:
			RGB_BLUE();
			RGB_GREEN();
			break;
		case MAGENTA:
			RGB_BLUE();
			RGB_RED();
			break;
		default:
			break;
	}
	
}

/*************************************************************************
Blink the led every 250ms. The value can be modified if needed.
Input:    none
Returns:  none
*************************************************************************/
void RGBLed_Blink(void)
{
	uint8_t rgb_temp;
	rgb_temp = PORT_RGB;				// Guarda pines del puerto
	for (uint8_t i = 0; i < 3; i++)		// Parpadea 3 veces
	{
		RGB_CLEAR();
		_delay_ms(250);
		RGBLed_Color(BLUE);
		_delay_ms(250);
	}
	PORT_RGB = rgb_temp;				// Regresa pines de puerto
}

