#include "Processor.h"
#include "Decompiler.h"

//а как сделать так чтобы он нормально печатал??
int DecomposeToAsmBuffer(char* code, const int sizeOfFile, FILE *decodeFile) {

	int instructionPtr = 0;

	while(instructionPtr < sizeOfFile){

		switch (code[instructionPtr] & 31){
		
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
				fprintf(decodeFile, "\t \t \t");
				fprintf(decodeFile, "push ");
				int arg = code[instructionPtr];
				char argStr[10] = {};
				if (arg & 32){
					argStr[1] = *(int *)(code + instructionPtr + 1);///мееееееееееее
					instructionPtr += 4;
					
				}
				if (arg & 64) {
					argStr[2] = code[instructionPtr];
					argStr[3] = 'x';
					instructionPtr++;
				}
				if (arg & 128){
					argStr[strlen(argStr)] = ']';
					argStr[0] = '[';
				}
				
				//fprintf(decodeFile, "%x %x \t", code[instructionPtr], code[instructionPtr + 1]);
				
				fprintf(decodeFile, "%s", argStr);
				instructionPtr ++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_POP: {//не определяет что это поп
				fprintf(decodeFile, "%4d \t", instructionPtr);
				fprintf(decodeFile, "%x \t\t", code[instructionPtr]);
				fprintf(decodeFile, "pop ");
				instructionPtr++;
				fprintf(decodeFile, "%cx", code[instructionPtr++] + 96);
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
