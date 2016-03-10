/*
 * FSM.c
 *
 *  Created on: Feb 21, 2016
 *      Author: trung
 */
#include <stdlib.h>
#include <string.h>
#include "FSM.h"

FSM * FSM_constructor(Memory *memory, Reg *regs, int orig, int numb) {
	FSM *fsm = (FSM *) malloc(sizeof(FSM));
	fsm->PC = orig;
	fsm->orig = orig;
	fsm->size = 0;
	fsm->numbOfInstructions = numb;
	fsm->alu = ALU_constructor(regs);
	fsm->maState = LOAD;
	fsm->IR = (char *) malloc(sizeof(WORD_SIZE + 1));
	fsm->registers = Register_initialize();
	int i;
	for (i = 0; i < CAPACITY; i++) {
		int j;
		for (j = 0; j < WORD_SIZE; j++)
			fsm->memory[i][j] = '\0';
	}
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
char *FSM_fetch(FSM *fsm, int address) {
	return fsm->memory[address];
}
void decodeR(FSM *fsm, char *opcode, char *instruction) {
	char *tok;
	tok = strtok(NULL, "|");
	printf("Reg X: %s\n", tok);
	char *regX = tok;
	tok = strtok(NULL, "|");
	printf("Reg Y: %s\n", tok);
	char *regY = tok;
	tok = strtok(NULL, "|");
	printf("Reg Z: %s\n", tok);
	char *regZ = tok;
	fsm->alu->A = Register_getValue(fsm->registers, regY);
	fsm->alu->B = Register_getValue(fsm->registers, regZ);
	fsm->alu->dest = regX;
	printf("ALU values: %s %s %s\n", fsm->alu->A, fsm->alu->B, fsm->alu->dest);
	if (strcmp(opcode, "0000") == 0){	//add x, y, z
		fsm->alu->inType = ADD,
		printf("Decoded instruction: ADD\n");
	} else if (strcmp(opcode, "0001") == 0) {	//nand x, y, z
		fsm->alu->inType = NAND,
		printf("Decoded instruction: NAND\n");
	}
}
int binaryToDec(char *binNum) {
	int len = strlen(binNum);
	unsigned int result = 0;
	unsigned int signExtend;
	unsigned int negResult = 0;

	//convert the char as bits in an unsigned int
	int i;
	for (i = 0; i < len; i++) {
		result = result << 1; //shift 1
		if (binNum[i] == '1') {
			result += 1;
		}
		//printf("%d\n", result);
	}

	//if it's a negative, use 2's complement, convert to positive number
	if (binNum[0] == '1') {
		signExtend = (1 << (len - 1));
		signExtend -= 1;
		signExtend = ~signExtend;
		result |= signExtend;

		negResult = (~result);
		negResult += 1;
	}

	return result;
}
void decodeI(FSM *fsm, char *opcode, char *instruction) {
	if (strcmp(opcode, "0011") == 0 || strcmp(opcode, "0100") == 0)	{	//lw and sw
		char *tok;
		tok = strtok(NULL, "|");
		printf("Reg X: %s\n", tok);
		char *regX = tok;
		int address;
		tok = strtok(NULL, "|");
		char *addressBin = tok;
		address = binaryToDec(addressBin);
		printf("Address: %d\n", address);

		tok = strtok(NULL, "|");
		int offset;
		sscanf(tok, "%d", &offset);
		printf("Offset: %d\n", offset);
		printf("Opcode: %s\n", opcode);
		if (strcmp(opcode, "0011") == 0) {	//lw
			fsm->alu->inType = LW;
			FSM_fetch(fsm, address);
			printf("Decoded instruction: LW\n");
		} else if (strcmp(opcode, "0100") == 0) { //sw
			fsm->alu->inType = SW;
			printf("Decoded instruction: SW\n");
			char *source =  Register_getValue(fsm->registers, regX);
			printf("Source: %s\n", source);
			strcpy(fsm->memory[address + offset], source);
			printf("Stored at memory location %d: %s\n", address + offset, fsm->memory[address + offset]);
		}
	} else {
		printf("Not implemented yet.\n");
	}

}
void decodeJ(char *binary) {

}
void findInstruction(FSM *fsm, char *opcode, char *instruction){
	if (strcasecmp(opcode, "0000") == 0) { //add
		decodeR(fsm, opcode, instruction);
	} else if (strcasecmp(opcode, "0001") == 0) { //nand
		decodeR(fsm, opcode, instruction);
	}else if (strcasecmp(opcode, "0010") == 0) { //addi
		decodeI(fsm, opcode, instruction);
	}else if (strcasecmp(opcode, "0011") == 0) { //lw
		decodeI(fsm, "0011", instruction);
	}else if (strcasecmp(opcode, "0100") == 0) { //sw
		decodeI(fsm, "0100", instruction);
	}else if (strcasecmp(opcode, "0101") == 0) { //st

	}else if (strcasecmp(opcode, "0110") == 0) {//not

	}else if (strcasecmp(opcode, "0110") == 0) {//beg
		decodeI(fsm, opcode, instruction);
	} else if (strcasecmp(opcode, "1000") == 0) {//jalr
	}
}
char *FSM_decode(FSM *fsm) {
	char *instruction = fsm->IR;
	char *opcode;
	opcode = strtok(instruction, "|");
	findInstruction(fsm, opcode, instruction);
	return NULL;
}
int executeInstruction(FSM * fsm) {
	ALU_execute(fsm->alu, fsm->registers);
	printRegisters(fsm->registers);
	return 0;
}
int FSM_handle(FSM *fsm) {
	switch (FSM_getState(fsm)) {
	case LOAD: {
		FILE *inputFile = NULL;
		size_t nBytes = 100;
		inputFile = fopen("main.txt", "r");
		char *line = (char *) malloc(sizeof(100 + 1));
		if (inputFile != NULL) {
			while (getline(&line, &nBytes, inputFile) > 0) {
				if (line[0] != '\n') {
					//printf("Line: %s\n", line);
					strcpy(fsm->memory[fsm->orig], line);
					fsm->size++;
					//printf("Line in memory: %s\n", fsm->memory[fsm->orig]);

				};
				fsm->orig++;
			}
		}
//		int i = 2000;
//		for ( ;i< fsm->size + 2000; i++) {
//			char *block = fsm->memory[i];
//			printf("%s\n", block);
//		}
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
		fsm->IR = FSM_fetch(fsm, fsm->PC);
		fsm->PC++;
		printf("Fetched instruction: %s", fsm->IR);
		FSM_nextState(fsm);
		break;
	}
	case DECODE: {
		printf("Decoding...\n");
		FSM_decode(fsm);
		FSM_nextState(fsm);
		break;
	}
	case EXECUTE: {
		printf("Executing...\n");
		if (executeInstruction(fsm) == 0) {
			printRegisters(fsm->registers);
			FSM_nextState(fsm);
			return 1;
		} else {
			printf("Error!\n");
			return 0;
		}

		break;
	}
	}
	return 0;
}

void FSM_start(FSM *fsm) {
	while (fsm->numbOfInstructions > 0) {
		if (FSM_handle(fsm) == 1) {
			fsm->numbOfInstructions--;
			printf("Num instruction remaining: %d\n", fsm->numbOfInstructions);

		}
	}
	printf("Execution ends.\n");
}
