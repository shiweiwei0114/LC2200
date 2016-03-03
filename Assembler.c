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
Assembler *Assembler_translate(Assembler *as, FILE * inputFile, char *input) {
	printf("Translating to binary...\n");
	unsigned int nbytes = 100;
	char *line = (char *)malloc(nbytes+1);
	int i = 1;
	while (getline(&line, &nbytes, inputFile) > -1) {
		if (line[0] != ';'&& line[0] != '\r') {
			printf("%i: %s", i++, line);
			char *tok = strtok(line, " ");
			while (tok != NULL) {
				if (strcmp(&tok[0],";")) {
					printf("|%s", tok);
					tok = strtok(NULL," ");
				}
			}
		}
	}



//getline();
//	char *p = input;
//
//	char *tok = strtok(input,"\n");
//	int i = 1;
//	while (tok != NULL) {
//
//			if (tok[0] != ';') {	//Ignore comment line beginning with ';'
//						printf("%d: %s\n", i++, tok);
//					}
//					tok = strtok(NULL, "\n");
//
//
//	}

//	while(fgets(buff, 20, fp)) {
//		tok = strtok(buff, " ");
//		printf("%s\n", tok );
//		printf("%s\n", opcode[i] );
//		tok = strtok(NULL, ",");
//		printf("%s\n", tok );
//		tok = strtok(NULL, ",");
//		printf("%s\n", tok );
//		tok = strtok(NULL, ",");
//		printf("%s\n", tok ); i++;
//	}

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

