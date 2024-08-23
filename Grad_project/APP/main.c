/*
 *	 Made By Eng: << Abdullah Abuslama & Mohamed ElSayed >>
 */

#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../HAL/CLCD/CLCD_interface.h"
#include "../HAL/KPD/KPD_interface.h"

#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/USART/USART_interface.h"

#include "user_data.h"

#include <util/delay.h>
#include <string.h>


#define MAX_ATTEMPTS 3
#define LED_PIN DIO_PIN4
#define THRESHOLD_HIGH 2 // Increased threshold
#define THRESHOLD_LOW 0     // Increased threshold

u32 Get_Averaged_ADC_Readings(u8 channel) {
    u32 sum = 0;
    for (u8 i = 0; i < 10; i++) {
        sum += ADC_u16GetChannelReading(channel);
        _delay_ms(10); // small delay between readings
    }
    return sum / 10; // return the average
}

void monitor_LDR_DCMotor(void)
{
//	CLCD_Clear();
//	CLCD_voidGOTOXY(0,0);
//	CLCD_voidSendString("OK, TRY USING");
//	CLCD_voidGOTOXY(1,0);
//	CLCD_voidSendString("THE ");
   // Initialize ADC if not already done
	ADC_voidINIT();
     // Set pin direction once
  //int y=100;
//    while (1)
//    {
    	//LDR

    	DIO_SetPin_Direction(DIO_PORTA, DIO_PIN7, PIN_INPUT);
        u32 x = (Get_Averaged_ADC_Readings(7) * 50) / 1024;

        DIO_SetPin_Direction(DIO_PORTA, DIO_PIN5, PIN_OUTPUT);

        if (x < 1) {
            DIO_SetPinValue(DIO_PORTA, DIO_PIN5, PIN_LOW);
            _delay_ms(100);

        } else {
            DIO_SetPinValue(DIO_PORTA, DIO_PIN5, PIN_HIGH);
            _delay_ms(100);

        }

        //--y;
        //if(y==0) break;

        //DC motor

        if(DIO_GetPinValue(DIO_PORTD, DIO_PIN3) == PIN_LOW){

        	DIO_SetPinValue(DIO_PORTD, DIO_PIN2,PIN_HIGH);
        	_delay_ms(100);

        }else{
        	DIO_SetPinValue(DIO_PORTD, DIO_PIN2,PIN_LOW);
			_delay_ms(100);
        }
//    }
}

void control_servo_motor(void);

//-------------------------------------------

void main(void) {

	DIO_SetPin_Direction(DIO_PORTD, DIO_PIN2, PIN_OUTPUT);
	DIO_SetPin_Direction(DIO_PORTD, DIO_PIN3, PIN_INPUT);
	DIO_SetPinValue(DIO_PORTD, DIO_PIN3,PIN_HIGH);

    // Initialize Ports
    DIO_SetPort_Direction(DIO_PORTC, PORT_OUTPUT);
    DIO_SetPort_Direction(DIO_PORTB, PORT_INPUT);
    DIO_SetPort_Direction(DIO_PORTA, PORT_OUTPUT);


    // Initialize Pins
    DIO_SetPin_Direction(DIO_PORTD, DIO_PIN0, PIN_INPUT);
    DIO_SetPin_Direction(DIO_PORTD, DIO_PIN1, PIN_OUTPUT);
    DIO_SetPin_Direction(DIO_PORTD, DIO_PIN5, PIN_OUTPUT);

    // Initialize Peripherals
    ADC_voidINIT();
    CLCD_voidINIT();
    KPD_voidINIT();
    GIE_voidEnable();
    USART_voidINIT();
      // Initialize the ADC

    u8 enteredUserID[USER_ID_LENGTH + 1];
    u8 enteredPassword[PASSWORD_LENGTH + 1];
    u8 attempts = 0;
    u8 currentChar;
    u8 i, j;
    u8 isPasswordCorrect = 0;
    u8 userFound = 0;


//    CLCD_Clear();
//    CLCD_voidSendString("enter home?");
//	CLCD_voidGOTOXY(1, 0);
//	CLCD_voidSendString("Yes(1) NO(2): ");
//	CLCD_voidGOTOXY(1, 14);
//	_delay_ms(500);
//	currentChar = NO_PRESSED_KEY;
//	do {
//		currentChar = KPD_GetMappedValue(KPD_u8GetPressedKey());
//
//		if (currentChar == NO_PRESSED_KEY) {
//			currentChar = USART_u8ReceiveNonBlocking();
//		}
//
//	} while (currentChar == NO_PRESSED_KEY);


	CLCD_Clear();
	while (attempts < MAX_ATTEMPTS) {
		CLCD_Clear();
		CLCD_voidSendString("ENTER USER ID:");
		CLCD_voidGOTOXY(1, 0);

		for (i = 0; i < USER_ID_LENGTH; i++) {
			do {
				currentChar = KPD_GetMappedValue(KPD_u8GetPressedKey());

				if (currentChar == NO_PRESSED_KEY) {
					currentChar = USART_u8ReceiveNonBlocking();
				}

			} while (currentChar == NO_PRESSED_KEY);

			enteredUserID[i] = currentChar;
			CLCD_voidSendData(currentChar);
			_delay_ms(300);
		}
		enteredUserID[USER_ID_LENGTH] = '\0';

		for (j = 0; j < NUM_USERS; j++) {
			if (strcmp((const char*)enteredUserID, users[j]) == 0) {
				userFound = 1;
				break;
			}
		}

		if (userFound) {
			CLCD_Clear();
			CLCD_voidSendString("ENTER PASSWORD:");
			CLCD_voidGOTOXY(1, 0);

			for (i = 0; i < PASSWORD_LENGTH; i++) {
				do {
					currentChar = KPD_GetMappedValue(KPD_u8GetPressedKey());

					if (currentChar == NO_PRESSED_KEY) {
						currentChar = USART_u8ReceiveNonBlocking();
					}

				} while (currentChar == NO_PRESSED_KEY);

				enteredPassword[i] = currentChar;
				CLCD_voidSendData('*');
				_delay_ms(300);
			}
			enteredPassword[PASSWORD_LENGTH] = '\0';

			if (strcmp((const char*)enteredPassword, passwords[j]) == 0) {
				CLCD_Clear();
				CLCD_voidSendString("ACCESS GRANTED");
				isPasswordCorrect = 1;

				_delay_ms(1000);
				// Ask if the user wants to open the door
				CLCD_Clear();
				CLCD_voidSendString("1: OPEN DOOR");
				CLCD_voidGOTOXY(1, 0);
				CLCD_voidSendString("2: CANCEL");

				while (1) {
					currentChar = KPD_GetMappedValue(KPD_u8GetPressedKey());

					if (currentChar == NO_PRESSED_KEY) {
						currentChar = USART_u8ReceiveNonBlocking();
					}

					if (currentChar == '1') {
						CLCD_Clear();
						CLCD_voidSendString("DOOR is OPEN");

						// Call the servo motor function to open the door
						control_servo_motor();

						_delay_ms(500);
						// Ask if the user wants to turn the LED on
						CLCD_Clear();
						CLCD_voidSendString("1-LEDon_2-LEDoff");
						CLCD_voidGOTOXY(1, 0);
						CLCD_voidSendString("USE LDR AND FAN");


						while (1) {

							monitor_LDR_DCMotor();


							currentChar = KPD_GetMappedValue(KPD_u8GetPressedKey());

							if (currentChar == NO_PRESSED_KEY) {
								currentChar = USART_u8ReceiveNonBlocking();
							}

							if (currentChar == '1') {

								DIO_SetPinValue(DIO_PORTA, LED_PIN, PIN_HIGH);  // Turn LED ON
								CLCD_voidGOTOXY(0,0);
								CLCD_voidSendString("                ");
								CLCD_voidGOTOXY(0,0);
								CLCD_voidSendString("LED is ON");

								// Start monitoring LDR for ambient light changes

								//break;
							} else if (currentChar == '2') {
								DIO_SetPinValue(DIO_PORTA, LED_PIN, PIN_LOW);
								CLCD_voidGOTOXY(0,0);
								CLCD_voidSendString("                ");
								CLCD_voidGOTOXY(0,0);
//								CLCD_Clear();
								CLCD_voidSendString("LED is OFF");
								//break;
							}
						}
						break;
					} else if (currentChar == '2') {
						CLCD_Clear();
						CLCD_voidSendString("OPERATION CANCELLED");
						break;
					}
				}
				break;
			} else {
				CLCD_Clear();
				CLCD_voidSendString("INCORRECT");
				_delay_ms(2000);
			}
		} else {
			CLCD_Clear();
			CLCD_voidSendString("INVALID USER ID");
			_delay_ms(2000);
		}

		attempts++;
	}

	if (!isPasswordCorrect) {
		CLCD_Clear();
		CLCD_voidSendString("ALARM TRIGGERED");
		DIO_SetPinValue(DIO_PORTA, DIO_PIN3, PIN_HIGH);
		_delay_ms(3000);
	}




	CLCD_Clear();
	CLCD_voidSendString("SEE YOU!");


}
