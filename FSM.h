/*
 * FSM.h
 *
 *  Created on: Feb 21, 2016
 *      Author: trung
 */

#ifndef FSM_H_
#define FSM_H_

#include <stdio.h>

#include "ALU.h"
#include "Memory.h"
#include "Registers.h"

enum macro_state {
	LOAD,
	WAITING,
	FETCH,
	DECODE,
	EXECUTE
};

typedef enum macro_state maState;

struct FSM_struct {
	int PC;
	maState maState;
	ALU * alu;
	Memory * memory;
	Reg * registers;
};

typedef struct FSM_struct FSM;

FSM * FSM_constructor(Memory *);

FSM * FSM_setState(FSM *, maState);

maState FSM_getState(FSM *);

FSM *FSM_nextState(FSM *);

void FSM_executeInstructions(FILE *objectFile);

void FSM_start();

#endif /* FSM_H_ */
