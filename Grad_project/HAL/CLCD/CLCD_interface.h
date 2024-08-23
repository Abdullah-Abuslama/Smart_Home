/*
 *	 Made By Eng: << Abdullah Abuslama >>
 */
 
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

void CLCD_voidINIT(void);
void CLCD_voidSendCommand(u8 Copy_u8Command);
void CLCD_voidSendData(u8 Copy_u8Data);
void CLCD_voidSendString(u8 * Copy_u8String);
void CLCD_voidWriteNumber(u16 Copy_u16Number);
void CLCD_voidWriteNumber(u16 Copy_u16Number);
void CLCD_voidGOTOXY(u8 Copy_u8XPosition , u8 Copy_u8YPosition);

void CLCD_Clear(void);

#endif /* CLCD_INTERFACE_H_ */
