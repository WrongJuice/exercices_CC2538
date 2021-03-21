#include "contiki.h"

#include "cpu.h"

#include "button-sensor.h"

#include "spi-arch.h"

#include "spi.h"



#include <stdio.h>

#include <stdint.h>



#define SPI_SEL_PORT_BASE GPIO_D_BASE

#define SPI_SEL_PIN_MASK GPIO_PIN_MASK(5)



PROCESS(cc2538_spi_test, "cc2538 spi test");

AUTOSTART_PROCESSES(&cc2538_spi_test);



/*---------------------------------------------------------------------------*/

PROCESS_THREAD(cc2538_spi_test, ev, data)

{

int8_t d[6]={0};

int16_t x,y,z;

PROCESS_BEGIN();

while(1) {

PROCESS_YIELD();

if(ev == sensors_event && data == &button_select_sensor) {

printf("AAA\n\r");



GPIO_CLR_PIN(SPI_SEL_PORT_BASE,SPI_SEL_PIN_MASK);

// 0x80 : lecture, 0x02 : adresse du registre

SPI_WRITE(0x80|0x02);

SPI_FLUSH();

SPI_READ(d[0]);

SPI_READ(d[1]);

SPI_READ(d[2]);

SPI_READ(d[3]);

SPI_READ(d[4]);

SPI_READ(d[5]);

// On indique la fin de la communication en mettant à 1 le SS

GPIO_SET_PIN(SPI_SEL_PORT_BASE,SPI_SEL_PIN_MASK);



x = (((int16_t)(d[1]) << 2) | ((d[0] >> 6) & 0x03));

y = (((int16_t)(d[3]) << 2) | ((d[2] >> 6) & 0x03));

z = (((int16_t)(d[5]) << 2) | ((d[4] >> 6) & 0x03));



printf("x-axis : %d\ny-axis : %d\nz-axis : %d\n",x,y,z);

}

}



PROCESS_END();

}