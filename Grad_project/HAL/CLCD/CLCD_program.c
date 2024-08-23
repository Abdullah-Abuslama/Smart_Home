/*
 *	 Made By Eng: << Abdullah Abuslama >>
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"
#include "CLCD_interface.h"
#include <util/delay.h>

 void CLCD_voidSendCommand(u8 Copy_u8Command)
 {
	 /* Set RS For Command */

	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,PIN_LOW);

	 /* Set R/W TO write */

	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,PIN_LOW);

	 /* Send Command */

	 DIO_SetPort_value(CLCD_DATA_PORT,Copy_u8Command) ;

	 /* Enable Pulse */

	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,PIN_HIGH);

	 _delay_ms(2);

	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,PIN_LOW);
 
 }
 
 void CLCD_voidSendData(u8 Copy_u8Data)
  {
 	 /* Set RS For Command */

 	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_RS_PIN,PIN_HIGH);

 	 /* Set R/W TO write */

 	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_RW_PIN,PIN_LOW);

 	 /* Send Command */

 	 DIO_SetPort_value(CLCD_DATA_PORT,Copy_u8Data) ;

 	 /* Enable Pulse */

 	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,PIN_HIGH);

 	 _delay_ms(2);

 	 DIO_SetPinValue(CLCD_CONTROL_PORT,CLCD_E_PIN,PIN_LOW);

  }

 void CLCD_voidINIT(void)
 {
	 /* wait 50 ms */

	 _delay_ms(50);

	 /* Set Function Set */
	 CLCD_voidSendCommand(Function_Set);
	 _delay_ms(1);
	 /* Display ON/OFF Control - no cursor - no blink */
	 CLCD_voidSendCommand(Display_Control);
	 _delay_ms(1);
	 /* Display Clear */

	 CLCD_voidSendCommand(Display_Clear);
	 _delay_ms(1);
 }
 void CLCD_voidSendString(u8 * Copy_u8String)
 {
	 u8 Local_u8Counter = 0 ;

	while(Copy_u8String[Local_u8Counter] != '\0')
	{
		CLCD_voidSendData(Copy_u8String[Local_u8Counter]);
		Local_u8Counter++ ;
	}

 }
 void CLCD_voidWriteNumber(u16 Copy_u16Number)
 {
     char buffer[6];
     u8 i = 0;
     if (Copy_u16Number == 0)
     {
         CLCD_voidSendData('0');
         return;
     }
     while (Copy_u16Number > 0)
     {
         buffer[i++] = (Copy_u16Number % 10) + '0';
         Copy_u16Number /= 10;
     }
     while (i > 0)
     {
         CLCD_voidSendData(buffer[--i]);
     }
 }

 void CLCD_voidGOTOXY(u8 Copy_u8row , u8 Copy_u8col)
 {
	 u8 Local_u8Address = 0xff;

	 if(Copy_u8row>1)
	 	 {
		 	 Copy_u8row=1;
	 	 }

	 Local_u8Address = 128 + (64 * Copy_u8row) + Copy_u8col  ;
	 CLCD_voidSendCommand(Local_u8Address);
 }

 void CLCD_Clear(void)
 {
	 CLCD_voidSendCommand(Display_Clear);

 }
