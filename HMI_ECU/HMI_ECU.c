/*============================================================================================
 * FILE NAME:            MHI_ECU.c
 * AUTHER :              MAHMOUD METWALY

 ===========================================================================================*/

#include "hmi_ecu.h"
#include "lcd.h"
#include "keypad.h"
#include <util/delay.h> /* For the delay functions */
#include "uart.h"

static uint8 key;
void takePassward(void)
{
	uint8 i = 0;

	while(1)
	{
		/* Get the pressed key number, if any switch pressed for more than 500 ms it will considered more than one press */

		key = KEYPAD_getPressedKey();
		UART_sendByte(key);

		if(key == 13)
		{
			return;
		}
		LCD_displayCharacter('*'); /* display the pressed keypad switch */


		_delay_ms(500); /* Press time */
		i++;  /*increase the counter*/
	}
}
void homeScreen(void)
{
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "+ : Open Door");
	LCD_displayStringRowColumn(1, 0, "- : Change Pass");
	key = KEYPAD_getPressedKey();
	UART_sendByte(key);
	_delay_ms(500); /* Press time */

}
