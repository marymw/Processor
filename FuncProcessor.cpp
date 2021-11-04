#include <stdio.h>
#include "Processor.h"
#include <assert.h>
#include <math.h>

int ExecuteCommand(Processor *SomeProcessorPtr, const int sizeOfFile){

	while(SomeProcessorPtr->instructionPtr <= sizeOfFile){
		
		char command = (*(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr)) & 31; //!TODO remove magic consts
		char typeOfCommand = (*(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
		int argumentJmp = 0;
		switch (command){
			
			case CMD_HLT: {
				PRINT_LOG();
				return NO_ERRORS;
			}
		
			case CMD_PUSH: {
				PRINT_LOG();
				int argument = 0;//
				SomeProcessorPtr->instructionPtr++;

				if (typeOfCommand & IMM_CONST){
					argument += *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
					DEBUG_PRINT_ONE_ARG_PROC("я хочу запушить число %d\n", argument);
					SomeProcessorPtr->instructionPtr += 4;
				}
				if (typeOfCommand & REG_CONST){
					int num = *(((SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr)));
					SomeProcessorPtr->instructionPtr++;
					DEBUG_PRINT_ONE_ARG_PROC("num = %d\n", num);
					argument += SomeProcessorPtr->REGS[ num];
				}
				if (typeOfCommand & RAM_CONST){
					printf("я в функции %s на строчке %d\n", __FUNCTION__, __LINE__);
					argument += SomeProcessorPtr->RAM[argument];
				}
				PRINT_LOG();
				DEBUG_PRINT_ONE_ARG_PROC("я запушил хз что но это = %d\n", argument);
				StackPush(&(SomeProcessorPtr->stackOfProc), argument);
				break;
			}

			case CMD_POP: {
				PRINT_LOG();
				if (SomeProcessorPtr->stackOfProc.stackSize <= 0){
					printf("Чисел в стеке больше нет!\n");
					return 0;
				}
				SomeProcessorPtr->instructionPtr += 1;
				SomeProcessorPtr->REGS[(int)(*(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr++))] = (int)StackPop(&(SomeProcessorPtr->stackOfProc));
				
				break;
			}

			case CMD_ADD:{
				PRINT_LOG();
				double arg1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double arg2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				StackPush(&(SomeProcessorPtr->stackOfProc), arg1 + arg2);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_SUB: {
				PRINT_LOG();
				double subtracter = StackPop(&(SomeProcessorPtr->stackOfProc));//сначала вытащили вычитаемое
				double minuend	  = StackPop(&(SomeProcessorPtr->stackOfProc));
				Type sub = minuend - subtracter;
				StackPush(&(SomeProcessorPtr->stackOfProc), sub);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_MUL: {
				PRINT_LOG();
				double multiplier1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double multiplier2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				Type mul          = multiplier1 * multiplier2;
				StackPush(&(SomeProcessorPtr->stackOfProc), mul);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_SQRT: {
				PRINT_LOG();
				double argForSqrt = StackPop(&(SomeProcessorPtr->stackOfProc));
				CheckAboveNull(argForSqrt, "Квадратный корень из отрицательного числа!\n", MATH_ERROR);
				Type sqrtn         = sqrtf(argForSqrt);
				StackPush(&(SomeProcessorPtr->stackOfProc), sqrtn);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_DIV: {
				PRINT_LOG();
				double divisor  = StackPop(&(SomeProcessorPtr->stackOfProc));//сначала вытащили делитель
				double dividend	= StackPop(&(SomeProcessorPtr->stackOfProc));
				Type div        = dividend / divisor;
				StackPush(&(SomeProcessorPtr->stackOfProc), div);
				SomeProcessorPtr->instructionPtr += 1;
				break;
			}

			case CMD_OUT: {
				PRINT_LOG();
				if (SomeProcessorPtr->stackOfProc.stackSize <= 0){
					printf("Чисел в стеке больше нет!\n");
					return 0;
				}
				printf("\n\t\tСейчас на вершине стека лежит %lf\n", StackTop(&(SomeProcessorPtr->stackOfProc)));
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
				PRINT_LOG()
				printf("Введите число, которое хотите записать в стек\n");
				SomeProcessorPtr->instructionPtr += 1;
				double number = 0;
				int statusOfScanf = scanf("%lf", &number);
				PRINT_LOG();
				while (statusOfScanf != 1) {
					printf("Вы ввели откровенный бред. Попробуйте снова.\n");//что сделать чтобы не зацикливалось??
					statusOfScanf = scanf("%lf", &number);
				}
				PRINT_LOG();
				StackPush(&(SomeProcessorPtr->stackOfProc), number);
				PRINT_LOG();
				break;
			}

			case CMD_JMP: {
				PRINT_LOG();
				SomeProcessorPtr->instructionPtr++;
				argumentJmp = *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
				DEBUG_PRINT_ONE_ARG_PROC("arg jmp = %d\n", argumentJmp);
				DEBUG_PRINT_ONE_ARG_PROC("arg jmp = %d\n", SomeProcessorPtr->code[argumentJmp]);
				SomeProcessorPtr->instructionPtr = argumentJmp;
				break;
			}
			case CMD_JA: {
				double arg1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double arg2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				if (arg1 > arg2){
					SomeProcessorPtr->instructionPtr++;
					argumentJmp = *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
					SomeProcessorPtr->instructionPtr = argumentJmp;
				}
				else {
					SomeProcessorPtr->instructionPtr += 5;
				}
				break;
			}
			case CMD_JAE: {
				double arg1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double arg2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				if (arg1 >= arg2){
					SomeProcessorPtr->instructionPtr++;
					argumentJmp = *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
					SomeProcessorPtr->instructionPtr = argumentJmp;
				}
				else {
					SomeProcessorPtr->instructionPtr += 5;
				}
				break;
			}
			case CMD_JB: {
				double arg1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double arg2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				if (arg1 < arg2){
					SomeProcessorPtr->instructionPtr++;
					argumentJmp = *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
					SomeProcessorPtr->instructionPtr = argumentJmp;
				}
				else {
					SomeProcessorPtr->instructionPtr += 5;
				}
				break;
			}
			case CMD_JBE: {
				double arg1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double arg2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				if (arg1 <= arg2){
					SomeProcessorPtr->instructionPtr++;
					argumentJmp = *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
					SomeProcessorPtr->instructionPtr = argumentJmp;
				}
				else {
					SomeProcessorPtr->instructionPtr += 5;
				}
				break;
			}
			case CMD_JE: {
				double arg1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double arg2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				if (arg1 == arg2){
					SomeProcessorPtr->instructionPtr++;
					argumentJmp = *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
					SomeProcessorPtr->instructionPtr = argumentJmp;
					DEBUG_PRINT_TWO_ARG_PROC("Я считаю что %lf и %lf равны\n ", arg1, arg2);
				}
				else {
					SomeProcessorPtr->instructionPtr += 5;
					DEBUG_PRINT_TWO_ARG_PROC("Я не считаю что %lf и %lf равны\n ", arg1, arg2);
				}
				DEBUG_PRINT_TWO_ARG_PROC("Я СРАВНИЛ %lf и %lf\n", arg1, arg2);
				break;
			}
			case CMD_JNE: {
				double arg1 = StackPop(&(SomeProcessorPtr->stackOfProc));
				double arg2 = StackPop(&(SomeProcessorPtr->stackOfProc));
				if (arg1 != arg2){
					SomeProcessorPtr->instructionPtr++;
					argumentJmp = *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
					SomeProcessorPtr->instructionPtr = argumentJmp;
				}
				else {
					SomeProcessorPtr->instructionPtr += 5;
				}
				break;
			}
			case CMD_CALL: {
				PRINT_LOG();
				StackPush(&(SomeProcessorPtr->stackOfReturns), SomeProcessorPtr->instructionPtr + 5);///////////+5
				SomeProcessorPtr->instructionPtr++;
				argumentJmp = *((int *)(SomeProcessorPtr->code + SomeProcessorPtr->instructionPtr));
				SomeProcessorPtr->instructionPtr = argumentJmp;
				break;
			}
			case CMD_RET: {
				PRINT_LOG();
				SomeProcessorPtr->instructionPtr = StackPop(&(SomeProcessorPtr->stackOfReturns));
				DEBUG_PRINT_ONE_ARG_PROC("return %d\n", SomeProcessorPtr->instructionPtr);
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


