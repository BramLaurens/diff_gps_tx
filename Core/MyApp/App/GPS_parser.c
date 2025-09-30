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
#include "ARM_keys.h"

// #define debug_GPS_parser 

#define samples_size 200 // Number of samples to average for GPS data. Keep in mind sample frequency of 1Hz, so this is 15 minutes of data.

GNRMC gnrmc_localcopy; // local copy of struct for GNRMC-messages
GPS_decimal_degrees_t GPS_samples[samples_size]; // Struct array to hold converted GPS coordinates
GPS_decimal_degrees_t GPS_average_pos = {0.0, 0.0}; // Struct to hold the average GPS position
int samplecount = 0; // Counter for the number of samples taken

char savedLatitude[20]; // Buffer to save latitude
char savedLongitude[20]; // Buffer to save longitude

double convert_decimal_degrees(char *nmea_coordinate, char* ns);
double calc_average(GPS_decimal_degrees_t *samples, int count, char coord);

/**
 * @brief Adds a sample to the GPS_samples array and calculates the average position when enough samples are collected.
 * @note This function checks validity of the GPS data before adding a sample.The sample size is defined by samples_size.
 * 
 */
void add_GPS_sample()
{
	/*
	 * Take a safe snapshot of the latest GNRMC data. GPS_getLatestGNRMC
	 * copies under the GPS mutex into the provided destination, so we
	 * first copy into a local temporary and then memcpy that snapshot
	 * into `gnrmc_localcopy`. This ensures the data we
	 * use remains valid even if frontendBuffer changes later.
	 */
	GPS_getLatestGNRMC(&gnrmc_localcopy);

	if(gnrmc_localcopy.status == 'V') // If status is 'N' (not valid), skip processing
	{
		#ifdef debug_GPS_parser 
			UART_puts("\r\nInvalid GPS data received (status N). Skipping sample.\r\n");
		#endif
	}

	if(samplecount < samples_size && gnrmc_localcopy.status == 'A') // Check if we have space for more samples and if data is valid
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
		enable_gpsaveraging = 0; // Disable GPS averaging after one complete average
	}
}

/**
 * @brief Converts NMEA coordinate format (ddmm.mmmm) to decimal degrees. (+ for N/E, - for S/W)
 * 
 * @param nmea_coordinate NMEA coordinate string
 * @param ns North south or East west indicator ('N', 'S', 'E', 'W')
 * @return Decimal degrees as double 
 */
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


/**
 * @brief Calculates the average of an array of GPS samples for either latitude or longitude.
 * 
 * @param samples Array of GPS samples of type GPS_decimal_degrees_t
 * @param count Number of samples in the array
 * @param coord 'L' for latitude, 'G' for longitude
 * @return Average value as double
 */
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

void GPS_parser(void *argument)
{
	osDelay(100);

	UART_puts((char *)__func__); UART_puts(" started\r\n");

	while (TRUE)
	{

		// Wait for notification from fill_gnrmc that new data is available
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY); 

		// Check if GPSdata mutex is available
		
		// Add a GPS sample to the averaging function
		if(enable_gpsaveraging == 1){add_GPS_sample();}

 		osDelay(1); //Function runs every second, as GPS data is updated every second
	}
}

