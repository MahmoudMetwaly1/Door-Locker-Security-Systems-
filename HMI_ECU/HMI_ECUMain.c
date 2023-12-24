/*============================================================================================
 * FILE NAME:            HMI_ECUMain.h
 * AUTHER :              MAHMOUD METWALY

 ===========================================================================================*/

#include "lcd.h"
#include "keypad.h"
#include <util/delay.h> /* For the delay functions */
#include "uart.h"
#include "lcd.h"
#include "keypad.h"
#include "hmi_ecu.h"

uint8 receiveTemp;  /*temp value to receive bytes from control_ECU*/

int main(void)
{
	UART_ConfigType UARTConfig = {UART_8_BIT_DATA, UART_PARITY_DISABLED,UART_1_BIT,9600}; /*configuration of uart*/
	LCD_init();                  /*lcd initialization*/
	UART_init(&UARTConfig);      /*uart initialization */
	UART_sendByte(IAM_READY);    /*send i am ready to control_ECU to send order*/
	while(1)
	{
		receiveTemp = UART_recieveByte(); /*receive order from control_ECU*/
		switch(receiveTemp)
		{
		case NEW_PASS:
			LCD_clearScreen(); /* clear the screen */
			LCD_displayStringRowColumn(0,0,"plz enter pass:");
			LCD_moveCursor(1,0); /* Move the cursor to the second row */
			takePassward();     /*take passward from user*/
			break;

		case RE_PASS:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"plz re-enter the:");
			LCD_displayStringRowColumn(1,0,"same pass: ");
			takePassward();
			break;

		case currtent_pass:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"plz enter pass:");
			LCD_moveCursor(1,0); /* Move the cursor to the second row */
			takePassward();
			break;

		case NOT_MATCH:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"the pass unmatched");
			_delay_ms(500);
			break;

		case HOME_SCREEN:
			homeScreen();
			break;

		case PASS_CREATED:
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"PASS CREATED:");
			_delay_ms(500);
			break;

		case DOOR_OPEN:
			LCD_displayStringRowColumn(0,0,"THE DOOR OPENED:");
			LCD_displayStringRowColumn(1,0,"            ");
			break;

		case DOOR_closed:
			LCD_displayStringRowColumn(0,0,"THE DOOR CLOSED:");
			LCD_displayStringRowColumn(1,0,"            ");
			break;

		case BUZZER_ON:
			LCD_displayStringRowColumn(0,0,"      ERROR        ");
			LCD_displayStringRowColumn(1,0,"            ");
			break;

		}
	}
}
