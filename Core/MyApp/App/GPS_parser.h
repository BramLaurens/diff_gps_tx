/*
 * GPS_parser.h
 *
 *  Created on: Jul 28, 2025
 *      Author: braml
 */

#ifndef MYAPP_APP_GPS_PARSER_H_
#define MYAPP_APP_GPS_PARSER_H_

/**
 * @brief Struct to hold GPS coordinates in decimal degrees.
 */
typedef struct {
	double latitude;    // Latitude in decimal degrees
	double longitude;   // Longitude in decimal degrees
} GPS_decimal_degrees_t;

extern double convert_decimal_degrees(char *nmea_coordinate, char* ns);

#endif /* MYAPP_APP_GPS_PARSER_H_ */
