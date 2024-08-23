/*
 *	 Made By Eng: << Abdullah Abuslama >>
 */

#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_PORT    DIO_PORTB

#define Column_0  	DIO_PIN0
#define Column_1  	DIO_PIN1
#define Column_2  	DIO_PIN2
#define Column_3  	DIO_PIN3

#define ROW_0 		DIO_PIN4
#define ROW_1 		DIO_PIN5
#define ROW_2 		DIO_PIN6
#define ROW_3 		DIO_PIN7

#define NO_PRESSED_KEY    0xff
#define KPD_VAL_ARR  { {0,1,2,3} ,{4,5,6,7}, {8,9,10,11},{12,13,14,15}}

#endif /* KPD_CONFIG_H_ */
