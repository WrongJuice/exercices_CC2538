/**
 * \file
 *         Exercice 4 : Un programme qui allume ou éteint les leds dans l’ordre suite à l'appui bouton
 * \author
 *         Alfred Gaillard
 */

#include "contiki.h"
#include "leds.h"
#include "dev/button-sensor.h"

/*---------------------------------------------------------------------------*/

PROCESS(ledsSelect, "exercice4");

AUTOSTART_PROCESSES(&ledsSelect);

/*---------------------------------------------------------------------------*/

PROCESS_THREAD(ledsSelect, ev, data)
{

	struct sensors_sensor *sensor; //boutons

	//LEDS
	static int i = 0; //indice du led (0,1 ou 2 correspondra respectivement à 1,2 ou 4)
	int leds[] = {1,2,4}; //4=red 1=green 2=yellow

	PROCESS_BEGIN();
  
		while(1) {
	    	PROCESS_WAIT_EVENT_UNTIL(ev == sensors_event); //attente d'un appui sur select
	    	//If we woke up after a sensor event, inform what happened
	    	sensor = (struct sensors_sensor *)data;
	    	if(sensor == &button_sensor){
	    		leds_toggle(leds[(i-1)%3]); //changement d'état du led
				leds_toggle(leds[i%3]); //changement d'état du led
				i++;
	    	}
	  	}
	  	
  	PROCESS_END();

}

/*---------------------------------------------------------------------------*/
