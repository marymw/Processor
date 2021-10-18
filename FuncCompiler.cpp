#include "Processor.h"
#include "HeadOneg.h"
#include "Compiler.h"
#include <string.h>


static int DefineCommand  (char *command, int *selectorPtr, int typeOfCommand);
static int IsEqualCommand (const char *firstCommand, const char *secondCommand, const int lenOfCommand);


static int DefineCommand(char *command, int *selectorPtr, int typeOfCommand) {

	if (IsEqualCommand(command, HLT, LEN_OF_CMD_HLT + 1)){
		*selectorPtr = CMD_HLT;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, PUSH, LEN_OF_CMD_PUSH + 1)){
		if (typeOfCommand != 2){
			printf("Выйди и запушь нормально!\n");
			return LACK_OF_ARGUMENTS;
		}
		*selectorPtr = CMD_PUSH;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, POP, LEN_OF_CMD_POP + 1)){
		*selectorPtr = CMD_POP;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, ADD, LEN_OF_CMD_ADD + 1)){
		*selectorPtr = CMD_ADD;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, SUB, LEN_OF_CMD_SUB + 1)){
		*selectorPtr = CMD_SUB;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, MUL, LEN_OF_CMD_MUL + 1)){
		*selectorPtr = CMD_MUL;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, DIV, LEN_OF_CMD_DIV + 1)){
		*selectorPtr = CMD_DIV;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, OUT, LEN_OF_CMD_OUT + 1)){
		*selectorPtr = CMD_OUT;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, VER, LEN_OF_CMD_VER + 1)){
		*selectorPtr = CMD_VER;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, DMP, LEN_OF_CMD_DMP + 1)){
		*selectorPtr = CMD_DMP;
		return NO_ERRORS;
	}
	else{
		printf("Неверная команда\n");
		return UNRECOGNIZED_COMMAND;
	}

}


static int IsEqualCommand (const char *firstCommand, const char *secondCommand, const int lenOfCommand) { 

	return !strncmp(firstCommand, secondCommand, lenOfCommand);

}


int DecomposeToCodeArray(MyString *indexPtr, char *codePtr, const int numberOfStrings, int *instructionPtr, int *typeOfCommand) {
	
	CheckNullPtr(indexPtr, "Index is undefined!\n", NULL_PTR_ERROR);
	
	char command[LEN_OF_COMMAND] = {};
	int param = 0;
	int selector = -1;

	for (int count = 0; count < numberOfStrings; count++){

		int statusOfScanf = sscanf(indexPtr[count].PtrOnStartOfString, "%s %d", command, &param);
		CheckNoNull(statusOfScanf, "Read error\n", READ_ERROR);
		
		if (statusOfScanf == 1){

			*typeOfCommand = 1;

			int statusOfDefineCommand = DefineCommand(command, &selector, *typeOfCommand);
			CheckNull(statusOfDefineCommand, "Ошибка определения команды!Вы ввели неверную команду!\n", UNRECOGNIZED_COMMAND);

			codePtr[(*instructionPtr)++] = selector;

		}
		else if (statusOfScanf == 2) {

			*typeOfCommand = 2;

			int statusOfDefineCommand = DefineCommand(command, &selector, *typeOfCommand);
			CheckNull(statusOfDefineCommand, "Ошибка определения команды!Вы ввели неверную команду!\n", UNRECOGNIZED_COMMAND);
		
			codePtr[(*instructionPtr)++] = selector;
			*((int *)(&codePtr[(*instructionPtr)])) = param; 
			
			(*instructionPtr) += 4;

		}
		else {
			return UNRECOGNIZED_COMMAND;
		}
		
	}

	return NO_ERRORS;
}

int PrintToCodeFile(const char *codePtr, const int instructionPtr) {

	FILE *codeFile = fopen("codeBin.bin", "wb");
	CheckNullPtr(codeFile, "Can't open file!\n", NULL_PTR_ERROR);

	int statusOfFwrite = fwrite(codePtr, sizeof(char), instructionPtr, codeFile);
	CheckEqual(statusOfFwrite, instructionPtr, "Не все символы записаны в файл\n", WRITE_ERROR);

	int statusOfFclose = fclose(codeFile);
	CheckNull(statusOfFclose, "Can't close file\n", CLOSE_ERROR);

	return NO_ERRORS;
}

/*
int GetSizeOfCodeArrFromBuffer(char *buffer){

	char *someString = strtok(buffer, " \n");

	int sizeOfCodeArrFromBuffer = 1;

	while (someString != NULL){
		sizeOfCodeArrFromBuffer++;
		*someString = strtok(NULL, " \n");
	}

	return sizeOfCodeArrFromBuffer;

}
*/
