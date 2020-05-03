#include <pthread.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>

#include "main.h"
#include "dyn/dyn_app_common.h"
#include "dyn/dyn_app_motors.h"
#include "dyn/dyn_app_sensor.h"
#include "dyn/dyn_frames.h"
#include "dyn/dyn_instr.h"
#include "dyn_test/dyn_emu.h"
#include "dyn_test/b_queue.h"
#include "joystick_emu/joystick.h"

uint8_t estado = Ninguno, estado_anterior = Ninguno, finalizar = 0;
/**
 * main.c
 */
int main(void)
{

	setbuf(stdout, NULL);

	pthread_t tid, jid;
	uint8_t tmp;
	bool direccio = true;

	//Init semaphores for TX data handshake
	//inicialitza els dos objectes sem�for amb el valor 0, en vermell
	sem_init(&sem_tx_msp, 0, 0);
	sem_init(&sem_tx_cli, 0, 0);

	//Init queue for RX data
	init_queue();

	//Start thread for dynamixel module emulation
	pthread_create(&tid, NULL, dyn_emu, (void*) &tid); //crea fil per simular la comunicaci� amsb els moduls dynamixel
	pthread_create(&jid, NULL, joystick_emu, (void*) &jid); //amb el joystick

	//Activem el mode endless turn
	//set_endless_turn_mode();

	//Testing some high level function
	/*printf("Setting LED to 0 \n");
    dyn_led_control(1, 0); //estableix en el m�dul amb id (primer par�metre) el valor del segon par�metre
    printf("Getting LED value \n");
    dyn_led_read(1, &tmp); //llegeix el valor del Led i el desa en tmp
    assert(tmp == 0);
    printf("Setting LED to 1 \n");
	dyn_led_control(1, 1);
	printf("Getting LED value \n");
    dyn_led_read(1, &tmp);
    assert(tmp == 1);*/

	//TODO: Falta inicialitzar velocitat a 0
    /*Testing motors high level function
    printf("\nMoure endavant!\n");
    moure_endavant();
    printf("\nMoure enrere!\n");
    moure_enrere();
    printf("\nMoure dreta!\n");
    moure_dreta();
	printf("\nMoure esquerra!\n");
    moure_esquerra();
	printf("\nTirabuixo!\n");
    tirabuixo();
	printf("\nAugmentar velocitat!\n");
    augmentar_velocitat(1);
	printf("\nDisminuir velocitat!\n");
    disminuir_velocitat(1);
	printf("\nParar!\n");
    parar();
	printf("\nAccelerar!\n");
    accelerar();
	printf("\nFrenar!\n");
    frenar();*/

	// Testing sensor high level function
	printf("\nLlegir valors sensor\n");
	assert(distancia_frontal() == 0x2C);
	assert(distancia_esquerra() == 0x50);
	assert(distancia_dreta() == 0x0E);

	printf("************************\n");
	printf("Test passed successfully\n");
	printf("Pulsar 'q' para terminar, qualquier tecla para seguir\r");
	//garanteix que el buffer estigui "net"
	fflush(stdout);//	return 0;

	while(estado != Quit)
	{
		/*
		 * Actualitza el valor de les variables d'estat segons l'ultima
		 * tecla clicada (simulant joystick i botons)
		 */
		Get_estado(&estado, &estado_anterior);
		if(estado != estado_anterior){
			//s'actualitza l'estat anterior amb el valor de l'actual
			Set_estado_anterior(estado);
			printf("estado = %d\n", estado);
			fflush(stdout);
			switch(estado){
			case Sw1:
				if(direccio) {
					printf("\nMoure enrere!\n");
					moure_enrere();
					direccio = false;
				} else {
					printf("\nMoure endavant!\n");
					moure_endavant();
					direccio = true;
				}
				break;
			case Sw2:
				printf("\nParar!\n");
				parar();
				break;
			case Up:
				printf("\nAccelerar!\n");
				accelerar();
				break;
			case Center:
				printf("\nTirabuixo!\n");
				tirabuixo();
				break;
			case Left:
				printf("\nMoure esquerra!\n");
				moure_esquerra();
				break;
			case Right:
				printf("\nMoure dreta!\n");
				moure_dreta();
				break;
			case Down:
				printf("\nFrenar!\n");
				frenar();
				break;
			case Quit:
				printf("Adios!\n");
				break;
			}
			fflush(stdout);
		}
	}
	printf("Programa terminado\n");
	//Signal the emulation thread to stop
	pthread_kill(tid, SIGTERM);
	pthread_kill(jid, SIGTERM);
}
