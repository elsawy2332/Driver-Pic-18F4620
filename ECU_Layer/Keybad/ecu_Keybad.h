/* 
 * File:   ecu_Keypad.h
 * Author: AH-ELSAWY
 *
 * Created on July 4, 2023, 5:15 PM
 */

#ifndef ECU_KEYBAD_H
#define	ECU_KEYBAD_H

/* section : includes */
#include "ecu_Keybad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* section : Macro Declarations */
#define ECU_KEYPAD_ROWS      4
#define ECU_KEYPAD_COLUMNS   4

/* section : Macro Function Declarations */


/* section : Data Type Declarations */
typedef struct {
    pin_config_t Keypad_row_pins[ECU_KEYPAD_ROWS];
    pin_config_t Keypad_columns_pins[ECU_KEYPAD_COLUMNS];

}Keypad_t;

/* section : Functions Declarations */
Std_ReturnType Keypad_intialize(const Keypad_t *keypad_obj);
Std_ReturnType Keypad_get_value(const Keypad_t *keypad_obj , uint8 *keypad_value);

 

#endif	/* ECU_KEYBAD_H */

