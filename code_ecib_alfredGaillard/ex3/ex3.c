/**
 * \file
 *         Exercice 3 : Un programme qui fait clignoter les trois leds, une à une, toutes les secondes.
 * \author
 *         Alfred Gaillard
 */

#include "contiki.h"
#include "leds.h"
#include <stdio.h> /* For printf() */

/*---------------------------------------------------------------------------*/

PROCESS(ledsTimer, "exercice3");

AUTOSTART_PROCESSES(&ledsTimer);

static struct etimer et;

/*---------------------------------------------------------------------------*/

PROCESS_THREAD(ledsTimer, ev, data)
{

	//LEDS
	static int i = 0; //indice du led (0,1 ou 2 correspondra respectivement à 1,2 ou 4)
	int leds[] = {1,2,4}; //4=red 1=green 2=yellow

	PROCESS_BEGIN();
  
		//clignotement des leds

		//On set les paramètres du timer tel que durée avant flag d'interruption
	 	etimer_set(&et, CLOCK_SECOND); // Trigger a timer after 1 second.
	  
		for(i;;i++){
			PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et)); //lancement timer
			etimer_reset(&et); //reset du flag
			leds_toggle(leds[(i-1)%3]); //changement d'état du led
			leds_toggle(leds[i%3]); //changement d'état du led
			printf("Indice de led : %i\n", i%3); //affichage de l'indice du led
	  	}
	  	
  	PROCESS_END();

}

/*---------------------------------------------------------------------------*/
