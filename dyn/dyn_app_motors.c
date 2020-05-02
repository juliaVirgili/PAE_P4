/*
 * dyn_motors.c
 *
 *  Created on: 14 abr. 2020
 *      Author: miro
 */

#include <stdio.h>
#include "dyn_instr.h"

#define velocitat_inicial;

// Per a la millor fluidesa dels motors, posem a 0 els registres corresponents als angles
void set_endless_turn_mode() {

	dyn_write(1, DYN_REG_CW_ANGLE_LIMIT_L, 0, 4);
	dyn_write(0, DYN_REG_CW_ANGLE_LIMIT_L, 0, 4);

}

// Posar les dues rodes en la mateixa velocitat i sentit contrari
void moure_endavant() {

	int velocitat = 0x032;
	int direccio = 1;
	uint8_t val[2];
	val[0] = velocitat & 0xFF;
	val[1] = ((direccio << 2) & 0x04) | ((velocitat >> 8) & 0x03);
	printf("Estem posant a velocitat %d el motor 1 i a direcció %d\n", velocitat, direccio);
	//posar roda dreta a velocitat 50 rpm (per ara)
	if (dyn_write(1, DYN_REG_MOV_SPEED_L, val, 2)) {
		//si entra ha succeït error
		printf("Error en moure_endavant roda dreta\n");
	}
	direccio = 0;
	val[0] = velocitat & 0xFF;
	val[1] = ((direccio << 2) & 0x04) | ((velocitat >> 8) & 0x03);
	printf("Estem posant a velocitat %d el motor 2 i a direccio %d\n", velocitat, direccio);
	if (dyn_write(2, DYN_REG_MOV_SPEED_L, val, 2)) {
		//si entra ha succeït error
		printf("Error en moure_endavant roda esquerra\n");
	}

}

void moure_enrere() {

	int velocitat = 0x032;
	int direccio = 0;
	uint8_t val[2];
	val[0] = velocitat & 0xFF;
	val[1] = ((direccio << 2) & 0x04) | ((velocitat >> 8) & 0x03);
	printf("Estem posant a velocitat %d el motor 1 i a direcció %d\n", velocitat, direccio);
	//posar roda dreta a velocitat 50 rpm (per ara)
	if (dyn_write(1, DYN_REG_MOV_SPEED_L, val, 2)) {
		//si entra ha succeït error
		printf("Error en moure_enrere roda dreta\n");
	}
	direccio = 1;
	val[0] = velocitat & 0xFF;
	val[1] = ((direccio << 2) & 0x04) | ((velocitat >> 8) & 0x03);
	printf("Estem posant a velocitat %d el motor 2 i a direccio %d\n", velocitat, direccio);
	if (dyn_write(2, DYN_REG_MOV_SPEED_L, val, 2)) {
		//si entra ha succeït error
		printf("Error en moure_enrere roda esquerra\n");
	}

}

void moure_dreta() {

	// Llegir velocitat de la mamoria i assignar a una variable
	int velocitat = augmentar_velocitat()
	// L

}

void moure_esquerra() {

}

// Girar sobre ell mateix (mateixa velocitat i sentit diferent)
void tirabuixo() {

}

void augmentar_velocitat(uint8_t id) {

	uint8_t val[2];
	dyn_read_byte(id, DYN_REG_MOV_SPEED_L, val[0]);
	dyn_read_byte(id, DYN_REG_MOV_SPEED_H, val[1]);
	int dir = val[1];
	dir &= 4;
	val[1] &= 3;
	int velocitat = val[0] + val[1]<<8;

}

void disminuir_velocitat() {

}

void parar() {

}
