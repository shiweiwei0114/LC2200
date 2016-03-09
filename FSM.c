/*
 * FSM.c
 *
 *  Created on: Feb 21, 2016
 *      Author: trung
 */
#include <stdlib.h>
#include "FSM.h"

FSM * FSM_constructor(Memory *memory, int orig, int numb) {
	FSM *fsm = malloc(sizeof(FSM));
	fsm->PC = orig;
	fsm->orig = orig;
	fsm->numbOfInstructions = numb;
	fsm->alu = ALU_constructor();
	fsm->maState = LOAD;

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

int FSM_handle(FSM *fsm) {
	switch (FSM_getState(fsm)) {
	case LOAD: {
		FILE *inputFile = NULL;
		inputFile = fopen("main.txt", "r");
		char *line = (char *) malloc(sizeof(100 + 1));
		if (inputFile != NULL) {
			while (fgets(line, WORD_SIZE + 1, inputFile) > 0) {
				if (line[0] != '\n') {
					printf("Line: %s\n", line);
					sscanf(line, "%s", fsm->memory[fsm->orig]);
					printf("Line in memory: %s\n", fsm->memory[fsm->orig]);

				};
				fsm->orig++;
			}
		}
		FSM_nextState(fsm);
		break;
	}
	case WAITING: {
		printf("Waiting...\n");
		char step;
		do {
			printf("Press letter 's' key to execute next instruction:\n");
			scanf("%c", &step);
		} while (step != 's' && step != 'S');
		printf("Valid.\n");
		FSM_nextState(fsm);
		break;
	}
	case FETCH: {
		printf("Fetching...\n");
		FSM_nextState(fsm);
		break;
	}
	case DECODE: {
		printf("Decoding...\n");

		FSM_nextState(fsm);
		break;
	}
	case EXECUTE: {
		printf("Executing...\n");

		FSM_nextState(fsm);
		return 1;
		break;
	}
	}
	return 0;
}

void FSM_start(FSM *fsm) {
		while (fsm->numbOfInstructions > 0) {
			if (FSM_handle(fsm) == 1) {
				printf("Num instruction: %d\n", fsm->numbOfInstructions);
				fsm->numbOfInstructions--;
			}
		}
}
