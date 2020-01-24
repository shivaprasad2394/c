

// A C program to demonstrate different storage 
// classes 
#include <stdio.h> 

// declaring the variable which is to be made extern 
// an intial value can also be initialized to x 
int x; 

void autoStorageClass() 
{ 

	printf("\nDemonstrating auto class\n\n"); 

	// declaring an auto variable (simply 
	// writing "int a=32;" works as well) 
	auto int a = 32; 

	// printing the auto variable 'a' 
	printf("Value of the variable 'a'"
		" declared as auto: %d\n", 
		a); 

	printf("--------------------------------"); 
} 

void registerStorageClass() 
{ 

	printf("\nDemonstrating register class\n\n"); 

	// declaring a register variable 
	register char b = 'G'; 

	// printing the register variable 'b' 
	printf("Value of the variable 'b'"
		" declared as register: %d\n", 
		b); 

	printf("--------------------------------"); 
} 

void externStorageClass() 
{ 

	printf("\nDemonstrating extern class\n\n"); 

	// telling the compiler that the variable 
	// z is an extern variable and has been 
	// defined elsewhere (above the main 
	// function) 
	extern int x; 

	// printing the extern variables 'x' 
	printf("Value of the variable 'x'"
		" declared as extern: %d\n", 
		x); 

	// value of extern variable x modified 
	x = 2; 

	// printing the modified values of 
	// extern variables 'x' 
	printf("Modified value of the variable 'x'"
		" declared as extern: %d\n", 
		x); 

	printf("--------------------------------"); 
} 

void staticStorageClass() 
{ 
	int i = 0; 

	printf("\nDemonstrating static class\n\n"); 

	// using a static variable 'y' 
	printf("Declaring 'y' as static inside the loop.\n"
		"But this declaration will occur only"
		" once as 'y' is static.\n"
		"If not, then every time the value of 'y' "
		"will be the declared value 5"
		" as in the case of variable 'p'\n"); 

	printf("\nLoop started:\n"); 

	for (i = 1; i < 5; i++) { 

		// Declaring the static variable 'y' 
		static int y = 5; 

		// Declare a non-static variable 'p' 
		int p = 10; 

		// Incrementing the value of y and p by 1 
		y++; 
		p++; 

		// printing value of y at each iteration 
		printf("\nThe value of 'y', "
			"declared as static, in %d "
			"iteration is %d\n", 
			i, y); 

		// printing value of p at each iteration 
		printf("The value of non-static variable 'p', "
			"in %d iteration is %d\n", 
			i, p); 
	} 

	printf("\nLoop ended:\n"); 

	printf("--------------------------------"); 
} 

int main() 
{ 
	printf("Storage Classes are used to describe the features of a variable/function\nThese features basically include the scope, visibility and life-time which help us to trace the existence of a particular variable during the runtime of a program\nC language uses 4 storage classes, namely:\nauto: This is the default storage class for all the variables declared inside a function or a block\nHence, the keyword auto is rarely used while writing programs in C language\nAuto variables can be only accessed within the block/function they have been declared and not outside them (which defines their scope)\nOf course, these can be accessed within nested blocks within the parent block/function in which the auto variable was declared\nHowever, they can be accessed outside their scope as well using the concept of pointers given here by pointing to the very exact memory location where the variables resides\nThey are assigned a garbage value by default whenever they are declared\nextern: Extern storage class simply tells us that the variable is defined elsewhere and not within the same block where it is used\nBasically, the value is assigned to it in a different block and this can be overwritten/changed in a different block as well\nSo an extern variable is nothing but a global variable initialized with a legal value where it is declared in order to be used elsewhere\nIt can be accessed within any function/block\nAlso, a normal global variable can be made extern as well by placing the ‘extern’ keyword before its declaration/definition in any function/block\nThis basically signifies that we are not initializing a new variable but instead we are using/accessing the global variable only\nThe main purpose of using extern variables is that they can be accessed between two different files which are part of a large program\nFor more information on how extern variables work, have a look at this link\nstatic: This storage class is used to declare static variables which are popularly used while writing programs in C language\nStatic variables have a property of preserving their value even after they are out of their scope! Hence, static variable\npreserve the value of their last use in their scope\nSo we can say that they are initialized only once and exist till the termination of the program\nThus, no new memory is allocated because they are not re-declared\nTheir scope is local to the function to which they were defined\nGlobal static variables can be accessed anywhere in the program\nBy default, they are assigned the value 0 by the compiler\nregister: This storage class declares register variables which have the same functionality as that of the auto variables\nThe only difference is that the compiler tries to store these variables in the register of the microprocessor if a free register is available\nThis makes the use of register variables to be much faster than that of the variables stored in the memory during the runtime of the program\nIf a free register is not available, these are then stored in the memory only\nUsually few variables which are to be accessed very frequently in a program are declared with the register keyword which improves the running time of the program\nAn important and interesting point to be noted here is that we cannot obtain the address of a register variable using pointers\nTo specify the storage class for a variable, the following syntax is to be followed:\nSyntax:\nstorage_class var_data_type var_name; ");
	printf("A program to demonstrate"
		" Storage Classes in C\n\n"); 

	// To demonstrate auto Storage Class 
	autoStorageClass(); 

	// To demonstrate register Storage Class 
	registerStorageClass(); 

	// To demonstrate extern Storage Class 
	externStorageClass(); 

	// To demonstrate static Storage Class 
	staticStorageClass(); 

	// exiting 
	printf("\n\nStorage Classes demonstrated"); 

	return 0; 
} 

// This code is improved by RishabhPrabhu 


