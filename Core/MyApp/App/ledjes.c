/**
* @file ledjes.c
* @brief Laat de werking van mutexes en tasknotification zien.<br>
* <b>Demonstreert: , xSemaphoreTake(), xSemaphoreGive(), xTaskNotifyGive(), ulTaskNotifyTake(), taskYIELD().</b><br>
*
* LED_Task1(), LED_Task2(), LED_Task3() en LED_Task4() tonen het mutual exclusion semaphore principe. <br>
* Allemaal zetten ze de LEDs op een bepaalde manier aan en uit.
* <i>Doordat ze een semaphore gebruiken kunnen ze allemaal hun eigen loepje
* afmaken, zonder dat ze door een context switch onderbroken worden</i>. De semaphore zorgt ervoor
* dat ze steeds even zelf eigenaar zijn van de LEDs, en zolang ze de semaphore bezitten worden
* andere taken uitgesloten (hence: <i>Mutual Exclusion Semaphore</i>). Ze krijgen dan pas de beurt als
* de task die de mutex bezit, deze vrijgeeft (met semaphoregive).
* LED_tasks 1 en 2 werken met het Round Robin principe. Dat kan door ze dezelfde prioriteit
* te geven.<br>
*
* Stel, je wilt dat niet, dan moet je iets anders verzinnen, zie LED_Task3() en LED_Task4().
* Deze hebben een kleine toevoeging t.o.v. 1 en 2:
* Ze laten niet het OS bepalen wie aan de beurt is met Round Robin,
* maar bepalen het zelf met tasknotify! Ze geven steeds elkaar de beurt.
* Zo kun je werken met verschillende task-priorities, zonder dat tasks met een lage
* prioriteit 'starven', dus geen timeslices krijgen van het OS.<br>
* Want: FreeRTOS bezit geen priority-inversion (uC//OSII bv. wel)! Daarbij gaat het OS een
* taak met een lage prioriteit die dreigt te 'starven', zelf ophogen zodat de taak wel aan de
* beurt komt.

* @author MSC
*
* @date 5/5/2022
*/

#include <admin.h>
#include "main.h"
#include "cmsis_os.h"

/// default value 100MSEC, kan veranderd worden via Terminal (user interface)
unsigned int os_delay = 100;


/**
* @brief Tasks die ledjes manipuleren nadat ze eerst afgeschermd zijn met mutex semaphores.
* @param *argument Niet gebruikt, eventueel een waarde of string om te testen
* @return void
*/
void LED_Task1 (void *argument)
{
	UART_puts((char *)__func__); UART_puts(" started\r\n");
	int i, leds;

	while(TRUE)
	{
	    xSemaphoreTake(hLED_Sem, portMAX_DELAY); /* wacht op toegang tot de semaphore;
	    * de code hieronder wordt alleen uitgevoerd nadat ik de mutex heb gekregen.
	    * andere tasks die op deze mutex wachten, kunnen pas door nadat ik de mutex
	    * heb vrijgegeven met Give.
	    */
		leds = 128; // start at led nr. 8
		for (i=0; i<8; i++, leds>>=1)
		{
        	LED_put(leds); // set leds
           	osDelay(os_delay);

	    	if (Uart_debug_out & LEDS_DEBUG_OUT)
			{
	    		UART_puts("\r\nM1 led: "); UART_putint(leds);
			}
   		}
     	xSemaphoreGive(hLED_Sem); // geef de semaphore weer vrij voor een ander
    	taskYIELD(); // done, force context switch, otherwise freeRTOS stays in this task
	}
}

/**
* @brief Tasks die ledjes manipuleren nadat ze eerst afgeschermd zijn met mutex semaphores.
* @param *argument Niet gebruikt, eventueel een waarde of string om te testen
* @return void
*/
void LED_Task2 (void *argument)
{
	UART_puts((char *)__func__); UART_puts(" started\r\n");
	int i, leds;

	while(TRUE)
	{
	    xSemaphoreTake(hLED_Sem, portMAX_DELAY); // wait to enter
		leds = 1;
		for (i=0; i<8; i++, leds<<=1)
		{
        	LED_put(leds); // set leds
          	osDelay(os_delay);

	    	if (Uart_debug_out & LEDS_DEBUG_OUT)
			{
	    		UART_puts("\r\n\tM2 led: "); UART_putint(leds);
			}
   		}
     	xSemaphoreGive(hLED_Sem); // free mutex
       	taskYIELD(); // done, force context switch, otherwise freeRTOS stays in this task
	}
}

/**
* @brief Tasks die ledjes manipuleren nadat ze eerst afgeschermd zijn met mutex semaphores.
* Task 3 en 4 werken daarnaast nog met tasknotification.
* @param *argument Niet gebruikt, eventueel een waarde of string om te testen
* @return void
*/
void LED_Task3 (void *argument)
{
	int          i, leds;
	osThreadId_t hTask4;

	if (!(hTask4 = xTaskGetHandle("LED_Task4")))
	   error_HaltOS("Err:hTask4");

	UART_puts((char *)__func__); UART_puts(" started\r\n");

	while(TRUE)
	{
	    xSemaphoreTake(hLED_Sem, portMAX_DELAY); // wait to get in...

	    for (i=0; i<4; i++) // voorbeeld hoe je je code zo overdraagbaar mogelijk maakt
	    {
	    	if 		(i==0)	leds = 8+16; // zichtbaar: 1. waarde i, 2. welke leds aan gaan
	    	else if (i==1)  leds = 4+32; // ... had ook met switch-case gekund
	    	else if (i==2)  leds = 2+64;
	    	else 			leds = 1+128;

	    	LED_put(leds);     // set leds
	    	osDelay(os_delay); // snelheid bepalen, kan veranderd worden via user interface

	    	if (Uart_debug_out & LEDS_DEBUG_OUT)
			{
				UART_puts("\r\n\t\tM3 led: "); UART_putint(leds);
			}
	    }

     	xSemaphoreGive(hLED_Sem); // free mutex

     	xTaskNotifyGive(hTask4); // give the ball to mutextask4
		osDelay(200);

		ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for task 4
	}
}

/**
* @brief Tasks die ledjes manipuleren nadat ze eerst afgeschermd zijn met mutex semaphores.
* Task 3 en 4 werken daarnaast nog met tasknotification.
* @param *argument Niet gebruikt, eventueel een waarde of string om te testen
* @return void
*/
void LED_Task4 (void *argument)
{
	int          i, leds;
	osThreadId_t hTask3;

	if (!(hTask3 = xTaskGetHandle("LED_Task3")))
	   error_HaltOS("Err:hTask3");

	UART_puts((char *)__func__); UART_puts(" started\r\n");

	while(TRUE)
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // wait for notification

	    xSemaphoreTake(hLED_Sem, portMAX_DELAY); // wait for mutex

	    for (i=0; i<4; i++) // voorbeeld hoe je je code zo overdraagbaar mogelijk maakt
	    {
	    	if 		(i==0)	leds = 1+128; // zichtbaar: 1. waarde i, 2. welke leds aan gaan
	    	else if (i==1)  leds = 2+64;  // had ook met switch-case gekund, maar dit is korter...
	    	else if (i==2)  leds = 4+32;
	    	else 			leds = 8+16;

	    	LED_put(leds);     // set leds
	    	osDelay(os_delay); // snelheid bepalen, waarde os_delay kan veranderd worden via user interface

	    	if (Uart_debug_out & LEDS_DEBUG_OUT)
			{
				UART_puts("\r\n\t\t\tM4 led: "); UART_putint(leds);
			}
	    }

     	xSemaphoreGive(hLED_Sem); // free mutex
		osDelay(200);

    	xTaskNotifyGive(hTask3); // give the ball back to task 3
	}
}

