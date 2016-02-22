#ifndef ALU_H
#define ALU_H

struct ALU {
	int DrALU;
	char *A;
	char *B;
};

typedef struct ALU ALU;

char * Nand(char *a, char *b);
int Add(char *regX, char *regY, char *regZ);
int Addi(char *b, int immVal, char *regX);

#endif
