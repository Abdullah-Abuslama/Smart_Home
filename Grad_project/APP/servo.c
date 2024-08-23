/*
 *	 Made By Eng: << Abdullah Abuslama >>
 */


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/TIMER/TIMER_config.h"
#include "../MCAL/TIMER/TIMER_interface.h"
#include "../MCAL/EXTI/EXTI_interface.h"
#include "../MCAL/TIMER/TIMER1_interface.h"
#include "../MCAL/GIE/GIE_interface.h"
#include <util/delay.h>// Function to control the servo motor
void control_servo_motor(void) {
    TIM1_voidInit();
    TIM1_voidEnable(2);
    TIM1_voidSetIcuRegValue(20000);

    TIM1_voidSetCmpARegValue(600);
    DIO_SetPinValue(DIO_PORTD, DIO_PIN7, PIN_HIGH);
    _delay_ms(1000);
    TIM1_voidSetCmpARegValue(1400);
    DIO_SetPinValue(DIO_PORTD, DIO_PIN7, PIN_LOW);
    _delay_ms(1000);
}

