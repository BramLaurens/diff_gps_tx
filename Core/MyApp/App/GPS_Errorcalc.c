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
#include "NRF_driver.h"

#define debug_GPS_differential

/*Define one of these statements, depending on testing situation*/
//#define live_GPS_differential
#define dummy_GPS_differential

GNRMC gnrmc_localcopy2; // local copy of struct for GNRMC-messages

GPS_decimal_degrees_t currentpos;
GPS_decimal_degrees_t differentialpos; // Struct to hold the working differential GPS position
GPS_decimal_degrees_t GPS_error; // Struct to hold the latest GPS error

GPS_decimal_degrees_t differentialstorage[] = 
{
    {52.084619172, 5.168584982},
    {52.000100, 4.000100},
    {52.000200, 4.000200},
    {52.000300, 4.000300},
    {0, 0}
};

void errorcalc()
{
    osThreadId_t hTask;

    #ifdef debug_GPS_differential
        UART_puts("\r\nStarting GPS error calc, waiting for new data\r\n");
    #endif

    #ifdef live_GPS_differential
    // Wait for notification from GPS.c that new data is available
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY); 
    // Take a safe snapshot of the latest GNRMC data.
	GPS_getLatestGNRMC(&gnrmc_localcopy2);
    #endif

    #ifdef debug_GPS_differential
        UART_puts("New data received. Checking data validity...\r\n");
    #endif

    #ifdef dummy_GPS_differential
        // For testing without real GPS data, cycle through the differential storage array
        osDelay(1000); // Simulate delay for new data every second
        strcpy(gnrmc_localcopy2.longitude, "5214.1873");
        gnrmc_localcopy2.NS_ind = 'N';
        strcpy(gnrmc_localcopy2.latitude, "0510.1150");
        gnrmc_localcopy2.EW_ind = 'E';
        gnrmc_localcopy2.status = 'A'; // Valid data
    #endif

	if(gnrmc_localcopy2.status != 'A') // If status is not valid, skip processing
	{
        LCD_clear();
        LCD_puts("No GPS Fix");
		#ifdef debug_GPS_differential
			UART_puts("Invalid GPS data received (status N). Skipping error calculation.\r\n");
		#endif
        return;
	}

    // Calculate error if valid GPS data is available
    if(gnrmc_localcopy2.status == 'A')
    {
        UART_puts("Valid GPS data, calculating error...\r\n");
        currentpos.latitude = convert_decimal_degrees(gnrmc_localcopy2.latitude, &gnrmc_localcopy2.NS_ind);
        currentpos.longitude = convert_decimal_degrees(gnrmc_localcopy2.longitude, &gnrmc_localcopy2.EW_ind);
        GPS_error.latitude = currentpos.latitude - differentialpos.latitude;
        GPS_error.longitude = currentpos.longitude - differentialpos.longitude;

        char lat_lcd[20];
        char lon_lcd[20];
        snprintf(lat_lcd, sizeof(lat_lcd), "ltE:%.9f", GPS_error.latitude);
        snprintf(lon_lcd, sizeof(lon_lcd), "lgE:%.9f", GPS_error.longitude);
        LCD_clear();
        LCD_puts(lat_lcd);
        LCD_puts(lon_lcd);

        // Update the error buffer for NRF transmission
        NRF_setErrorBuffer(GPS_error);

        // Notify the NRF task that new error data is available
        if (!(hTask = xTaskGetHandle("NRF_driver")))
                    error_HaltOS("Err:NRF_hndle");
        xTaskNotifyGive(hTask);

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

            DisplayTaskData();  // display all task data on UART
        #endif
    }

}


void GPS_Errorcalc(void *argument)
{
    osDelay(100);

	UART_puts((char *)__func__); UART_puts(" started\r\n");

    // Pointer to move through the differential storage array, start pointing to the first element
    PGPS_decimal_degrees_t ptd = differentialstorage; 

    differentialpos.latitude = ptd->latitude;
    differentialpos.longitude = ptd->longitude;

    while (1)
    {
		if(enable_errorcalc == 1){errorcalc();}
        osDelay(1);
    }
}

