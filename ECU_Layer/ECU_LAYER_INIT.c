/* 
 * File:   ECU_LAYER_INIT.c
 * Author: AH-ELSAWY
 *
 * Created on July 4, 2023, 7:08 PM
 */


#include"ECU_LAYER_INIT.h"




chr_lcd_4bit_t lcd_1 = {
.lcd_rs.port = PORTC_INDEX,
.lcd_rs.pin = GPIO_PIN0,
.lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
.lcd_rs.logic = GPIO_LOW,

.lcd_en.port = PORTC_INDEX,
.lcd_en.pin = GPIO_PIN1,
.lcd_en.direction = GPIO_DIRECTION_OUTPUT,
.lcd_en.logic = GPIO_LOW,

.lcd_data[0].port = PORTC_INDEX,
.lcd_data[0].pin = GPIO_PIN2,
.lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[0].logic = GPIO_LOW,

.lcd_data[1].port = PORTC_INDEX,
.lcd_data[1].pin = GPIO_PIN3,
.lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[1].logic = GPIO_LOW,

.lcd_data[2].port = PORTC_INDEX,
.lcd_data[2].pin = GPIO_PIN4,
.lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[2].logic = GPIO_LOW,

.lcd_data[3].port = PORTC_INDEX,
.lcd_data[3].pin = GPIO_PIN5,
.lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[3].logic = GPIO_LOW
};



chr_lcd_8bit_t lcd_2 = {
.lcd_rs.port = PORTC_INDEX,
.lcd_rs.pin = GPIO_PIN6,
.lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
.lcd_rs.logic = GPIO_LOW,

.lcd_en.port = PORTC_INDEX,
.lcd_en.pin = GPIO_PIN7,
.lcd_en.direction = GPIO_DIRECTION_OUTPUT,
.lcd_en.logic = GPIO_LOW,

.lcd_data[0].port = PORTD_INDEX,
.lcd_data[0].pin = GPIO_PIN0,
.lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[0].logic = GPIO_LOW,

.lcd_data[1].port = PORTD_INDEX,
.lcd_data[1].pin = GPIO_PIN1,
.lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[1].logic = GPIO_LOW,

.lcd_data[2].port = PORTD_INDEX,
.lcd_data[2].pin = GPIO_PIN2,
.lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[2].logic = GPIO_LOW,

.lcd_data[3].port = PORTD_INDEX,
.lcd_data[3].pin = GPIO_PIN3,
.lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[3].logic = GPIO_LOW,
        
.lcd_data[4].port = PORTD_INDEX,
.lcd_data[4].pin = GPIO_PIN4,
.lcd_data[4].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[4].logic = GPIO_LOW,

.lcd_data[5].port = PORTD_INDEX,
.lcd_data[5].pin = GPIO_PIN5,
.lcd_data[5].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[5].logic = GPIO_LOW,

.lcd_data[6].port = PORTD_INDEX,
.lcd_data[6].pin = GPIO_PIN6,
.lcd_data[6].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[6].logic = GPIO_LOW,

.lcd_data[7].port = PORTD_INDEX,
.lcd_data[7].pin = GPIO_PIN7,
.lcd_data[7].direction = GPIO_DIRECTION_OUTPUT,
.lcd_data[7].logic = GPIO_LOW
};


const uint8 customChar_1[] = {
  0x00,
  0x07,
  0x04,
  0x1F,
  0x04,
  0x04,
  0x04,
  0x04
};


const uint8 customChar_2[] = {
  0x00,
  0x18,
  0x04,
  0x02,
  0x01,
  0x1F,
  0x00,
  0x00
};

const uint8 customChar_3[] = {
  0x00,
  0x00,
  0x0E,
  0x0A,
  0x0A,
  0x1B,
  0x0A,
  0x0E
};


const uint8 customChar_4[] = {
  0x00,
  0x00,
  0x1C,
  0x02,
  0x02,
  0x1F,
  0x00,
  0x00
};





 void ecu_layer_intialize(void){
    Std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_intailze(&(lcd_1));
    ret = lcd_8bit_intailze(&(lcd_2));
    
 }