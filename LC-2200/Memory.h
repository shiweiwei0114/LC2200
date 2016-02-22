/*
 * Memory.h
 *
 *  Created on: Feb 21, 2016
 *      Author: trung
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#define CAPACITY 10000
#define WORD_SIZE 16

struct memory {
	int[CAPACITY][WORD_SIZE];
	int DrMem;
	int MemRead;
	int MemWrite;
};

typedef struct memory Memory;


#endif /* MEMORY_H_ */
