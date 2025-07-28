/*
 * GPS_parser.c
 *
 *  Created on: Jul 10, 2025
 *      Author: braml
 */

#include <admin.h>
#include "main.h"
#include "cmsis_os.h"
#include "gps.h"

/**
* @brief GPS parser task
* @param argument, kan evt vanuit tasks gebruikt worden
* @return void
*/

void GPS_parser(void *argument)
{
	osDelay(100);

	UART_puts((char *)__func__); UART_puts(" started\r\n");

	while (TRUE)
	{

		osDelay(1000);

		if (Uart_debug_out & GPS_DEBUG_OUT)
		{

		}
	}
}

