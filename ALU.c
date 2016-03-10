#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ALU.h"

ALU *ALU_constructor(Reg *regs) {
	ALU *alu = malloc(sizeof(ALU));
	alu->regs = regs;
	alu->A = calloc(32 + 1, sizeof(char));
	alu->B = calloc(32 + 1, sizeof(char));
	alu->dest = calloc(32 + 1, sizeof(char));
	alu->result = calloc(32 + 1, sizeof(char));

	return alu;
}
//Convert the binary to decimal
int binToDec(char *binNum) {
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
char * Nand(char *a, char *b) {
	int i;
	char *result = malloc(1000);

	for (i = 0; i < strlen(a); i++) {
		if (a[i] == '1' && b[i] == '1') {
			strcat(result, "0");
		} else {
			strcat(result, "1");
		}
	}

	return result;
}

//int Add(char *regX, char *regY, char *regZ) {
//	long int result1;
//	long int result2;
//	long int sum;
//
//	result1 = strtol(regY, NULL, 2);
//	result2 = strtol(regZ, NULL, 2);
//
//	sum = result1 + result2;
//
//	long int finalResult = decimalToBinary(sum);
//	printf("\t\t%s = %ld", regX, finalResult);
//	return finalResult;
//}

/*
 * Code from website: http://www.programmingsimplified.com/c/source-code/c-program-convert-decimal-to-binary
 */
char *decToBinary(int n) {

	int c, d, count;
	char *pointer;

	count = 0;
	pointer = (char*) malloc(32 + 1);

	if (pointer == NULL)
		exit(EXIT_FAILURE);

	for (c = 31; c >= 0; c--) {
		d = n >> c;

		if (d & 1)
			*(pointer + count) = 1 + '0';
		else
			*(pointer + count) = 0 + '0';

		count++;
	}
	*(pointer + count) = '\0';

	return pointer;
}
char * ALU_add(ALU *alu) {
	int a = binToDec(alu->A);
	int b = binToDec(alu->B);
	int c = a + b;
	//printf("A: %d, B: %d, Result: %d\n", a, b, c);
	return decToBinary(c);
}
int Addi(char *b, int immVal, char *regX) {
	long int result1;
	long int result2;
	long int sum;

	result1 = strtol(b, NULL, 2);
	sum = result1 + immVal;

	printf("\t\t%s = %ld", regX, sum);
	return sum;
}

int ALU_execute(ALU *alu, Reg *regs) {
	switch (alu->inType) {
	case ADD: {
		alu->result = ALU_add(alu);
		Register_store(alu->regs, alu->dest, alu->result);

		break;
	}
	case NAND: {
		break;
	}
	default: {
		break;
	}
	}

	return 0;
}
