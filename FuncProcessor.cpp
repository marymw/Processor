#include <stdio.h>
#include "Processor.h"
#include <assert.h>

int DoCommand(Stack *someStackPtr, int *code, const int sizeOfFile){//type не нужен вроде

	int instructionPtr = 0;

	while(instructionPtr <= sizeOfFile){

		switch (code[instructionPtr]){
			case -1: {
				return 0;
				break;
			}

			case CMD_HLT: {
				return 0;
				break;
			}

			case CMD_PUSH: {
				StackPush(someStackPtr, code[instructionPtr + 1]);
				instructionPtr += 2;
				break;
			}

			case CMD_POP: {
				StackPop(someStackPtr);//пусть пока выбрасывает в никуда
				instructionPtr += 1;
				break;
			}

			case CMD_ADD:{
				double arg1 = StackPop(someStackPtr);
				double arg2 = StackPop(someStackPtr);
				StackPush(someStackPtr, arg1 + arg2);
				instructionPtr += 1;
				break;
			}

			case CMD_SUB: {
				double subtracter = StackPop(someStackPtr);//сначала вытащили вычитаемое
				double minuend	  = StackPop(someStackPtr);
				Type sub = minuend - subtracter;
				StackPush(someStackPtr, sub);
				instructionPtr += 1;
				break;
			}

			case CMD_MULT: {
				double multiplier1 = StackPop(someStackPtr);
				double multiplier2 = StackPop(someStackPtr);
				Type mult          =multiplier1 * multiplier2;
				StackPush(someStackPtr, mult);
				instructionPtr += 1;
				break;
			}

			case CMD_DIV: {
				double divisor = StackPop(someStackPtr);//сначала вытащили делитель
				double dividend	  = StackPop(someStackPtr);
				Type div        = dividend / divisor;
				StackPush(someStackPtr, div);
				instructionPtr += 1;
				break;
			}

			case CMD_OUT: {
				printf("Сейчас на вершине стека лежит %lf\n", StackTop(someStackPtr));
				instructionPtr += 1;
				break;
			}

			case CMD_VER: {
				printf("Запущен верификатор!!\n");
				ASSERT_OK(someStackPtr);
				instructionPtr += 1;
				break;
			}

			case CMD_DMP: {
				printf("Запущен дамп!!\n");
				StackDump(someStackPtr);
				instructionPtr += 1;
				break;
			}
			
			default:{
				printf("Неверная команда\n");
				return -1;
			}
		}
	}
	return 0;
}


