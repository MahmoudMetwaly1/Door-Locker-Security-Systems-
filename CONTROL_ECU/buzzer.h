/*============================================================================================
 * FILE NAME:            buzzer.h
 * AUTHER :              MAHMOUD METWALY

 ===========================================================================================*/


#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

#define BUZZER_PORT_ID     PORTD_ID

#define BUZZER_PIN_ID      PIN2_ID
/*initialize the buzzer*/
void Buzzer_init(void);
/*turn on the buzzer*/
void Buzzer_on(void);
/*turn of the buzzer*/
void Buzzer_off(void);
#endif /* BUZZER_H_ */
