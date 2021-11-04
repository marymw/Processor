#include <stdio.h>
#include "Processor.h"
#include "HeadOneg.h"
#include "Compiler.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

	CheckEqual(argc, 2, "No instruction file!\n", NO_FILE);
	CheckNullPtr(argv[1], "No instruction file!\n", NULL_PTR_ERROR);

	char *ASM_FILE = argv[1]; //!TODO delete

	FILE *asmFile = fopen(ASM_FILE, "rb");
	CheckNullPtr(asmFile, "Can't open file!\n", NULL_PTR_ERROR);

	MyString *index  = nullptr;											
	char     *buffer = nullptr;	

	ReadFromFile(&buffer, ASM_FILE);
	CheckNullPtr(buffer, "Buffer is undefined!\n", NULL_PTR_ERROR);

	int numberOfStrings = DecomposeToStringArray(&index, &buffer); 
	CheckNullPtr(index, "Index is undefined!\n", NULL_PTR_ERROR);

	int instructionPtr   = 0;
	char typeOfCommand   = 0;
	label *arrayOfLabels = (label *)calloc(MAX_NUM_OF_LABELS, sizeof(label));
	
	for (int i = 0; i < MAX_NUM_OF_LABELS; i++){
		arrayOfLabels[i].name = (char *)calloc(MAX_LEN_OF_LABEL, sizeof(char));
		arrayOfLabels[i].address = -1;
	}
 
 	char *code = (char *)calloc(MAX_LEN_OF_CODE_ARRAY, sizeof(char)); 
 	CheckNullPtr(code, "code is undefined!\n", NULL_PTR_ERROR);
 	PRINT_LOG();

	int statusDecomposeToCodeArray = DecomposeToCodeArray(arrayOfLabels, index, code, numberOfStrings, &instructionPtr, &typeOfCommand);
	CheckNull(statusDecomposeToCodeArray, "Failed to decompose into code array\n", NULL_PTR_ERROR);
	PRINT_LOG();

	instructionPtr = 0;

	statusDecomposeToCodeArray = DecomposeToCodeArray(arrayOfLabels, index, code, numberOfStrings, &instructionPtr, &typeOfCommand);
	CheckNull(statusDecomposeToCodeArray, "Failed to decompose into code array\n", NULL_PTR_ERROR);
	PRINT_LOG();
	#ifdef DEBUG5
	for (int i = 0; i < MAX_NUM_OF_LABELS; i++){
		printf("%d %s %d\n", i, arrayOfLabels[i].name, arrayOfLabels[i].address);
	}
	#endif
	
	int statusPrintToCodeFile = PrintToCodeFile(code, instructionPtr);
	CheckNull(statusPrintToCodeFile, "Failed to print the code array into fail\n", NULL_PTR_ERROR);
	
	free(code);
	for (int i = 0; i < MAX_NUM_OF_LABELS; i++){
		free(arrayOfLabels[i].name);
	}
	free(index);
	free(buffer);
	fclose(asmFile);
	free(arrayOfLabels);
	
	return 0;

}

