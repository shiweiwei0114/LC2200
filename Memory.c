/*
 * Memory.c
 *
 *  Created on: Feb 25, 2016
 *      Author: trung
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Memory.h"

Memory * Memory_constructor() {
	Memory *mem = (Memory *) malloc(sizeof(Memory));
	return mem;
}

void Memory_store(Memory * mem, int address, char *data) {
	sscanf(data, "%s", mem->memory[address]);


}
