#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "Assembler.h"

//convert the instructions from assembly code to binary

Assembler *Assembler_constructor() {
	Assembler * as = malloc(sizeof(Assembler));

	return as;
}
Assembler *Assembler_translate(Assembler *as, char *input) {

	return as;
}



//Convert the binary to decimal
int AssemblerBinToDec(char *binNum) {
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
		printf(result);
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

