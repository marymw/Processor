#ifndef PROC_H
#define PROC_H

#include "Lifo.h"

//как совместно использовать два хедера?
const int  LEN_OF_COMMAND = 10;
const char HLT[]  = "hlt";
const char PUSH[] = "push";
const char POP[]  = "pop";
const char ADD[]  = "add";
const char SUB[]  = "sub";
const char MUL[]  = "mul";
const char DIV[]  = "div";
const char OUT[]  = "out";
const char VER[]  = "ver";
const char DMP[]  = "dmp";

//sin cos sqrt

enum ProcErrors {
	//NO_ERRORS,			 //0
	COMMAND_ENTRY_ERROR = 1, //1
	LACK_OF_ARGUMENTS,		 //2
	UNRECOGNIZED_COMMAND,    //3
	NULL_PTR_ERROR,          //4
	READ_ERROR,		         //5
	WRITE_ERROR,		     //6
	RIDE_ERROR,			     //7
	CLOSE_ERROR,			 //8
	RUNTIME_ERROR			 //9
};


enum CommandsOfCalculator{
	CMD_HLT  = 0,
	CMD_PUSH = 1,
	CMD_POP  = 2,
	CMD_ADD  = 3,
 	CMD_SUB  = 4,
	CMD_MUL  = 5,
	CMD_DIV  = 6,
	CMD_OUT  = 7,
	CMD_VER  = 8,
	CMD_DMP  = 9
};


enum LenOfCommands{
	LEN_OF_CMD_HLT  = 3,
	LEN_OF_CMD_PUSH = 4,
	LEN_OF_CMD_POP  = 3,
	LEN_OF_CMD_ADD  = 3,
 	LEN_OF_CMD_SUB  = 3,
	LEN_OF_CMD_MUL  = 3,
	LEN_OF_CMD_DIV  = 3,
	LEN_OF_CMD_OUT  = 3,
	LEN_OF_CMD_VER  = 3,
	LEN_OF_CMD_DMP  = 3
};


struct Processor {

	int REGS[4];
	struct Stack stackOfProc;
	char *code;
	int instructionPtr;

};


#define CheckNullPtr(param, string, nameOfError) do {			\
										if (param == nullptr) { \
											printf(string);		\
											return nameOfError;	\
										}						\
									} while(0)


#define CheckNull(param, string, nameOfError) do {				       \
												if (param != 0) {	   \
													printf(string);    \
													return nameOfError;\
												}				       \
								 			  } while(0)


#define CheckEqual(param1, param2, string, nameOfError) do {				       \
															if (param1 != param2) {\
																printf(string);    \
																return nameOfError;\
															}				       \
								 			  			} while(0)


#define CheckNoNull(param, string, nameOfError) do {				       \
													if (param == 0) {	   \
														printf(string);    \
														return nameOfError;\
													}				       \
								 			    } while(0)



//const int MAX_LEN_OF_CODE_ARRAY = 200;//норм???

int ExecuteCommand(Processor *SomeProcessorPtr, const int sizeOfFile);

#endif PROC_H
