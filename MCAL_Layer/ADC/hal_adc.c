/* 
 * File:   hal_adc.c
 * Author: AH-ELSAWY
 *
 * Created on January 18, 2024, 6:58 PM
 */

#include "hal_adc.h"
#if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    static void (*ADC_Interrupt_Handler)(void) = NULL;
#endif

/**
 ********* Helper functions *********
 **/
static inline void adc_input_channel_port_configure(adc_channel_select_t channel);
static inline void select_result_format(const adc_conf_t *_adc);
static inline void configure_voltage_reference(const adc_conf_t *_adc);
 /* ************************************* */


/**
 * @Summary Initializes the ADC
 * @Description This routine initializes the ADC.
 *              This routine must be called before any other ADC routine is called.
 *              This routine should only be called once during system initialization.
 * @Preconditions None
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_init(const adc_conf_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the ADC */
        ADC_CONVERTOR_DISABLE();
        /* Configure the acquisition time */
        ADCON2bits.ACQT = _adc->acquisition_time;
        /* Configure the conversion clock */
        ADCON2bits.ADCS = _adc->conversion_clock;
        /* Configure the default channel */
        ADCON0bits.CHS = _adc->channel_select;
        adc_input_channel_port_configure(_adc->channel_select);
        /* Configure the interrupt */
        #if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptEnable();
        ADC_InterruptFlagClear();
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        if(INTERRUPT_HIGH_PRIORITY == _adc->priority){ADC_HighPrioritySet();}
        else if(INTERRUPT_LOW_PRIORITY == _adc->priority){ADC_LowPrioritySet();}
        else{/* nothing */}
        #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
        #endif
        ADC_Interrupt_Handler = _adc->ADC_InterruptHandler;
        #endif
        
        /* configure the result format*/
        select_result_format(_adc);
        /* configure the voltage reference */
        configure_voltage_reference(_adc);
        /* Enable the ADC */
        ADC_CONVERTOR_ENABLE();
        ret = E_OK ;
    }
    return ret;
}


/**
 * @Summary De-Initializes the ADC
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_deInit(const adc_conf_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
         /* Disable the ADC */
        ADC_CONVERTOR_DISABLE();
        /* Configure the interrupt */
        #if ADC_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        ADC_InterruptDisable();
        #endif
        ret = E_OK ;
    }
    return ret;
}

/**
 * @Summary Allows selection of a channel for conversion
 * @Description This routine is used to select desired channel for conversion.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_select_channel(const adc_conf_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
          /* Configure the default channel */
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel); 
        
        ret = E_OK ;
    }
    return ret;
}

/**
 * @Summary Starts conversion
 * @Description This routine is used to start conversion of desired channel.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_start_conversion(const adc_conf_t *_adc){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
        ADC_START_CONVERSION();
        ret = E_OK ;
    }
    return ret;
}

/**
 * @Summary Returns true when the conversion is completed otherwise false.
 * @Description This routine is used to determine if conversion is completed.
 *              When conversion is complete routine returns true. It returns false otherwise.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 *                ADC_StartConversion() should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_status The conversion status
 *          true  - If conversion is complete
 *          false - If conversion is not completed
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_is_conversion_done(const adc_conf_t *_adc, uint8 *conversion_status){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || NULL == (conversion_status)){
        ret = E_NOT_OK;
    }
    else{
        *conversion_status = (uint8)(!(ADCON0bits.GO_nDONE));
        ret = E_OK ;
    }
    return ret;
}

/**
 * @Summary Returns the ADC conversion value.
 * @Description This routine is used to get the analog to digital converted value.
 *              This routine gets converted values from the channel specified.
 * @Preconditions   This routine returns the conversion value only after the conversion is complete.
 *                  Completion status can be checked using ADC_IsConversionDone() routine.
 * @param _adc Pointer to the ADC configurations
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_get_conversion_result(const adc_conf_t *_adc, uint8 *conversion_result){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || NULL == (conversion_result)){
        ret = E_NOT_OK;
    }
    else{
        if(ADC_RESULT_RIGHT == _adc->result_format){
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL) ;
        }else if(ADC_RESULT_LEFT == _adc->result_format){
            *conversion_result = (adc_result_t)(((ADRESH << 8) + ADRESL) >> 6) ;
        }else{
            *conversion_result = (adc_result_t)((ADRESH << 8) + ADRESL) ;
        }
        ret = E_OK ;
    }
    return ret;
}

/**
 * @Summary Returns the ADC conversion value, also allows selection of a channel for conversion.
 * @Description This routine is used to select desired channel for conversion.
 *              This routine is get the analog to digital converted value.
 * @Preconditions ADC_Init() function should have been called before calling this function.
 * @param _adc Pointer to the ADC configurations
 * @param channel Defines the channel available for conversion.
 * @param conversion_result The converted value.
 * @return Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType ADC_get_conversion_blocking(const adc_conf_t *_adc, adc_channel_select_t channel,
                                                      adc_result_t *conversion_status){
    Std_ReturnType ret = E_NOT_OK;
    if((NULL == _adc) || (NULL == conversion_status)){
        ret = E_NOT_OK;
    }
    else{
              /*select A/D channel*/
        ret = ADC_select_channel(_adc, channel);
              /* start the conversion */
        ret = ADC_start_conversion(_adc);
             /* check if conversion is completed */
        while(ADCON0bits.GO_nDONE);
        ret = ADC_get_conversion_result(_adc, conversion_status);
    }
    return ret;
}



/**
 * 
 * @param _adc
 * @param channel
 * @return 
 */
Std_ReturnType ADC_start_conversion_interrupt(const adc_conf_t *_adc, adc_channel_select_t channel){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == _adc){
        ret = E_NOT_OK;
    }
    else{
              /*select A/D channel*/
        ret = ADC_select_channel(_adc, channel);
              /* start the conversion */
        ret = ADC_start_conversion(_adc);
 
    }
    return ret;
}


static inline void adc_input_channel_port_configure(adc_channel_select_t channel){
    switch(channel){
        case ADC_CHANNEL_AN0 : SET_BIT(TRISA, _TRISA_RA0_POSN); break;
        case ADC_CHANNEL_AN1 : SET_BIT(TRISA, _TRISA_RA1_POSN); break;
        case ADC_CHANNEL_AN2 : SET_BIT(TRISA, _TRISA_RA2_POSN); break;
        case ADC_CHANNEL_AN3 : SET_BIT(TRISA, _TRISA_RA3_POSN); break;
        case ADC_CHANNEL_AN4 : SET_BIT(TRISA, _TRISA_RA5_POSN); break;
        case ADC_CHANNEL_AN5 : SET_BIT(TRISE, _TRISE_RE0_POSN); break;
        case ADC_CHANNEL_AN6 : SET_BIT(TRISE, _TRISE_RE1_POSN); break;
        case ADC_CHANNEL_AN7 : SET_BIT(TRISE, _TRISE_RE2_POSN); break;
        case ADC_CHANNEL_AN8 : SET_BIT(TRISB, _TRISB_RB2_POSN); break;
        case ADC_CHANNEL_AN9 : SET_BIT(TRISB, _TRISB_RB3_POSN); break;
        case ADC_CHANNEL_AN10 : SET_BIT(TRISB, _TRISB_RB1_POSN); break;
        case ADC_CHANNEL_AN11: SET_BIT(TRISB, _TRISB_RB4_POSN); break;
        case ADC_CHANNEL_AN12 : SET_BIT(TRISB, _TRISB_RB0_POSN); break;
        default : /* nothing */ ;
    }

}


static inline void select_result_format(const adc_conf_t *_adc){
    if(ADC_RESULT_RIGHT == _adc->result_format){
        ADC_RESULT_RIGHT_FORMAT();
    }else if(ADC_RESULT_LEFT == _adc->result_format){
        ADC_RESULT_LEFT_FORMAT();
    }else{
        ADC_RESULT_RIGHT_FORMAT();
    }

}


static inline void configure_voltage_reference(const adc_conf_t *_adc){
    if(ADC_VOLTAGE_REFERENCE_ENABLED  == _adc->voltage_reference){
        ADC_ENABLE_VOLTAGE_REFRENCE();
    }else if(ADC_VOLTAGE_REFERENCE_DISABLED == _adc->voltage_reference){
        ADC_DISABLE_VOLTAGE_REFRENCE();
    }else{
       ADC_DISABLE_VOLTAGE_REFRENCE(); 
    }

}

void ADC_ISR(void){
    ADC_InterruptFlagClear();
    if(ADC_Interrupt_Handler){
        ADC_Interrupt_Handler();
    }
}


