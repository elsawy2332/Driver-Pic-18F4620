/* 
 * File:   DC_Motor.c
 * Author: AH-ELSAWY
 *
 * Created on June 24, 2023, 12:30 AM
 */
#include "DC_Motor.h"




/**
 * 
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }else{
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin[0]));
        gpio_pin_intialize(&(_dc_motor->dc_motor_pin[1]));
     }
    return ret;  

}




/**
 * 
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }else{
        gpio_pin_Write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_HIGH);
        gpio_pin_Write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_LOW);
     }
    return ret;

}





/**
 * 
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }else{
        gpio_pin_Write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_LOW);
        gpio_pin_Write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_HIGH);  
     }
    return ret;

}




/**
 * 
 * @param _dc_motor
 * @return 
 */
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor){
    Std_ReturnType ret = E_OK;
    if(NULL == _dc_motor){
        ret = E_NOT_OK;
    }else{
       gpio_pin_Write_logic(&(_dc_motor->dc_motor_pin[0]), GPIO_LOW);
       gpio_pin_Write_logic(&(_dc_motor->dc_motor_pin[1]), GPIO_LOW);  
     }
    return ret;

}
