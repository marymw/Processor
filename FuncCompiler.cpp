#include "Processor.h"
#include "HeadOneg.h"
#include "Compiler.h"

int DefineCommand(char *command, int *selectorPtr){

	if (IsEqualCommand(command, HLT)){
		*selectorPtr = CMD_HLT;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, PUSH)){
		*selectorPtr = CMD_PUSH;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, POP)){
		*selectorPtr = CMD_POP;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, ADD)){
		*selectorPtr = CMD_ADD;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, SUB)){
		*selectorPtr = CMD_SUB;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, MULT)){
		*selectorPtr = CMD_MULT;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, DIV)){
		*selectorPtr = CMD_DIV;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, OUT)){
		*selectorPtr = CMD_OUT;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, VER)){
		*selectorPtr = CMD_VER;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, DMP)){
		*selectorPtr = CMD_DMP;
		return NO_ERRORS;
	}
	else{
		printf("Неверная команда\n");
	}
	*selectorPtr = -1;
	return NO_ERRORS;
}


int IsEqualCommand (const char *firstCommand, const char *secondCommand){
	int i = 0;
	for (i = 0; firstCommand[i] != '\0' && secondCommand[i] != '\0'; i++){
		if(firstCommand[i] != secondCommand[i]){
			return 0;
		}
	}

	if (firstCommand[i] == '\0' && secondCommand[i] == '\0'){
		return 1;
	}

	return 0;
}

int DecomposeToCodeArray(MyString *indexPtr, char *codePtr, int numberOfStrings, int *instructionPtr) {
	
	assert(indexPtr);
	
	char command[LEN_OF_COMMAND] = {};
	int param = 0;
	int selector = -1;

	for (int count = 0; count < numberOfStrings; count++){

		int statusOfScanf = sscanf(indexPtr[count].PtrOnStartOfString, "%s %d", command, &param);
		//printf("параметр %d\n", param);
		//printf("команда %s\n", command);
		assert(statusOfScanf != 0);
		
		if (statusOfScanf == 1){
			int statusOfDefineCommand = DefineCommand(command, &selector);
		
			if (statusOfDefineCommand != 0){
				printf("Ошибка определения команды!Вы ввели неверную команду!\n");
			return -1;
			}
		
			codePtr[(*instructionPtr)++] = selector;
		}

		else if (statusOfScanf == 2) {
			int statusOfDefineCommand = DefineCommand(command, &selector);
		
			if (statusOfDefineCommand != 0){
				printf("Ошибка определения команды!Вы ввели неверную команду!\n");
			return -1;
			}
		
			codePtr[(*instructionPtr)++] = selector;
			*((int *)(&codePtr[(*instructionPtr)])) = param;
			// int ip = *instructionPtr;
			// int *p = (int *)codePtr + ip;
			// *p = param;
			(*instructionPtr)+=4;
		}

		else {
			return -1;
		}
		
	}

	return 0;
}

int PrintToCodeFile(char *codePtr, int instructionPtr){
	FILE *codeFile = fopen("codeBin.bin", "wb");
		fwrite(codePtr, sizeof(char), instructionPtr, codeFile);
	fclose(codeFile);
	return 0;
}
