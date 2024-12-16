/* 
 * File:   button.c
 * Author: AH-ELSAWY
 * 
 * Created on April 29, 2023, 3:03 AM
 */
#include "button.h"

/**
 * @brief  : button_initialize
 * @param  : btn is a pointer to the configurations @ref button_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
Std_ReturnType button_initialize(const button_t *btn){
    Std_ReturnType ret = E_OK;
    if(NULL == btn){
        ret = E_NOT_OK;
    }else{
      ret = gpio_pin_Direction_intialize(&(btn->button_pin)); 
     }
    return ret;
}

/**
 * @brief : button_read_state 
 * @param : btn is a pointer to the configurations @ref button_t
 * @param : btn_state is a pointer to the configurations @ref button_state_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */

Std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
     Std_ReturnType ret = E_NOT_OK;
     logic_t pin_logic_status = GPIO_LOW;
    if(NULL == btn || NULL == btn_state){
         ret = E_NOT_OK;
    }else{
        gpio_pin_Read_logic(&(btn->button_pin),&pin_logic_status);    
        if(BUTTON_ACTIVE_HIGH == btn->button_connection){
            if(GPIO_HIGH == pin_logic_status){
               *btn_state = BUTTON_PRESSED;
            }else{
                *btn_state = BUTTON_RELAESED;
            }
        }else if(BUTTON_ACTIVE_LOW == btn->button_connection){
              if(GPIO_LOW == pin_logic_status){
                  *btn_state = BUTTON_RELAESED;
             }else{
                  *btn_state = BUTTON_PRESSED;
            }
        
        }else{/* nothing */}
        ret = E_OK;  
    }//else

    return ret;
}