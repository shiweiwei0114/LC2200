/*
 * Memory.h
 *
 *  Created on: Feb 21, 2016
 *      Author: trung
 */

#ifndef MEMORY_H_
#define MEMORY_H_

#define CAPACITY 10000
#define WORD_SIZE 32

struct memory {
	int memory[CAPACITY][WORD_SIZE];

};

typedef struct memory Memory;


#endif /* MEMORY_H_ */
