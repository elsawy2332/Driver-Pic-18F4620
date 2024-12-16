/* 
 * File:   ecu_led.c
 * Author: AH-ELSAWY
 *
 * Created on April 25, 2023, 1:11 AM
 */

#include "ecu_led.h"

/**
 * @brief Initialize the led status on or off @ref led_status_t
 * @param led_t : pointer to the configurations @ref led_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_initialize(const led_t *led){
    Std_ReturnType ret = E_OK;
 
    
    if(NULL == led){
        ret = E_NOT_OK ;
        }else{
            pin_config_t pin_obj = {
                .port = led->port_name ,
                .pin = led->pin_num,
                .direction = GPIO_DIRECTION_OUTPUT,
                .logic = led->led_status
            };
            gpio_pin_intialize(&pin_obj);
    }
    return ret;

}

/**
 * @brief turn on of the led in turn on mode @ref led_t
 * @param led_t : pointer to the configurations @ref led_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_on(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK ;
        }else{
            pin_config_t pin_obj = {
                .port = led->port_name ,
                .pin = led->pin_num,
                .direction = GPIO_DIRECTION_OUTPUT,
                .logic = led->led_status
            };
            gpio_pin_Write_logic(&pin_obj,GPIO_HIGH);
    }
    return ret;


}

/**
 * @brief turn off of the led in turn on mode @ref led_t
 * @param led_t pointer to the configurations @ref led_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_off(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK ;
        }else{
            pin_config_t pin_obj = {
                .port = led->port_name ,
                .pin = led->pin_num,
                .direction = GPIO_DIRECTION_OUTPUT,
                .logic = led->led_status
            };
            gpio_pin_Write_logic(&pin_obj,GPIO_LOW);
    }
    return ret;


}

/**
 * @brief toggle value on led @ref led_t
 * @param led_t : pointer to the configurations @ref led_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType led_turn_toggle(const led_t *led){
    Std_ReturnType ret = E_OK;
    if(NULL == led){
        ret = E_NOT_OK ;
        }else{
            pin_config_t pin_obj = {
                .port = led->port_name ,
                .pin = led->pin_num,
                .direction = GPIO_DIRECTION_OUTPUT,
                .logic = led->led_status
            };
            gpio_pin_Toggle_logic(&pin_obj);
    }
    return ret;



}