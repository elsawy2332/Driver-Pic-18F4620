/* 
 * File:   hal_adc.h
 * Author: AH-ELSAWY
 *
 * Created on January 18, 2024, 6:58 PM
 */
#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* section : includes */
#include "hal_adc_cfg.h"
#include "pic18f4620.h"
#include "../../MCAL_Layer/mcal_std_types.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "../interrupt/mcal_internal_interrupt.h"

/* section : Macro Declarations */

/**
 * @brief Analog-To-Digital Port Configuration Control
 * @note  When ADC_AN4_ANALOG_FUNCTIONALITY is configured, this means
 *        AN4,AN3,AN2,AN1,AN0 are Analog functionality.
 */
#define ADC_AN0_ANALOG_FUNCTIONALITY    0x0E
#define ADC_AN1_ANALOG_FUNCTIONALITY    0x0D
#define ADC_AN2_ANALOG_FUNCTIONALITY    0x0C
#define ADC_AN3_ANALOG_FUNCTIONALITY    0x0B
#define ADC_AN4_ANALOG_FUNCTIONALITY    0x0A
#define ADC_AN5_ANALOG_FUNCTIONALITY    0x09
#define ADC_AN6_ANALOG_FUNCTIONALITY    0x08
#define ADC_AN7_ANALOG_FUNCTIONALITY    0x07
#define ADC_AN8_ANALOG_FUNCTIONALITY    0x06
#define ADC_AN9_ANALOG_FUNCTIONALITY    0x05
#define ADC_AN10_ANALOG_FUNCTIONALITY   0x04
#define ADC_AN11_ANALOG_FUNCTIONALITY   0x03
#define ADC_AN12_ANALOG_FUNCTIONALITY   0x02
#define ADC_ALL_ANALOG_FUNCTIONALITY    0x00
#define ADC_ALL_DIGITAL_FUNCTIONALITY   0x0F

#define ADC_RESULT_RIGHT    0x01U
#define ADC_RESULT_LEFT     0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLED       0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLED      0x00U


#define ADC_CONVERSION_COMPLETED    1
#define ADC_CONVERSION_INPROGRESS   0

/* section : Macro Function Declarations */

/* A/D Conversion Status : A/D Conversion in progress / A/D Idle */
#define ADC_CONVERSION_STATUS() (ADCON0bits.GO_nDONE)

/**
 * @brief start the analog-to-digetal conversion
 */
#define ADC_START_CONVERSION() (ADCON0bits.GODONE = 1)


/* Analog _To_Digital_Control : Enable / Disable */
              /* Enable ADC */
#define ADC_CONVERTOR_ENABLE() (ADCON0bits.ADON = 1)
             /* Disable ADC */
#define ADC_CONVERTOR_DISABLE() (ADCON0bits.ADON = 0)

/* Voltage Reference Configuration */

         /* ADC Enable Voltage Reference */
#define ADC_ENABLE_VOLTAGE_REFRENCE() do{ADCON1bits.VCFG1 = 1;\
                                         ADCON1bits.VCFG0 = 1;\
                                         }while(0)
         /* ADC disable Voltage Reference */
#define ADC_DISABLE_VOLTAGE_REFRENCE() do{ADCON1bits.VCFG1 = 0;\
                                         ADCON1bits.VCFG0 = 0;\
                                         }while(0)

        /*Analog_TO_Digital_Configuration_Control*/
#define ADC_ANALOG_DIGITAL_PORT_CONFIG(_CONFIG)(ADCON1bits.PCFG = _CONFIG)

          /* A/D Result Format Select */
#define ADC_RESULT_RIGHT_FORMAT()(ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()(ADCON2bits.ADFM = 0)



/* section : Data Type Declarations */

typedef enum {
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12        
}adc_channel_select_t;


typedef enum {
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD
}adc_acquisition_time_t;

typedef enum {
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64
}adc_conversion_clock_t;

typedef struct {
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    void (* ADC_InterruptHandler)(void);
    interrupt_priority_cfg priority; 
#endif
    adc_acquisition_time_t acquisition_time ; /* @ref adc_acquisition_time_t */
    adc_conversion_clock_t conversion_clock ; /* @ref adc_conversion_clock_t */
    adc_channel_select_t channel_select ;     /* @ref adc_channel_select_t  */
    uint8 voltage_reference : 1 ;             /* voltage reference configuration*/
    uint8 result_format : 1 ;                 /* A / D result format select */
    uint8 ADC_Resreved : 6 ;  
}adc_conf_t;
 
typedef uint16 adc_result_t;

/* section : Functions Declarations */
Std_ReturnType ADC_init(const adc_conf_t *_adc);
Std_ReturnType ADC_deInit(const adc_conf_t *_adc);
Std_ReturnType ADC_select_channel(const adc_conf_t *_adc, adc_channel_select_t channel);
Std_ReturnType ADC_start_conversion(const adc_conf_t *_adc);
Std_ReturnType ADC_is_conversion_done(const adc_conf_t *_adc, uint8 *conversion_status);
Std_ReturnType ADC_get_conversion_result(const adc_conf_t *_adc, uint8 *conversion_result);
Std_ReturnType ADC_get_conversion_blocking(const adc_conf_t *_adc, adc_channel_select_t channel,
                                                      adc_result_t *conversion_status);
Std_ReturnType ADC_start_conversion_interrupt(const adc_conf_t *_adc, adc_channel_select_t channel);

void ADC_Default_Interrupt_Handler(void);








#endif	/* HAL_ADC_H */

