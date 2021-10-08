#include <stdio.h>
#include "Processor.h"
#include <assert.h>

int GetCommand(char *command, double *paramPtr, int* typeOfCommandPtr){

	int statusOfScanf = scanf("%s %lf", command, paramPtr);

	if (statusOfScanf == 0){
		return COMMAND_ENTRY_ERROR;
	}

	if (statusOfScanf == 1){
		*typeOfCommandPtr = 1;
	}

	if (statusOfScanf == 2){
		*typeOfCommandPtr = 2;
	}

	//char a;
	//int i = 0;
	//for (i = 0; (a = getchar()) != EOF && a != '\n'; i++){
	//	command[i] = a;
	//}
	//command[i] = '\0';

	return NO_ERRORS;
}

int DefineCommand(char *command, int *selectorPtr){

	if (IsEqualCommand(command, HLT)){
		*selectorPtr = 1;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, PUSH)){
		*selectorPtr = 2;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, POP)){
		*selectorPtr = 3;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, ADD)){
		*selectorPtr = 4;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, SUB)){
		*selectorPtr = 5;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, MULT)){
		*selectorPtr = 6;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, DIV)){
		*selectorPtr = 7;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, OUT)){
		*selectorPtr = 8;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, VER)){
		*selectorPtr = 9;
		return NO_ERRORS;
	}
	if (IsEqualCommand(command, DMP)){
		*selectorPtr = 10;
		return NO_ERRORS;
	}
	*selectorPtr = 0;
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

//!TODO обработка ошибок и что выводит
int DoCommand(Stack *someStackPtr, int selector, int typeOfCommand, double param){//type не нужен вроде
	switch (selector){

		case 0: {
			return 0;
		}break;

		case 1: {
			return 0;
		}break;

		case 2: {
			StackPush(someStackPtr, param);
		}break;

		case 3: {
			StackPop(someStackPtr);//пусть пока выбрасывает в никуда
		}break;

		case 4:{
			double arg1 = StackPop(someStackPtr);
			double arg2 = StackPop(someStackPtr);
			StackPush(someStackPtr, arg1 + arg2);
		}break;

		case 5: {
			double subtracter = StackPop(someStackPtr);//сначала вытащили вычитаемое
			double minuend	  = StackPop(someStackPtr);
			Type sub = minuend - subtracter;
			StackPush(someStackPtr, sub);
		}break;

		case 6: {
			double multiplier1 = StackPop(someStackPtr);
			double multiplier2 = StackPop(someStackPtr);
			Type mult          =multiplier1 * multiplier2;
			StackPush(someStackPtr, mult);
		}break;

		case 7: {
			double divisor = StackPop(someStackPtr);//сначала вытащили делитель
			double dividend	  = StackPop(someStackPtr);
			Type div        = dividend / divisor;
			StackPush(someStackPtr, div);
		}break;

		case 8: {
			printf("Сейчас на вершине стека лежит %lf\n", StackTop(someStackPtr));
		}break;

		case 9: {
			printf("Запущен верификатор!!\n");
			ASSERT_OK(someStackPtr);
		}break;

		case 10: {
			printf("Запущен дамп!!\n");
			StackDump(someStackPtr);
		}break;

		default:{
			;
		}



	}
	return 0;
}


