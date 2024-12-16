/* 
 * File:   ecu_led.h
 * Author: AH-ELSAWY
 *
 * Created on April 25, 2023, 1:11 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/* section : includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"

/* section : Macro Declarations */

/* section : Macro Function Declarations */

/* section : Data Type Declarations */
typedef enum {
    LED_ON = 0,
    LED_OFF
}led_status_t;

typedef struct{
    uint8 port_name : 4;    
    uint8 pin_num : 3;
    uint8 led_status :1;
}led_t;

/* section : Functions Declarations */
Std_ReturnType led_initialize(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_turn_toggle(const led_t *led);



#endif	/* ECU_LED_H */

