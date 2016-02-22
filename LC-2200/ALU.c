//#include <stdio.h>
//#include "ALU.h"
//
//char * Nand(char *a, char *b) {
//	int i;
//	char *result = malloc(1000);
//
//	for (i = 0; i < strlen(a); i++) {
//		if (a[i] == '1' && b[i] == '1') {
//			strcat(result, "0");
//		} else {
//			strcat(result, "1");
//		}
//	}
//
//	return result;
//}
//
//int Add(char *regX, char *regY, char *regZ) {
//	long int result1;
//	long int result2;
//	long int sum;
//
//	result1 = strtol(regY, NULL, 2);
//	result2 = strtol(regZ, NULL, 2);
//
//	sum = result1 + result2;
//
//	long int finalResult = decimalToBinary(sum);
//	printf("\t\t%s = %ld", regX, finalResult);
//	return finalResult;
//}
//
//int Addi(char *b, int immVal, char *regX) {
//	long int result1;
//	long int result2;
//	long int sum;
//
//	result1 = strtol(b, NULL, 2);
//	sum = result1 + immVal;
//
//	printf("\t\t%s = %ld", regX, sum);
//	return sum;
//}
