/*
 * dyn_motors.c
 *
 *  Created on: 14 abr. 2020
 *      Author: miro
 */

#include <stdio.h>
#include "dyn_instr.h"

// Per a la millor fluidesa dels motors, posem a 0 els registres corresponents als angles
void set_endless_turn_mode() {

	dyn_write(1, DYN_REG_CW_ANGLE_LIMIT_L, 0, 4);
	dyn_write(0, DYN_REG_CW_ANGLE_LIMIT_L, 0, 4);

}

// Posar les dues rodes en la mateixa velocitat i sentit contrri
void moure_endavant() {

	int velocitat = 0x032;
	int direccio = 1;
	uint8_t *val;
	val[0] = velocitat & 0xFF;
	val[1] = ((direccio << 2) & 0x04) | ((velocitat >> 8) & 0x03);
	printf("Estem posant a velocitat %d el motor 1 i a direcció %d\n", velocitat, direccio);
	//posar roda dreta a velocitat 50 rpm (per ara)
	if (dyn_write(1, DYN_REG_MOV_SPEED_L, val, 2)) {
		//si entra ha succeït error
		printf("Error en moure_endavant roda dreta\n");
	}
	direccio = 0;
	printf("Estem posant a velocitat %d el motor 0 i a direccio %d\n", velocitat, direccio);
	if (dyn_write(0, DYN_REG_MOV_SPEED_L, val, 2)) {
		//si entra ha succeït error
		printf("Error en moure_endavant roda esquerra\n");
	}

}

void moure_enrere() {

}

void moure_dreta() {

}

void moure_esquerra() {

}

// Girar sobre ell mateix (mateixa velocitat i sentit diferent)
void tirabuixo() {

}

void augmentar_velocitat() {

}

void disminuir_velocitat() {

}

void parar() {

}
