#ifndef ALU_H
#define ALU_H

#include "Registers.h"

typedef enum Instruction {
	ADD,
	NAND,
	ADDI,
	LW,
	SW,
	ST,
	NOT,
	BEG,
	JALR
}InstructionType;

struct ALU_type {
	InstructionType inType;
	char *A;
	char *B;
	char *dest;
	char *result;
	Reg *regs;
};

typedef struct ALU_type ALU;

ALU *ALU_constructor(Reg *);

int ALU_execute(ALU *, Reg *);
char * Nand(char *a, char *b);
int Add(char *regX, char *regY, char *regZ);
int Addi(char *b, int immVal, char *regX);

#endif
