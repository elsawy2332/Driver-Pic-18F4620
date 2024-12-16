/* 
 * File:   ecu_Keybad.c
 * Author: AH-ELSAWY
 *
 * Created on July 4, 2023, 5:15 PM
 */

#include"ecu_Keybad.h"


static const uint8 btn_keybad_values[ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
                                                                 {'7','8','9','/'},
                                                                 {'4','5','6','*'},
                                                                 {'1','2','3','-'},
                                                                 {'#','0','=','+'},
};

/**
 * 
 * @param keypad_obj
 * @return 
 */
Std_ReturnType Keypad_intialize(const Keypad_t *keypad_obj){
    Std_ReturnType ret = E_OK;
    uint8 rows_counter = 0 , columns_counter = 0;
    if(NULL == keypad_obj){
        ret = E_NOT_OK;
    }else{
        for(rows_counter = 0;rows_counter < ECU_KEYPAD_ROWS;rows_counter++){
        
            ret = gpio_pin_intialize(&(keypad_obj->Keypad_row_pins[rows_counter]));
        }
        
        for(columns_counter = 0; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++){
            
            ret = gpio_pin_Direction_intialize(&(keypad_obj->Keypad_columns_pins[columns_counter]));
        
        }
     }
    return ret; 

}


/**
 * 
 * @param keypad_obj
 * @param key_pad_value
 * @return 
 */
Std_ReturnType Keypad_get_value(const Keypad_t *keypad_obj , uint8 *keypad_value){
    Std_ReturnType ret = E_OK;
     uint8 rows_counter = 0 , columns_counter = 0, l_counter = 0;
     uint8 columns_logic = 0;
    if((NULL == keypad_obj) && (NULL == keypad_value)){
        ret = E_NOT_OK;
    }else{
        for(rows_counter = 0; rows_counter < ECU_KEYPAD_ROWS ;rows_counter++){
        
            for(l_counter = 0; l_counter < ECU_KEYPAD_ROWS ;l_counter++){
                ret =  gpio_pin_Write_logic(&(keypad_obj->Keypad_row_pins[l_counter]),GPIO_LOW);
            }
            ret =  gpio_pin_Write_logic(&(keypad_obj->Keypad_row_pins[rows_counter]) ,GPIO_HIGH);
            for(columns_counter = 0; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++){
                ret = gpio_pin_Read_logic(&(keypad_obj->Keypad_columns_pins[columns_counter]),&columns_logic);
                if(GPIO_HIGH == columns_logic){
                    *keypad_value = btn_keybad_values[rows_counter][columns_counter];
                
                }
        }
        }
        

        
        
     }
    return ret; 



}



