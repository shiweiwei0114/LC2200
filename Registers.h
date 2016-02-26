#ifndef REGISTER_H
#define REGISTER_H
#define ZERO 0

typedef struct Registers {
	char $zero[32]; //0000
	char $a0[32];	//0011
	char $a1[32];	//0100
	char $a2[32];	//0101
	char $t0[32];	//0110
	char $t1[32];	//0111
	char $t2[32];	//1000
	char $s0[32];	//1001
	char $s1[32];	//1010
	char $s2[32];	//1100
}Reg;

void Register_initialize(Reg *regs);
char* Register_getValue(Reg *regs, char* bit);
void Register_store(Reg *regs, char *bit, char *data);
void Register_reset(Reg *regs);

#endif
