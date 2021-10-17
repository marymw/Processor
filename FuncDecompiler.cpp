#include "Processor.h"

int DecomposeToAsmBuffer(char* code, int sizeOfFile, FILE *decodeFile){

	int instructionPtr = 0;

	while(instructionPtr <= sizeOfFile){

		switch (code[instructionPtr]){
		
			case CMD_HLT: {
				fprintf(decodeFile, "hlt ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_PUSH: {
				fprintf(decodeFile, "push ");
				fprintf(decodeFile, "%d", *(int *)(code + instructionPtr + 1));
				instructionPtr += 5;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_POP: {
				fprintf(decodeFile, "pop ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_ADD:{
				fprintf(decodeFile, "add ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_SUB: {
				fprintf(decodeFile, "sub ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_MULT: {
				fprintf(decodeFile, "mult ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_DIV: {
				fprintf(decodeFile, "div ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_OUT: {
				fprintf(decodeFile, "out ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_VER: {
				fprintf(decodeFile, "ver ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}

			case CMD_DMP: {
				fprintf(decodeFile, "dmp ");
				instructionPtr++;
				fprintf(decodeFile, "\n");
				break;
			}
			
			default:{
				}
			}
	}
	return 0;

}

