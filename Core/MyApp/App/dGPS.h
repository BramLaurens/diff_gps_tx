/*
 * dGPS.h
 *
 *  Created on: Oct 8, 2025
 *      Author: braml
 */

#include "main.h"
#include "cmsis_os.h"


#ifndef MYAPP_APP_dGPS_H_
#define MYAPP_APP_dGPS_H_

// DEFINE THIS TO ENABLE AVERAGING MODE TO DETERMINE BASE LOCATION
#define GPS_averagingmode

typedef struct {
    double latitude;
    double longitude;
    uint32_t timestamp; // Unix timestamp of the GPS data
} dGPS_errorData_t;

#endif /* MYAPP_APP_dGPS_H_ */
