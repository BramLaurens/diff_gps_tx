/*
 * GPS_Errorcalc.c
 *
 *  Created on: Sep 30, 2025
 *      Author: braml
 */


// Test
#include <admin.h>
#include "main.h"
#include "cmsis_os.h"
#include "gps.h"
#include "GPS_parser.h"
#include "ARM_keys.h"

GNRMC gnrmc_localcopy; // local copy of struct for GNRMC-messages

void errorcalc()
{
    // Wait for notification from GPS.c that new data is available
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY); 
    UART_puts("New coordinate received. Performing new GPS error calculation...\r\n");

    // Take a safe snapshot of the latest GNRMC data.
	GPS_getLatestGNRMC(&gnrmc_localcopy);

}


void GPS_Errorcalc(void *argument)
{
    osDelay(100);

	UART_puts((char *)__func__); UART_puts(" started\r\n");

    while (1)
    {
		if(enable_errorcalc == 1){errorcalc();}
        osDelay(1);
    }
}

