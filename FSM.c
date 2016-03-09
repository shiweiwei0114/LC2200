/*
 * FSM.c
 *
 *  Created on: Feb 21, 2016
 *      Author: trung
 */
#include <stdlib.h>
#include "FSM.h"

FSM * FSM_constructor(Memory *memory) {
	FSM *fsm = malloc(sizeof(FSM));
	fsm->PC = 0;
	fsm->alu = ALU_constructor();
	fsm->maState = LOAD;
	fsm->memory = memory;
	return fsm;
}

FSM *FSM_setState(FSM *fsm, maState new) {
	fsm->maState = new;
	return fsm;
}

maState FSM_getState(FSM *fsm) {
	return fsm->maState;
}
FSM *FSM_nextState(FSM * fsm) {
	switch (fsm->maState) {
	case LOAD:
		fsm->maState = WAITING;
		break;
	case WAITING:
		fsm->maState = FETCH;
		break;
	case FETCH:
		fsm->maState = DECODE;
		break;
	case DECODE:
		fsm->maState = EXECUTE;
		break;
	case EXECUTE:
		fsm->maState = WAITING;
		break;
	}
	return fsm;
}

void FSM_start() {

}
