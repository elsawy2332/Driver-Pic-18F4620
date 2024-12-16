/* 
 * File:   Relay.c
 * Author: AH-ELSAWY
 *
 * Created on June 22, 2023, 11:22 PM
 */

#include "Relay.h"



/**
 * 
 * @param _relay
 * @return 
 */
Std_ReturnType Relay_initialize(const relay_t *_relay ){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }else{
        pin_config_t pin_obj = {.port = _relay->relay_port,.pin = _relay->relay_pin,
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = _relay->relay_status};
        gpio_pin_intialize(&pin_obj);
     }
    return ret;    
}


/**
 * 
 * @param _relay
 * @return 
 */
Std_ReturnType Relay_ON(const relay_t *_relay ){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }else{
         pin_config_t pin_obj = {.port = _relay->relay_port,.pin = _relay->relay_pin,
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = _relay->relay_status};
         gpio_pin_Write_logic(&pin_obj,GPIO_HIGH);
     }
    return ret;
}


/**
 * 
 * @param _relay
 * @return 
 */
Std_ReturnType Relay_OFF(const relay_t *_relay ){
    Std_ReturnType ret = E_OK;
    if(NULL == _relay){
        ret = E_NOT_OK;
    }else{
         pin_config_t pin_obj = {.port = _relay->relay_port,.pin = _relay->relay_pin,
                                .direction = GPIO_DIRECTION_OUTPUT,.logic = _relay->relay_status};
         gpio_pin_Write_logic(&pin_obj , GPIO_LOW); 
     }
    return ret;
}


