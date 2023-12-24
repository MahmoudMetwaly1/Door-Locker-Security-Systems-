/*
 * timer.h
 *
 *  Created on: Oct 25, 2022
 *      Author: PC
 */

#ifndef TIMER_H_
#define TIMER_H_
/*--------------------INCLUDES-------------*/
#include "std_types.h"
/*--------------------enum and structure --------------*/
typedef enum{
	T1_NO_CLk, T1_CLK_1, T1_CLK_8, T1_CLK_64, T1_CLK_256, T1_CLK_1024
}Timer1_Prescaler;

typedef enum{
	T1_NORMAL_MODE, T1_COMPER_MODE
}Timer1_Mode;
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;


/*------------------------FUNCTION DECLERATION-------------------*/

/*initialize the timer*/
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
/*stop the  timer */
void Timer1_deInit(void);
/*timer call  back function for compare mode*/
void Timer1_Comp_setCallBack(void(*a_ptr)(void));
/*timer call  back function for normal mode*/
void Timer1_NORMAL_setCallBack(void(*a_ptr)(void));


#endif /* TIMER_H_ */
