#ifndef ALU_H
#define ALU_H

struct ALU {
	char *A;
	char *B;
	char *dest;
};

typedef struct ALU ALU;

ALU *ALU_constructor();

char * Nand(char *a, char *b);
int Add(char *regX, char *regY, char *regZ);
int Addi(char *b, int immVal, char *regX);

#endif
