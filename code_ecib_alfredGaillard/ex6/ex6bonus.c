/**
 * \file
 *         Exercice 6bonus : Un programme qui affiche la température
 * \author
 *         Alfred Gaillard
 */

#include "contiki.h"
#include "dev/als-sensor.h"
#include "dev/cc2538-sensors.h"
#include <stdio.h> /* For printf() */

/*---------------------------------------------------------------------------*/

PROCESS(capteurTemp, "exercice6bonus");

AUTOSTART_PROCESSES(&capteurTemp);

/*---------------------------------------------------------------------------*/

//Optionnel (uniquement necessaire pour light sensor)
#define SENSOR_READ_INTERVAL (CLOCK_SECOND)
static struct etimer et; //instance nécessaire pour paramétrer le timer

PROCESS_THREAD(capteurTemp, ev, data)
{

	PROCESS_BEGIN();

		//On set les paramètres du timer tel que durée avant flag d'interruption
	 	etimer_set(&et, (CLOCK_SECOND)); // Trigger a timer after 1 second.

	 	while(1){
			PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et)); //lancement timer
			etimer_reset(&et); //reset du flag
			printf("Flag time\n");
			printf("Temperature = %d mC\n" , cc2538_temp_sensor.value(CC2538_SENSORS_VALUE_TYPE_CONVERTED));
	  	}
	  	
  	PROCESS_END();

}

/*---------------------------------------------------------------------------*/
