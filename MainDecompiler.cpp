#include <stdio.h>
#include "Processor.h"
#include "HeadOneg.h"
//#include "Decompiler.h"
#include <stdlib.h>

int DecomposeToAsmBuffer(int* code, int sizeOfFile, FILE *decodeFile);

int main(int argc, char *argv[]) {

	char *CODE_FILE = argv[1];

	FILE *codeFile = fopen(CODE_FILE, "rb");
	FILE *decodeFile = fopen("decodeFile.txt", "w");

	int *code = (int *)calloc(100, sizeof(int));

	int sizeOfFile = GetSizeOfFile(codeFile);

	fread(code, sizeof(int), sizeOfFile, codeFile);

	
	DecomposeToAsmBuffer(code, sizeOfFile, decodeFile);

	
	free(code);

	
	fclose(decodeFile);
	fclose(codeFile);

	return 0;

}

