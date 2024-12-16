/* 
 * File:   Relay.h
 * Author: AH-ELSAWY
 *
 * Created on June 22, 2023, 11:22 PM
 */

#ifndef RELAY_H
#define	RELAY_H
 /* section : includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "Relay_cfg.h"

/* section : Macro Declarations */
#define RELAY_ON_STATUS   0x01U
#define RELAY_OFF_STATUS  0x00U
/* section : Macro Function Declarations */

/* section : Data Type Declarations */
typedef struct{
    uint8 relay_port : 4;
    uint8 relay_pin : 3;
    uint8 relay_status : 1;
}relay_t;
/* section : Functions Declarations */

Std_ReturnType Relay_initialize(const relay_t *_relay );
Std_ReturnType Relay_ON(const relay_t *_relay );
Std_ReturnType Relay_OFF(const relay_t *_relay );








#endif	/* RELAY_H */

