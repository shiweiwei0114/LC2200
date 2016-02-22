#ifndef REGISTER_H
#define REGISTER_H
#define ZERO 0

typedef struct Registers {
	char $zero[32];
	char $at[32];
	char $v0[32];
	char $a0[32];
	char $a1[32];
	char $a2[32];
	char $t0[32];
	char $t1[32];
	char $t2[32];
	char $s0[32];
	char $s1[32];
	char $s2[32];
	char $k0[32];
	char $sp[32];
	char $fp[32];
	char $ra[32];
};

typedef struct Registers Reg;

void RegisterInit(Reg *regs);
char* RegisterGetvalue(Reg *regs, char* bit);
void RegisterStore(Reg *regs, char *bit, char *data);
void RegisterReset(Reg *regs);

#endif
