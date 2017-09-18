/*
	 BY: Glenn Lopez
   NAME.c
   gcc -o NAME NAME.c -lpigpio -lrt -lpthread
   sudo ./NAME
	 Note: This version is stable
*/

#include <stdio.h>		//standard lib
#include <pigpio.h>		//for gpio
#include <unistd.h>		//for usleep

struct fsmData{
	void (*out)(void);
	long delay;
	unsigned int next[4];
}; typedef const struct fsmData FSM;

//state function prototypes
void S0();
void S1(); void S4(); void S7();
void S2(); void S5(); void S8();
void S3(); void S6(); void S9();

FSM Motor[10] = {
	//inputs-->	 0 1 2 3
	{&S0,	5000,	{1,3,0,0}},	//initial state

	{&S1,	5000,	{2,0,0,0}},
	{&S2,	5000,	{3,1,0,0}},
	{&S3,	5000,	{0,2,0,0}},
};






/***************
	MAIN
***************/
int main (){ unsigned int cState;

	//GPIO init error prompt
	if (gpioInitialise() < 0){
      fprintf(stderr, "pigpio initialisation failed\n");
      return 1;
   }

	//GPIO setup: 5,6,13,26
	gpioSetMode(5, PI_OUTPUT);
	gpioSetMode(6, PI_OUTPUT);
	gpioSetMode(13, PI_OUTPUT);
	gpioSetMode(26, PI_OUTPUT);

	while(1){ unsigned int i, j, step, dir;

		printf("[0]forward or [1]backwards: ");
		scanf("%i", &dir);

		printf("How many steps: ");
		scanf("%i", &step);

		printf("\n");		//newline


		//Finite state machine loop
		for(i = 0; i < step; i++){
			for(j = 0; j < 4; j++){
				usleep(Motor[cState].delay);
				Motor[cState].out();
				usleep(Motor[cState].delay);
				cState = Motor[cState].next[dir];
			}
		}
	}

	printf("\n");		//newline

	/* Stop DMA, release resources */
	gpioTerminate();
	return 0;
}





/***************
	FUNCTION
***************/
void S0(){						//0x05
   gpioWrite(5,	0);
   gpioWrite(6,	1);
   gpioWrite(13,	0);
   gpioWrite(26,	1);
}

void S1(){						//0x06
   gpioWrite(5,	0);
   gpioWrite(6,	1);
   gpioWrite(13,	1);
   gpioWrite(26,	0);
}

void S2(){						//0x0A
   gpioWrite(5,	1);
   gpioWrite(6,	0);
   gpioWrite(13,	1);
   gpioWrite(26,	0);
}

void S3(){						//0x09
   gpioWrite(5,	1);
   gpioWrite(6,	0);
   gpioWrite(13,	0);
   gpioWrite(26,	1);
}
