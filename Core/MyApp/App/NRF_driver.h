/*
 * NRF_driver.h
 *
 *  Created on: Sep 23, 2025
 *      Author: braml
 */
#include "GPS_parser.h"
#include "dGPS.h"

#ifndef MYAPP_APP_NRF_DRIVER_H_
#define MYAPP_APP_NRF_DRIVER_H_

extern void NRF_Driver(void *);
extern uint8_t nrf24_SPI_commscheck(void);
void NRF_setErrorBuffer(dGPS_errorData_t error);

#endif