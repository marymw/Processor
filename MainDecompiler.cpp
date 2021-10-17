#include <stdio.h>
#include "Processor.h"
#include "HeadOneg.h"
//#include "Decompiler.h"
#include <stdlib.h>

int DecomposeToAsmBuffer(char* code, int sizeOfFile, FILE *decodeFile);

int main(int argc, char *argv[]) {

	char *CODE_FILE = argv[1];

	FILE *codeFile = fopen(CODE_FILE, "rb");
	FILE *decodeFile = fopen("decodeFile.txt", "w");

	char *code = (char *)calloc(100, sizeof(char));

	int sizeOfFile = GetSizeOfFile(codeFile);

	fread(code, sizeof(char), sizeOfFile, codeFile);

	
	DecomposeToAsmBuffer(code, sizeOfFile, decodeFile);

	
	free(code);

	
	fclose(decodeFile);
	fclose(codeFile);

	return 0;

}



