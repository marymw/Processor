#include "Processor.h"
#include "Decompiler.h"

//а как сделать так чтобы он нормально печатал??
int DecomposeToAsmBuffer(char* code, const int sizeOfFile, FILE *decodeFile) {

	int instructionPtr = 0;

	while(instructionPtr < sizeOfFile){

		switch (code[instructionPtr] & 31){
		
			case CMD_HLT: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "hlt ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_PUSH: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "\t \t");
				fprintf(decodeFile, "push ");
				int arg = code[instructionPtr++];
				if (arg & RAM_CONST){
					fprintf(decodeFile, "[");
				}
				if (arg & IMM_CONST){
					fprintf(decodeFile, "%d", *(int *)(code + instructionPtr));
					instructionPtr += LEN_OF_INT;
					
				}
				if (arg & IMM_CONST && arg & REG_CONST){
					fprintf(decodeFile, "+");
				}
				if (arg & REG_CONST) {
					fprintf(decodeFile, "%cx", code[instructionPtr] + ASCII_BEFORE_A);
					instructionPtr++;
				}
				if (arg & RAM_CONST){
					fprintf(decodeFile, "]");
				}
				
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_POP: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "pop ");
				instructionPtr++;
				fprintf(decodeFile, "%cx", code[instructionPtr++] + 96);
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_ADD:{
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "add ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_SUB: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "sub ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_MUL: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "mul ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_DIV: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "div ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_OUT: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "out ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_VER: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "ver ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_DMP: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "dmp ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_IN: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "in ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_JMP: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr++]);
				fprintf(decodeFile, "jmp ");
				fprintf(decodeFile, "%d", *(int *)(code + instructionPtr));
				instructionPtr += LEN_OF_INT;
				fprintf(decodeFile, "\n");
				break;
			}
			case CMD_JA: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr++]);
				fprintf(decodeFile, "ja ");
				fprintf(decodeFile, "%d", *(int *)(code + instructionPtr));
				instructionPtr += LEN_OF_INT;
				fprintf(decodeFile, "\n");
				break;
			}
			case CMD_JAE: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr++]);
				fprintf(decodeFile, "jae ");
				fprintf(decodeFile, "%d", *(int *)(code + instructionPtr));
				instructionPtr += LEN_OF_INT;
				fprintf(decodeFile, "\n");
				break;
			}
			case CMD_JB: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr++]);
				fprintf(decodeFile, "jb ");
				fprintf(decodeFile, "%d", *(int *)(code + instructionPtr));
				instructionPtr += LEN_OF_INT;
				fprintf(decodeFile, "\n");
				break;
			}
			case CMD_JBE: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr++]);
				fprintf(decodeFile, "jbe ");
				fprintf(decodeFile, "%d", *(int *)(code + instructionPtr));
				instructionPtr += LEN_OF_INT;
				fprintf(decodeFile, "\n");
				break;
			}
			case CMD_JE: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr++]);
				fprintf(decodeFile, "je ");
				fprintf(decodeFile, "%d", *(int *)(code + instructionPtr));
				instructionPtr += LEN_OF_INT;
				fprintf(decodeFile, "\n");
				break;
			}
			case CMD_JNE: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr++]);
				fprintf(decodeFile, "jne ");
				fprintf(decodeFile, "%d", *(int *)(code + instructionPtr));
				instructionPtr += LEN_OF_INT;
				fprintf(decodeFile, "\n");
				break;
			}
			case CMD_SQRT:{
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "sqrt ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}
			case CMD_CALL: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr++]);
				fprintf(decodeFile, "call ");
				fprintf(decodeFile, "%d", *(int *)(code + instructionPtr));
				instructionPtr += LEN_OF_INT;
				fprintf(decodeFile, "\n");
				break;
			}
			case CMD_RET: {
				fprintf(decodeFile, "%04d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "ret ");
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
