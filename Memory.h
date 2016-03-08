/*
 *  Memory.h
 *
 *  Created on: Feb 21, 2016
 *  Author: trung, Weiwei 
 */

#ifndef MEMORY_H_
#define MEMORY_H_
#include <stdbool.h>

#define CAPACITY 10000
#define WORD_SIZE 32

struct memory {
	//int memory[CAPACITY][WORD_SIZE];
	char machineCode[WORD_SIZE];
	char assemblyCode[CAPACITY];
	int id;
};

typedef struct memory Memory;

//initialize the memory, it will help for the GUI display too
void Memory_initial(Memory mem[], int const Mem_size); 

char* Memory_fetch(Memory mem[], int index, bool isLast);
char* Memory_getValue(Memory mem[], int index);

void Memory_store(Memory mem[], int index, char* theMachineCode, char* theAssemblyCode,
		          int theId);
				  
void Memory_reset(Memory mem[], int const Mem_size);

#endif /* MEMORY_H_ */
