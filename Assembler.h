#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <stdbool.h>

struct instruction {
	int orig;
	bool origExsit;
	char machineLine[100][34];
	int endIndex;
};

typedef struct instruction Instruction;

int AssemblerBinToDec(char *binNum);

Instruction * AssemblerTranslate(char* input[100], int LineNumber);

void AssemblerReset();

#endif
