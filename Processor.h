#ifndef PROC_H
#define PROC_H

#include "Lifo.h"

//как совместно использовать два хедера?
const int  LEN_OF_COMMAND = 10;
const char HLT[]   = "hlt";
const char PUSH[]  = "push";
const char POP[]   = "pop";
const char ADD[]   = "add";
const char SUB[]   = "sub";
const char MUL[]   = "mul";
const char DIV[]   = "div";
const char OUT[]   = "out";
const char VER[]   = "ver";
const char DMP[]   = "dmp";
const char IN[]    = "in";
const char JMP[]   = "jmp";
const char LABEL[] = "label";
const char JA[]    = "ja";
const char JAE[]   = "jae";
const char JB[]    = "jb";
const char JBE[]   = "jbe";
const char JE[]    = "je";
const char JNE[]   = "jne";
const char CALL[]  = "call";
const char RET[]   = "ret";
const char SQRT[]  = "sqrt";

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
	RUNTIME_ERROR,			 //9
	READ_ARGS_ERROR,		 //10
	NO_FILE,				 //11
	MATH_ERROR				 //12
};


enum CommandsOfCalculator{
	CMD_HLT   = 0,
	CMD_PUSH  = 1,
	CMD_POP   = 2,
	CMD_ADD   = 3,
 	CMD_SUB   = 4,
	CMD_MUL   = 5,
	CMD_DIV   = 6,
	CMD_OUT   = 7,
	CMD_VER   = 8,
	CMD_DMP   = 9,
	CMD_IN    = 10,
	CMD_JMP   = 11,
	CMD_LABEL = 12,
	CMD_JA	  = 13,
	CMD_JAE   = 14,
	CMD_JB    = 15,
	CMD_JBE   = 16,
	CMD_JE    = 17,
	CMD_JNE   = 18,
	CMD_CALL  = 19,
	CMD_RET   = 20,
	CMD_SQRT  = 21
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
	LEN_OF_CMD_DMP  = 3,
	LEN_OF_CMD_IN   = 2,
	LEN_OF_CMD_JMP  = 3,
	LEN_OF_CMD_JA   = 2,
	LEN_OF_CMD_JAE  = 3,
	LEN_OF_CMD_JB   = 2,
	LEN_OF_CMD_JBE  = 3,
	LEN_OF_CMD_JE   = 2,
	LEN_OF_CMD_JNE  = 3,
	LEN_OF_CMD_CALL = 4,
	LEN_OF_CMD_RET  = 3,
	LEN_OF_CMD_SQRT = 4
};


enum TypesOfCommands {
	COMMAND_WITHOUT_ARGUMENTS, //0
	COMMAND_WITH_ARGUMENTS     //1
};



struct Processor {

	int   *REGS;
	struct Stack stackOfProc;
	struct Stack stackOfReturns;
	char  *code;
	int    instructionPtr;
	int   *RAM;

};

//128 = 10000000
//64  = 01000000
//32  = 00100000
const unsigned char RAM_CONST      		  = 128;
const unsigned char REG_CONST     		  = 64;
const unsigned char IMM_CONST     		  = 32;
const int           LEN_OF_INT 	   		  = 4;
const int           ASCII_BEFORE_A        = 96;
const int 			MAX_LEN_OF_CODE_ARRAY = 400;

//#define DEBUG5 1

#ifdef DEBUG5
#define PRINT_LOG() printf("Я в функции %s, на строчке %d\n", __FUNCTION__, __LINE__);
#define DEBUG_PRINT_PROC(str) printf(str);
#define DEBUG_PRINT_ONE_ARG_PROC(str, arg) printf(str, arg);
#define DEBUG_PRINT_TWO_ARG_PROC(str, arg1, arg2) printf(str, arg1, arg2);
#else
#define PRINT_LOG() printf(" ");
#define DEBUG_PRINT_PROC(str) printf(" ");
#define DEBUG_PRINT_ONE_ARG_PROC(str, arg) printf(" ");
#define DEBUG_PRINT_TWO_ARG_PROC(str, arg1, arg2) printf(" ");
#endif


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

#define CheckNoEqual(param1, param2, string, nameOfError) do {				       \
															if (param1 == param2) {\
																printf(string);    \
																return nameOfError;\
															}				       \
								 			  			} while(0)

#define CheckNoNull(param, string, nameOfError) do {				       \
													if (param == 0) {	   \
														printf(string);    \
														return nameOfError;\
													}				       \
								 			    } while(0);

#define CheckAboveNull(param, string, nameOfError) do {				       \
													if (param < 0) {	   \
														printf(string);    \
														return nameOfError;\
													}				       \
								 			    } while(0);

#define DEBUG_PRINT(string, arg1, arg2) printf(string, arg1, arg2);

int ExecuteCommand(Processor *SomeProcessorPtr, const int sizeOfFile);

#endif 
