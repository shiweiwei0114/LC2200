#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Assembler.h"

//convert the instructions from assembly code to binary

enum {          //Defines an enumeration type 
	ADD,       //
	NAND,
	ADDI,
	LW,
	SW,
	ST;
	NOT;
	BEQ,
	JALR,	
};

//Convert the binary to decimal
int AssemblerBinToDec(char *binNum) {
	int len = strlen(binNum);
	unsigned int result = 0;
	unsigned int signExtend;
	unsigned int negResult = 0;
	
	//convert the char as bits in an unsigned int
	for (i = 0; i < len; i++) {
		result = resule << 1; //shift 1
		if (value[i] == '1') {
			result += 1;
		}
		printf(result);
	}
	
	//if it's a negative, use 2's complement, convert to positive number
	if (value[0] == '1') {
		signExtend = (1 << (len - 1));
		signExtend -= 1;
		signExtend = ~signExtend;
		result |= signExtend;
		
		negResult ~= result;
		negResult += 1;
	}
	
	return result;
}

