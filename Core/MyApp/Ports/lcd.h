/*
Author: 	J.F. van der Bent
			W Pielage & E Helmond

Date:		24-11-2021
Revision:	5
    lcd.c:
          LCD-driver ARM-board v5

    pin-info:
           PE2  - DB4   --->> PE3
           PE4  - DB5
           PE5  - DB6
           PE6  - DB7
           PC13 - E:  start data
           PC15 - RS: register-select
           PC14 - RW: read/write

    opmerkingen:
                -Alle instructies voor het display staan achterstevoren! (maakt
                 de code wat eenvoudiger)
                -Zorg ervoor dat de delay-code ook wordt meegecompileerd, anders
                 gaat het hier mis...
                -Deze code is gebaseerd op
                 "LCD routines for OLIMEX LPC-MT-2106,16x2 Character LCD 1602K,
                  4-bit mode operation",
                 Copyright (c) 2004 senz at arm.dreamislife.com
                 15-07-2014 aanpassing voor 1x16 display define eenregel bepaald type display J.F. van der Bent
*/

#define eenregel		// define voor 1x16 display

#ifndef LCD_H
#define LCD_H

/* I/O-pinnen */
#define  STARTBIT       0
#define  LCD_D7         GPIOE, GPIO_PIN_6
#define  LCD_D6         GPIOE, GPIO_PIN_5
#define  LCD_D5         GPIOE, GPIO_PIN_4
#define  LCD_D4         GPIOE, GPIO_PIN_3
#define  LCD_EN         GPIOD, GPIO_PIN_0
#define  LCD_RS         GPIOC, GPIO_PIN_13
#define  LCD_RW         GPIOC, GPIO_PIN_11

#define  LCD_DATA       (LCD_D4|LCD_D5|LCD_D6|LCD_D7)
#define  LCD_IOALL      (LCD_D4|LCD_D5|LCD_D6|LCD_D7|LCD_EN|LCD_RS)

#define LCD_SETCGRAMADDR 0x40

#define LCD_display_on()     LCD_writecontrol(0x0E)
#define LCD_display_off()    LCD_writecontrol(0x08)

#define LCD_cursor_blink()   LCD_writecontrol(0x0F)
#define LCD_cursor_on()      LCD_writecontrol(0x0E)
#define LCD_cursor_off()     LCD_writecontrol(0x0C)

#define LCD_cursor_left()    LCD_writecontrol(0x10)
#define LCD_cursor_right()   LCD_writecontrol(0x14)
#define LCD_display_sleft()  LCD_writecontrol(0x18)
#define LCD_display_sright() LCD_writecontrol(0x1C)

void LCD_init(void);
void LCD_clear(void);
void LCD_cursor_home(void);
void LCD_writecontrol(unsigned char data);
void LCD_put(char *c);
void LCD_puts(char *c);
void LCD_putchar(char c);
void LCD_putint(unsigned int num);
void delay_LCD(unsigned int time);
void LCD_XY(unsigned int x, unsigned int y);
void busyflag(void);
void LCD_createChar(uint8_t location, uint8_t map[8]);

#endif /*LCD_H*/
