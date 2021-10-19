#include <stdio.h>
#include "Processor.h"
#include <assert.h>


int ExecuteCommand(Processor *SomeProcessorPtr, const int sizeOfFile){

	while(SomeProcessorPtr->instructionPtr <= sizeOfFile){

		switch (*(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr)){

			case CMD_HLT: {
				return NO_ERRORS;
			}

			case CMD_PUSH: {
				StackPush(&(SomeProcessorPtr->stackOfProc), *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr + 1)));
				SomeProcessorPtr->instructionPtr += 5;
				break;
			}

			case CMD_POP: {
				if (SomeProcessorPtr->stackOfProc.stackSize <= 0){
					printf("Чисел в стеке больше нет!\n");
					return 0;
				}
				StackPop(&(SomeProcessorPtr->stackOfProc));//пусть пока выбрасывает в никуда
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_ADD:{
				double arg1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double arg2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				StackPush(&(SomeProcessorPtr->stackOfProc), arg1 + arg2);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_SUB: {
				double subtracter = StackPop(&(SomeProcessorPtr->stackOfProc));//сначала вытащили вычитаемое
				double minuend	  = StackPop(&(SomeProcessorPtr->stackOfProc));
				Type sub = minuend - subtracter;
				StackPush(&(SomeProcessorPtr->stackOfProc), sub);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_MUL: {
				double multiplier1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double multiplier2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				Type mul          = multiplier1 * multiplier2;
				StackPush(&(SomeProcessorPtr->stackOfProc), mul);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_DIV: {
				double divisor  = StackPop(&(SomeProcessorPtr->stackOfProc));//сначала вытащили делитель
				double dividend	= StackPop(&(SomeProcessorPtr->stackOfProc));
				Type div        = dividend / divisor;
				StackPush(&(SomeProcessorPtr->stackOfProc), div);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_OUT: {
				if (SomeProcessorPtr->stackOfProc.stackSize <= 0){
					printf("Чисел в стеке больше нет!\n");
					return 0;
				}
				printf("Сейчас на вершине стека лежит %lf\n", StackTop(&(SomeProcessorPtr->stackOfProc)));
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_VER: {
				printf("Запущен верификатор!!\n");
				ASSERT_OK(&(SomeProcessorPtr->stackOfProc));
				SomeProcessorPtr->instructionPtr += 1;

				break;
			}

			case CMD_DMP: {
				printf("Запущен дамп!!\n");
				StackDump(&(SomeProcessorPtr->stackOfProc));
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_IN: {
				printf("Введите число, которое хотите записать в стек\n");
				SomeProcessorPtr->instructionPtr += 1;
				double number = 0;
				int statusOfScanf = scanf("%d", &number);
				//почему эта
				while (statusOfScanf != 1) {
					printf("Вы ввели откровенный бред. Попробуйте снова.");
					statusOfScanf = scanf("%d", &number);
				}

				StackPush(&(SomeProcessorPtr->stackOfProc), number);
				break;
			}
			
			default:{
				printf("Неверная команда\n");
				return UNRECOGNIZED_COMMAND;
			}
		}
	}

	return NO_ERRORS;

}


