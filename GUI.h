/*
 * GUI.h
 *
 *  Created on: March 2, 2016
 *  Author: Weiwei Shi
 */
#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include "Memory.h"
#include "Register.h"

enum {
	PREVIOUS,
	NEXT
};

//constructor
void GUI_Main(int argc, char *argv[]);

//for displaying registers
//void GUI_Register(Register Regs);

//for displaying memory
//void GUI_Memory(Memory Mem[], int const MemorySize, bool isBegin);

