#include "Processor.h"
#include "HeadOneg.h"
#include "Compiler.h"
#include <string.h>


static int DefineCommand   (char *command, int *selectorPtr, char typeOfCommand);
static int IsEqualCommand  (const char *firstCommand, const char *secondCommand, const int lenOfCommand);
static int GetCommand      (char *string, int *param, char *command, char *typeOfCommand, int *reg);


static int DefineCommand(char *command, int *selectorPtr, char typeOfCommand) {

	if (IsEqualCommand(command, HLT, LEN_OF_CMD_HLT + 1)){
		CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_HLT;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, PUSH, LEN_OF_CMD_PUSH + 1)){
		CheckNoNull(typeOfCommand, "Выйди и запушь нормально!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_PUSH;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, POP, LEN_OF_CMD_POP + 1)){
		CheckEqual(typeOfCommand, REG_CONST, "Выйди и запопь нормально!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_POP;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, ADD, LEN_OF_CMD_ADD + 1)){
		CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_ADD;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, SUB, LEN_OF_CMD_SUB + 1)){
		CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_SUB;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, MUL, LEN_OF_CMD_MUL + 1)){
		CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_MUL;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, DIV, LEN_OF_CMD_DIV + 1)){
		CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_DIV;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, OUT, LEN_OF_CMD_OUT + 1)){
		CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_OUT;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, VER, LEN_OF_CMD_VER + 1)){
		CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_VER;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, DMP, LEN_OF_CMD_DMP + 1)){
		CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_DMP;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, IN, LEN_OF_CMD_IN + 1)){
		CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_IN;
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


int DecomposeToCodeArray(MyString *indexPtr, char *codePtr, const int numberOfStrings, int *instructionPtr, char *typeOfCommand) {

	CheckNullPtr(indexPtr, "Index is undefined!\n", NULL_PTR_ERROR);
	
	char command[LEN_OF_COMMAND] = {};
	int param = 0;
	int selector = -1;
	int reg = 0;
	printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
	printf("numberOfStrings = %d\n", numberOfStrings);

	for (int count = 0; count < numberOfStrings; count++){
		printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
		int statusOfGetCommand = GetCommand(indexPtr[count].PtrOnStartOfString, &param, command, typeOfCommand, &reg);
		printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);

		CheckNull(statusOfGetCommand, "Read error\n", READ_ERROR);
		printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);

		
		if (*typeOfCommand == 0){
			printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);

			int statusOfDefineCommand = DefineCommand(command, &selector, *typeOfCommand);
			CheckNull(statusOfDefineCommand, "Ошибка определения команды!Вы ввели неверную команду!\n", UNRECOGNIZED_COMMAND);
			codePtr[(*instructionPtr)++] = selector;

		}
		else if (*typeOfCommand != 0) {
			printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);

			int statusOfDefineCommand = DefineCommand(command, &selector, *typeOfCommand);
			CheckNull(statusOfDefineCommand, "Ошибка определения команды!Вы ввели неверную команду!\n", UNRECOGNIZED_COMMAND);
	
			codePtr[(*instructionPtr)++] = selector ^ (*typeOfCommand);

			if((*typeOfCommand) & IMM_CONST){
				*((int *)(&codePtr[(*instructionPtr)])) = param; 
				(*instructionPtr) += 4;
			}
			if((*typeOfCommand) & REG_CONST){
				int regSelector = reg - 96;//добавить константу

				codePtr[(*instructionPtr)++] = regSelector;
			}
			
		}
		else {
			printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);

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


static int GetCommand(char *string, int *param, char *command, char *typeOfCommand, int *reg){
	printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
 	CheckNullPtr(string, "нулевой указатель на строчку!!\n", NULL_PTR_ERROR);

	*typeOfCommand = 0;
	//char strForArg[10] = {};
	int ok1 = 0;
	int ok2 = 0;

	//int statusOfScanf1 = sscanf(string, "%s %s\n", command, strForArg);
	//CheckNoNull(statusOfScanf1, "Не удалось распознать команду\n", UNRECOGNIZED_COMMAND);

	//if (statusOfScanf1 == 1){
	//	return NO_ERRORS;
	//}

	//printf("command = %s, strForArg = %s", command, strForArg);

	sscanf(string, "%s %n[%d+%cx]%n",command, &ok1, param, reg, &ok2);

	if ((ok2 - ok1) != 6){

		sscanf(string, "%s %n%d+%cx%n", command, &ok1, param, reg, &ok2);
		printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);

		if((ok2 - ok1) != 4){
			sscanf(string, "%s %n[%d]%n", command, &ok1, param, &ok2);
			printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);

			if ((ok2 - ok1) != 3){
				sscanf(string, "%s %n%d%n", command, &ok1, param, &ok2);
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);

				if ((ok2 - ok1) != 1) {
					sscanf(string, "%s %n[%cx]%n", command, &ok1, reg, &ok2);
					printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);

					if ((ok2 - ok1) != 4) {
						sscanf(string, "%s %n%cx%n", command, &ok1, reg, &ok2);
						printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
						if ((ok2 - ok1) != 2) {
							printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
							int statusOfScanf1 = sscanf(string, "%s \n", command);
							CheckNoNull(statusOfScanf1, "Не удалось распознать команду\n", UNRECOGNIZED_COMMAND);

							return NO_ERRORS;
						}
						else{
							*typeOfCommand ^= REG_CONST;
							printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
						}
					}
					else{
						*typeOfCommand ^= REG_CONST;
						*typeOfCommand ^= RAM_CONST;
						printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
					}
				}
				else{
					*typeOfCommand ^= IMM_CONST;
					printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				}
			}
			else{
				*typeOfCommand ^= IMM_CONST;
				*typeOfCommand ^= RAM_CONST;
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
			}
		}
		else{
			*typeOfCommand ^= IMM_CONST;
			*typeOfCommand ^= REG_CONST;
			printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
		}
	}
	else{
		*typeOfCommand ^= IMM_CONST;
		*typeOfCommand ^= REG_CONST;
		*typeOfCommand ^= RAM_CONST;
		printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);

	}

	return NO_ERRORS;

}


