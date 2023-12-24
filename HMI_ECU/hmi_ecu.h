/*============================================================================================
 * FILE NAME:            hmi_ecu.h
 * AUTHER :              MAHMOUD METWALY

 ===========================================================================================*/

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

/*------------------INCLUDES---------------------------*/
#include "std_types.h"

/*--------------------------Definitions and Configuration---------------*/

#define IAM_READY      0
#define NEW_PASS       1
#define RE_PASS        2
#define currtent_pass  3
#define NOT_MATCH      4
#define HOME_SCREEN    5
#define PASS_CREATED   6
#define DOOR_OPEN      7
#define DOOR_closed    8
#define BUZZER_ON      9

/*---------------------------- Function Declaration -----------------------------------------*/

/*
 * [Function Name] : takePassward
 * [Description]   : take password from the user
 *[ARG]            : no arg

 * [Return]        : Void
 */
void takePassward(void);

/*
 * [Function Name] : homeScreen
 * [Description]   : display the home screen and take option from the user
 *[ARG]            : no arg

 * [Return]        : Void
 */
void homeScreen(void);

#endif /* HMI_ECU_H_ */
