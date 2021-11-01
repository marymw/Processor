#ifndef COMP_H
#define COMP_H

const int MAX_NUM_OF_LABELS = 10;
const int MAX_LEN_OF_LABEL  = 10;

struct label {
	int   address;
	char *name;
};



// #define CURCOMMAND(arg) LEN_OF_CMD_arg
//#define CMD(arg) CMD_arg

// #define CHECK_COMMAND(commandToCheck) if (IsEqualCommand(command, commandToCheck, CURCOMMAND(commandToCheck + 1)){\
// 	 										CheckNull(typeOfCommand, "Ввёл что-то не то!\n", LACK_OF_ARGUMENTS);\
// 	 										*selectorPtr = COM(arg);\
// 	 										return NO_ERRORS;\
// 	 									}

int DecomposeToCodeArray(label **arrayOfLabels, MyString *indexPtr, char *codePtr, const int numberOfStrings, int *instructionPtr, char *typeOfCommand);
int PrintToCodeFile     (const char *codePtr, const int instructionPtr);

#endif 
