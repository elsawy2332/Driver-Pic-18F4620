/*
 * File:   hal_gpio.h
 * Author: AH-ELSAWY
 *
 * Created on April 25, 2023, 1:20 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

 /* section : includes */

#include "../mcal_std_types.h"
#include "../device_config.h"
#include "../hal_gpio_cfg.h"
#include "pic18f4620.h"



/* section : Macro Declarations */
#define MASK_BIT   (uint8)1
#define PORT_PIN_MAX_NUMBER    8
#define PORT_MAX_NUMBER        5
#define  GPIO_PORT_PIN_CONFIGRATINS     CONFIG_ENABLE
#define  GPIO_PORT_CONFIGRATINS     CONFIG_ENABLE
#define PORTA_MASK   0xFF
#define PORTB_MASK   0xFF
#define PORTC_MASK   0xFF
#define PORTD_MASK   0xFF
#define PORTE_MASK   0xFF
/* section : Macro Function Declarations */
#define HWREG(_x)      ( *((volatile uint8 *)(_x)))

#define SET_BIT(REG, BIT_POSN)           (REG |= (MASK_BIT << BIT_POSN))
#define CLEAR_BIT(REG, BIT_POSN)         (REG &= ~(MASK_BIT <<BIT_POSN))
#define TOGGLE_BIT(REG, BIT_POSN)        (REG ^= (MASK_BIT << BIT_POSN))
#define READ_BIT(REG, BIT_POSN)          ((REG >>BIT_POSN) & MASK_BIT)

/* section : Data Type Declarations */
typedef enum {
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum {
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum {
    GPIO_PIN0 = 0,
    GPIO_PIN1,
    GPIO_PIN2,
    GPIO_PIN3,
    GPIO_PIN4,
    GPIO_PIN5,
    GPIO_PIN6,
    GPIO_PIN7
}pin_index_t;
typedef enum {
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef struct{
    uint8 port : 3;         /* @ref port_index_t */
    uint8 pin  : 3;         /* @ref pin_index_t */
    uint8 direction : 1;    /* @ref direction_t */
    uint8 logic : 1;        /* @ref logic_t */
}pin_config_t;



/* section : Functions Declarations */

                    /*pin function*/
Std_ReturnType gpio_pin_Direction_intialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_Get_direction_status(const pin_config_t *_pin_config , direction_t *direction_status);
Std_ReturnType gpio_pin_Write_logic(const pin_config_t *_pin_config, logic_t  w_logic);
Std_ReturnType gpio_pin_Read_logic(const pin_config_t *_pin_config , logic_t *logic);
Std_ReturnType gpio_pin_Toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config);


                     /*port function*/
Std_ReturnType gpio_port_Direction_intialize(const port_index_t port, uint8 direction);
Std_ReturnType gpio_Get_port_Direction_status(const port_index_t port, uint8 *direction_status);
Std_ReturnType gpio_port_Write_logic(const port_index_t port, uint8 w_logic);
Std_ReturnType gpio_port_Read_logic(const port_index_t port, uint8 *logic);
Std_ReturnType gpio_port_Toggle_logic(const port_index_t port);



#endif	/* HAL_GPIO_H */

