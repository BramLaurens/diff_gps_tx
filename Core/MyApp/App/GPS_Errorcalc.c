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

// #define debug_GPS_differential

GNRMC gnrmc_localcopy; // local copy of struct for GNRMC-messages

GPS_decimal_degrees_t currentpos;
extern GPS_decimal_degrees_t differentialpos; // Struct to hold the working differential GPS position
extern GPS_decimal_degrees_t GPS_error; // Struct to hold the latest GPS error

void errorcalc()
{
    // Wait for notification from GPS.c that new data is available
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY); 

    #ifdef debug_GPS_differential
        UART_puts("New coordinate received. Performing new GPS error calculation...\r\n");
    #endif

    // Take a safe snapshot of the latest GNRMC data.
	GPS_getLatestGNRMC(&gnrmc_localcopy);

	if(gnrmc_localcopy.status == 'V') // If status is 'N' (not valid), skip processing
	{
		#ifdef debug_GPS_differential
			UART_puts("\r\nInvalid GPS data received (status N). Skipping error calculation.\r\n");
		#endif
        return;
	}

    // Calculate error if valid GPS data is available
    if(gnrmc_localcopy.status == 'A')
    {
        currentpos.latitude = convert_decimal_degrees(gnrmc_localcopy.latitude, &gnrmc_localcopy.NS_ind);
        currentpos.longitude = convert_decimal_degrees(gnrmc_localcopy.longitude, &gnrmc_localcopy.EW_ind);
        GPS_error.latitude = currentpos.latitude - differentialpos.latitude;
        GPS_error.longitude = currentpos.longitude - differentialpos.longitude;

        #ifdef debug_GPS_differential
            char lat_str[20];
            char lon_str[20];

            snprintf(lat_str, sizeof(lat_str), "%.6f", currentpos.latitude);
            snprintf(lon_str, sizeof(lon_str), "%.6f", currentpos.longitude);
            UART_puts("Current Position: "); UART_puts(lat_str); UART_puts(" "); UART_puts(lon_str); UART_puts("\r\n");

            snprintf(lat_str, sizeof(lat_str), "%.6f", differentialpos.latitude);
            snprintf(lon_str, sizeof(lon_str), "%.6f", differentialpos.longitude);
            UART_puts("Differential Position: "); UART_puts(lat_str); UART_puts(" "); UART_puts(lon_str); UART_puts("\r\n");

            snprintf(lat_str, sizeof(lat_str), "%.6f", GPS_error.latitude);
            snprintf(lon_str, sizeof(lon_str), "%.6f", GPS_error.longitude);
            UART_puts("Calculated GPS Error: "); UART_puts(lat_str); UART_puts(" "); UART_puts(lon_str); UART_puts("\r\n");
        #endif
    }

}


void GPS_Errorcalc(void *argument)
{
    osDelay(100);

	UART_puts((char *)__func__); UART_puts(" started\r\n");

    differentialpos.latitude = 52.084683;
    differentialpos.longitude = 5.168671;

    while (1)
    {
		if(enable_errorcalc == 1){errorcalc();}
        osDelay(1);
    }
}

