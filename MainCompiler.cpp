#include <stdio.h>
#include "Processor.h"
#include "HeadOneg.h"
#include "Compiler.h"
#include <stdlib.h>

//почему целая куча переводов строки в консоли??
int main(int argc, char *argv[]) {

	CheckNullPtr(argv[1], "No instruction file!\n", NULL_PTR_ERROR);

	char *ASM_FILE = argv[1];

	FILE *asmFile = fopen(ASM_FILE, "rb");
	CheckNullPtr(asmFile, "Can't open file!\n", NULL_PTR_ERROR);

	MyString *index  = nullptr;											
	char     *buffer = nullptr;	

	ReadFromFile(&buffer, ASM_FILE);
	CheckNullPtr(buffer, "Buffer is undefined!\n", NULL_PTR_ERROR);

	int numberOfStrings = DecomposeToIndex(&index, &buffer);
	CheckNullPtr(index, "Index is undefined!\n", NULL_PTR_ERROR);

	int instructionPtr = 0;
	int typeOfCommand  = 0;
 
 	char *code = (char *)calloc(3 * numberOfStrings + 1, sizeof(char)); 

	int statusDecomposeToCodeArray = DecomposeToCodeArray(index, code, numberOfStrings, &instructionPtr, &typeOfCommand);
	CheckNull(statusDecomposeToCodeArray, "Failed to decompose into code array\n", NULL_PTR_ERROR);

	int statusPrintToCodeFile = PrintToCodeFile(code, instructionPtr);
	CheckNull(statusPrintToCodeFile, "Failed to print the code array into fail\n", NULL_PTR_ERROR);

	free(code);
	free(index);
	free(buffer);
	fclose(asmFile);

	return 0;

}

