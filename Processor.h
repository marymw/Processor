#ifndef PROC_H
#define PROC_H

#include "Lifo.h"

//как совместно использовать два хедера?
const int  LEN_OF_COMMAND = 10;
const char HLT[]  = {'h', 'l', 't', '\0'};
const char PUSH[] = {'p', 'u', 's', 'h', '\0'};
const char POP[]  = {'p', 'o', 'p', '\0'};
const char ADD[]  = {'a', 'd', 'd', '\0'};
const char SUB[]  = {'s', 'u', 'b', '\0'};
const char MULT[] = {'m', 'u', 'l', 't', '\0'};
const char DIV[]  = {'d', 'i', 'v', '\0'};
const char OUT[]  = {'o', 'u', 't', '\0'};
const char VER[]  = {'v', 'e', 'r', '\0'};
const char DMP[]  = {'d', 'm', 'p', '\0'};

//sin cos sqrt

enum Errors1 {
	//NO_ERRORS,			//0
	COMMAND_ENTRY_ERROR //1
};

enum CommandsOfCalculator{
	CMD_HLT  = 0,
	CMD_PUSH = 1,
	CMD_POP  = 2,
	CMD_ADD  = 3,
 	CMD_SUB  = 4,
	CMD_MULT = 5,
	CMD_DIV  = 6,
	CMD_OUT  = 7,
	CMD_VER  = 8,
	CMD_DMP  = 9
};



//const int MAX_LEN_OF_CODE_ARRAY = 200;//норм???

int DoCommand(Stack *someStackPtr, int *code, const int sizeOfFile);
#endif PROC_H
