/**
 * \file
 *         Exercice 6a : Un programme qui affiche une mesure de luminosité toute les secondes
 * \author
 *         Alfred Gaillard
 */

#include "contiki.h"
#include "dev/als-sensor.h"
#include "dev/cc2538-sensors.h"
#include <stdio.h> /* For printf() */

/*---------------------------------------------------------------------------*/

PROCESS(capteurLuminosite, "exercice6a");

AUTOSTART_PROCESSES(&capteurLuminosite);

/*---------------------------------------------------------------------------*/

//Optionnel (uniquement necessaire pour light sensor)
#define SENSOR_READ_INTERVAL (CLOCK_SECOND)
static struct etimer et; //instance nécessaire pour paramétrer le timer

PROCESS_THREAD(capteurLuminosite, ev, data)
{

	PROCESS_BEGIN();

		//On set les paramètres du timer tel que durée avant flag d'interruption
	 	etimer_set(&et, (CLOCK_SECOND)); // Trigger a timer after 1 second.

	 	while(1){
			PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et)); //lancement timer
			etimer_reset(&et); //reset du flag
			printf("Flag time\n");
			printf("Ambient light sensor = %d raw\n", als_sensor.value(0));
	  	}
	  	
  	PROCESS_END();

}

/*---------------------------------------------------------------------------*/
