/* 
 * File:   ecu_lcd.c
 * Author: AH-ELSAWY
 *
 * Created on July 11, 2023, 11:42 PM
 */
#include "ecu_lcd.h"


static Std_ReturnType send_4bit_lcd(const chr_lcd_4bit_t *lcd , uint8 _data_command);
static Std_ReturnType send_enable_signal_4bit_lcd(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 coulmn);

static Std_ReturnType send_enable_signal_8bit_lcd(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 coulmn);




/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_4bit_intailze(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 data_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK ;
        }else{
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(data_counter = 0 ; data_counter<4 ; data_counter++){
            ret = gpio_pin_intialize(&(lcd->lcd_data[data_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_command(lcd, 0x80);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd , uint8 command){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK ;
        }else{
        ret = gpio_pin_Write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = send_4bit_lcd(lcd ,command >> 4);
        ret = send_enable_signal_4bit_lcd(lcd);
        ret = send_4bit_lcd(lcd ,command);
    }   ret = send_enable_signal_4bit_lcd(lcd);
    return ret;
}
/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd , uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK ;
        }else{
            ret = gpio_pin_Write_logic(&(lcd->lcd_rs), GPIO_HIGH);
            ret = send_4bit_lcd(lcd ,data >> 4);
            ret = send_enable_signal_4bit_lcd(lcd);
            ret = send_4bit_lcd(lcd ,data);
            ret = send_enable_signal_4bit_lcd(lcd);
        }
        
        
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @param row
 * @param column
 * @return 
 */
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd , uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK ;
        }else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_4bit_send_string(const chr_lcd_4bit_t *lcd ,uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == str){
        ret = E_NOT_OK ;
        }else{
        while(*str){
            ret = lcd_4bit_send_char_data(lcd, *str++);
        
        }
    }
    return ret;

}
/**
 * 
 * @param lcd
 * @param str
 * @param row
 * @param column
 * @return 
 */
Std_ReturnType lcd_4bit_send_string_pos(const chr_lcd_4bit_t *lcd , uint8 row, uint8 column,uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == str){
        ret = E_NOT_OK ;
        }else{
            ret = lcd_4bit_set_cursor(lcd, row, column);
        while(*str){
            ret = lcd_4bit_send_char_data(lcd, *str++);
        
        }
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_4bit_send_custome_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column,
                                          const uint8 _chr[],uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK ;
        }else{
            ret = lcd_4bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
            for(lcd_counter = 0;lcd_counter<=7;++lcd_counter){
                ret =lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
            }//for
            ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    return ret;


}
   /* ========================= 8bit_mode=================================*/

/**
 * 
 * @param lcd
 * @return 
 */
Std_ReturnType lcd_8bit_intailze(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    uint8 data_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK ;
        }else{
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(data_counter = 0 ; data_counter<8 ; data_counter++){
            ret = gpio_pin_intialize(&(lcd->lcd_data[data_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE_INC_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2_LINE); 
        ret = lcd_8bit_send_command(lcd, 0x80); 
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return 
 */
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd , uint8 command){
    Std_ReturnType ret = E_OK;
    uint8 pin_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK ;
        }else{
            ret = gpio_pin_Write_logic(&(lcd->lcd_rs), GPIO_LOW);
            for(pin_counter = 0 ; pin_counter < 8 ; ++pin_counter){
                ret = gpio_pin_Write_logic(&(lcd->lcd_data[pin_counter]),(command >> pin_counter) & (uint8)0x01);
            }
            ret = send_enable_signal_8bit_lcd(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd , uint8 data){
    Std_ReturnType ret = E_OK;
    uint8 pin_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK ;
        }else{
            ret = gpio_pin_Write_logic(&(lcd->lcd_rs), GPIO_HIGH);
            for(pin_counter = 0 ; pin_counter < 8 ; pin_counter++){
                ret = gpio_pin_Write_logic(&(lcd->lcd_data[pin_counter]),(data >> pin_counter) & (uint8)0x01);
            }
            ret = send_enable_signal_8bit_lcd(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @param row
 * @param column
 * @return 
 */
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd , uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK ;
        }else{
             ret = lcd_8bit_set_cursor(lcd, row,column);
             ret = lcd_8bit_send_char_data(lcd,data);   
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string(const chr_lcd_8bit_t *lcd ,uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == str){
        ret = E_NOT_OK ;
        }else{
        while(*str){
            ret = lcd_8bit_send_char_data(lcd, *str++);
        
        }
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @param str
 * @param row
 * @param column
 * @return 
 */
Std_ReturnType lcd_8bit_send_string_pos(const chr_lcd_8bit_t *lcd , uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd || NULL == str){
        ret = E_NOT_OK ;
        }else{
            ret = lcd_8bit_set_cursor(lcd, row,column);
            while(*str){
                ret = lcd_8bit_send_char_data(lcd, *str++);
        }
            
    }
    return ret;

}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param _chr
 * @param mem_pos
 * @return 
 */
Std_ReturnType lcd_8bit_send_custome_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, 
                                          const uint8 _chr[],uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter = 0;
    if(NULL == lcd){
        ret = E_NOT_OK ;
        }else{
            ret = lcd_8bit_send_command(lcd, (_LCD_CGRAM_START + (mem_pos*8)));
            for(lcd_counter = 0;lcd_counter<=7;++lcd_counter){
                ret =lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
            }//for
            ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
        }//else
    return ret;
}

/*======================== converting=========================*/
/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK ;
        }else{
            memset((char *)str, '\0', 11);
            sprintf((char *)str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    uint8 Temp_String[6] = {0};
    uint8 DataCounter = 0;
    if(NULL == str){
        ret = E_NOT_OK;
    }
    else{    
        memset(str, ' ', 5);
        str[5] = '\0';
        sprintf((char *)Temp_String, "%i", value);
        while(Temp_String[DataCounter] != '\0'){
            str[DataCounter] = Temp_String[DataCounter]; 
            DataCounter++;
        }
    }
    return ret;
}
/**
 * 
 * @param value
 * @param str
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str){
        ret = E_NOT_OK ;
        }else{
        memset((char *)str, '\0', 4);
        sprintf((char *)str, "%i", value);
    }
    return ret;
}

/* ============================= helper function ===============================*/
/**
 * 
 * @param lcd
 * @param _data_command
 * @return 
 */
static Std_ReturnType send_4bit_lcd(const chr_lcd_4bit_t *lcd , uint8 _data_command){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_Write_logic(&(lcd->lcd_data[0]),(_data_command >> 0) & (uint8)0x01);
    ret = gpio_pin_Write_logic(&(lcd->lcd_data[1]),(_data_command >> 1) & (uint8)0x01);
    ret = gpio_pin_Write_logic(&(lcd->lcd_data[2]),(_data_command >> 2) & (uint8)0x01);
    ret = gpio_pin_Write_logic(&(lcd->lcd_data[3]),(_data_command >> 3) & (uint8)0x01);
return ret;
}

/**
 * 
 * @param lcd
 * @return 
 */
static Std_ReturnType send_enable_signal_4bit_lcd(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_Write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_Write_logic(&(lcd->lcd_en), GPIO_LOW);
return ret;
}


/**
 * 
 * @param lcd
 * @return 
 */
static Std_ReturnType send_enable_signal_8bit_lcd(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    ret = gpio_pin_Write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_Write_logic(&(lcd->lcd_en), GPIO_LOW);
return ret;
}



static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 coulmn){
    Std_ReturnType ret = E_OK;
    coulmn--;
    switch(row){
        case ROW1:ret = lcd_8bit_send_command(lcd, (0x80 + coulmn)); break;
        case ROW2:ret = lcd_8bit_send_command(lcd, (0xC0 + coulmn)); break;
        case ROW3:ret = lcd_8bit_send_command(lcd, (0x94 + coulmn)); break;
        case ROW4:ret = lcd_8bit_send_command(lcd, (0xD4 + coulmn)); break;
        default : ;
    }

    return ret;
}


static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 coulmn){
    Std_ReturnType ret = E_OK;
    coulmn--;
    switch(row){
        case ROW1:ret = lcd_4bit_send_command(lcd, (0x80 + coulmn)); break;
        case ROW2:ret = lcd_4bit_send_command(lcd, (0xC0 + coulmn)); break;
        case ROW3:ret = lcd_4bit_send_command(lcd, (0x94 + coulmn)); break;
        case ROW4:ret = lcd_4bit_send_command(lcd, (0xD4 + coulmn)); break;
        default : ;
    }

    return ret;
}