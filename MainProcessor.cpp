#include <stdio.h>
#include "Processor.h"
#include "Lifo.h"
#include <stdlib.h>
#include "HeadOneg.h"

int main(int argc, char *argv[]){

	Stack MyStack = {};

	StackCtor(&MyStack, 10);

	char *CODE_FILE = argv[1];

	FILE *codeFile = fopen(CODE_FILE, "rb");

	char *code = (char *)calloc(100, sizeof(int));
	

	int sizeOfFile = GetSizeOfFile(codeFile);
	
	fread(code, sizeof(char), sizeOfFile, codeFile);
	int statusOfDoCommand = DoCommand(&MyStack, code, sizeOfFile);
	if (statusOfDoCommand != 0){
		printf("Ошибка выполнения команды!\n");
		return -1;
	}

	printf("Я устал, я мухожук... \n");
	free(code);
	fclose(codeFile);
	StackDtor(&MyStack);

	return 0;
}
