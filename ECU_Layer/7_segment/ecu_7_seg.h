/* 
 * File:   ecu_7_seg.h
 * Author: AH-ELSAWY
 *
 * Created on July 3, 2023, 2:55 AM
 */

#ifndef ECU_7_SEG_H
#define	ECU_7_SEG_H

 /* section : includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* section : Macro Declarations */

/* section : Macro Function Declarations */

/* section : Data Type Declarations */
typedef enum{
    SEGMENT_COMMON_CATHDE,
    SEGMENT_COMMON_ANODE
}segment_type_t;

typedef struct{
pin_config_t segment_pins[4];
segment_type_t segment_type;
}segment_t;

/* section : Functions Declarations */
Std_ReturnType segment_intialize(const segment_t *seg);
Std_ReturnType segment_write_number(const segment_t *seg , uint8 number);


#endif	/* ECU_7_SEG_H */

