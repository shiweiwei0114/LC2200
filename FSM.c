/*
 * FSM.c
 *
 *  Created on: Feb 21, 2016
 *      Author: trung
 */
#include <stdlib.h>
#include "FSM.h"

FSM * FSM_constructor() {
	FSM *fsm = malloc(sizeof(FSM));
	fsm->PC = 0;
	fsm->alu = ALU_constructor();
	return fsm;
}

FSM *FSM_setState(FSM *fsm, maState new) {
	fsm->maState = new;
	return fsm;
}

maState FSM_getState(FSM *fsm) {

	return fsm->maState;
}

