#ifndef COMP_H
#define COMP_H



int DecomposeToCodeArray(MyString *indexPtr, char *codePtr, const int numberOfStrings, int *instructionPtr, char *typeOfCommand);
int PrintToCodeFile     (const char *codePtr, const int instructionPtr);

#endif COMP_H
