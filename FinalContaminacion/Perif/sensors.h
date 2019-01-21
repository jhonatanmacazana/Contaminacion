/*
 * sensors.h
 *
 * Created: 18/01/2019 08:31:16
 *  Author: Jhonatan
 */ 


#ifndef SENSORS_H_
#define SENSORS_H_

/* Sensor de CO2 */

#define GASCOMMAND1 0xFF
#define GASCOMMAND2 0x01
#define GASCOMMAND3 0x86
#define GASCOMMAND4 0x00
#define GASCOMMAND5 0x00
#define GASCOMMAND6 0x00
#define GASCOMMAND7 0x00
#define GASCOMMAND8 0x00
#define GASCOMMAND9 0x79
#define CO2HIGH 2
#define CO2LOW 3


/* Prototipos */
uint16_t CO2getData(void);



#endif /* SENSORS_H_ */