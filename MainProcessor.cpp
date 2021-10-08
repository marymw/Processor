#include <stdio.h>
#include "Processor.h"
#include "Lifo.h"
#include <stdlib.h>




int main(int argc, char *argv[]){

	Stack MyStack = {};
	StackCtor(&MyStack, 10);


	//char *INPUT_FILE = argv[1];

	//FILE *inputFile = fopen(INPUT_FILE, "r");

	char command[LEN_OF_COMMAND] = {};
	double param = 0;
	int typeOfCommand = 0;

	//char  *command = (char *)calloc(LEN_OF_COMMAND, sizeof(char));

	int selector = 1;

	do {
		int statusOfGetCommand = GetCommand(command, &param, &typeOfCommand);

		if (statusOfGetCommand != 0){
			printf("Ошибка введения команды!\n");
			return -1;
		}

		int statusOfDefineCommand = DefineCommand(command, &selector);

		if (statusOfDefineCommand != 0){
			printf("Ошибка определения команды!Вы ввели неверную команду!\n");
			return -1;
		}

		printf("command selector is %d\n", selector);
		printf("type of command is %d\n", typeOfCommand);

		int statusOfDoCommand = DoCommand(&MyStack, selector, typeOfCommand, param);
		if (statusOfDoCommand != 0){
			printf("Ошибка выполнения команды!\n");
			return -1;
		}

		//printf("%s\n", command);

	}while (selector != 1);
	printf("Я устал, я мухожук... \n");//
	//}
	

	//fclose(inputFile);
	StackDtor(&MyStack);

	return 0;
}
