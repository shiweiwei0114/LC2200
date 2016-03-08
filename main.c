#include <stdio.h>
#include <stdlib.h>             /* strtol() */
#include <string.h>             /* strtok() */
#include <assert.h>

#include "Assembler.h"
#include "ALU.h"
#include "Memory.h"
#include "Registers.h"
#include "FSM.h"

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
    char fileName[50] = {0};
	//char option;
	char    *buffer;
	long    numbytes;
	FILE *inputFile = NULL;
//	do {
//		printf("Enter the file name:\n");
//		scanf("%s", fileName);
//		inputFile = fopen(fileName, "r");
//	} while (inputFile == NULL);
	inputFile = fopen("test.txt", "r");

	/* Get the number of bytes */
	fseek(inputFile, 0L, SEEK_END);
	numbytes = ftell(inputFile);

	/* reset the file position indicator to
	the beginning of the file */
	fseek(inputFile, 0L, SEEK_SET);

	/* grab sufficient memory for the
	buffer to hold the text */
	buffer = (char*)calloc(numbytes, sizeof(char));

	/* copy all the text into the buffer */
	fread(buffer, sizeof(char), numbytes, inputFile);
//	if (fclose(inputFile) == 0) {
//		printf("File was closed successfully\n");
//	}

	/* confirm we have read the file by
	outputing it to the console */
	printf("File is read as:\n");
	printf("%s\n", buffer);

	FSM *stateMachine = FSM_constructor();

	if (stateMachine == NULL) {
		printf("State machine creation failed.\n");
	}
	Memory *mem = Memory_constructor();
	Assembler *as = Assembler_constructor();

	fseek(inputFile, 0L, SEEK_SET);
	as = Assembler_translate(as, inputFile, buffer);



	/* free the memory we used for the buffer */
	free(buffer);
	/**
	FILE *fp, *fp1;
	fp = fopen(fileName, "r");
	
	if (fp = NULL) {
		fprinf(stderr, "Could not find the file!\n");
		exit(1);
	}
	

	
	fp1 = fopen(fileName, "r");
	if (fp1 == NULL) {
		fprintf(stderr, "File doesn't exist.\n");
		exit(1);
	}

	
	printf("\nAssemble another code? Enter Y or N: \n");
	scanf(" %c", &option);
	
	while (option == 'Y'){

		//DisplayAssemblyCode(fp);
		fseek(fp, 0, SEEK_SET);

		printf("\nAssemble another code? Enter Y or N: \n");
		fseek(fp, 0, SEEK_SET);
		scanf(" %c", &option);
		if(option == 'N') {
			printf("\nExit the program");
			break;
		}

	}
	fclose(fp);
	fclose(fp1);
	**/
	return 0;

}



