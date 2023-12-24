/*============================================================================================
 * FILE NAME:            CONTROL_ECUMain.h
 * AUTHER :              MAHMOUD METWALY

 ===========================================================================================*/
#include "control_ecu.h"
#include "control_ecu.h"
#include "uart.h"
#include "external_eeprom.h"
#include "timer.h"
#include "dcmotor.h"
#include "twi.h"
#include "buzzer.h"
#include <avr/io.h>

uint8 newPass[pass_length];
uint8 rePass[pass_length];
uint8 currentPass[pass_length];
uint8 cheakPass[pass_length];
int main(void)
{
	SREG  |= (1<<7);   /*enable interrupt*/
	UART_ConfigType UARTConfig = {UART_8_BIT_DATA, UART_PARITY_DISABLED,UART_1_BIT,9600}; /*configuration of uart*/
	UART_init(&UARTConfig);        /*uart initialization*/

	TWI_ConfigType twiConfig = {0b00000010,400};  /*configuration of i2c*/
	TWI_init(&twiConfig);                       /*initialization of i2c*/

	Buzzer_init();   /*initialization of buzzer*/


	while(UART_recieveByte() != IAM_READY){}  /*wait until the hmi ready */
	creatPassward(newPass, rePass); /*create the password of the system*/
	while(1)
	{
		UART_sendByte(HOME_SCREEN);
		if(home_screen() == '+')
		{
			openDoor(currentPass,cheakPass );
		}
		else
		{
			changePassward(newPass, rePass, currentPass, cheakPass);
		}
	}



}



