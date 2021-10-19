#include "Processor.h"
#include "Decompiler.h"

//а как сделать так чтобы он нормально печатал??
int DecomposeToAsmBuffer(char* code, const int sizeOfFile, FILE *decodeFile) {

	int instructionPtr = 0;

	while(instructionPtr < sizeOfFile){

		switch (code[instructionPtr]){
		
			case CMD_HLT: {
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "hlt ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_PUSH: {
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x %x \t", code[instructionPtr], code[instructionPtr + 1]);
				fprintf(decodeFile, "push ");
				fprintf(decodeFile, "%d", *(int *)(code + instructionPtr + 1));
				instructionPtr += 5;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_POP: {
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "pop ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_ADD:{
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "add ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_SUB: {
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "sub ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_MUL: {
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "mul ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_DIV: {
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "div ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_OUT: {
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "out ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_VER: {
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "ver ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_DMP: {
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "dmp ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_IN: {
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "in ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			
			default:{
				printf("Неведомая ошибка..Не получилось определить команду!\n");
				return UNRECOGNIZED_COMMAND;
			}
		}

	}

	return NO_ERRORS;

}
