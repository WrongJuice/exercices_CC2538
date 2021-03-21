/**
 * \file
 *         Exercice 2 : un programme qui allume les 3 leds
 * \author
 *         Alfred Gaillard
 */

#include "contiki.h"
#include "leds.h"

/*---------------------------------------------------------------------------*/

PROCESS(leds, "exercice2");

AUTOSTART_PROCESSES(&leds);

/*---------------------------------------------------------------------------*/

PROCESS_THREAD(leds, ev, data)
{

	PROCESS_BEGIN();
  
		leds_toggle(LEDS_ALL);
	  	
  	PROCESS_END();

}

/*---------------------------------------------------------------------------*/
