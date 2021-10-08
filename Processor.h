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

enum Errors1 {
	//NO_ERRORS,			//0
	COMMAND_ENTRY_ERROR //1
};

int GetCommand    (char *command, double *paramPtr, int *typeOfCommand);
int DefineCommand (char *command, int *selector);
int IsEqualCommand(const char *firstCommand, const char *secondCommand);
int DoCommand     (Stack *MyStack, int selector, int typeOfCommand, double param);

#endif
