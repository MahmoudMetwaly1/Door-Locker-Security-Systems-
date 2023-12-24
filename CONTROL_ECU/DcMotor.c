/*============================================================================================
 * FILE NAME:            DcMotor.C
 * AUTHER :              MAHMOUD METWALY
 * DATE CREATED :        7/10/2022
 * DESCRIPTION :         DCMOTOR DRIVER

 ===========================================================================================*/
#include "dcmotor.h"
#include "gpio.h"
#include "common_macros.h"

/*-------------------------------- global variables -------------------------------------*/
volatile uint8 g_DutyCycle = 0;

/*---------------------------------- Function Definition --------------------------------*/

/*
 * [Function Name] : DcMotor_Init()
 * [Description]   : The Function responsible for setup the direction for the two
                            motor pins through the GPIO driver
 *Stop at the DC-Motor at the beginning through the GPIO driver.
 *[ARG]            :  No ARG
 *
 * [Return]        : Void
 */
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,DC_MOTOR_PINA_ID,PIN_OUTPUT); //set the Direction of DC motor PIN A as OUTPUT
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID,DC_MOTOR_PINB_ID,PIN_OUTPUT); //set the Direction of DC motor PIN B as OUTPUT
	/* Dc Motor is Stop At The First */
	GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PINA_ID,LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PINB_ID,LOGIC_LOW);
}

/*
 * [Function Name] : LCD_displayStringRowColumn()
 * [Description]   : The function responsible for rotate the DC Motor CW/ or A-CW or
                           stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the
               required speed value.
 *[ARG]            :
 *
 *[in]        DcMotor_State state:
 *                       This Arg Indicate To The state of DC Motor CW , ACW or STOP.
 *            uint8 speed:
 *                       This Arg Indicate To The Speed of DC MOtor.
 *
 * [Return]        : Void
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	if(state == DC_STOP)
	{
		/* Stop the DC Motor By set PINA and PINB = 0*/
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PINA_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PINB_ID,LOGIC_LOW);
	}
	else if(state == DC_CW)
	{
		/* the DC Motor rotate CW By set PINA = 0 and PINB = 1*/

		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PINA_ID,LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PINB_ID,LOGIC_HIGH);
	}
	else if(state == DC_A_CW)
	{
		/* the DC Motor rotate A_CW By set PINA = 1 and PINB = 0*/

		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PINA_ID,LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PORT_ID,DC_MOTOR_PINB_ID,LOGIC_LOW);
	}
	/* Calculate the duty cycle to control the  motor speed */
	 g_DutyCycle = (uint8)((uint16)0xFF * speed / 100);
}
