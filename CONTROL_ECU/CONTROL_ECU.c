/*============================================================================================
 * FILE NAME:            CONTROL_ECU.c
 * AUTHER :              MAHMOUD METWALY

 ===========================================================================================*/

/*----------------------------------- INCLUDES--------------------------*/
#include "control_ecu.h"
#include "timer.h"
#include "uart.h"
#include "twi.h"
#include "buzzer.h"
#include "pwm.h"
#include "dcmotor.h"
#include "external_eeprom.h"
#include <util/delay.h>

Timer1_ConfigType timerConfig = {0,7813,T1_CLK_1024,T1_COMPER_MODE}; /*timer configuration */

/*-------------------------Global Variables----------------------------*/
const static volatile uint16 eeprom_first_location = 0x0311;  /*the first address will store in eeprom */
static volatile uint16 eeprom_last_location;                  /*the last address will store in eeprom*/
uint8 g_buzzer_tick = 0;                                      /*use in buzzer action function*/
uint8 g_DC_tick = 0;                                          /*use in buzzer action function*/
uint8 g_uart_rx = 0;                                          /* to receive bytes from uart */

/*----------------------------------FUNCTION DEFINATION------------------------*/
uint8 home_screen(void)
{
	g_uart_rx= 0;
	while(1)
	{
		g_uart_rx = UART_recieveByte();   /*receive byte from hmi*/
		_delay_ms(100);

		if((g_uart_rx == '+') || (g_uart_rx == '-'))
		{
			break;
		}
	}
	return g_uart_rx;   /*return this byte */
}
void newPassward(uint8 *str1){
	UART_sendByte(NEW_PASS);  /* send NEW_PASS to hmi to indicate it to what actin it will take */
	uint8 i= 0;    /*counter*/
	while(1)
	{
		str1[i] = UART_recieveByte();    /*receive byte from hmi and store in the  string that act as password*/
		_delay_ms(100);

		if(str1[i] == 13)            /* 13 mean enter*/
		{
			str1[i] = '\0';
			break;
		}
		i++;
	}
}
void rePassward(uint8 *str2)
{
	UART_sendByte(RE_PASS); /* send NEW_PASS to hmi to indicate it to what actin it will take */
	uint8 i= 0;        /*counter*/
	while(1)
	{
		str2[i] = UART_recieveByte();      /*receive byte from hmi and store in the  string that act as password*/
		_delay_ms(100);

		if(str2[i] == 13)                     /* 13 mean enter*/
		{
			str2[i] = '\0';

			break;
		}
		i++;
	}
}
void currentPasword (uint8 *str3)
{
	UART_sendByte(currtent_pass);             /* send NEW_PASS to hmi to indicate it to what actin it will take */
	uint8 i= 0;                                /*counter*/
	while(1)
	{
		str3[i] = UART_recieveByte();           /*receive byte from hmi and store in the  string that act as password*/
		_delay_ms(100);

		if(str3[i] == 13)
		{
			str3[i] = '\0';

			break;
		}
		i++;
	}
}
uint8 cheakPassward(uint8 *str1, uint8 *str2)
{
	for(int i = 0; i < pass_length; i++)
	{
		if(str1[i] !=  str2[i])         /* check if the tow string are the same to confirmation */
		{
			UART_sendByte(NOT_MATCH);
			return 0;

		}
	}
	return 1;
}
void storPassward(uint8 *str1)
{
	uint8 i = 0;         /*counter*/
	eeprom_last_location = eeprom_first_location;   /*let the last location variable in the eeprom = the first location to increment it*/
	while(i < pass_length)
	{
		EEPROM_writeByte(eeprom_last_location, str1[i]);   /*write byte in eeprom */
		_delay_ms(100);
		eeprom_last_location++;           /*increment to the next address in eeprom*/
		i++;
	}
	EEPROM_writeByte(eeprom_last_location, '\0');   /*put null in the last element of the string*/
}
void readPassward(uint8 *str4)
{
	uint8 i = 0;
	eeprom_last_location = eeprom_first_location; /*let the last location variable in the eeprom = the first location to increment it*/
	while(i < pass_length )
	{
		EEPROM_readByte(eeprom_last_location, str4 +i);  /*read byte from eeprom */
		eeprom_last_location++;                    /*increment to the next address in eeprom*/
		i++;
	}
	EEPROM_readByte(eeprom_last_location, '\0');   /*put null in the last element of the string*/
}
void creatPassward(uint8 *str1, uint8 *str2)
{
	while(1)
	{
		newPassward(str1);      /*function to take the password you need set to the system */
		rePassward(str2);       /*function to re enter the password to confirmation */
		if(cheakPassward(str1,str2))   /*function to check if the two password are the same */
		{
			storPassward(str1);         /*function to stor the password in eeprom*/
			UART_sendByte(PASS_CREATED);  /*send to hmi that the password created */
			break;
		}
		else
		{
			continue;
		}
	}

}
void openDoor(uint8 *str3, uint8 *str4)
{
	uint8 count = 0;
	while(1)
	{
		currentPasword(str3);          /*function to take the password of the system*/
		readPassward(str4);            /*function to read the password from eeprom to confirmation*/
		if(cheakPassward(str3,str4))   /*function to check if the password enter from the user is identical with the system password */
		{

			TimerStartWithMotor();     /*DC-motor ON*/
			while(g_DC_tick <= 15)
			{
				DcMotor_Rotate(DC_CW,100);
				UART_sendByte(DOOR_OPEN);  /*send to hmi that the door is open*/

			}
			while(g_DC_tick <= 18)
			{
				DcMotor_Rotate(DC_STOP,0);
			}
			while(g_DC_tick <= 33)
			{

				DcMotor_Rotate(DC_A_CW,100);
				UART_sendByte(DOOR_closed);     /*send to hmi that the door is open*/

			}
			DcMotor_Rotate(DC_STOP,0);   /*dc motor stop*/
			Timer1_deInit();             /*timer stop*/
			break;
		}
		else                         /*if the two password not the same*/
		{
			if (count == 2)
			{
				/* Bazzer on */
				TimerStartWithBUZZER();
				while(g_buzzer_tick <= 60)
				{
					Buzzer_on();
					UART_sendByte(BUZZER_ON);  /*send to hmi that the buzzer is on*/

				}
				Buzzer_off();                   /*send to hmi that the buzzer is off*/
				Timer1_deInit();

				break;
			}
			else
			{
				count++;

				continue;
			}
		}

	}

}

void changePassward(uint8 *str1, uint8 *str2, uint8 *str3, uint8 *str4)
{
	uint8 count = 0;
	while(1)
	{
		currentPasword(str3);                 /*function to take the password of the system*/
		readPassward(str4);                   /*function to read the password from eeprom to confirmation*/
		if(cheakPassward(str4, str3))         /*function to check if the password enter from the user is identical with the system password */
		{
			creatPassward(str1,str2);          /*function to create the new password*/
			break;
		}
		else
		{
			if (count == 2)
			{
				/* Bazzer on */
				TimerStartWithBUZZER();
				while(g_buzzer_tick <= 60)
				{
					Buzzer_on();
					UART_sendByte(BUZZER_ON);

				}
				Buzzer_off();
				Timer1_deInit();

				break;
			}
			else
			{
				count++;

				continue;
			}
		}
	}
}
void timer1_DC_processe(void)
{
	g_DC_tick++;
}
void timer1_buzzer_processe(void)
{
	g_buzzer_tick++;
}

void TimerStartWithMotor(void)
{
	Timer1_Comp_setCallBack(timer1_DC_processe); /*call back function*/
	Timer1_init(&timerConfig);                   /*initialize the timer*/
	DcMotor_Init();                              /*initialize the dc motor*/
	g_DC_tick = 0;

}
void TimerStartWithBUZZER(void)
{
	Timer1_Comp_setCallBack(timer1_buzzer_processe);     /*call back function*/
	Timer1_init(&timerConfig);                           /*initialize the timer*/
	g_buzzer_tick = 0;                                   /*initialize the dc motor*/
}

