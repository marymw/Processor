#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc, char *argv[], char *envp[]) {
	
	
	char *ASM_FILE  = argv[1];
	char *CODE_FILE = argv[2];

	struct stat asmFile  = {};
	struct stat codeFile = {};

	stat(ASM_FILE, &asmFile);
	stat(CODE_FILE, &codeFile);

	time_t timeAsm  = asmFile.st_ctime;
	time_t timeCode = codeFile.st_ctime;

	if (timeAsm > timeCode){//а что за время то там ?
		//перекомпилировать код и запустить процессор
		printf("Надо бы перекомпилить..\n");
		system("./COMPBINVERS6 asm.txt");
		system("./ProcBinVERS10 codeBin.bin");
		system("./DECOMBINVERS3 codeBin.bin");
		
	}

	else{
		//запустить процессор
		printf("ничего перекомпилировать не нужно!\n");
		system("./ProcBinVERS10 codeBin.bin");

	} 

	return 0;
}
