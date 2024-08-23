/*
 *	 Made By Eng: << Abdullah Abuslama >>
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"
#include "KPD_interface.h"

void KPD_voidINIT(void)
{
	DIO_SetPin_Direction(KPD_PORT,Column_0,PIN_OUTPUT);
	DIO_SetPin_Direction(KPD_PORT,Column_1,PIN_OUTPUT);
	DIO_SetPin_Direction(KPD_PORT,Column_2,PIN_OUTPUT);
	DIO_SetPin_Direction(KPD_PORT,Column_3,PIN_OUTPUT);

	DIO_SetPin_Direction(KPD_PORT,ROW_0,PIN_INPUT);
	DIO_SetPin_Direction(KPD_PORT,ROW_1,PIN_INPUT);
	DIO_SetPin_Direction(KPD_PORT,ROW_2,PIN_INPUT);
	DIO_SetPin_Direction(KPD_PORT,ROW_3,PIN_INPUT);

	DIO_SetPort_value(KPD_PORT,PORT_HIGH);
}


 u8 KPD_u8GetPressedKey(void)
 {
	 u8 KPD_VAL[4][4] = KPD_VAL_ARR;
	 u8 Local_u8ColumnIDX , Local_u8RowIDX ;
	 u8 Columns[4] = { Column_0 , Column_1 , Column_2 , Column_3  };
	 u8 ROWS[4] = {ROW_0 , ROW_1 , ROW_2 , ROW_3};
	 u8 Local_u8ButtonValue =  NO_PRESSED_KEY ;
	 u8 Local_u8ButtonStatus = PIN_HIGH ;
	 for(Local_u8ColumnIDX = 0 ; Local_u8ColumnIDX < 4 ; Local_u8ColumnIDX ++ )
	 {
		 /* Activate Column Index */
		 DIO_SetPinValue(KPD_PORT , Columns[Local_u8ColumnIDX],PIN_LOW);
		 for(Local_u8RowIDX = 0 ; Local_u8RowIDX < 4 ; Local_u8RowIDX ++)
		 {
			 Local_u8ButtonStatus = DIO_GetPinValue(KPD_PORT,ROWS[Local_u8RowIDX]);
			 if(Local_u8ButtonStatus == 0)
			 {
				 while( Local_u8ButtonStatus == PIN_LOW){
					 Local_u8ButtonStatus = DIO_GetPinValue(KPD_PORT,ROWS[Local_u8RowIDX]);
				 }
				 Local_u8ButtonValue = KPD_VAL[Local_u8RowIDX][Local_u8ColumnIDX] ;
				 DIO_SetPinValue(KPD_PORT , Columns[Local_u8ColumnIDX],PIN_HIGH);
				 return Local_u8ButtonValue ;
			 }
		 }
		 DIO_SetPinValue(KPD_PORT , Columns[Local_u8ColumnIDX],PIN_HIGH);
	 }
	 return Local_u8ButtonValue ;
 }

 u8 KPD_GetMappedValue(u8 key)
 {
     switch(key)
     {
         case 0: return '7';
         case 1: return '8';
         case 2: return '9';
         case 3: return 'A';
         case 4: return '4';
         case 5: return '5';
         case 6: return '6';
         case 7: return 'B';
         case 8: return '1';
         case 9: return '2';
         case 10:return '3';
         case 11:return 'C';
         case 12:return '*';
         case 13:return '0';
         case 14:return '#';
         case 15:return 'D';
         default: return NO_PRESSED_KEY;  // No key pressed or invalid key
     }
 }
