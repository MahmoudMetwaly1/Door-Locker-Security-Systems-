/*============================================================================================
 * FILE NAME:            control_ecu.h
 * AUTHER :              MAHMOUD METWALY

 ===========================================================================================*/


#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_

/*---------------------------------INCLUDES-----------------------------*/

#include "std_types.h"

/*------------------------ Definitions and Configuration ------------------------------------*/

#define pass_length    (5)
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
 * [Function Name] : home_screen
 * [Description]   : receive the selection from the home screen
 *[ARG]            : no arg

 * [Return]        : Void
 */
uint8 home_screen(void);

/*
 * [Function Name] : newPassward
 * [Description]   : receive the password from  the HMI and store it in string  to create the password
 *[ARG]            :
 *[in]             :uint8 *str1
                        the arg indicate to the string will receive the password
 *
 * [Return]        : Void
 */

void newPassward(uint8 *str1);

/*
 * [Function Name] : rePassward
 * [Description]   : function to reenter the password and take it from the user for confirmation
 * to create the password.
 **[ARG]            :
 *[in]             :uint8 *str2
                        the arg indicate to the string will receive the re enter password
 *
 * [Return]        : Void
 */

void rePassward(uint8 *str2);

/*
 * [Function Name] : currentPasword
 * [Description]   : receive the password from HMI to open the system
 **[ARG]            :
 *[in]             :uint8 *str3
                        the arg indicate to the string will receive the current password
 *
 * [Return]        : Void
 */
void currentPasword (uint8 *str3);

/*
 * [Function Name] : cheakPassward
 * [Description]   :  to check two password are the same or not
 *[ARG]            :
 *
 *[in]        uint8 *str1:
 *                       This Arg Indicate To the first password
 *            uint8 *str2:
 *                       This Arg Indicate To the second password
 * [Return]        : 1 for same password or 0 for the different password;
 */
uint8 cheakPassward(uint8 *str1, uint8 *str2);

/*
 * [Function Name] : storPassward()
 * [Description]   : function to store the password in external eeprom after confirmation
 *[ARG]            :
 *[in]             :uint8 *str1
 *[in]             the arg indicate to thje password will store.
 *
 * [Return]        : Void
 */

void storPassward(uint8 *str1);

/*
 * [Function Name] : readPassward
 * [Description]   : function to read password from external eeprom
 *[ARG]            :
 *[in]             :    uint8 *str4
 *[in]             the arg indicate to string to stor the read data.
 *
 * [Return]        : Void
 */

void readPassward(uint8 *str4);

/*
 * [Function Name] : creatPassward
 * [Description]   : function to create the password after confirmation
 *[ARG]            :
 *[in]             : uint8 *str1
 *[in]             arg indicate to the first password

 *[in]             :uint8 *str2
                     arg indicate to the re enter pasword to confirmation the first password
 *
 * [Return]        : Void
 */

void creatPassward(uint8 *str1, uint8 *str2);

/*
 * [Function Name] :openDoor
 * [Description]   : function to open the Door
 *[ARG]            :
 *[in]             :uint8 *str3
                     arg indicate to the password of the system.
                   :uint8 *str4
                   arg indicate to the string that store the password read from eeprom to check with the password of the system
 *
 * [Return]        : Void
 */

void openDoor(uint8 *str3, uint8 *str4);

/*
 * [Function Name] : changePassward
 * [Description]   : function to change the password of the system
 *[ARG]            :
 *[in]             : uint8 *str1
                     arg indicate to the new password for the system
                   : uint8 *str2
                     arg indicate to the re enter  password to confirmation
                   : uint8 *str3
                   arge indicate to the password of the system
                   : uint8 *str4
                   arg indicate to the string that store the password read from eeprom to check with the password of the system
 *
 * [Return]        : Void
 */

void changePassward(uint8 *str1, uint8 *str2, uint8 *str3, uint8 *str4);

/*
 * [Function Name] : timer1_DC_processe()
 * [Description]   : the function to  call back from timer interrupt for Dc-motor action
 *[ARG]            :  No ARG
 *
 * [Return]        : Void
 */
void timer1_DC_processe(void);

/*
 * [Function Name] : timer1_buzzer_processe
 * [Description]   : the function to  call back from timer interrupt for buzzer action
 *[ARG]            :  No ARG
 *
 * [Return]        : Void
 */

void timer1_buzzer_processe(void);

/*
 * [Function Name] : TimerStartWithMotor
 * [Description]   : function to configure timer with dc motor
 *[ARG]            :  No ARG
 *
 * [Return]        : Void
 */

void TimerStartWithMotor(void);

/*
 * [Function Name] : TimerStartWithBUZZER()
 * [Description]   : function to configure timer with buzzer
 *[ARG]            :  No ARG
 *
 * [Return]        : Void
 */

void TimerStartWithBUZZER(void);


#endif /* CONTROL_ECU_H_ */
