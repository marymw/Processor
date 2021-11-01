#include <stdio.h>
#include "Processor.h"
#include <assert.h>


int ExecuteCommand(Processor *SomeProcessorPtr, const int sizeOfFile){
	printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
	while(SomeProcessorPtr->instructionPtr <= sizeOfFile){
		printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
		char command = (*(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr)) & 31; //!TODO remove magic consts
		char typeOfCommand = (*(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
		switch (command){
			
			case CMD_HLT: {
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				return NO_ERRORS;
			}
		
			case CMD_PUSH: {
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				
				int argument = 0;
				SomeProcessorPtr->instructionPtr++;

				if (typeOfCommand & IMM_CONST){
					printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
					argument += *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
					SomeProcessorPtr->instructionPtr += 4;
				}
				if (typeOfCommand & REG_CONST){
					printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
					printf("SomeProcessorPtr->instructionPtr = %d\n", SomeProcessorPtr->instructionPtr);
					int num = *(((SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr)));
					SomeProcessorPtr->instructionPtr++;
					printf("num = %d\n", num);//тут какой-то мусор
					argument += SomeProcessorPtr->REGS[ num ];
				}
				if (typeOfCommand & RAM_CONST){
					printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
					argument += SomeProcessorPtr->RAM[argument];
				}
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				StackPush(&(SomeProcessorPtr->stackOfProc), argument);
				break;
			}

			case CMD_POP: {
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				if (SomeProcessorPtr->stackOfProc.stackSize <= 0){
					printf("Чисел в стеке больше нет!\n");
					return 0;
				}
				SomeProcessorPtr->instructionPtr += 1;
				SomeProcessorPtr->REGS[(int)(*(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr++))] = (int)StackPop(&(SomeProcessorPtr->stackOfProc));
				
				break;
			}

			case CMD_ADD:{
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				double arg1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double arg2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				StackPush(&(SomeProcessorPtr->stackOfProc), arg1 + arg2);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_SUB: {
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				double subtracter = StackPop(&(SomeProcessorPtr->stackOfProc));//сначала вытащили вычитаемое
				double minuend	  = StackPop(&(SomeProcessorPtr->stackOfProc));
				Type sub = minuend - subtracter;
				StackPush(&(SomeProcessorPtr->stackOfProc), sub);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_MUL: {
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				double multiplier1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double multiplier2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				Type mul          = multiplier1 * multiplier2;
				StackPush(&(SomeProcessorPtr->stackOfProc), mul);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_DIV: {
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				double divisor  = StackPop(&(SomeProcessorPtr->stackOfProc));//сначала вытащили делитель
				double dividend	= StackPop(&(SomeProcessorPtr->stackOfProc));
				Type div        = dividend / divisor;
				StackPush(&(SomeProcessorPtr->stackOfProc), div);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_OUT: {
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				if (SomeProcessorPtr->stackOfProc.stackSize <= 0){
					printf("Чисел в стеке больше нет!\n");
					return 0;
				}
				printf("Сейчас на вершине стека лежит %lf\n", StackTop(&(SomeProcessorPtr->stackOfProc)));
				StackPop(&(SomeProcessorPtr->stackOfProc));//дед сказал выбрасывать в помойку
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_VER: {

				printf("Запущен верификатор!!\n");
				ASSERT_OK(&(SomeProcessorPtr->stackOfProc));
				SomeProcessorPtr->instructionPtr += 1;

				break;
			} //sin, cos, sqrt

			case CMD_DMP: {
				printf("Запущен дамп!!\n");
				StackDump(&(SomeProcessorPtr->stackOfProc));
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_IN: {
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				printf("Введите число, которое хотите записать в стек\n");
				SomeProcessorPtr->instructionPtr += 1;
				double number = 0;
				int statusOfScanf = scanf("%lf", &number);
				//почему эта
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				while (statusOfScanf != 1) {
					printf("Вы ввели откровенный бред. Попробуйте снова.");
					statusOfScanf = scanf("%lf", &number);
				}
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				StackPush(&(SomeProcessorPtr->stackOfProc), number);
				printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
				break;
			}

			case CMD_JMP: {
				SomeProcessorPtr->instructionPtr = SomeProcessorPtr->code[SomeProcessorPtr->instructionPtr + 1];
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


