/* 
 * File:   DC_Motor.h
 * Author: AH-ELSAWY
 *
 * Created on June 24, 2023, 12:30 AM
 */

#ifndef DC_MOTOR_H
#define	DC_MOTOR_H

 /* section : includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "DC_Motor_cfg.h"
 
/* section : Macro Declarations */
#define Motor_ON_STATUS   0x01U
#define Motor_OFF_STATUS  0x00U
/* section : Macro Function Declarations */

/* section : Data Type Declarations */

typedef struct{
 pin_config_t dc_motor_pin[2];   
}dc_motor_t;
/* section : Functions Declarations */
Std_ReturnType dc_motor_initialize(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_right(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_move_left(const dc_motor_t *_dc_motor);
Std_ReturnType dc_motor_stop(const dc_motor_t *_dc_motor);


#endif	/* DC_MOTOR_H */

