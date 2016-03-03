/*
 * Memory.c
 *
 *  Created on: Feb 25, 2016
 *      Author: trung
 */
#include <stdlib.h>
#include <string.h>
#include "Memory.h"

Memory * Memory_constructor() {
	Memory *mem = malloc(sizeof(Memory));
	memset(mem->memory, 0, 10000 * 32);
	return mem;
}
