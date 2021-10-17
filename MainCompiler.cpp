#include "Compiler.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

	char *ASM_FILE = argv[1];

	FILE *asmFile = fopen(ASM_FILE, "rb");

	char *code = (char *)calloc(100, sizeof(char));

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
	free(code);
	
	free(index);
	free(buffer);

	fclose(asmFile);
	return 0;

}


