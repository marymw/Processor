#include <stdio.h>
#include "Processor.h"
#include "HeadOneg.h"
#include "Decompiler.h"
#include <stdlib.h>

 
int main(int argc, char *argv[]) {

	CheckNullPtr(argv[1], "No code file!\n", NULL_PTR_ERROR);
	char *CODE_FILE = argv[1];

	FILE *codeFile = fopen(CODE_FILE, "rb");
	CheckNullPtr(codeFile, "Can't open file!\n", NULL_PTR_ERROR);

	FILE *decodeFile = fopen("decodeFile.txt", "w");
	CheckNullPtr(decodeFile, "Can't open file!\n", NULL_PTR_ERROR);

	int sizeOfFile = GetSizeOfFile(codeFile);

	char *code = (char *)calloc(sizeOfFile + 1, sizeof(char));

	int statusOfFread = fread(code, sizeof(char), sizeOfFile, codeFile);//ошибки
	CheckEqual(statusOfFread, sizeOfFile, "Не все символы прочитаны\n", WRITE_ERROR);
	
	int statusOfDecomposeToAsmBuffer = DecomposeToAsmBuffer(code, sizeOfFile, decodeFile);
	CheckNull(statusOfDecomposeToAsmBuffer, "Command recognition error\n", UNRECOGNIZED_COMMAND);
	
	free(code);
	fclose(decodeFile);
	fclose(codeFile);

	return 0;

}

