/* 
 * File:   button.h
 * Author: AH-ELSAWY
 *
 * Created on May 9, 2023, 4:31 PM
 */

#ifndef BUTTON_H
#define	BUTTON_H

/* section : includes */
#include "button_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/* section : Macro Declarations */

/* section : Macro Function Declarations */

                             /* section : Data Type Declarations */
typedef enum {
    BUTTON_PRESSED = 0,
    BUTTON_RELAESED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH = 0 ,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct {
pin_config_t button_pin;
button_state_t button_state;
button_active_t button_connection;
}button_t;

                             /* section : Functions Declarations */

/**
 * 
 * @param btn
 * @return 
 */
Std_ReturnType button_initialize(const button_t *btn);



/**
 * 
 * @param btn
 * @param btn_state
 * @return 
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

#endif	/* BUTTON_H */

