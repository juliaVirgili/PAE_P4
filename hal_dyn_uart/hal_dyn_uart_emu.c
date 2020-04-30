/*
 * hal_dyn_uart_emu.c
 *
 *  Created on: 22 mar. 2020
 *      Author: droma
 */

#include <stdio.h>
#include <stdint.h>
#include "dyn_test/b_queue.h"
#include "main.h"
#include "dyn/dyn_frames.h"
#include "fake_msp.h"


void Sentit_Dades_Rx_emu(void) {
	printf("Changed direction to RX\n");
}

void Sentit_Dades_Tx_emu(void) {
	printf("Changed direction to TX\n");
}

void TxUAC2_emu(byte bTxdData) {
	// Wait for Tx consumer to get data
	sem_wait(&sem_tx_cli);
	// Copy data to global var
	UCA2TXBUF = bTxdData;
	printf("Cosa X : %02X ", bTxdData);
	// Signal consumer for new data
	sem_post(&sem_tx_msp);
}

void Activa_Timer_TimeOut_emu() {
	// TODO: (Opcional) Implementar iniciar timer
}

/**
 * Read a byte from the thread-safe queue and place it
 * inside the Statuspacket of RxReturn
 */
void rx_uart_byte_emu(struct RxReturn * respuesta) {
	QUEUE_RET ret = QUEUE_ERR;
	while (ret != QUEUE_OK) {
		ret = queue_pop(&(respuesta->StatusPacket[respuesta->idx]));
	}
	respuesta->idx++;
}
