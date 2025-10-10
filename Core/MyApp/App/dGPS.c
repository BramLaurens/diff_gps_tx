#include <admin.h>
#include "main.h"
#include "cmsis_os.h"
#include "gps.h"
#include "GPS_parser.h"
#include "ARM_keys.h"
#include "NRF_driver.h"
#include "dGPS.h"

#define dGPS_debug

GNRMC gnrmc_localbuffer; // local copy of struct for GNRMC-messages
char last_GPStime[10] = "000000.000";
char c_received_GPStime[10] = "000000.000";
uint32_t last_GPS_time = 0;
uint32_t u_working_GPS_time = 0;

GPS_decimal_degrees_t GPS_working_decimalbuffer;
GPS_decimal_degrees_t GPS_working_errorbuffer;
GPS_decimal_degrees_t GPS_knowncoordinates = {52.0846255748, 5.1682501789}; // Known coordinates for error calculation
dGPS_errorData_t GPS_final_errorbuffer; // Final averaged error to be sent

int i=0; // Counter for number of data points in the current second

/**
 * @brief Calculate the average GPS error.
 * 
 */
void AVG_errorcalc(uint32_t time)
{
    GPS_working_errorbuffer.latitude  /= i;
    GPS_working_errorbuffer.longitude /= i;

    /* Store the final averaged error values, to be sent.*/
    GPS_final_errorbuffer.latitude  = GPS_working_errorbuffer.latitude;
    GPS_final_errorbuffer.longitude = GPS_working_errorbuffer.longitude;
    GPS_final_errorbuffer.timestamp = time;
}

/**
 * @brief Initialize the working error buffer.
 * 
 */
void AVG_errorinit()
{
    GPS_working_decimalbuffer.latitude = 0.0;
    GPS_working_decimalbuffer.longitude = 0.0;
    GPS_working_errorbuffer.latitude = 0.0;
    GPS_working_errorbuffer.longitude = 0.0;
}

/**
 * @brief Calculate and add a new data point to the working error buffer.
 * 
 */
void AVG_erroradddata(int i, uint32_t time)
{
    // Convert NMEA coordinates to decimal degrees, subtract known coordinates to get error, and accumulate
    double lat = convert_decimal_degrees(gnrmc_localbuffer.latitude, &gnrmc_localbuffer.NS_ind);
    double lon = convert_decimal_degrees(gnrmc_localbuffer.longitude, &gnrmc_localbuffer.EW_ind);
    GPS_working_errorbuffer.latitude += lat;
    GPS_working_errorbuffer.longitude += lon;

    #ifdef dGPS_debug
        char msg[100];
        snprintf(msg, sizeof(msg), "Added datapoint number %d for time %ld with lat %.9f and lon %.9f \r\n", i, time, lat, lon);
        UART_puts(msg);
    #endif
}

/**
 * @brief Notifies the NRF driver of new data, and lets it send data
 * 
 */
void NotifyNRF()
{
    // Send averaged error to NRF driver via queue so transmissions are buffered.
    if (xQueueSend(hNRF_Queue, &GPS_final_errorbuffer, 0) != pdPASS)
    {
        // Queue full: drop oldest and enqueue new (simple drop-oldest policy)
        dGPS_errorData_t tmp;
        if (xQueueReceive(hNRF_Queue, &tmp, 0) == pdPASS)
        {
            xQueueSend(hNRF_Queue, &GPS_final_errorbuffer, 0);
        }
    }
}

void parse_GPSdata()
{
    // gnrmc_localbuffer is expected to already contain the GNRMC to process
    if(gnrmc_localbuffer.status != 'A') // If status is not valid, skip processing
    {
        #ifdef dGPS_debug
            UART_puts("Invalid GPS data received (status N). Skipping error calculation.\r\n");
        #endif
        return;
    }

    // Extract time and convert to integer seconds in HHMMSS format
    GNRMC *ptd = &gnrmc_localbuffer;
    char *s;

    strcpy(c_received_GPStime, ptd->time);
    s = strtok(c_received_GPStime, ".");
    u_working_GPS_time = atoi(s);

    /*Check if we have a new second, if so, reset the averaging buffer and add a new point*/
    if (u_working_GPS_time != last_GPS_time)
    {
        /* New second, reset the averaging buffer and counter*/
        #ifdef dGPS_debug
            UART_puts("\r\nNew second detected. Resetting averaging buffer.\r\n");
        #endif
        i=0;
        AVG_errorinit();
        AVG_erroradddata(i+1, u_working_GPS_time);
        last_GPS_time = u_working_GPS_time;
        i++;
    }
    else
    {
        /* We have a new data point for the current second, add it to the buffer*/
        AVG_erroradddata(i+1, u_working_GPS_time);
        i++;
    }

    if(i>=5) // After collecting 5 data points, calculate the average error, and notify the NRF driver
    {
        AVG_errorcalc(u_working_GPS_time);
        NotifyNRF();

        #ifdef dGPS_debug
            UART_puts("Averaged GPS calculated.\r\n");
            char time[10];
            char lat_str[20];
            char lon_str[20];

            snprintf(time, sizeof(time), "%ld", GPS_final_errorbuffer.timestamp);
            snprintf(lat_str, sizeof(lat_str), "%.9f", GPS_final_errorbuffer.latitude);
            snprintf(lon_str, sizeof(lon_str), "%.9f", GPS_final_errorbuffer.longitude);
            UART_puts("Calculated average GPS for timestamp: "); UART_puts(time); UART_puts(" "); UART_puts(lat_str); UART_puts(" "); UART_puts(lon_str); UART_puts("\r\n");
        #endif
    }
}

void dGPS(void *argument)
{
    osDelay(100);
    
    UART_puts((char *)__func__); UART_puts(" started\r\n");

    while (1)
    {
        // Receive parsed GNRMC messages from GPS task via queue and process each one.
        GNRMC incoming;
        if (xQueueReceive(hGNRMC_Queue, &incoming, portMAX_DELAY) == pdTRUE)
        {
            // process the received message
            gnrmc_localbuffer = incoming;
            parse_GPSdata();

            // drain any additional queued items without blocking
            while (xQueueReceive(hGNRMC_Queue, &incoming, 0) == pdTRUE)
            {
                gnrmc_localbuffer = incoming;
                parse_GPSdata();
            }
        }
        osDelay(1);
    }
}
