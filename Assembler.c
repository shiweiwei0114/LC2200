#include <stdio.h>
#include <string.h>
//#include <ctype.h>
#include <stdlib.h>
#include "Assembler.h"

//convert the instructions from assembly code to binary

Assembler *Assembler_constructor() {
	Assembler * as = malloc(sizeof(Assembler));
	as->numOfInstruction = 0;
	return as;
}

char* assemblyToOpcode(char *string){
	if (strcasecmp(string, "add") == 0) {
		return "0000";
	} else if (strcasecmp(string, "nand") == 0) {
		return "0001";
	}else if (strcasecmp(string, "addi") == 0) {
		return "0010";
	}else if (strcasecmp(string, "lw") == 0) {
		return "0011";
	}else if (strcasecmp(string, "sw") == 0) {
		return "0100";
	}else if (strcasecmp(string, "st") == 0) {
		return "0101";
	}else if (strcasecmp(string, "not") == 0) {
		return "0110";
	}else if (strcasecmp(string, "beq") == 0) {
		return "0111";
	} else if (strcasecmp(string, "jalr") == 0) {
		return "1000";
	}
	return NULL;
}
char *numberToBinary(char *tok){
	//printf("Number: ");
	int number;
	char *result = (char *) calloc(WORD_SIZE, sizeof(char));
	sscanf(tok, "%d", &number);
	//printf("%d\n", number);

	int powerOf2 = 1;
	while (powerOf2 * 2 < number) {
		powerOf2 = powerOf2 * 2;
	}
	while (powerOf2 != 0) {
		if (number - powerOf2 >= 0) {
			strcat(result, "1");
			number -= powerOf2;
		}
		else if (number - powerOf2 < 0) {
			strcat(result, "0");
		}
		powerOf2 /= 2;
	}
	int needBits = 20 - strlen(result);
	char *bits = (char *) calloc(20, sizeof(char));
	int j = 0;
	char *p = bits;
	while (p != NULL && j < needBits) {
		*p = '0';
		p++; j++;
	}
	//printf("Bits: %s\n", bits);
	strcat(bits, result);
	//printf("Binary: %s\n", bits);
	return bits;
}
char * assemblyToRegister(char *tok) {
	if (strcasecmp(tok, "$zero") == 0) {
		return "0000";
	} else if (strcasecmp(tok, "$a0") == 0) {
		return "0011";
	}else if (strcasecmp(tok, "$a1") == 0) {
		return "0100";
	}else if (strcasecmp(tok, "$a2") == 0) {
		return "0101";
	}else if (strcasecmp(tok, "$t0") == 0) {
		return "0110";
	}else if (strcasecmp(tok, "$t1") == 0) {
		return "0111";
	}else if (strcasecmp(tok, "$t2") == 0) {
		return "1000";
	}else if (strcasecmp(tok, "$s0") == 0) {
		return "1001";
	}else if (strcasecmp(tok, "$s1") == 0) {
		return "1010";
	}else if (strcasecmp(tok, "$s2") == 0) {
		return "1100";
	}
//		char $zero[32]; //0000
//			char $a0[32];	//0011
//			char $a1[32];	//0100
//			char $a2[32];	//0101
//			char $t0[32];	//0110
//			char $t1[32];	//0111
//			char $t2[32];	//1000
//			char $s0[32];	//1001
//			char $s1[32];	//1010
//			char $s2[32];	//1100
	return NULL;
}

FILE * printObjectCode(char *buffer) {
	char *output = "main.o";
	FILE *outputFile = fopen(output, "w");
	fprintf(outputFile, "%s\n", buffer);
	return outputFile;
}
int Assembler_getNumInstructions(Assembler *as) {
	return as->numOfInstruction;
}

Assembler *Assembler_translate(Assembler *as, FILE * inputFile, char *input) {
	printf("Translating to binary...\n");
	size_t nbytes = 100;
	char *line = (char *)malloc(nbytes+1);
	int count = 0;
	char *buffer = (char *) malloc(nbytes * 100000);
	while (fgets(line, nbytes+1, inputFile)) {
		char * binaryLine = (char*)calloc(nbytes+1,sizeof(char));
		if (line[0] != ';'&& line[0] != '\r') {
			//printf("%i: %s", i++, line);
			char* tok = (char*) calloc(10, sizeof(char));
			tok = strtok(line, " \t,\n()");					//space, tab, comma, newline, and parentheses are delimiter
			while (tok != NULL) {
				//printf("Token: %s\n", tok);
				if (strcasecmp(tok, ".orig") == 0) {
					tok = strtok(NULL," \t,\n()");
					if (tok != NULL) {
						int orig;
						as->orig = sscanf(tok, "%d", &orig);
						as->orig = orig;
						printf("Start of program at address: %d\n", as->orig);
						break;
					}
				} else {
					if (tok[0] == ';' || strcasecmp(tok, ".end\r") == 0) {
						//printf("Comment: %s\n", tok);
						break;
					} else {
						if (tok[0] == '$') {
							strcat(binaryLine, assemblyToRegister(tok));
							//strcat(binaryLine, "|");
						} else if (tok[0] >= 48 && tok[0] <= 57) {		//token is a number
							strcat(binaryLine, numberToBinary(tok));
							//strcat(binaryLine, "|");
						} else if ((tok[0] >= 65 && tok[0] <= 90) || (tok[0] >= 97 && tok[0] <= 122)) {		//token is a word
							strcat(binaryLine, assemblyToOpcode(tok));
							//strcat(binaryLine, "|");
						} else {
							//printf("Token: %s\n", tok);
							printf("Unidentifiable syntax.\n");
						}
					}
					tok = strtok(NULL," \t,\n()");
				}
			}
			if (binaryLine[0] != '\0') {
				//printf("Binary: %s\n", binaryLine);
				count++;
				strcat(buffer, binaryLine);
				strcat(buffer, "\n");

			}
		}
	}
	as->numOfInstruction = count;
	printf("%s", buffer);
	printf("Number of instructions read: %d\n", as->numOfInstruction);
	as->outputFile = printObjectCode(buffer);

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
		printf("%d\n", result);
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

