 
#include <stdio.h> 
#define INCREMENT(x) ++x 
int main() 
{ 
	printf("A macro is a name given to a block of C statements as a pre-processor directive. Being a pre-processor, the block of code is \ncommunicated to the compiler before entering into the actual coding (main () function). A macro is defined with the preprocessor directive\n#define.\nThe advantage of using macro is the execution speed of the program fragment. When the actual code snippet is to be used, it can be \nsubstituted by the name of the macro. The same block of statements, on the other hand, need to be repeatedly hard coded as and when required.\nThe disadvantage of the macro is the size of the program. The reason is, the pre-processor will replace all the macros in the program by its \nreal definition prior to the compilation process of the program.\n");
	char *ptr = "GeeksQuiz"; 
	int x = 10; 
	printf("%s ", INCREMENT(ptr)); 
	printf("%d", INCREMENT(x)); 
	return 0; 
} 

