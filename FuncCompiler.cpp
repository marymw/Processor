#include "Processor.h"
#include "HeadOneg.h"
#include "Compiler.h"
#include <string.h>


static int DefineCommand   			  	      (char *command, int *selectorPtr, char typeOfCommand);
static int IsEqualCommand  			  	      (const char *firstCommand, const char *secondCommand, const int lenOfCommand);
static int GetCommand  						  (label **arrayOfLabels, char *string, int *param, char *command, char *typeOfCommand, int *reg);
static int CheckCommandWithoutArgument	      (char *string, char *command);
static int CheckArgumentIsOnlyRegister        (char *string, char *command, char *typeOfCommand, int *reg);
static int CheckArgumentIsRegisterInBrakets   (char *string, char *command, char *typeOfCommand, int *reg);
static int CheckArgumentIsOnlyConstant     	  (char *string, int *param, char *command, char *typeOfCommand, int *reg);
static int CheckArgumentIsConstInBrackets     (char *string, int *param, char *command, char *typeOfCommand, int *reg);
static int CheckArgumentIsJustConstAndRegister(char *string, int *param, char *command, char *typeOfCommand, int *reg);
static int IsLabel							  (label **arrayOfLabels, int *instructionPtr, char *command, int *labelPtr);
static int IsCommandWithoutArguments          (char *codePtr, int *instructionPtr, char *typeOfCommand, char *command, int *selector);
static int IsCommandWithArguments             (char *codePtr, int *instructionPtr, char *typeOfCommand, char *command, int *selector, const int param, const int reg);
static int CheckIsJump						  (label **arrayOfLabels, char *label, char *string, int *param, char *command, char *typeOfCommand);


static int DefineCommand(char *command, int *selectorPtr, char typeOfCommand) {

	// #define CHECK_COMMAND(commandToCheck) if (IsEqualCommand(commandToCheck, HLT, LEN_OF_CMD_HLT + 1)){
	// 	CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
	// 	*selectorPtr = CMD_HLT;
	// 	return NO_ERRORS;
	// }

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
	if (IsEqualCommand(command, JMP, LEN_OF_CMD_JMP + 1)){
		PRINT_LOG();
		CheckNoNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);
		*selectorPtr = CMD_JMP;
		return NO_ERRORS;
	}

	printf("Неверная команда\n");
	return UNRECOGNIZED_COMMAND;


}


static int IsEqualCommand (const char *firstCommand, const char *secondCommand, const int lenOfCommand) { 

	return !strncmp(firstCommand, secondCommand, lenOfCommand); // pusher

}


int DecomposeToCodeArray(label **arrayOfLabels, MyString *indexPtr, char *codePtr, const int numberOfStrings, int *instructionPtr, char *typeOfCommand) {

	CheckNullPtr(indexPtr, "Index is undefined!\n", NULL_PTR_ERROR);
	
	char command[LEN_OF_COMMAND] = {};
	int  param    = 0;
	int  selector = -1;
	int  reg      = 0;
	int  labelPtr = 0;
	
	for (int count = 0; count < numberOfStrings; count++){
		PRINT_LOG();
		int statusOfGetCommand = GetCommand(arrayOfLabels, indexPtr[count].PtrOnStartOfString, &param, command, typeOfCommand, &reg);
		CheckNull(statusOfGetCommand, "Read error\n", READ_ERROR);
		PRINT_LOG();
		if      (IsLabel(arrayOfLabels, instructionPtr, command, &labelPtr)) 									 {PRINT_LOG();}
		else if (IsCommandWithoutArguments(codePtr, instructionPtr, typeOfCommand, command, &selector)) 		 {PRINT_LOG();}
		else if (IsCommandWithArguments(codePtr, instructionPtr, typeOfCommand, command, &selector, param, reg)) {PRINT_LOG();}
		else {
			PRINT_LOG();
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


static int GetCommand(label **arrayOfLabels, char *string, int *param, char *command, char *typeOfCommand, int *reg) {

 	CheckNullPtr(string, "нулевой указатель на строчку!!\n", NULL_PTR_ERROR);
 	PRINT_LOG();

	*typeOfCommand       = 0;
	int leftCountOfSymb  = 0;
	int rightCountOfSymb = 0;
	char label[MAX_LEN_OF_LABEL] = {};

	sscanf (string, "%s %s\n", command, label);

	if (int statusOfCheckIsJump = CheckIsJump(arrayOfLabels, label, string, param, command, typeOfCommand)) {
		CheckNoEqual(statusOfCheckIsJump, UNRECOGNIZED_COMMAND, "Напишите jmp по-человечески....\n", UNRECOGNIZED_COMMAND);
		PRINT_LOG();
		return NO_ERRORS;
	}
	PRINT_LOG();

	sscanf(string, "%s %n[%d+%cx]%n",command, &leftCountOfSymb, param, reg, &rightCountOfSymb);

	if ((rightCountOfSymb - leftCountOfSymb) < 6){ 
		int statusOfFunc = CheckArgumentIsJustConstAndRegister(string, param, command, typeOfCommand, reg);
		CheckNull(statusOfFunc, "Error in readind argument", UNRECOGNIZED_COMMAND); 
		
	}
	else{
		*typeOfCommand ^= IMM_CONST;
		*typeOfCommand ^= REG_CONST;
		*typeOfCommand ^= RAM_CONST;

	}

	return NO_ERRORS;

}


static int CheckCommandWithoutArgument(char *string, char *command) {

	int statusOfScanf1 = sscanf(string, "%s \n", command);
							
	CheckNoNull(statusOfScanf1, "Не удалось распознать команду\n", UNRECOGNIZED_COMMAND);

	if(statusOfScanf1 == 3){
		return UNRECOGNIZED_COMMAND;
	}

	return NO_ERRORS;
						
}


static int CheckArgumentIsOnlyRegister(char *string, char *command, char *typeOfCommand, int *reg) {

	int leftCountOfSymb  = 0;
	int rightCountOfSymb = 0;

	sscanf(string, "%s %n%cx%n", command, &leftCountOfSymb, reg, &rightCountOfSymb);

	if ((rightCountOfSymb - leftCountOfSymb) < 2) {
		return CheckCommandWithoutArgument(string, command);
	}
	else{
		*typeOfCommand ^= REG_CONST;
		return NO_ERRORS;
	}

}


static int CheckArgumentIsRegisterInBrakets(char *string, char *command, char *typeOfCommand, int *reg) {

	int leftCountOfSymb  = 0;
	int rightCountOfSymb = 0;

	sscanf(string, "%s %n[%cx]%n", command, &leftCountOfSymb, reg, &rightCountOfSymb);
					
	if ((rightCountOfSymb - leftCountOfSymb) < 4) {
		int statusOfFunc = CheckArgumentIsOnlyRegister(string, command, typeOfCommand, reg);
		CheckNull(statusOfFunc, "Error in readind argument", UNRECOGNIZED_COMMAND); 
	}
	else{
		*typeOfCommand ^= REG_CONST;
		*typeOfCommand ^= RAM_CONST;
	}

	return NO_ERRORS;
}

static int CheckArgumentIsOnlyConstant(char *string, int *param, char *command, char *typeOfCommand, int *reg) {

	int statusOfsscanf = sscanf(string, "%s %d", command, param);

	if (statusOfsscanf != 2) {
		int statusOfFunc = CheckArgumentIsRegisterInBrakets(string, command, typeOfCommand, reg);
		CheckNull(statusOfFunc, "Error in readind argument", UNRECOGNIZED_COMMAND); 
	}
	else{
		*typeOfCommand ^= IMM_CONST;
	}

	return NO_ERRORS;

}


static int CheckArgumentIsConstInBrackets(char *string, int *param, char *command, char *typeOfCommand, int *reg) {

	int leftCountOfSymb  = 0;
	int rightCountOfSymb = 0;

	sscanf(string, "%s %n[%d]%n", command, &leftCountOfSymb, param, &rightCountOfSymb);

	if ((rightCountOfSymb - leftCountOfSymb) < 3){ 
		int statusOfFunc = CheckArgumentIsOnlyConstant(string, param, command, typeOfCommand, reg);
		CheckNull(statusOfFunc, "Error in readind argument", UNRECOGNIZED_COMMAND); 
	}
	else{
		*typeOfCommand ^= IMM_CONST;
		*typeOfCommand ^= RAM_CONST;
	}

	return NO_ERRORS;

}


static int CheckArgumentIsJustConstAndRegister(char *string, int *param, char *command, char *typeOfCommand, int *reg) {

	int leftCountOfSymb  = 0;
	int rightCountOfSymb = 0;

	sscanf(string, "%s %n%d+%cx%n", command, &leftCountOfSymb, param, reg, &rightCountOfSymb);

	if((rightCountOfSymb - leftCountOfSymb) < 4){
		int statusOfFunc = CheckArgumentIsConstInBrackets(string, param, command, typeOfCommand, reg);
		CheckNull(statusOfFunc, "Error in readind argument", UNRECOGNIZED_COMMAND); 
	}
	else{
		*typeOfCommand ^= IMM_CONST;
		*typeOfCommand ^= REG_CONST;
	}

	return NO_ERRORS;

}

static int IsLabel(label **arrayOfLabels, int *instructionPtr, char *command, int *labelPtr) {
		PRINT_LOG();
		if (command[strlen(command) - 1] == ':'){
			command[strlen(command) - 1] = '\0';
			PRINT_LOG();
			DEBUG_PRINT_PROC("It is a label\n");
			sscanf(command, "%s\n", arrayOfLabels[(*labelPtr)]->name);
			arrayOfLabels[(*labelPtr)++]->address = *instructionPtr;
			return 1;
		}

		return 0;
}

static int IsCommandWithoutArguments(char *codePtr, int *instructionPtr, char *typeOfCommand, char *command, int *selector) {

	if (*typeOfCommand == COMMAND_WITHOUT_ARGUMENTS){ 
		int statusOfDefineCommand = DefineCommand(command, selector, *typeOfCommand);
		CheckNull(statusOfDefineCommand, "Ошибка определения команды!Вы ввели неверную команду!\n", UNRECOGNIZED_COMMAND);
		codePtr[(*instructionPtr)++] = *selector;
		return 1;
	}

	return 0;
}


static int IsCommandWithArguments(char *codePtr, int *instructionPtr, char *typeOfCommand, char *command, int *selector, const int param, const int reg) {
	PRINT_LOG();
	if (*typeOfCommand != COMMAND_WITHOUT_ARGUMENTS) {

			int statusOfDefineCommand = DefineCommand(command, selector, *typeOfCommand);
			CheckNull(statusOfDefineCommand, "Ошибка определения команды!Вы ввели неверную команду!\n", UNRECOGNIZED_COMMAND);
	
			codePtr[(*instructionPtr)++] = (*selector) ^ (*typeOfCommand);

			if(((*selector) == CMD_JMP)){
				codePtr[(*instructionPtr)++] = param;
				PRINT_LOG();
			}
			if(((*typeOfCommand) & IMM_CONST) && ((*selector) != CMD_JMP)){
				PRINT_LOG();
				*((int *)(&codePtr[(*instructionPtr)])) = param; 
				(*instructionPtr) += LEN_OF_INT;
			}
			if(((*typeOfCommand) & REG_CONST) && ((*selector) != CMD_JMP)){
				PRINT_LOG();
				int regSelector = reg - ASCII_BEFORE_A; 
				codePtr[(*instructionPtr)++] = regSelector;
			}

		return 1;
	}

	return 0;

}


static int CheckIsJump(label **arrayOfLabels, char *label, char *string, int *param, char *command, char *typeOfCommand) {
	PRINT_LOG();
	if (IsEqualCommand(command, JMP, LEN_OF_CMD_JMP + 1)){
		*typeOfCommand ^= IMM_CONST;
		PRINT_LOG();
		int statusOfsscanf = sscanf(label, "%d", param);
		PRINT_LOG();
		if (statusOfsscanf == 1) {PRINT_LOG();}
		else {
			CheckNoNull((strlen(label)), "Не хватает аргумента у jmp\n", UNRECOGNIZED_COMMAND);
			PRINT_LOG();
			for (int i = 0; i < 10; i++){
				PRINT_LOG();
				if (strncmp(arrayOfLabels[i]->name, label, strlen(label)) == 0){
					PRINT_LOG();
					*param = arrayOfLabels[i]->address;
					PRINT_LOG();
					return 1;
				}
				else {
					PRINT_LOG();
					*param = -1;//это будет в каждой итерации
					if ((strlen(arrayOfLabels[i]->name) == 0)) {
						return 1;
					}
				}
			}
		}

		return 1;

	}

	return 0;
}
