/*============================================================================================
 * FILE NAME:            dcmotor.h
 * AUTHER :              MAHMOUD METWALY
 * DATE CREATED :        7/10/2022
 * DESCRIPTION :         THe Header File for DCMOTOR DRIVER

 ===========================================================================================*/
#ifndef DCMOTOR_H_
#define DCMOTOR_H_

/*------------------------------------- -- INCLUDES -----------------------------------------*/
#include "std_types.h"


/*--------------------------------------- DEFINITION -----------------------------------------*/
#define DC_MOTOR_PORT_ID     PORTB_ID
#define DC_MOTOR_PINA_ID      PIN0_ID
#define DC_MOTOR_PINB_ID      PIN1_ID

/*------------------------- Extern moudle Shred global Variable -------------------------------*/

extern volatile uint8 g_DutyCycle;


/*------------------------------------------ ENUMS ---------------------------------------------*/

typedef enum
{
	DC_STOP, DC_CW, DC_A_CW
}DcMotor_State;

/*-------------------------------------FUNCION DECLARATION ------------------------------------*/

/*
 * [Function Name] : DcMotor_Init()
 * [Description]   : The Function responsible for setup the direction for the two
                            motor pins through the GPIO driver
 *Stop at the DC-Motor at the beginning through the GPIO driver.
 *[ARG]            :  No ARG
 *
 * [Return]        : Void
 */
void DcMotor_Init(void);
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
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DCMOTOR_H_ */
