#ifndef COMP_H
#define COMP_H

#define CheckNullPtr(param, string, nameOfError) do {			\
										                                if (param == nullptr) {  \
										                                     	printf(string);		  \
											                                    return nameOfError;	\
									                                 	}						              \
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

int DecomposeToCodeArray(MyString *indexPtr, char *codePtr, const int numberOfStrings, int *instructionPtr, int *typeOfCommand);
int PrintToCodeFile     (const char *codePtr, const int instructionPtr);

#endif COMP_H
