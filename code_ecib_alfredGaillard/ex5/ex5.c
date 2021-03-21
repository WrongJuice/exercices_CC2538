/**
 * \file
 *         Exercice 5 : Un programme qui allume ou éteint les leds toutes les 4 secondes ou selon l'appui du bouton.
 * \author
 *         Alfred Gaillard
 */

#include "contiki.h"
#include "leds.h"
#include "dev/button-sensor.h"

/*---------------------------------------------------------------------------*/

PROCESS(ledsTimer, "exercice5 - leds every 4 seconds");
PROCESS(ledsSelect, "exercice5 - leds when select pushed");

AUTOSTART_PROCESSES(&ledsTimer , &ledsSelect);

static struct etimer et;

/*---------------------------------------------------------------------------*/

PROCESS_THREAD(ledsTimer, ev, data)
{

	static struct etimer et; //instance nécessaire pour paramétrer le timer

	PROCESS_BEGIN();
  
		//On set les paramètres du timer tel que durée avant flag d'interruption
		etimer_set(&et, CLOCK_SECOND*4); // Trigger a timer after 1 second.
  
		while(1){
			PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et)); //lancement timer
			etimer_reset(&et); //reset du flag
			leds_toggle(LEDS_ALL); //changement d'état du led
		}
	  	
  	PROCESS_END();

}

PROCESS_THREAD(ledsSelect, ev, data)
{

	struct sensors_sensor *sensor; //boutons


	PROCESS_BEGIN();
  
		while(1) {
	    	PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event); //attente d'un appui sur select
	    	//If we woke up after a sensor event, inform what happened
	    	sensor = (struct sensors_sensor *)data;
	    	if(sensor == &button_sensor) leds_toggle(LEDS_ALL);
	  	}
	  	
  	PROCESS_END();

}

/*---------------------------------------------------------------------------*/
