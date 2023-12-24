/*============================================================================================
 * FILE NAME:            lcd.h
 * AUTHER :              MAHMOUD METWALY
 * DATE CREATED :        5/10/2022
 * DESCRIPTION :         Header File For LCD Driver
 ===========================================================================================*/


#ifndef LCD_H_
#define LCD_H_

/*---------------------------------- INCLUDES -----------------------------------------------*/
#include "std_types.h"

/*------------------------ Definitions and Configuration ------------------------------------*/

/* LCD Data bits mode configuration, its value should be 4 or 8*/

#define LCD_DATA_BITS_MODE 4
#if((LCD_DATA_BITS_MODE != 4) && (LCD_DATA_BITS_MODE != 8))

#error "Number of Data bits should be equal to 4 or 8"

#endif

/* LCD HW Ports and Pins Ids */
/* RS PIN */
#define LCD_RS_PORT_ID           PORTA_ID
#define LCD_RS_PIN_ID            PIN6_ID

/* Enable Pin */
#define LCD_E_PORT_ID            PORTA_ID
#define LCD_E_PIN_ID             PIN5_ID

/* Data port */
#define LCD_DATA_PORT_ID         PORTA_ID

#if (LCD_DATA_BITS_MODE == 4)

#define LCD_DB4_PIN_ID                 PIN3_ID
#define LCD_DB5_PIN_ID                 PIN2_ID
#define LCD_DB6_PIN_ID                 PIN1_ID
#define LCD_DB7_PIN_ID                 PIN0_ID

#endif

/* Most Common LCD commands */
#define LCD_TWO_LINES_EIGHT_BITS_MODE        0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE         0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_Clear_Display_Screen             0x01
#define LCD_Reurn_Home                       0x02
#define LCD_Shift_Cursor_Left                0x04
#define LCD_Shift_Display_Right              0x05
#define LCD_Shift_Cursor_Right               0x06
#define LCD_Shift_Display_Left               0x07
#define LCD_Display_Off_Cursor_Off           0x08
#define LCD_Display_Off_Cursor_On            0x0A
#define LCD_Display_On_Cursor_Off            0x0C
#define LCD_Display_On_Cursor_On             0x0E
#define LCD_Display_On_Cursor_Blanking       0x0F
#define LCD_Shift_Cursor_Position_Left       0x10
#define LCD_Shift_Cursor_Position_Right      0x14
#define LCD_Shift_The_Entire_Display_Left    0x18
#define LCD_Shift_The_Entire_Display_Right   0x1C
#define LCD_Cursor_position                  0x80


/*---------------------------- Function Declaration -----------------------------------------*/
/*
 * [Function Name] : LCD_init()
 * [Description]   : Initialize the LCD:
 * 1. Setup the LCD pins directions by use the GPIO driver.
 * 2. Setup the LCD Data Mode 4-bits or 8-bits.
 *[ARG]            :  No ARG
 *
 * [Return]        : Void
 */
void LCD_init(void);
/*
 * [Function Name] : LCD_sendCommand()
 * [Description]   : Send the required command to the screen
 *[ARG]            :
 *
 *[in]        uint8 command:
 *                       This Arg Indicate To The command.
 *
 * [Return]        : Void
 */
void LCD_sendCommand(uint8 command);
/*
 * [Function Name] : LCD_displayCharacter()
 * [Description]   : Display the required character on the screen
 *[ARG]            :
 *
 *[in]        uint8 uint8 data:
 *                       This Arg Indicate To The Data need to Display.
 *
 * [Return]        : Void
 */
void LCD_displayCharacter(uint8 data);
/*
 * [Function Name] : LCD_displayString()
 * [Description]   : Display the required string on the screen
 *[ARG]            :
 *
 *[in]        uint8 const *str_ptr:
 *                       This Arg Receive the Address Of the String need to Display.
 *
 * [Return]        : Void
 */
void LCD_displayString(uint8 const *str_ptr);
/*
 * [Function Name] : LCD_moveCursor()
 * [Description]   : Move the cursor to a specified row and column index on the screen
 *[ARG]            :
 *
 *[in]        uint8 row:
 *                       This Arg Indicate To The Number of Row.
 *            uint8 col:
 *                       This Arg Indicate To The Number of Column.
 * [Return]        : Void
 */
void LCD_moveCursor(uint8 row, uint8 col);
/*
 * [Function Name] : LCD_displayStringRowColumn()
 * [Description]   : Display the required string in a specified row and column index on the screen
 *[ARG]            :
 *
 *[in]        uint8 row:
 *                       This Arg Indicate To The Number of Row.
 *            uint8 col:
 *                       This Arg Indicate To The Number of Column.
 *            uint8 const *str_ptr:
 *                       This Arg Receive the Address Of the String need to Display.
 *
 * [Return]        : Void
 */
void LCD_displayStringRowColumn(uint8 row, uint8 col, const uint8 *str_ptr);
/*
 * [Function Name] : LCD_intgerToString()
 * [Description]   :  Display the required decimal value on the screen
 *[ARG]            :
 *
 *[in]        int data:
 *                       This Arg Indicate To The Decimal Data.
 *
 * [Return]        : Void
 */
void LCD_intgerToString(int data);
/*
 * [Function Name] : LCD_clearScreen()
 * [Description]   : Send the clear screen command
 *[ARG]            : NO ARG
 *
 * [Return]        : Void
 */
void LCD_clearScreen(void);


#endif /* LCD_H_ */
