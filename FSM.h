/*
 * FSM.h
 *
 *  Created on: Feb 21, 2016
 *      Author: trung
 */

#ifndef FSM_H_
#define FSM_H_

#include "ALU.h"
#include "Memory.h"
#include "Registers.h"

enum macro_state {
	FETCH,
	DECODE,
	EXECUTE
};

typedef enum macro_state maState;

enum micro_state {
	ifect1, ifetch2, ifetch3,
	add1, add2, add3,
	nand1, nand2, nand3,
	addi1, addi2, addi3,
	lw1, lw2, lw3,
	sw1, sw2, sw3, sw4,
	jump1, jump2,
	halt

};


struct FSM_struct {
	maState maState;

};

typedef struct FSM_struct FSM;

FSM * setState(FSM *, maState);
maState getState(FSM *);

#endif /* FSM_H_ */
