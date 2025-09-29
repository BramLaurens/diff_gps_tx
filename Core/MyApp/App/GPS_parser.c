/*
 * GPS_parser.c
 *
 *  Created on: Jul 10, 2025
 *      Author: braml
 */


// Test
#include <admin.h>
#include "main.h"
#include "cmsis_os.h"
#include "gps.h"
#include "GPS_parser.h"

#define samples_size 500 // Number of samples to average for GPS data. Keep in mind sample frequency of 1Hz, so this is 15 minutes of data.

/**
* @brief GPS parser task
* @param argument, kan evt vanuit tasks gebruikt worden
* @return void
*/

GNRMC gnrmc_localcopy; // local copy of struct for GNRMC-messages
GNRMC *localBuffer;
GPS_decimal_degrees_t GPS_samples[samples_size]; // Struct array to hold converted GPS coordinates
GPS_decimal_degrees_t GPS_average_pos = {0.0, 0.0}; // Struct to hold the average GPS position
int samplecount = 0; // Counter for the number of samples taken

char savedLatitude[20]; // Buffer to save latitude
char savedLongitude[20]; // Buffer to save longitude

double convert_decimal_degrees(char *nmea_coordinate, char* ns);
double calc_average(GPS_decimal_degrees_t *samples, int count, char coord);

void GPS_parser(void *argument)
{
	osDelay(100);

	UART_puts((char *)__func__); UART_puts(" started\r\n");

	while (TRUE)
	{
		// Check if GPSdata mutex is available
		if(xSemaphoreTake(hGPS_Mutex, portMAX_DELAY) == pdTRUE)
		{
			//Get adress of the latest complete GNRMC data
			//GPS_getLatestGNRMC(localBuffer);
			// Copy the data from the readerBuffer to a local struct
			memcpy(&gnrmc_localcopy, (const void*)localBuffer, sizeof(GNRMC)); // copy data from readerBuffer to local gnrmc_readercopy

			if(samplecount < samples_size && gnrmc_localcopy.status == 'A') // Check if we have space for more samples
			{
				GPS_samples[samplecount].latitude = convert_decimal_degrees(gnrmc_localcopy.latitude, &gnrmc_localcopy.NS_ind);
				GPS_samples[samplecount].longitude = convert_decimal_degrees(gnrmc_localcopy.longitude, &gnrmc_localcopy.EW_ind);


				// Print the saved GPS sample to UART
				UART_puts("\r\nGPS sample added: ");
				UART_putint(samplecount);
				UART_puts("	Lat: ");
				snprintf(savedLatitude, sizeof(savedLatitude),"%.6f", GPS_samples[samplecount].latitude);
				UART_puts(savedLatitude);

				UART_puts(" Long: ");
				snprintf(savedLongitude, sizeof(savedLongitude),"%.6f", GPS_samples[samplecount].longitude);
				UART_puts(savedLongitude);

				samplecount++;
			}
			else if (samplecount >= samples_size) // If we have enough samples, calculate the average
			{
				GPS_average_pos.latitude = calc_average(GPS_samples, samplecount, 'L');
				GPS_average_pos.longitude = calc_average(GPS_samples, samplecount, 'G');

				// Print the average GPS position to UART
				UART_puts("\r\nAverage GPS position: ");
				UART_puts("Lat: ");
				snprintf(savedLatitude, sizeof(savedLatitude),"%.6f", GPS_average_pos.latitude);
				UART_puts(savedLatitude);

				UART_puts(" Long: ");
				snprintf(savedLongitude, sizeof(savedLongitude),"%.6f", GPS_average_pos.longitude);
				UART_puts(savedLongitude);

				// Reset sample count for next averaging
				samplecount = 0;
			}



			xSemaphoreGive(hGPS_Mutex); // Release the mutex
		}


 		osDelay(1000); //Function runs every second, as GPS data is updated every second

		if (Uart_debug_out & GPS_DEBUG_OUT)
		{

		}
	}
}

double convert_decimal_degrees(char *nmea_coordinate, char* ns)
{
	double raw = atof(nmea_coordinate); // Convert string to double

	int degrees = (int)(raw / 100); // Get the degrees part
	double minutes = raw - (degrees * 100); // Get the minutes part

	double decimal_degrees = degrees + (minutes / 60.0); // Convert to decimal degrees

	if (ns[0] == 'S' || ns[0] == 'W') // Check if the coordinate is South or West
	{
		decimal_degrees = -decimal_degrees; // Make it negative
	}

	return decimal_degrees; // Return the converted value

}

double calc_average(GPS_decimal_degrees_t *samples, int count, char coord)
{
	double sum = 0.0;

	for (int i = 0; i < count; i++)
	{
		if (coord == 'L') // Latitude
		{
			sum += samples[i].latitude;
		}
		else if (coord == 'G') // Longitude
		{
			sum += samples[i].longitude;
		}
	}

	return sum / count; // Return the average
}



