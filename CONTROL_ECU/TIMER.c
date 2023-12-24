#include "timer.h"
#include <avr/io.h>
#include "common_macros.h"
#include <avr/interrupt.h>

static void (*g_callBackPtr)(void) = NULL_PTR;
static void (*g_callBackPtr2)(void) = NULL_PTR;

ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	/*for compare mode*/
		TCCR1A = (1 << FOC1A) | (1 << FOC1B);
		TCNT1 = Config_Ptr->initial_value;
		if((Config_Ptr->mode) == T1_COMPER_MODE)
		{
			OCR1A = Config_Ptr->compare_value;
		TIMSK = (1 << OCIE1A);
		TCCR1B = (Config_Ptr->prescaler) | ((Config_Ptr->mode)<<WGM12);

		}
		else
		{
		TIMSK = (1 << TOIE1);
		TCCR1B = (Config_Ptr->prescaler) | ((Config_Ptr->mode)<<WGM12);
		}
}
void Timer1_deInit(void)
{
	TCCR1B &= 0xF8;
}

void Timer1_Comp_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
void Timer1_NORMAL_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr2 = a_ptr;
}
