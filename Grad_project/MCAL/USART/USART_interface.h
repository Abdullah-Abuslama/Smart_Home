/*
 *	 Made By Eng: << Abdullah Abuslama >>
 */
 
#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_


void USART_voidINIT(void);
void USART_voidSendSynhronous(u8 Copy_u8Data);
u8 USART_u8ReceiveSynhronous(void);

u8 USART_u8IsDataAvailable(void);
u8 USART_u8ReceiveNonBlocking(void);

#endif /* USART_INTERFACE_H_ */
