/* 
 * File:   hal_gpio.c
 * Author: AH-ELSAWY
 *
 * Created on April 25, 2023, 1:28 AM
 */

#include "hal_gpio.h"

/*Reference to the data direction control register */
volatile uint8 *tris_registers[] = {&TRISA,&TRISB,&TRISC,&TRISD,&TRISE};
/*Reference to the data latch register (read and write to data register)*/
volatile uint8 *lat_registers[] = {&LATA,&LATB,&LATC,&LATD,&LATE};
/*Reference to the data port status register*/
volatile uint8 *port_registers[] = {&PORTA,&PORTB,&PORTC,&PORTD,&PORTE};

  


  /**
 * @brief Initialize the direction of a specific pin @ref direction_t
 * @param _pin_config pointer to the configurations @ref pin_config_t 
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */ 
#if GPIO_PORT_PIN_CONFIGRATINS==CONFIG_ENABLE

Std_ReturnType gpio_pin_Direction_intialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK ;
        }else{
                switch(_pin_config->direction){
                case GPIO_DIRECTION_OUTPUT :
                CLEAR_BIT(*tris_registers[_pin_config->port] , _pin_config->pin);
                    break;
                case GPIO_DIRECTION_INPUT :
                SET_BIT(*tris_registers[_pin_config->port] , _pin_config->pin);
                    break;
                default : ret = E_NOT_OK ;
                }
        }
    return ret;
}
#endif



/**
 * 
 * @param _pin_config is a pointer to the configurations @ref pin_config_t
 * @param direction_status the direction of a specific pin @ref direction_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_PIN_CONFIGRATINS==CONFIG_ENABLE
Std_ReturnType gpio_pin_Get_direction_status(const pin_config_t *_pin_config , direction_t *direction_status){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == direction_status || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
         ret = E_NOT_OK;
    }else{
    *direction_status = READ_BIT(*tris_registers[_pin_config->port] , _pin_config->pin);
    }

return ret;
}
#endif

/**
 * 
 * @param _pin_config is a pointer to the configurations @ref pin_config_t
 * @param w_logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
#if GPIO_PORT_PIN_CONFIGRATINS==CONFIG_ENABLE
Std_ReturnType gpio_pin_Write_logic(const pin_config_t *_pin_config, logic_t  w_logic){
    Std_ReturnType ret = E_OK;
        if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
         ret = E_NOT_OK;
    }else{
            switch(w_logic){
                case GPIO_LOW :
                    CLEAR_BIT(*lat_registers[_pin_config->port] ,_pin_config->pin);
                break;
                case GPIO_HIGH :
                    SET_BIT(*lat_registers[_pin_config->port] ,_pin_config->pin);
                break;
                default : ret = E_NOT_OK;                 
            }
    }
return ret;
}
#endif

/**
 * 
 * @param _pin_config is a pointer to the configurations @ref pin_config_t
 * @param logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
#if GPIO_PORT_PIN_CONFIGRATINS==CONFIG_ENABLE
Std_ReturnType gpio_pin_Read_logic(const pin_config_t *_pin_config , logic_t *logic){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || NULL == logic || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
         ret = E_NOT_OK;
    }else{
        *logic = READ_BIT(*port_registers[_pin_config->port] , _pin_config->pin);
    }
return ret;
}
#endif

/**
 * 
 * @param _pin_config is a pointer to the configurations @ref pin_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
#if GPIO_PORT_PIN_CONFIGRATINS==CONFIG_ENABLE
Std_ReturnType gpio_pin_Toggle_logic(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
         ret = E_NOT_OK;
    }else{
        TOGGLE_BIT(*lat_registers[_pin_config->port] ,_pin_config->pin);
    }
return ret;
}
#endif

/**
 * 
 * @param _pin_config is a pointer to the configurations @ref pin_config_t
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
#if GPIO_PORT_PIN_CONFIGRATINS==CONFIG_ENABLE
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config){
    Std_ReturnType ret = E_OK;
    if(NULL == _pin_config || _pin_config->pin > PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK ;
        }else{
            ret = gpio_pin_Direction_intialize(_pin_config);
            ret = gpio_pin_Write_logic(_pin_config ,_pin_config->logic);
        }
    return ret;
}
#endif


/**
 * 
 * @param port_index
 * @param direction
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */ 
#if GPIO_PORT_CONFIGRATINS==CONFIG_ENABLE
Std_ReturnType gpio_port_Direction_intialize(const port_index_t port, uint8 direction){
    Std_ReturnType ret = E_OK;
    if(port >PORT_PIN_MAX_NUMBER-1){
        ret = E_NOT_OK;
    }else{
        *tris_registers[port] = direction;
    
    }
 return ret;
}
#endif


/**
 * 
 * @param port_index
 * @param direction_status
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
#if GPIO_PORT_CONFIGRATINS==CONFIG_ENABLE
Std_ReturnType gpio_Get_port_Direction_status(const port_index_t port, uint8 *direction_status){
    Std_ReturnType ret = E_OK;
        if( (NULL == direction_status) && (port >PORT_PIN_MAX_NUMBER-1)){
         ret = E_NOT_OK;
    }else{
    *direction_status = *tris_registers[port];
    }
return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param w_logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
#if GPIO_PORT_CONFIGRATINS==CONFIG_ENABLE
Std_ReturnType gpio_port_Write_logic(const port_index_t port, uint8 w_logic){
    Std_ReturnType ret = E_OK;
    if( port >PORT_PIN_MAX_NUMBER-1){
         ret = E_NOT_OK;
    }else{
     *lat_registers[port] = w_logic;
    }
return ret;
}
#endif

/**
 * 
 * @param _pin_config
 * @param logic
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if GPIO_PORT_CONFIGRATINS==CONFIG_ENABLE
Std_ReturnType gpio_port_Read_logic(const port_index_t port, uint8 *logic){
    Std_ReturnType ret = E_OK;
    if( (port >PORT_PIN_MAX_NUMBER-1) && (NULL == logic)){
         ret = E_NOT_OK;
    }else{
    
        *logic = *lat_registers[port]; 
    }
return ret;

}
#endif

/**
 * 
 * @param port
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action 
 */
#if GPIO_PORT_CONFIGRATINS==CONFIG_ENABLE
Std_ReturnType gpio_port_Toggle_logic(const port_index_t port){
    Std_ReturnType ret = E_OK;
     if( port >PORT_PIN_MAX_NUMBER-1){
         ret = E_NOT_OK;
    }else{
     *lat_registers[port] ^= PORTC_MASK ;
    }
return ret;
}
#endif







