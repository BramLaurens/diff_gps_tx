/*
Author: 	W Pielage & E Helmond
Date:		2-10-2013
Revision:	2

    leds.c:
           LED-driver for SpARM-board v1

    pin-info:
           PB1 - RCK: Storage register clock
           PB8  - SCK: Shift register clock
           PA15 - SER: Data input

To use the LEDs use the following line to set the pins:
	LED_init();
After that, you can put an 8 bit value to the LEDs
*/

#include "main.h"


/* LED Initialize
 * This function initializes the pins reset state
 */
void LED_init(void)
{
	HAL_GPIO_WritePin(P_LED_SER, LED_SER_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(P_LED_SCK, LED_SCK_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(P_LED_RCK, LED_RCK_Pin, GPIO_PIN_SET);
    LED_put(0);
}

/* LED put
 * This function puts an 8 bit value to the LEDs, where left is the LSB
 */
void LED_put(unsigned short led_byte)
{
     unsigned int i;

     for(i=128; i>=1; i>>=1)
     {
       	  HAL_GPIO_WritePin(P_LED_SER, LED_SER_Pin, (led_byte & i) ? GPIO_PIN_SET : GPIO_PIN_RESET);

          HAL_GPIO_WritePin(P_LED_SCK, LED_SCK_Pin, GPIO_PIN_SET);
          HAL_GPIO_WritePin(P_LED_SCK, LED_SCK_Pin, GPIO_PIN_RESET);
     }

     HAL_GPIO_WritePin(P_LED_RCK, LED_RCK_Pin, GPIO_PIN_SET);
     HAL_GPIO_WritePin(P_LED_RCK, LED_RCK_Pin, GPIO_PIN_RESET);
}

