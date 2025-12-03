#include "lcd.h"

static void send8BitLCD(char D)
{
	int b0, b1, b2, b3, b4, b5, b6, b7;

    b0 = (D & 0x01) ? 1 : 0;
    b1 = (D & 0x02) ? 1 : 0;
    b2 = (D & 0x04) ? 1 : 0;
    b3 = (D & 0x08) ? 1 : 0;
    b4 = (D & 0x10) ? 1 : 0;
    b5 = (D & 0x20) ? 1 : 0;
    b6 = (D & 0x40) ? 1 : 0;
    b7 = (D & 0x80) ? 1 : 0;

	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D0_PIN, b0);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D1_PIN, b1);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D2_PIN, b2);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D3_PIN, b3);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D4_PIN, b4);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D5_PIN, b5);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D6_PIN, b6);
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_D7_PIN, b7);
}

static void sendCMD2LCD(char cmd)
{
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RS_PIN, GPIO_PIN_RESET); // RS = 0
	send8BitLCD(cmd); // Send 8 bit to 8 Pin
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_RESET); // EN = 0
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_SET); // EN = 1
	HAL_Delay(1);
}

static void sendChar2LCD(char Char)
{
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RS_PIN, GPIO_PIN_SET); // RS = 1
	send8BitLCD(Char); // Send 8 bit to 8 Pin
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_RESET); // EN = 0
	HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_EN_PIN, GPIO_PIN_SET); // EN = 1
	HAL_Delay(1);
}

static void sendString2LCD(char *str)
{
	for (int i=0; str[i] != '\0' ; i++){
		sendChar2LCD(str[i]);
	}
}


//--------------------- API public ------------------------//

void LCD_Clear()
{
	sendCMD2LCD(0x01); // Clear LCD
}

void LCD_Init()
{
	LCD_Clear();
	sendCMD2LCD(0x0C); // Open LCD Display, turn off pointer
	sendCMD2LCD(0x38); // 2 lines mode
}

void LCD_Write(char *str, uint8_t line)
{
	if (line == 1) sendCMD2LCD(0x80);
	else sendCMD2LCD(0xC0);
	sendString2LCD(str);
}
