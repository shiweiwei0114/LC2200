#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdbool.h>
#include "Memory.h"
#include "Registers.h"


#define WORD_SIZE 32
#define OPCODE_SIZE 4
#define REGISTER_SIZE = 4

struct instruction_format {
	char opcode[4];
	char registers[8];
	char general[20];
};

//All supported instructions
typedef enum {
	add,
	nand,
	addi,
	lw,
	sw,
	st,
	not,
	beq,
	jalr,
} ISA;

struct Assembler {
	int orig;
	bool origExsit;
	char machineLine[100][WORD_SIZE];
	Memory memory;
	int endIndex;
	int numOfInstruction;
	FILE *outputFile;
};

typedef struct Assembler Assembler;

Assembler *Assembler_constructor(void);

int AssemblerBinToDec(char *binNum);

Assembler *Assembler_translate(Assembler *,FILE *, char *);

void AssemblerReset();

int Assembler_getNumInstructions();

#endif
