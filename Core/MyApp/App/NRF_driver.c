/*
 * NRF_driver.c
 *
 *  Created on: Sep 23, 2025
 *      Author: braml
 */


#include <admin.h>
#include "main.h"
#include "cmsis_os.h"
#include "NRF_driver.h"
#include "NRF24.h"
#include "NRF24_reg_addresses.h"
#include <string.h>
#include "stm32f4xx_hal.h"
#include "NRF24_conf.h"
#include "GPS_parser.h"

#define PLD_SIZE 32 // Payload size in bytes
uint8_t txBuffer[PLD_SIZE] = {"Hello"}; // Transmission buffer test
uint8_t ack[PLD_SIZE]; // Acknowledgment buffer
uint8_t status = 1;

extern SPI_HandleTypeDef hspiX;

GPS_decimal_degrees_t errorBuffer = {0, 0}; // Struct to hold the GPS error to be transmitted

void NRF_transmitGPS(){
    memset(txBuffer, 0, PLD_SIZE);
    memcpy(txBuffer, &errorBuffer, sizeof(errorBuffer));

    HAL_GPIO_WritePin(GPIOD, LEDBLUE, GPIO_PIN_SET); // Turn on LED
    status = nrf24_transmit(txBuffer, sizeof(txBuffer)); // Transmit data
    LCD_clear();
    LCD_puts("Sent packet. TX status: ");
    char fail[] = "Failed";
    char ok[] = "OK";
    LCD_puts(status ? fail : ok);
    osDelay(50);
    HAL_GPIO_WritePin(GPIOD, LEDBLUE, GPIO_PIN_RESET); // Turn off LED
}

void NRF_setErrorBuffer(GPS_decimal_degrees_t error) {
    errorBuffer = error;
}

uint8_t nrf24_SPI_commscheck(void) {
    uint8_t tx[2] = {0x00, 0xFF};   // R_REGISTER + CONFIG(0x00), then dummy 0xFF
    uint8_t rx[2] = {0};

    HAL_GPIO_WritePin(csn_gpio_port, csn_gpio_pin, GPIO_PIN_RESET);
    for (volatile int i = 0; i < 50; i++) __NOP();

    HAL_SPI_TransmitReceive(&hspi1, tx, rx, 2, HAL_MAX_DELAY);

    for (volatile int i = 0; i < 50; i++) __NOP();
    HAL_GPIO_WritePin(csn_gpio_port, csn_gpio_pin, GPIO_PIN_SET);

    // rx[0] = STATUS, rx[1] = CONFIG
    return rx[1];
}

void NRF_Driver(void *argument)
{
    osDelay(100);

    UART_puts((char *)__func__); UART_puts(" started\r\n");
    uint8_t addr[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
    HAL_GPIO_WritePin(ce_gpio_port, ce_gpio_pin, 0); // Set CE low
    HAL_GPIO_WritePin(csn_gpio_port, csn_gpio_pin, 1); // Set CSN high


    nrf24_init(); // Initialize NRF24L01+
    nrf24_tx_pwr(3); // Set transmission power to maximum
    nrf24_data_rate(0); // Set data rate to 1Mbps
    nrf24_set_channel(78); // Set channel to 76
    nrf24_pipe_pld_size(0, PLD_SIZE); // Set payload size for pipe 0
    nrf24_set_crc(en_crc, _1byte); // Enable CRC with 1 byte

    nrf24_open_tx_pipe(addr); // Open TX pipe with address

    nrf24_pwr_up(); // Power up the NRF24L01+
    
    while (TRUE)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        NRF_transmitGPS();
        osDelay(1);
    }
}