#include <stdio.h>
#include <stdlib.h>             /* strtol() */
#include <string.h>             /* strtok() */
#include <assert.h>



int main(void) {
	
	
	
    char fileName[50];
	//char option;
	char    *buffer;
	long    numbytes;
	
	printf("Enter the file name: ");
	scanf("%s", fileName);
	FILE *inputFile = fopen(fileName, "r");
	
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
	fclose(inputFile);

	/* confirm we have read the file by
	outputing it to the console */
	printf("\n%s", buffer);

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



