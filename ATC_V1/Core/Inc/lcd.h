#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "stm32f1xx_hal.h"

#define LCD_GPIO_PORT      GPIOB

#define LCD_D0_PIN         GPIO_PIN_0
#define LCD_D1_PIN         GPIO_PIN_1
#define LCD_D2_PIN         GPIO_PIN_2
#define LCD_D3_PIN         GPIO_PIN_3
#define LCD_D4_PIN         GPIO_PIN_4
#define LCD_D5_PIN         GPIO_PIN_5
#define LCD_D6_PIN         GPIO_PIN_6
#define LCD_D7_PIN         GPIO_PIN_7

#define LCD_RS_PIN         GPIO_PIN_10
#define LCD_EN_PIN         GPIO_PIN_11

//--------------------- API public ------------------------//
void LCD_Init();
void LCD_Write(char *str, uint8_t line);
void LCD_Clear();

#endif
