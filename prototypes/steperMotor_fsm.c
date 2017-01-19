/*
   NAME.c
   gcc -o NAME NAME.c -lpigpio -lrt -lpthread
   sudo ./NAME
*/

#include <stdio.h>
#include <pigpio.h>

struct fsmData{
	void (*out)(void);
	unsigned int delay;
	unsigned int next[4];

}; typedef const struct fsmData FSM;

//state function prototypes
void S0();
void S1(); void S4(); void S7();
void S2(); void S5(); void S8();
void S3(); void S6(); void S9();

FSM Motor[10] = {
	{&S0,	1,	{1,1,1,1}},
};

unsigned int cState, input, output;





/***************
	MAIN
***************/
int main (){
	if (gpioInitialise() < 0)
   {
      fprintf(stderr, "pigpio initialisation failed\n");
      return 1;
   }


	//GPIO setup: 5,6,13,26
	gpioSetMode(5, PI_OUTPUT);
	gpioSetMode(6, PI_OUTPUT);
	gpioSetMode(13, PI_OUTPUT);
	gpioSetMode(26, PI_OUTPUT);

	gpioSetMode(27, PI_OUTPUT);	//debug


	while(1){
		Motor[0].out();

	}

	printf("\n");		//newline

	/* Stop DMA, release resources */
	gpioTerminate();
	return 0;
}





/***************
	FUNCTION
***************/
void S0(){
   gpioWrite(27, 1); /* on */
}
