/* 
 * File:   ecu_7_seg.c
 * Author: AH-ELSAWY
 *
 * Created on July 3, 2023, 2:55 AM
 */

#include "ecu_7_seg.h"

/**
 * 
 * @param seg
 * @return 
 */
Std_ReturnType segment_intialize(const segment_t *seg){
    Std_ReturnType ret = E_OK;
    if(NULL == seg){
        ret = E_NOT_OK;
    }else{
     ret = gpio_pin_intialize(&(seg->segment_pins[0]));
     ret = gpio_pin_intialize(&(seg->segment_pins[1])); 
     ret = gpio_pin_intialize(&(seg->segment_pins[2])); 
     ret = gpio_pin_intialize(&(seg->segment_pins[3])); 
     }
    return ret;

}

/**
 * 
 * @param seg
 * @param number
 * @return 
 */
Std_ReturnType segment_write_number(const segment_t *seg , uint8 number){
    Std_ReturnType ret = E_OK;
    if((NULL == seg) && (number > 9)){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_Write_logic(&(seg->segment_pins[0]),number & 0x01);
        ret = gpio_pin_Write_logic(&(seg->segment_pins[1]),(number >> 1) & 0x01);        
        ret = gpio_pin_Write_logic(&(seg->segment_pins[2]),(number >> 2) & 0x01);
        ret = gpio_pin_Write_logic(&(seg->segment_pins[3]),(number >> 3) & 0x01);
     }
    return ret;





}
