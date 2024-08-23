/*
 *	 Made By Eng: << Abdullah Abuslama >>
 */
 
//----------------------------
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
//-------------------------------------
#include "USART_private.h"
#include "USART_config.h"
#include "USART_interface.h"

 #define NO_PRESSED_KEY    0xff

void USART_voidINIT(void)
{
	u8 Local_u8UCSRCValue = 0 ;

	SET_BIT(Local_u8UCSRCValue,UCSRC_URSEL);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRCValue,UCSRC_UCSZ0);

	UCSRC = Local_u8UCSRCValue ;

	UBRRL = 51 ;

	SET_BIT(UCSRB,UCSRB_RXEN);
	SET_BIT(UCSRB,UCSRB_TXEN);
}
void USART_voidSendSynhronous(u8 Copy_u8Data)
{
	while((GET_BIT(UCSRA,UCSRA_UDRE) == 0));
	UDR = Copy_u8Data ;
}
u8 USART_u8ReceiveSynhronous(void)
{
	while((GET_BIT(UCSRA,UCSRA_RXC) == 0));
	return UDR ;
}
 

// Added Recently

u8 USART_u8IsDataAvailable(void) {
    return (UCSRA & (1 << UCSRA_RXC));  // Check if RXC bit is set, indicating data is available
}

u8 USART_u8ReceiveNonBlocking(void) {
    if (USART_u8IsDataAvailable()) {
        return UDR;  // Read data from the USART Data Register (UDR)
    }
    return NO_PRESSED_KEY;  // Return a special value indicating no data available
}
