#ifndef COMP_H
#define COMP_H

int DefineCommand       (char *command, int *selectorPtr);
int IsEqualCommand      (const char *firstCommand, const char *secondCommand);
int DecomposeToCodeArray(MyString *indexPtr, int *codePtr, int numberOfStrings, int *instructionPtr);
int PrintToCodeFile     (int *codePtr, int instructionPtr);

#endif COMP_H
