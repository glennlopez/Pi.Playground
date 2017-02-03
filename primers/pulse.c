/*
   pulse.c
	gcc -o pulse pulse.c -lpigpio -lrt -lpthread
   sudo ./pulse
*/

#include <stdio.h>		//standard lib
#include <pigpio.h>		//for gpio
#include <unistd.h>		//for usleep

#define delayParam 5000

int main(int argc, char *argv[])
{

	/* RasPi Setup routine */
   if (gpioInitialise() < 0)
   {
      fprintf(stderr, "pigpio initialisation failed\n");
      return 1;
   }

   /* Set GPIO modes */
   gpioSetMode(23, PI_OUTPUT);

	/* RasPi loop subroutine */
	while(1){
		gpioWrite(23, 1); /* on */
      usleep(delayParam);
      gpioWrite(23, 0); /* off */
      usleep(delayParam);
	}

   /* Stop DMA, release resources */
   gpioTerminate();

   return 0;
}
