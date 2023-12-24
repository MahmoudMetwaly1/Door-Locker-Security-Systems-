/*================================================================================
 * FILE NAME:            pwm.h
 * DATE CREATED :        5/10/2022
 * DESCRIPTION :         The Header File To PWM Driver
 ===============================================================================*/

#ifndef PWM_H_
#define PWM_H_
/*---------------------------------INCLUDES -----------------------*/
#include "std_types.h"

/*-------------------------- FUNCTION DECLARATION ------------------*/

/*
 * [Function Name] : PWM_Timer0_Init()
 * [Description]   : function to initialize the PWM TIMER 0.
 * And control the motor Speed.
 * [ARG]           :
 *
 *[in]        uint8 set_duty_cycle:
 *                       This Arg Indicate To The duty cycle .
 *
 * [Return]        : Void
 */
void PWM_Timer0_Init(uint8 set_duty_cycle);

#endif /* PWM_H_ */
