#include <stdio.h>
#include "Processor.h"
#include "HeadOneg.h"
#include "Compiler.h"

int main(int argc, char *argv[]) {

	char *ASM_FILE = argv[1];

	FILE *asmFile = fopen(ASM_FILE, "r");

	int *code = (int *)calloc(MAX_LEN_OF_CODE_ARRAY, sizeof(int));

	MyString *index  = nullptr;											
	char     *buffer = nullptr;	

	ReadFromFile(&buffer, ASM_FILE);
	assert(buffer);

	int numberOfStrings = DecomposeToIndex(&index, &buffer);

	int instructionPtr = 0;
	
	int statusDecomposeToCodeArray = DecomposeToCodeArray(index, code, numberOfStrings, &instructionPtr);
	assert(statusDecomposeToCodeArray == 0);

	int statusPrintToCodeFile = PrintToCodeFile(code, instructionPtr);
	assert(statusPrintToCodeFile == 0);

	fclose(asmFile);
	return 0;

}

