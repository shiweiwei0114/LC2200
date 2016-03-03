#include <stdio.h>
#include <string.h>
#include "Registers.h"

void Register_initialize(Reg *regs) {
	char *zeros = "00000000000000000000000000000000";
	memcpy(regs->$zero, zeros, 32);
	memcpy(regs->$a0, zeros, 32);
	memcpy(regs->$a1, zeros, 32);
	memcpy(regs->$a2, zeros, 32);
	memcpy(regs->$t0, zeros, 32);
	memcpy(regs->$t1, zeros, 32);
	memcpy(regs->$t2, zeros, 32);
	memcpy(regs->$s0, zeros, 32);
	memcpy(regs->$s1, zeros, 32);
	memcpy(regs->$s2, zeros, 32);
}
char* Register_getValue(Reg *regs, char* bit) {

	if (strcmp(bit, "0000") == 0) { // Reg $a0
		return regs->$zero;
	} else if (strcmp(bit, "0011") == 0) { // Reg $a0
		return regs->$a0;
	} else if (strcmp(bit, "0100") == 0) { // Reg $a1
		return regs->$a1;
	} else if (strcmp(bit, "0101") == 0) { // Reg $a2
		return regs->$a2;
	} else if (strcmp(bit, "0110") == 0) { // Reg $t0
		return regs->$t0;
	} else if (strcmp(bit, "0111") == 0) { // Reg $t1
		return regs->$t1;
	} else if (strcmp(bit, "1000") == 0) { // Reg $t2
		return regs->$t2;
	} else if (strcmp(bit, "1001") == 0) { // Reg $s0
		return regs->$s0;
	} else if (strcmp(bit, "1010") == 0) { // Reg $s1
		return regs->$s1;
	} else if (strcmp(bit, "1011") == 0) { // Reg $s2
		return regs->$s2;
	} else {
		printf("RegisterGetvalue Wrong\n");
		return NULL;
	}
}
void Register_store(Reg *regs, char *bit, char *data) {
	if (strcmp(bit, "0011") == 0) { // Reg $a0
		memcpy(regs->$a0, data, 32);
	} else if (strcmp(bit, "0100") == 0) { // Reg $a1
		memcpy(regs->$a1, data, 32);
	} else if (strcmp(bit, "0101") == 0) { // Reg $a2
		memcpy(regs->$a2, data, 32);
	} else if (strcmp(bit, "0110") == 0) { // Reg $t0
		memcpy(regs->$t0, data, 32);
	} else if (strcmp(bit, "0111") == 0) { // Reg $t1
		memcpy(regs->$t1, data, 32);
	} else if (strcmp(bit, "1000") == 0) { // Reg $t2
		memcpy(regs->$t2, data, 32);
	} else if (strcmp(bit, "1001") == 0) { // Reg $s0
		memcpy(regs->$s0, data, 32);
	} else if (strcmp(bit, "1010") == 0) { // Reg $s1
		memcpy(regs->$s1, data, 32);
	} else if (strcmp(bit, "1011") == 0) { // Reg $s2
		memcpy(regs->$s2, data, 32);
	} else {
		printf("RegisterStore Wrong!\n");
	}
}

void RegisterReset(Reg *regs) {
	Register_initialize(regs);
}
