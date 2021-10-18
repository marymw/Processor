#include <stdio.h>
#include "Processor.h"
#include "Lifo.h"
#include <stdlib.h>
#include "HeadOneg.h"

int main(int argc, char *argv[]){

	struct Processor MyProcessor = {};

	StackCtor(&(MyProcessor.stackOfProc), 10);

	CheckNullPtr(argv[1], "No instruction file!\n", NULL_PTR_ERROR);
	char *CODE_FILE = argv[1];

	FILE *codeFile = fopen(CODE_FILE, "rb");
	CheckNullPtr(codeFile, "Can't open file!\n", NULL_PTR_ERROR);

	int sizeOfFile = GetSizeOfFile(codeFile);

	MyProcessor.code = (char *)calloc(sizeOfFile + 1, sizeof(int));

	int statusOfFread = fread(MyProcessor.code, sizeof(char), sizeOfFile, codeFile);
	CheckEqual(statusOfFread, sizeOfFile, "Не все символы прочитаны\n", WRITE_ERROR);

	int statusOfDoCommand = ExecuteCommand(&MyProcessor, sizeOfFile);
	CheckNull(statusOfDoCommand, "Ошибка выполнения команды!\n", RUNTIME_ERROR);
	
	printf("Я устал, я мухожук... \n");

	free(MyProcessor.code);
	fclose(codeFile);
	StackDtor(&(MyProcessor.stackOfProc));
	
	return 0;
}
