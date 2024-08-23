/*
 *	 Made By Eng: << Abdullah Abuslama >>
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"

 
 
void ADC_voidINIT(void)
{

	CLR_BIT(ADMUX,ADMUX_REFS1);
	SET_BIT(ADMUX,ADMUX_REFS0);


	SET_BIT(ADCSRA,ADCSRA_ADPS0);
	SET_BIT(ADCSRA,ADCSRA_ADPS1);
	SET_BIT(ADCSRA,ADCSRA_ADPS2);


	SET_BIT(ADCSRA,ADCSRA_ADEN);

}

u16 ADC_u16GetChannelReading(u8 Copy_u8ChannelNum)
{
	ADMUX &= 0b11100000;
	ADMUX |= Copy_u8ChannelNum ;

	SET_BIT(ADCSRA,ADCSRA_ADSC);

	while( (GET_BIT(ADCSRA,ADCSRA_ADIF) ) ==  0);

	SET_BIT(ADCSRA,ADCSRA_ADIF);

	return ADC ;
}
