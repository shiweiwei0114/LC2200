/*
 *  Memory.c
 *
 *  Created on: Feb 25, 2016
 *  Author: trung, Weiwei
 */
#include <stdlib.h>
#include <string.h>
#include "Memory.h"
/*
Memory * Memory_constructor() {
	Memory *mem = malloc(sizeof(Memory));
	memset(mem->memory, 0, 10000 * 32);
	return mem;
}
*/
void Memory_initial(Memory mem[], int const Mem_size) {
	int index;
	for (index = 0; index < Mem_size; index++){
		strcpy(mem[index].machineCode,"00000000000000000000000000000000");
		strcpy(mem[index].assemblyCode, "NOP"); 
		mem[index].id = 0;
	}
}

char* Memory_fetch(Memory mem[], int index, bool isLast) {
	mem[index].id = 3;
	if(!isLast){
		mem[index + 1].id = 2;
	}
	return mem[index].machineCode;
}

char* Memory_getValue(Memory mem[], int index) {
	return mem[index].machineCode;
}

void Memory_store(Memory mem[], int index, char* theMachineCode, char* theAssemblyCode, int theId) {
	strcpy(mem[index].machineCode, theMachineCode);
	strcpy(mem[index].assemblyCode, theAssemblyCode); 
	mem[index].id = theId;

}

void Memory_reset(Memory mem[], int const Mem_size) {
	Memory_initial(mem, Mem_size);
}			  


