#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdbool.h>
#include "Memory.h"


#define WORD_SIZE 32
#define OPCODE_SIZE 4
#define REGISTER_SIZE = 4

struct instruction_format {
	char opcode[4];
	char registers[8];
	char general[20];
};

//All supported instructions
enum {
	ADD,
	NAND,
	ADDI,
	LW,
	SW,
	ST,
	NOT,
	BEQ,
	JALR,
};

struct Assembler {
	int orig;
	bool origExsit;
	char machineLine[100][WORD_SIZE];
	Memory memory;
	int endIndex;
};

typedef struct Assembler Assembler;

Assembler *Assembler_constructor(void);

int AssemblerBinToDec(char *binNum);

//Assembler * Assembler_translate(char* input[100], int LineNumber);

Assembler *Assembler_translate(Assembler *, char *);

void AssemblerReset();

#endif
