# Hello ,
Agenda
======
    1)C
    2)C++
    3)Linux system programmming
    4)Wifi
    5)Gps


Lets get Started With **C**

Intro:-
======
C programming is just one of the Way to communicate with Electronic gadgets which operate on Binary system[0's And 1's].
- C is a **mid-level language** and it needs a **compiler** to convert C-code into an executable code[0's And 1's] so that the program can be run on our machine. 

Advantages of c
- faster than high level languages.(macros/inline)
- system programming (access to memory /pointers).

compilation of C-code:-

gcc –Wall filename.c –o filename

Compilation Process:-
C Compiler converts a C program into an object code and then creates executable code. 
There are four phases for a C program to become an executable: 

    - Pre-processing
    - Compilation
    - Assembly
    - Linking
    - Loading

1)Pre-processing is the first phase through which source code is passed.

A preprocessor is a program that process any source code in c before compilation.

the preprocessor first examines source code for any preprocessor directive present . 

This phase include:  

    - Removal of Comments
    - Expansion of Macros
    - Expansion of the included files.
    - Conditional compilation
Ex:-**#include**
an external File containing the a macro definition /Function will be included before the main(), if **#include** directive is found.

2)Compilation

During the compilation stage,
- the compiler  compiles the output of preprocessor [filename.i] and produce an intermediate compiled output file [filename.s].
- This file is in assembly level instructions[mnemonics]. 

3)Assembly
In this phase the the output filename.s is taken as input and turned into filename.o by assembler. 
The assembler output is stored in an object file.This file contain machine level instructions(ascii/hexa format etc). 
At this phase, only existing code is converted into machine language.system/function calls like printf are not resolved. 

4)Linking

This is the 3rd phase in which all the linking of function calls with their definitions are done. 
Linker knows where all these functions are implemented. Linker does some extra work also, it adds some extra code to our program which is required when the program starts and ends. 
For example, there is a code which is required for setting up the environment like passing command line arguments.
**ask if you need extra info**

5)Loader.

Loader is the program of the operating system which loads the executable from the disk into the primary memory(RAM) for execution.

**ask if you need extra info**

**Macros**:-A macro is a segment of code which is replaced by the value of macro.

A preprocessor directive.

	  pros:-
	      • It replaces the value before compiling.
	  Cons:-
	      • no typecasting.
	      • Usually used to create alias in c
	      • used has file guard in c.

Macro------------------->>v/s<<-----------------functions
================================================================================================                                        
    No TypeChecking (ex:- func parameter)     |                             exist
    preprocessed                              |                             compiled
    codelength increases on Macro call        |                             remains same
    Speed of Execution faster                 |                             Speed of execution Slower
    useful in small code                      |                             usefull in large code
    difficult to debug                        |                             Easy
    
    =============================================================================================


 • In macros, no type checking(incompatible operand, etc.) is done and thus use of macros can lead to errors/side-effects in some cases.
 •However, this is not the case with functions. Also, macros do not check for compilation error (if any). 
 
 Consider the following two codes:

	#include<stdio.h> 
	  #define CUBE(b) b*b*b 
	  int main() 
	  { 
	    printf("%d", CUBE(1+2)); 
	    return 0; 
	  } 

Inline Function are those function whose definitions are small and be substituted at the place where its function call is happened. 
Function substitution is totally compiler choice.

	Let’s take below example:
	#include <stdio.h> 

	// Inline function in C 
	static inline int foo() 
	{ 
	  return 2; 
	} 

	// Driver code 
	int main() 
	{ 

	  int ret; 

	  // inline function call 
	  ret = foo(); 

	  printf("Output is: %d\n", ret); 
	  return 0; 
	} 
note:if static is not used then it will give error.

In function `main':
undefined reference to `foo'
To resolve this problem use “static” before inline. 
Using static keyword forces the compiler to consider this inline function in the linker, 
and hence the program compiles and run successfully.[for more refer the readme in inline subs]


storage classes :-
---------------
they are Qualifiers which are used along the data types. storage class specifiers indicate/decide

               1)the extent(lifetime) of variable.
               2)scope (visibility) of the variable
               3)storage location in memory.
               4)default value

there are 4 types of storage class specifier:-
--------------------------------------------
    1)auto------->a default specifier class for local variables,if variable not specifeid any storage class.
                 • Local variables are auto by default,Garbage value(default).
                 •function with auto specifier cannot have return type.if tried will give compilation error.
    2)static----->varible with static specifier have internal or no linkage.it is not accessible outside the translation unit it is declared in.
                  • memory persistant
                  • initialized once.
    4)extern----->default specifier class for global variables and function.
                 •varibles with extern class have no storage allocation for variable.
                 •indicates/informs compiler about offload declaration/definition of variable.
    4)register--->variable with register class have visibility Local to Function.
                 •informs compiler to store the variable in cpu registers.


static extras:-

    void func (void)
    {
      static int foo = 5;   // will get stored in .data
      ...modify foo here...
  
- Before main() is even called, the "C run-time libraries"  run various start-up code. This includes copying down values into .data and .bss. So the above line is actually executed before your program even starts.

- If you initialize a static variable with a value, then most systems store it in a segment called .data. If you don't initialize it, or explicitly initialize it to zero, it gets stored in another segment called .bss 
 
- line containing the initialization is not executed the first time the function is entered (as often taught in beginner classes) - it is not executed inside the function at all and it is always ignored during function execution.
  
- So by the time func() is called for the first time, foo is already initialized. Any other changes to foo inside the function will happen in run-time, as with any other variable.


**demo**:-

    #include <stdio.h>
    static int animals = 8;
    const int i = 5;

    static int call_me(void)
    {
        printf("%d %d", i, animals);
    } 
    int main()
    {
          int animals = 2;
        call_me();
        printf("%d", animals);
        return 0;
    }

Answer 582

Incremnet & decrement Operator	
=============================
++ / --

	operand should be a varible
	5++;//invalid
	a+b++;//valid
	(a+b)++;//inavlid

	a++;
	a=a+1;
	c=(a+b)++;//invalid

post increment & pre increment
============================
	a++  //post incremnt
	++a  //pre incremnt

	post incremmt-->value is assigned then incremnt
	pre incremnt  -->first incremnt then value is asssigned
				
		int main()
		{
			int a,b=10;
			a=b++;
			printf("%d  %d\n",a,b);//10  11
		}

		int main()
		{
			int a,b=10;
			a=++b;
			printf("%d  %d\n",a,b);//11  11
		}

				
		a--  //post decremnet
		--a  //pre decremnt

	post decremnet-->value is assigned then decremnet
	pre decremnet  -->first decremnet then value is asssigned
				
------------------------------------------------------------------------------------------

typedef :-defining new names to existing types.
-------  
    Pros:-
        • to reduce complexity
        • to increase code readability and portability.
        
        
        // C program to demonstrate importance 
        // of typedef over #define for data types 
        #include <stdio.h> 
        typedef char* ptr; 
        #define PTR char* 
        int main() 
        { 
          ptr a, b, c; 
          PTR x, y, z; 
          printf("sizeof a:%u\n" ,sizeof(a) ); 
          printf("sizeof b:%u\n" ,sizeof(b) ); 
          printf("sizeof c:%u\n" ,sizeof(c) ); 
          printf("sizeof x:%u\n" ,sizeof(x) ); 
          printf("sizeof y:%u\n" ,sizeof(y) ); 
          printf("sizeof z:%u\n" ,sizeof(z) ); 
          return 0; 
        } 

      Output:

      sizeof a:8
      sizeof b:8
      sizeof c:8
      sizeof x:8
      sizeof y:1
      sizeof z:1
      From the output of the above program size of “a” which is a pointer is 8 (on a machine where pointers are stored using 8 bytes). In the above program, when the compiler comes to

      typedef char* ptr;
      ptr a, b, c;
      the statement effectively becomes

      char *a, *b, *c;
      This declares a, b, c as char*.

      In contrast, #define works like this:

      #define PTR char*
      PTR x, y, z;
      the statement effectively becomes

      char *x, y, z;

This makes x, y and z different, as, x is pointer-to-a char, whereas, y and z are char variables. When we declare macros with pointers while defining if we declare more than one identifier then the actual definition is given to the first identifier and for the rest non-pointer definition is given. In the above case x will be declared as char*, so its size is the size of a pointer, whereas, y and z will be declared as char so, their size will be 1 byte.

=======================================================================================

Macro:-    A preprocessor directive.
-----
          • It replaces the value before compiling.
      Cons:-
          • no typecasting.
          • Usually used to create alias in c
          • used has file guard in c.
========================================================================================

Enum:- A userdefined data type  and it consist of a set of named constant integers.
----
      Pro:-
          • increases code readability.
          • Easy to debug symbolic constant.

=========================================================================================

1)What is the volatile keyword?
=================================
A Type qualifier that prevents object from the compiler optimization.

according to c standards:-

     - • A volatile object can be modified in ways unknown to the implementation.
     - • the value of the object can be changed at any time without any action being taken by the code.
     - • when a variable or object is declared volatile the compiler reloads the value from the memory each time it is accessed by the program.[i.e:-it prevents from cacheing a variable into registers]
      •reading the value from memory is the only way to check the unpredictable change of the value.

	/*--------------------------
	volatile int Flag = 0;

	ISR(void) 
	{ 
	  Flag = 1; 
	} 

	int main(void) 
	{ 

	  while (!Flag)
	  {
	      //do some work
	  }

	  return 0;
	}-------------------------*/
=========================================================================================

2)What is the **use of volatile keyword**?
• Sharing the global variables or buffers between the multiple threads.
• Accessing the global variables in an interrupt routine or signal handler.

=======================================================================================

3)What is the **difference between the const and volatile qualifiers in C**?
Const:-
-----
- • The const keyword is compiler-enforced and says that the program could not change the value of the object, that means it makes the object non-modifiable type.

Volatile:-
--------
- • volatile prevents any compiler optimization and says that the value of the object can be changed by something that is beyond the control of the program and so that compiler will not make any assumption about the object. 
- • When the compiler sees the above declaration then it avoids to make any assumption regarding the “a” and in every iteration read the value from the address which is assigned to the “a”.

=======================================================================================

4)**Can a variable be both constant and volatile in C**?
YES

Example:- a switch or any output device is attached with GPIO[input].
•in that situation, volatile plays an important role and ensures that the compiler always read the value from the GPIO address and avoid to ma	ke any assumption.
•if pointer is not of const type so it might be possible program change the pointing address of the pointer. So we have to create a constant p	ointer with a volatile keyword.

	int volatile * const PortRegister;
	 |     |     |   |    |
	 |     |     |   |    +------> PortRegister is a
	 |     |     |   +-----------> constant
	 |     |     +---------------> pointer to a
	 |     +---------------------> volatile
	 +---------------------------> integer

	/*Define macro for address
	#define PORTX 0x00020000  // Address of the GPIO 
	main(){
	//Create pointer to point the address
	uint32_t volatile * const pcPortReg = (uint32_t *) PORTX;
	// Write value to the port
	*pcPortReg = value;
	// Read value from the port
	value = *pcPortReg;
	}

**Void Pointer**:-A generic pointer whiich has no associated data type .Thats why it can store Address of any type of object and can be typecast to any other type.

**Dangling pointer**:-When the reference object is deleted or Deallocated without Changing the value of the pointer.it creates a problem because the pointer is still pointing the memory that is no longer available.

**Wild pointer**:-A pointer Not initialized properly proir to its First use is Know as wild pointer.
**malloc” or “memory allocation”** method in C is used to dynamically allocate a single large block of memory with the specified size. 

- It returns a pointer of type void which can be cast into a pointer of any form. 
- It doesn’t Iniatialize memory at execution time so that it has initializes each block with the default garbage value initially. 

		Syntax:  
		ptr = (cast-type*) malloc(byte-size)
		For Example:
		ptr = (int*) malloc(100 * sizeof(int));

**calloc” or “contiguous allocation”** method in C is used to dynamically allocate the specified number of blocks of memory of the specified type. 

- it is very much similar to malloc() but has two different points and these are:
- It initializes each block with a default value ‘0’.
- It has two parameters or arguments as compare to malloc().

		Syntax: 

		ptr = (cast-type*)calloc(n, element-size);
		here, n is the no. of elements and element-size is the size of each element.
		For Example: 
		ptr = (float*) calloc(25, sizeof(float));
		This statement allocates contiguous space in memory for 25 elements each with the size of the float.

**realloc” or “re-allocation”** method in C is used to dynamically change the memory allocation of a previously allocated memory. 

- In other words, if the memory previously allocated with the help of malloc or calloc is insufficient, realloc can be used to dynamically re-allocate memory. - - re-allocation of memory maintains the already present value and new blocks will be initialized with the default garbage value.

		Syntax:  

		ptr = realloc(ptr, newSize);

		where ptr is reallocated with new size 'newSize'.

		// Dynamically allocate memory using calloc()
	    ptr = (int*)calloc(n, sizeof(int));

        // Dynamically re-allocate memory using realloc()
        ptr = realloc(ptr, n * sizeof(int));


# Big Endian V/S Little Endian

**Endianess**:-Order in which data Bytes are stored in Memory and it Also describes the order of byte transmission.
- Big Endian:-MSB byte is stored first
- Little Endian:-LSB byte is stored first

		Ex:- 0X11223344
		00 --> 0x11		00 --> 0x44
		01 --> 0x22		01 --> 0x33
		02 --> 0x33		02 --> 0x22
		03 --> 0x44		03 --> 0x11
		-----------		------------
		Big Endian		Little Endian
		
**Function pointer**:-Special Variable which holds the Adress of function .

Foo is a pointer to a function that takes 3 ints and returns an int pointer.
	**Syntax**:- int*(*foo)(int,int,int)
Ex:-

	//Declaration of a pointer to a function that takes an integer 
	//and returns an integer.
	int (*f_ptr)(int);

	//Assignment of a function foo to the function pointer f_ptr declared above.
	f_ptr = foo;

	//Calling foo indirectly via f_ptr, passing the return value of foo to r.
	int r = f_ptr(v);

	//Assigning an address of a function to the function pointer f_ptr,
	//then calling foo by dereferencing the function pointer.  
	f_ptr = &foo;
	int r = (*f_ptr)(v);

Ex:-

	Void Do_operation(int (*op)(int x,int y)){
	return op(X,Y);
	}
	int Add(int a,int b){
	//do something
	}
	int Multiply(int a,int b){
	//do something
	}
	int main(){
	int result = Do_operation(Add,2,3);
	int result = Do_operation(Multiply,2,3);
	}

# Function pointers and type def

	Syntax:- Typedef Void(*<AliasName>)(parameters)
		and then 
		in main--> AliasName <somename> = &Func
				    <somename>->Func

Ex:-

	#include <stdio.h>
	// The top-level class.
	typedef struct sCommClass {
	    int (*open)(struct sCommClass *self, char *fspec);
	} tCommClass;

	// Function for the TCP 'class'.

	static int tcpOpen (tCommClass *tcp, char *fspec) {
	    printf ("Opening TCP: %s\n", fspec);
	    return 0;
	}
	static int tcpInit (tCommClass *tcp) {
	    tcp->open = &tcpOpen;
	    return 0;
	}
	// Function for the HTTP 'class'.

	static int httpOpen (tCommClass *http, char *fspec) {
	    printf ("Opening HTTP: %s\n", fspec);
	    return 0;
	}
	static int httpInit (tCommClass *http) {
	    http->open = &httpOpen;
	    return 0;
	}
	// Test program.
	int main (void) {
	    int status;
	    tCommClass commTcp, commHttp;

	    // Same 'base' class but initialised to different sub-classes.

	    tcpInit (&commTcp);
	    httpInit (&commHttp);

	    // Called in exactly the same manner.

	    status = (commTcp.open)(&commTcp, "bigiron.box.com:5000");
	    status = (commHttp.open)(&commHttp, "http://www.microsoft.com");

	    return 0;
	}
# optput:-

	Opening TCP: bigiron.box.com:5000
	Opening HTTP: http://www.microsoft.com

# For accessing Specific memory from user space
run below code and try to make some sence

	#include <stdio.h>
	void addr(int *var){
	    printf("Adress of var = %x, var=%d,\t return=%x\n", &var, var,(int*)&var);
	    int *ptr=(int*)&var;
	    printf(" ptr points to %x\n", ptr);
	    *ptr = 123;
	    printf("New value of var=%d\n", var);
	}
	int main() {
	  int var = 7456;
	  addr(&var);
	  return 0;
	}
# to access a fixed memory address. So you need to follow the below steps, these are high-level steps.

	//Memory address, you want to access
	#define RW_FLAG 0x1FFF7800
	//Pointer to access the Memory address
	volatile uint32_t *flagAddress = NULL;
	//variable to stored the read value
	uint32_t readData = 0;
	//Assign addres to the pointer
	flagAddress = (volatile uint32_t *)RW_FLAG;
	//Read value from memory
	* flagAddress = 12; // Write
	//Write value to the memory
	readData = * flagAddress;
# pointer to an Array

Syntax:-int(*ptr)[10];//**A pointer that can point to an array of 10 int**

Access it as below:- 
- ptr[i] ==>*(*ptr+i)
- ptr[i][j] ==>*(*(ptr+i))+j)
# Array of pointers

Syntax:-char *name[]={"amit",
		      "ankur",
		      "amar",
		      "akhil"};
		      
Access it like a normal array:-
-printf("%s",names[i]);

**pointer to an Array**==>here pointing range will be block length
- ptr==>base address of array
- (ptr+i)==>points to 'i'th block.
- *(ptr+i)==>gives base address of 'i'th block od 2-d array.

		# include<stdio.h>
		int main()
		{

		    int i = 0, j=0, sum0=0, sum1=0;
		    int data[4][3] = { {23,55,50},{45,38,55},{70,43,45},{34,46,60}};
		    int bata[3][3] = { {9,8,7},{6,5,4},{3,2,1}};
		    int (*ttr)[3]=bata;
		    //int *ttr=bata;//this will give error
		    for (i=0; i<3; i++) {
			for (j = 0; j < 3; j++) {
			    printf("printing in reverse pos=%d Address =%d and value=%d\n",(((9-j)-i)),(ttr+9-(i*j)),*(*(ttr+i)+j));
			}
		    }                               

		i=0;
		j=0;

		    int *Ptr = *data;    //Why is the indirection operator used here? 
				    // Does Ptr = 23 by this assignment?

		    for (i=0; i<4; i++) {
			sum1 = 0;
			for (j = 0; j < 3; j++) {
			    sum1 += data[i][j];
			}
			if (sum1 > sum0) {
				 sum0 = sum1;
				 Ptr = *(data + i);     // Seems like this statement makes Ptr
			}                               // point one row below ... what syntax
		    }                                   // can you use to access columns then?
						       // Is it possible to use pointer arithmetic
		    for (i=0; i<3; i++)                 // to access elements of data[i][j] that
			printf("%d\n", Ptr[i]);          // are not at j = 0?

		  return 0;
		}

# dynamically allocate a 2D array in C
- Using a single pointer: 

		#include <stdio.h>
		#include <stdlib.h>

		void main()
		{
			int r = 3, c = 4; //Taking number of Rows and Columns
			int *ptr, count = 0, i;
			ptr = (int *)malloc((r * c) * sizeof(int)); //Dynamically Allocating Memory
			for (i = 0; i < r * c; i++)
			{
				ptr[i] = i + 1; //Giving value to the pointer and simultaneously printing it.
				printf("%d ", ptr[i]);
				if ((i + 1) % c == 0)
				{
					printf("\n");
				}
			}
			free(ptr);
		}

- Using an array of pointers 

		#include <stdio.h>
		#include <stdlib.h>

		int main()
		{
			int r = 3, c = 4, i, j, count;

			int *arr[r];
			for (i=0; i<r; i++)
				arr[i] = (int *)malloc(c * sizeof(int));

			// Note that arr[i][j] is same as *(*(arr+i)+j)
			count = 0;
			for (i = 0; i < r; i++)
			for (j = 0; j < c; j++)
				arr[i][j] = ++count; // Or *(*(arr+i)+j) = ++count

			for (i = 0; i < r; i++)
			for (j = 0; j < c; j++)
				printf("%d ", arr[i][j]);

			/* Code for further processing and free the
			dynamically allocated memory */

		return 0;
		}

- Using pointer to a pointer 

		#include <stdio.h>
		#include <stdlib.h>

		int main()
		{
			int r = 3, c = 4, i, j, count;

			int **arr = (int **)malloc(r * sizeof(int *));
			for (i=0; i<r; i++)
				arr[i] = (int *)malloc(c * sizeof(int));

			// Note that arr[i][j] is same as *(*(arr+i)+j)
			count = 0;
			for (i = 0; i < r; i++)
			for (j = 0; j < c; j++)
				arr[i][j] = ++count; // OR *(*(arr+i)+j) = ++count

			for (i = 0; i < r; i++)
			for (j = 0; j < c; j++)
				printf("%d ", arr[i][j]);

		/* Code for further processing and free the
			dynamically allocated memory */

		return 0;
		}

- Using double pointer and one malloc call 

		#include<stdio.h>
		#include<stdlib.h>

		int main()
		{
			int r=3, c=4, len=0;
			int *ptr, **arr;
			int count = 0,i,j;

			len = sizeof(int *) * r + sizeof(int) * c * r;
			arr = (int **)malloc(len);

			// ptr is now pointing to the first element in of 2D array
			ptr = (int *)(arr + r);

			// for loop to point rows pointer to appropriate location in 2D array
			for(i = 0; i < r; i++)
				arr[i] = (ptr + c * i);

			for (i = 0; i < r; i++)
				for (j = 0; j < c; j++)
					arr[i][j] = ++count; // OR *(*(arr+i)+j) = ++count

			for (i = 0; i < r; i++)
				for (j = 0; j < c; j++)
					printf("%d ", arr[i][j]);

			return 0;
		}
- using **pointer to array**

		#include <stdio.h>
		//void print(int *arr, int m, int n)
		void print(int m, int n)
		{
		    int (*ptr)[n]=(int *)malloc((m * n) * sizeof(int)); //Dynamically Allocating Memory
			int i, j;
			for (i = 0; i < m; i++)
			for (j = 0; j < n; j++){
			*(*(ptr+i) + j)=(i*n)+j;
				printf("%d ", *(*(ptr+i) + j));
				//printf("%d ", *((arr+i*n) + j));
			}
		}

		int main()
		{
		//	int arr[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
			int m = 3, n = 3;

			// We can also use "print(&arr[0][0], m, n);"
			print(m, n);
			return 0;
		}

# char pointers V/S char Arrays

	#include <stdio.h>
	#include <string.h>

	int main()
	{
	    char *p = "hello";// **string literal**,may be stored in read-only memory
	    char q[] = "hello"; //So this is just a shortcut for:- char c[] = {'a', 'b', 'c', '\0'};
	    
	    printf("%zu\n", sizeof(p)); // => size of pointer to char -- 4 on x86, 8 on x86-64
	    printf("%zu\n", sizeof(q)); // => size of char array in memory -- 6 on both

	    // size_t strlen(const char *s) and we don't get any warnings here:
	    printf("%zu\n", strlen(p)); // => 5
	    printf("%zu\n", strlen(q)); // => 5

	    return 0;
	}
	
# ask extra:-

	#include <stdio.h>

	int main(void) {
	    char *s = "abc";
	    printf("%s\n", s);
	    return 0;
	}
	Compile and decompile:

	gcc -ggdb -std=c99 -c main.c
	objdump -Sr main.o
	Output contains:

	 char *s = "abc";
	8:  48 c7 45 f8 00 00 00    movq   $0x0,-0x8(%rbp)
	f:  00 
		c: R_X86_64_32S .rodata
	Conclusion: GCC stores char* it in .rodata section, not in .text.

	If we do the same for char[]:

	 char s[] = "abc";
	we obtain:

	17:   c7 45 f0 61 62 63 00    movl   $0x636261,-0x10(%rbp)
	so it gets stored in the stack (relative to %rbp).

	Note however that the default linker script puts .rodata and .text in the same segment, which has execute but no write permission. This can be observed with:

	readelf -l a.out
	which contains:

	 Section to Segment mapping:
	  Segment Sections...
	   02     .text .rodata
   
================================================================================================
Structures and union

C structures and union - A structure is a user defined data type, which groups a set of data types. It is a collection of variables of different type under single name......

Properties of Union

Properties of Union - A union is utilized to use same memory space for all different members of union. Union offers a memory section to be treated for one variable type.....

A)When we declare a structure or union, we actually declare a new data type suitable for our purpose. So we cannot initialize values as it is not a variable declaration but a data type declaration.

#include‹stdio.h›
int main()
{
	struct site
	{
		char name[] = "GeeksQuiz";
		int no_of_pages = 200;
	};
	struct site *ptr;
	printf("%d ", ptr->no_of_pages);
	printf("%s", ptr->name);
	getchar();
	return 0;
}

B)In C, struct and union types cannot have static members. In C++, struct types are allowed to have static members, but union cannot have static members in C++ also.

#include<stdio.h>
struct st
{
	int x;
	static int y;
};

int main()
{
	printf("%d", sizeof(struct st));
	return 0;
}

C)Short array s[5] will take 10 bytes as size of short is 2 bytes.

When we declare a union, memory allocated for the union is equal to memory needed for the largest member of it, and all members share this same memory space. Since u is a union, memory allocated to u will be max of float y(4 bytes) and long z(8 bytes). So, total size will be 18 bytes (10 + 8)

struct {
	short s[5];
	union {
		float y;
		long z;
	}u;
} t;

D)A structure variable can be assigned to other using =, but cannot be compared with other using ==

E)hen we declare a union, memory allocated for a union variable of the type is equal to memory needed for the largest member of it, and all members share this same memory space. In above example, “char arr[8]” is the largest member. Therefore size of union test is 8 bytes.

F)Since x and arr[4] share the same memory, when we set x = 0, all characters of arr are set as 0. O is ASCII value of ‘\0’. When we do “t.arr[1] = ‘G'”, arr[] becomes “\0G\0\0”. When we print a string using “%s”, the printf function starts from the first character and keeps printing till it finds a \0. Since the first character itself is \0, nothing is printed.

union test
{
	int x;
	char arr[4];
	int y;
};

int main()
{
	union test t;
	t.x = 0;
	t.arr[1] = 'G';
	printf("%s", t.arr);
	return 0;
}

G)
# include <iostream>
# include <string.h>
using namespace std;

struct Test
{
char str[20];
};

int main()
{
struct Test st1, st2;
strcpy(st1.str, "GeeksQuiz");
st2 = st1;
st1.str[0] = 'S';
cout << st2.str;
return 0;
}

	O/P:-GeeksQuiz

	#include<stdio.h>
struct Point
{
int x, y, z;
};

int main()
{
struct Point p1 = {.y = 0, .z = 1, .x = 2};
printf("%d %d %d", p1.x, p1.y, p1.z);
return 0;
}

	O/P:-201
memcpy()  function is is used to copy a specified number of bytes from one memory to another.

memset() just sets all pieces of memory to the same value.
	
memmove() function is used to copy a specified number of bytes from one memory to another or to overlap on same memory.

Difference between memmove() and memcpy() is, overlap can happen on memmove(). Whereas, memory overlap won’t happen in memcpy() and it should be done in non-destructive way.
	or
The C standard specifies two functions for copying memory regions, memcpy and memmove. The important difference is that it is undefined behavior to call memcpy with overlapping regions. One must use memmove for that. As the names imply, memcpy copies data from one region to another, while memmove moves data within a region. (It’s also perfectly acceptable to memmove between different regions.)

This subtle but important distinction allows memcpy to be optimized more aggressively. In the case of memmove between overlapping regions, care must be taken not to destroy the contents of the source before they are done copying. This is easiest to see with a naive implementation of a copy loop.

	#include <memory.h>
	#include <string.h>
	#include <stdio.h>

	char str1[7] = "abcdef";

	int main()
	{

	   printf( "The string: %s\n", str1 );
	   memcpy( (str1+6), str1, 10 );
	   printf( "New string: %s\n", str1 );

	   strcpy_s( str1, sizeof(str1), "aabbcc" );   // reset string


	   printf("\nstr1: %s\n", str1);
	   printf( "The string: %s\n", str1 );
	   memmove( (str1+6), str1, 10 );
	   printf( "New string: %s\n", str1 );

	}	
gives:

The string: abcdef
New string: abcdefabcdefabcd
The string: abcdef
New string: abcdefabcdef
	
Extra:-
=======
- **compiler** is a computer program that translates computer code written in one programming language (the source language) into another .
- **mid-level language**C is called middle-level language because it actually **binds the gap between a machine level language and high-level languages**. A user can use c language to do **System Programming** (for writing operating system) as well as **Application Programming** (menu driven customer billing system )

Keywords
========
		-->reserwed words
		-->predefined meaning which is known to compiler
Identifiers
==========
		-->name given by user to variable,function,structure,array,macro
-------------------------------------------------------
A **variable** in simple terms is a storage place which has some memory allocated to it. Basically, a variable used to store some form of data. 
Difference b/w variable declaration and definition .

Variable declaration refers to the part where a variable is first declared or introduced before its first use. 

Variable definition is the part where the variable is assigned a memory location and a value. 

Most of the times, variable declaration and definition are done together.

# Difference between “int main()” and “int main(void)” in C/C++?

  
Consider the following two definitions of main().

	int main()
	{
	   /*  */
	   return 0;
	}

and

	int main(void)
	{
	   /*  */
	   return 0;
	}

What is the difference?

In C++, there is no difference, both are same.

Both definitions work in C also, but the second definition with void is considered technically better as it clearly specifies that main can only be called without any parameter.
In C, if a function signature doesn’t specify any argument, it means that the function can be called with any number of parameters or without any parameters. For example, try to compile and run following two C programs (remember to save your files as .c). Note the difference between two signatures of fun().

	// Program 1 (Compiles and runs fine in C, but not in C++)
	void fun() {  } 
	int main(void)
	{
	    fun(10, "GfG", "GQ");
	    return 0;
	}

The above program compiles and runs fine (See this), but the following program fails in compilation (see this)

	// Program 2 (Fails in compilation in both C and C++)
	void fun(void) {  }
	int main(void)
	{
	    fun(10, "GfG", "GQ");
	    return 0;
	}

Unlike C, in C++, both of the above programs fails in compilation. In C++, both fun() and fun(void) are same.





datatypes
========
			
			char    -->1 byte
			int     -->nonportable datatype
				-->size of int depende on 
				size of the compiler 
UNSIGNED INTEGER

In the case of an unsigned integer, only positive numbers can be stored. In this datatype, all the 32 bits will be reserved for the storage of data.

SIGNED INTEGER
An ‘int’ is actually 1 sign bit + 31 data bits, that is 31 bits are available for storing the number being assigned to a ‘int’ type variable and 1 bit is reserved for maintaining the sign of the number which is either + or – . 

			float   -->4 bytes
			double  -->8 bytes

-----------------------------------------------------------
format specifiers
===============
				%c  -->char
				%d   -->int
				%f  -->float
				%lf   -->double
				%x   ->hexadecimal
				%o   -->octal
  
bits op info:-
------------
find number of bits required to represent an integer in memory-->bits = sizeof(int) * 8;//for performing ops in bit format

msb/lsb -->msb = 1 << (bits - 1);//mask em at either ends.for msb left shift bits-1 times.

if((num & msb) == 1)-->msb

Rotating bits of a number to left, means shifting all bits to left and pushing the dropped MSB bit to LSB Bit.

Rotating bits of a number to right, means shifting all bits to right and pushing the dropped LSB Bit to MSB Bit.  

Logic:-dropping bit s are saved for masking and shift the num in any direction the required number of times.

// C++ code to rotate bits of number

	#include<iostream>

	using namespace std;
	#define INT_BITS 32
	class gfg
	{

	/*Function to left rotate n by d bits*/
	public:
	int leftRotate(int n, unsigned int d)
	{

		/* In n<<d, last d bits are 0. To
		put first 3 bits of n at
		last, do bitwise or of n<<d
		with n >>(INT_BITS - d) */
		return (n << d)|(n >> (INT_BITS - d));
	}

	/*Function to right rotate n by d bits*/
	int rightRotate(int n, unsigned int d)
	{
		/* In n>>d, first d bits are 0.
		To put last 3 bits of at
		first, do bitwise or of n>>d
		with n <<(INT_BITS - d) */
		return (n >> d)|(n << (INT_BITS - d));
	}
	};

	int main()
	{
		gfg g;
		int n = 16;
		int d = 2;
		cout << "Left Rotation of " << n <<
				" by " << d << " is ";
		cout << g.leftRotate(n, d);
		cout << "\nRight Rotation of " << n <<
				" by " << d << " is ";
		cout << g.rightRotate(n, d);
		getchar();
	}

The left-shift of 1 by i is equivalent to 2 raised to power i. 

The right-shift of 1 by i is equivalent to 2 devided to power i ??please verify once 

An expression used to swaps the nibbles.

like if num is 0011 0010 then after the above expression it will be 0010 0011.

 • Steps 4:
  num = (((num & 0xff00ff00) >> 8) | ((num & 0x00ff00ff) << 8));

This statement uses to swap the bytes of an integer.

Let num is 00001000 00001100, after the above expression, it will be 00001100 00001000.

 • Steps 5:
  ((num >> 16) | (num << 16));

=============================================================================================
# Linux system programming

# Shared memory
- Two or more process can access the common memory. And communication is done via this shared memory where changes made by one process can be viewed by another process.

SYSTEM CALLS USED ARE:



- **ftok()**: is use to generate a unique key.

- **shmget()**: int shmget(key_t,size_tsize,intshmflg); upon successful completion, shmget() returns an identifier for the shared memory segment.

- **shmat()**: Before you can use a shared memory segment, you have to attach yourself to it, using shmat(). 

       void *shmat(int shmid ,void *shmaddr ,int shmflg);
      *shmid* is shared memory id. 
      *shmaddr* specifies specific address to use but we should set it to zero and, OS will automatically choose the address.

- **shmdt()**: When you’re done with the shared memory segment, your program should detach itself from it using shmdt(). 

      int shmdt(void *shmaddr);

- **shmctl()**: when you detach from shared memory,it is not destroyed. So, to destroy
- **shmctl()** is used. 

      shmctl(int shmid,IPC_RMID,NULL);



The problem with pipes, fifo and message queue – is that for two process to exchange information. The information has to go through the kernel.

- Server reads from the input file.
- The server writes this data in a message using either a pipe, fifo or message queue.
- The client reads the data from the IPC channel,again requiring the data to be copied from kernel’s IPC buffer to the client’s buffer.
- Finally the data is copied from the client’s buffer.
- A total of four copies of data are required (2 read and 2 write). So, shared memory provides a way by letting two or more processes share a memory segment. With Shared Memory the data is only copied twice – from input file into shared memory and from shared memory to the output file.

# SHARED MEMORY FOR WRITER PROCESS

       #include <iostream>
       #include <sys/ipc.h>
       #include <sys/shm.h>
       #include <stdio.h>
       using namespace std;

       int main()
       {
        // ftok to generate unique key
        key_t key = ftok("shmfile",65);

        // shmget returns an identifier in shmid
        int shmid = shmget(key,1024,0666|IPC_CREAT);

        // shmat to attach to shared memory
        char *str = (char*) shmat(shmid,(void*)0,0);

        cout<<"Write Data : ";
        gets(str);

        printf("Data written in memory: %s\n",str);

        //detach from shared memory
        shmdt(str);

        return 0;
       }
# SHARED MEMORY FOR READER PROCESS
     #include <iostream>
     #include <sys/ipc.h>
     #include <sys/shm.h>
     #include <stdio.h>
     using namespace std;

     int main()
     {
      // ftok to generate unique key
      key_t key = ftok("shmfile",65);

      // shmget returns an identifier in shmid
      int shmid = shmget(key,1024,0666|IPC_CREAT);

      // shmat to attach to shared memory
      char *str = (char*) shmat(shmid,(void*)0,0);

      printf("Data read from memory: %s\n",str);

      //detach from shared memory
      shmdt(str);

      // destroy the shared memory
      shmctl(shmid,IPC_RMID,NULL);

      return 0;
     }

# Message Queues
A message queue is a linked list of messages stored within the kernel and identified by a message queue identifier. 
- A new queue is created or an existing queue opened by **msgget()**. 
- New messages are added to the end of a queue by **msgsnd()**. 
- when the message is added to a queue. Messages are fetched from a queue by **msgrcv()**.
- we can fetch messages based on their type field.Each message is given an identification or type so that processes can select the appropriate message.

System calls used for message queues: 
 

- **ftok()**: is use to generate a unique key.
- **msgget()**: either returns the message queue identifier for a newly created message queue or returns the identifiers for a queue which exists with the same key value.
- **msgsnd()**: Data is placed on to a message queue by calling msgsnd().
- **msgrcv()**: messages are retrieved from a queue.
- **msgctl()**: It performs various operations on a queue. Generally it is use to destroy message queue.

# MESSAGE QUEUE FOR WRITER PROCESS 
         // C Program for Message Queue (Writer Process)
         #include <stdio.h>
         #include <sys/ipc.h>
         #include <sys/msg.h>
         #define MAX 10

         // structure for message queue
         struct mesg_buffer {
          long mesg_type;
          char mesg_text[100];
         } message;

         int main()
         {
          key_t key;
          int msgid;

          // ftok to generate unique key
          key = ftok("progfile", 65);

          // msgget creates a message queue
          // and returns identifier
          msgid = msgget(key, 0666 | IPC_CREAT);
          message.mesg_type = 1;

          printf("Write Data : ");
          fgets(message.mesg_text,MAX,stdin);

          // msgsnd to send message
          msgsnd(msgid, &message, sizeof(message), 0);

          // display the message
          printf("Data send is : %s \n", message.mesg_text);

          return 0;
         }
# MESSAGE QUEUE FOR READER PROCESS
     // C Program for Message Queue (Reader Process)
     #include <stdio.h>
     #include <sys/ipc.h>
     #include <sys/msg.h>

     // structure for message queue
     struct mesg_buffer {
      long mesg_type;
      char mesg_text[100];
     } message;

     int main()
     {
      key_t key;
      int msgid;

      // ftok to generate unique key
      key = ftok("progfile", 65);

      // msgget creates a message queue
      // and returns identifier
      msgid = msgget(key, 0666 | IPC_CREAT);

      // msgrcv to receive message
      msgrcv(msgid, &message, sizeof(message), 1, 0);

      // display the message
      printf("Data Received is : %s \n",
          message.mesg_text);

      // to destroy the message queue
      msgctl(msgid, IPC_RMID, NULL);

      return 0;
     }
# fork() and pipe()
P1 takes a string and passes it to P2. P2 concatenates the received string with another string without using string function and sends it back to P1 for printing.
Examples:

Other string is: forgeeks.org

Input  : www.geeks
Output : www.geeksforgeeks.org
        
Input :  www.practice.geeks
Output : practice.geeksforgeeks.org
# Explanation:

- To create child process we use fork(). 
   - fork() returns :

       - <0 fail to create child (new) process
       - =0 for child process
       - >0 i.e process ID of the child process to the parent process. When >0 parent process will execute.

- **pipe()** is used for passing information from one process to another. pipe() is unidirectional therefore, for two-way communication between processes, two pipes can be set up, one for each direction.

Example:

     int fd[2];
     pipe(fd);
     fd[0]; //-> for using read end
     fd[1]; //-> for using write end
 
Inside Parent Process : 
- We firstly close the reading end of first pipe (fd1[0]) then write the string though writing end of the pipe (fd1[1]).
- Now parent will wait until child process is finished. 
-  After the child process, parent will close the writing end of second pipe(fd2[1]) and read the string through reading end of pipe (fd2[0]).

Inside Child Process : 
- Child reads the first string sent by parent process by closing the writing end of pipe (fd1[1]) and 
- after reading concatenate both string and passes the string to parent process via fd2 pipe and will exit.

       // C program to demonstrate use of fork() and pipe()
       #include<stdio.h>
       #include<stdlib.h>
       #include<unistd.h>
       #include<sys/types.h>
       #include<string.h>
       #include<sys/wait.h>

       int main()
       {
        // We use two pipes
        // First pipe to send input string from parent
        // Second pipe to send concatenated string from child

        int fd1[2]; // Used to store two ends of first pipe
        int fd2[2]; // Used to store two ends of second pipe

        char fixed_str[] = "forgeeks.org";
        char input_str[100];
        pid_t p;

        if (pipe(fd1)==-1)
        {
         fprintf(stderr, "Pipe Failed" );
         return 1;
        }
        if (pipe(fd2)==-1)
        {
         fprintf(stderr, "Pipe Failed" );
         return 1;
        }

        scanf("%s", input_str);
        p = fork();

        if (p < 0)
        {
         fprintf(stderr, "fork Failed" );
         return 1;
        }

        // Parent process
        else if (p > 0)
        {
         char concat_str[100];

         close(fd1[0]); // Close reading end of first pipe

         // Write input string and close writing end of first
         // pipe.
         write(fd1[1], input_str, strlen(input_str)+1);
         close(fd1[1]);

         // Wait for child to send a string
         wait(NULL);

         close(fd2[1]); // Close writing end of second pipe

         // Read string from child, print it and close
         // reading end.
         read(fd2[0], concat_str, 100);
         printf("Concatenated string %s\n", concat_str);
         close(fd2[0]);
        }

        // child process
        else
        {
         close(fd1[1]); // Close writing end of first pipe

         // Read a string using first pipe
         char concat_str[100];
         read(fd1[0], concat_str, 100);

         // Concatenate a fixed string with it
         int k = strlen(concat_str);
         int i;
         for (i=0; i<strlen(fixed_str); i++)
          concat_str[k++] = fixed_str[i];

         concat_str[k] = '\0'; // string ends with '\0'

         // Close both reading ends
         close(fd1[0]);
         close(fd2[0]);

         // Write concatenated string and close writing end
         write(fd2[1], concat_str, strlen(concat_str)+1);
         close(fd2[1]);

         exit(0);
        }
       }
https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/

# FIFO/Named Pipes

a named pipe appears as a file and generally processes attach to it for inter-process communication. 
A FIFO file is a special kind of file on the local storage which allows two or more processes to communicate with each other by reading/writing to/from this file.

**mkfifo()** makes a FIFO special file with name **pathname**. Here **mode** specifies the FIFO’s permissions. 
It is modified by the process’s umask in the usual way: the permissions of the created file are (mode & ~umask).

	int mkfifo(const char *pathname, mode_t mode);

Example Programs to illustrate the named pipe: -There are two programs that use the same FIFO. 

Program 1 writes first, then reads. 

program 2 reads first, then writes. They both keep doing it until terminated.

Program 1-->writes

	// C program to implement one side of FIFO
	// This side writes first, then reads
	#include <stdio.h>
	#include <string.h>
	#include <fcntl.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <unistd.h>

	int main()
	{
		int fd;

		// FIFO file path
		char * myfifo = "/tmp/myfifo";

		// Creating the named file(FIFO)
		// mkfifo(<pathname>, <permission>)
		mkfifo(myfifo, 0666);

		char arr1[80], arr2[80];
		while (1)
		{
			// Open FIFO for write only
			fd = open(myfifo, O_WRONLY);

			// Take an input arr2ing from user.
			// 80 is maximum length
			fgets(arr2, 80, stdin);

			// Write the input arr2ing on FIFO
			// and close it
			write(fd, arr2, strlen(arr2)+1);
			close(fd);

			// Open FIFO for Read only
			fd = open(myfifo, O_RDONLY);

			// Read from FIFO
			read(fd, arr1, sizeof(arr1));

			// Print the read message
			printf("User2: %s\n", arr1);
			close(fd);
		}
		return 0;
	}

Program2 -->reads

	// C program to implement one side of FIFO
	// This side reads first, then reads
	#include <stdio.h>
	#include <string.h>
	#include <fcntl.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <unistd.h>

	int main()
	{
		int fd1;

		// FIFO file path
		char * myfifo = "/tmp/myfifo";

		// Creating the named file(FIFO)
		// mkfifo(<pathname>,<permission>)
		mkfifo(myfifo, 0666);

		char str1[80], str2[80];
		while (1)
		{
			// First open in read only and read
			fd1 = open(myfifo,O_RDONLY);
			read(fd1, str1, 80);

			// Print the read string and close
			printf("User1: %s\n", str1);
			close(fd1);

			// Now open in write mode and write
			// string taken from user.
			fd1 = open(myfifo,O_WRONLY);
			fgets(str2, 80, stdin);
			write(fd1, str2, strlen(str2)+1);
			close(fd1);
		}
		return 0;
	}

# Pthread

To execute the c file, we have to use the -pthread or -lpthread in the command line while compiling the file.

cc -pthread file.c or
cc -lpthread file.c

The functions defined in the pthreads library include:

**pthread_create**: used to create a new thread
Syntax:

int **pthread_create**(pthread_t * thread, 
                   const pthread_attr_t * attr, 
                   void * (*start_routine)(void *), 
                   void *arg);
Parameters:

	- thread: pointer to an unsigned integer value that returns the thread id of the thread created.

	- attr: pointer to a structure that is used to define thread attributes like detached state, scheduling policy, stack address, etc. Set to NULL for default thread attributes.

	- start_routine: pointer to a subroutine that is executed by the thread. The return type and parameter type of the subroutine must be of type void *. 
	The function has a single attribute but if multiple values need to be passed to the function, a struct must be used.

	- arg: pointer to void that contains the arguments to the function defined in the earlier argument

- **pthread_exit**: used to terminate a thread

Syntax:

**void pthread_exit(void *retval)**;

Parameters: This method accepts a mandatory parameter retval which is the pointer to an integer that stores the return status of the thread terminated. The scope of this variable must be global so that any thread waiting to join this thread may read the return status.

**pthread_join**: used to wait for the termination of a thread.

Syntax:

int **pthread_join**(pthread_t th, void * *thread_return);

Parameter: This method accepts following parameters:

- th: thread id of the thread for which the current thread waits.

- thread_return: pointer to the location where the exit status of the thread mentioned in th is stored.

- **pthread_self**: used to get the thread id of the current thread.

Syntax:

pthread_t **pthread_self**(void);

- **pthread_equal**: compares whether two threads are the same or not. If the two threads are equal, the function returns a non-zero value otherwise zero.

Syntax:

int **pthread_equal**(pthread_t t1, pthread_t t2);

Parameters: This method accepts following parameters:

t1: the thread id of the first thread

t2: the thread id of the second thread

- **pthread_cancel**: used to send a cancellation request to a thread

Syntax:

int **pthread_cancel**(pthread_t thread);

Parameter: This method accepts a mandatory parameter thread which is the thread id of the thread to which cancel request is sent.

- **pthread_detach**: used to detach a thread. A detached thread does not require a thread to join on terminating. 

The resources of the thread are automatically released after terminating if the thread is detached.

Syntax:

int **pthread_detach**(pthread_t thread);

Parameter: This method accepts a mandatory parameter thread which is the thread id of the thread that must be detached.

Example: A simple implementation of threads may be as follows:


	// C program to show thread functions

	#include <pthread.h>
	#include <stdio.h>
	#include <stdlib.h>

	void* func(void* arg)
	{
		// detach the current thread
		// from the calling thread
		pthread_detach(pthread_self());

		printf("Inside the thread\n");

		// exit the current thread
		pthread_exit(NULL);
	}

	void fun()
	{
		pthread_t ptid;

		// Creating a new thread
		pthread_create(&ptid, NULL, &func, NULL);
		printf("This line may be printed"
			" before thread terminates\n");

		// The following line terminates
		// the thread manually
		// pthread_cancel(ptid);

		// Compare the two threads created
		if(pthread_equal(ptid, pthread_self())
			printf("Threads are equal\n");
		else
			printf("Threads are not equal\n");

		// Waiting for the created thread to terminate
		pthread_join(ptid, NULL);

		printf("This line will be printed"
			" after thread ends\n");

		pthread_exit(NULL);
	}

	// Driver code
	int main()
	{
		fun();
		return 0;
	}


https://www.geeksforgeeks.org/multiplication-of-matrix-using-threads/

https://www.geeksforgeeks.org/binary-search-using-pthread/

# Thread synchronization

Thread Synchronization Problems Ex:-

	#include <pthread.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>

	pthread_t tid[2];
	int counter;

	void* trythis(void* arg)
	{
		unsigned long i = 0;
		counter += 1;
		printf("\n Job %d has started\n", counter);

		for (i = 0; i < (0xFFFFFFFF); i++)
			;
		printf("\n Job %d has finished\n", counter);

		return NULL;
	}

	int main(void)
	{
		int i = 0;
		int error;

		while (i < 2) {
			error = pthread_create(&(tid[i]), NULL, &trythis, NULL);
			if (error != 0)
				printf("\nThread can't be created : [%s]", strerror(error));
			i++;
		}

		pthread_join(tid[0], NULL);
		pthread_join(tid[1], NULL);

		return 0;
	}
Output :

	Job 1 has started
	Job 2 has started
	Job 2 has finished
	Job 2 has finished
- The log ‘Job 2 has started’ is printed just after ‘Job 1 has Started’ so it can easily be concluded that while thread 1 was processing the scheduler scheduled the thread 2.
- we can say that lack of **synchronization** between the threads while using the shared resource ‘**counter**’ caused the problems.
- A **Mutex** is a lock that we set before using a shared resource and release after using it.
- even **if thread 2 is scheduled while thread 1 was not done accessing the shared resource and the code is locked by thread 1 using mutexes** ,then thread 2 cannot even access that region of code.
- Now if **scheduler decides to do a context switch**, then all the other threads which are ready to execute the same region are unblocked.
- Only one of all the threads would make it to the execution but **if this thread tries to execute the same region of code that is already locked then it will again go to sleep**.

int **pthread_mutex_init**(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr) 
- Creates a mutex, referenced by mutex, with attributes specified by attr. 
If attr is NULL, the default mutex attribute (NONRECURSIVE) is used.

Returned value
- pthread_mutex_init() returns 0 --> If successful ,and the state of the mutex becomes initialized and unlocked.
- pthread_mutex_init() returns -1.--> If unsuccessful.

int **pthread_mutex_lock**(pthread_mutex_t *mutex) : Locks a mutex object, which identifies a mutex. If the mutex is already locked by another thread, the thread waits for the mutex to become available. 

Returned value
- pthread_mutex_lock() returns 0-->If successful.
- pthread_mutex_lock() returns -1.-->If unsuccessful. 

- **When the mutex has the attribute of recursive**, the use of the lock may be different. When this kind of mutex is locked multiple times by the same thread, 

then a count is incremented and no waiting thread is posted. **The owning thread must call pthread_mutex_unlock() the same number of times to decrement the count to zero.**

**The mutex can be unlocked and destroyed** by calling following two functions:-
- int **pthread_mutex_unlock**(pthread_mutex_t *mutex) : Releases a mutex object
- int **pthread_mutex_destroy**(pthread_mutex_t *mutex) : Deletes a mutex object

EX:-

		#include <pthread.h>
		#include <stdio.h>
		#include <stdlib.h>
		#include <string.h>
		#include <unistd.h>

		pthread_t tid[2];
		int counter;
		pthread_mutex_t lock;

		void* trythis(void* arg)
		{
			pthread_mutex_lock(&lock);

			unsigned long i = 0;
			counter += 1;
			printf("\n Job %d has started\n", counter);

			for (i = 0; i < (0xFFFFFFFF); i++)
				;

			printf("\n Job %d has finished\n", counter);

			pthread_mutex_unlock(&lock);

			return NULL;
		}

		int main(void)
		{
			int i = 0;
			int error;

			if (pthread_mutex_init(&lock, NULL) != 0) {
				printf("\n mutex init has failed\n");
				return 1;
			}

			while (i < 2) {
				error = pthread_create(&(tid[i]),
									NULL,
									&trythis, NULL);
				if (error != 0)
					printf("\nThread can't be created :[%s]",
						strerror(error));
				i++;
			}

			pthread_join(tid[0], NULL);
			pthread_join(tid[1], NULL);
			pthread_mutex_destroy(&lock);

			return 0;
		}
======================================================================================================================
# socket[Software equipment for network data transmission]
int socket(int domain, int type, int protocol);

type (socket type, data transmission method)



name | Socket |
--- | --- | 
SOCK_STREAM |Stream format socket TCP| 
SOCK_DGRAM   |	Datagram format socket UDP |

- SOCK_STREAM (complete delivery of data, tcp sending data, with ack)

- Data will not disappear during transmission;
- Data is transmitted in order;
- The sending and receiving of data are not synchronized (some tutorials also say that "there is no data boundary"). It is mainly because the receiver does not know the boundary between the messages, and does not know how many bytes of data are extracted at one time; 
- sending can be batched 30+50+20, receiving and putting 100 at a time to take away, or 10 10 A fetch, etc. it is like a conveyor belt , the http protocol used by the browser is based on this, to ensure the complete delivery of the data, there is a reply ack.

- SOCK_DGRAM (efficiency and real-time)

- Emphasize fast transmission rather than transmission sequence;
- The transmitted data may be lost or damaged;
- Limit the size of data transmitted each time;
- The sending and receiving of data is synchronized (some tutorials also call "there is a data boundary").
Just like express delivery, ensure fast delivery , such as QQ chat and voice

protocol (protocol information used in communication between computers)
Usually 0, 

the first two parameters can be determined;
Unless there are multiple protocols with the same data transmission method in the same protocol family (? There is no example in the book~)

sockaddr_in

	struct sockaddr_in   
	{
	   sa_family_t	  sin_family; //Address family
	   uint16_t	  sin_port; //16-bit TCP/UDP port number
	   struct in_addr sin_addr; //32-bit IP address
	   char 	  sin_zero[8];//Not applicable
	};


sin_port

A computer can provide multiple network services at the same time, and the port number is to distinguish different network services

sin_addr

At present, IPv4 addresses are widely used, and its resources are very limited. It is unrealistic for a computer to have an IP address. It is often a local area network that has an IP address.

INADDR_ANY, used for the server, automatically obtains the IP address of the computer running the server (client side, unless it has some server-side functions, it will not be used)

1.3, bind()

The server is used to assign an IP address and port number to the socket. Only in this way, the data flowing through the IP address and port can be handed over to the socket for processing

int bind(int sock, struct sockaddr *addr, socklen_t addrlen);  //Linux

int bind(SOCKET sock, const struct sockaddr *addr, int addrlen);  //Windows

sockfd (socket file descriptor, the return value of socket creation)

myaddr (a structure containing the address information of the created socket)

addrlen (length of myaddr)

1.4, connect()
Used to establish a connection, used for TCP

int connect(int sock, struct sockaddr *serv_addr, socklen_t addrlen);  //Linux

int connect(SOCKET sock, const struct sockaddr *serv_addr, int addrlen);  //Windows

	sockfd (socket file descriptor, the return value of socket creation)
	myaddr (a structure containing the address information of the created socket)
	addrlen (length of myaddr)

The above is common to both, the following analysis is different

2. TCP
Create the server first and reach listen(), this is the client can connect to the connect() server; before the client calls connect(), the server may call accept() first. At this time, the server enters a blocking state;

2.1, listen()

Let the socket enter the passive monitoring state, then the client can enter the connection request that can be sent, that is, call the connect function

int listen(int sock, int backlog);  //Linux

int listen(SOCKET sock, int backlog);  //Windows

	sock (socket file descriptor)
	backlog (the length of the waiting queue for connection requests, such as 5, then up to 5 connection requests will enter the queue)

2.2, accept()

Respond to client requests

int accept(int sock, struct sockaddr *addr, socklen_t *addrlen);  //Linux

SOCKET accept(SOCKET sock, struct sockaddr *addr, int *addrlen);  //Windows

	sock (socket file descriptor)
	myaddr (a structure containing customer address information)
	addrlen (length of myaddr)
2.3, read, write

Because TCP needs to be connected to communicate , the address information of the other party is not needed when sending and receiving data

- To write data, just write the data into the buffer (similar to a queue). When will it be sent and how much data will be sent, there is a judgment rule, so the receiver does not know the beginning and the end~

- Read data is also read from the cache

- When the return value of the read() function is 0, it means that the opposite end has closed the socket. At this time, the socket must also be closed, otherwise it will cause the socket to leak. Under the netstat command, if there is a socket in the closewait state, the socket is leaked.

ssize_t write(int fd, const void *buf, size_t nbytes);//Linux

ssize_t read(int fd, void *buf, size_t nbytes);//Linux

int send(SOCKET sock, const char *buf, int len, int flags);//Windows

int recv(SOCKET sock, char *buf, int len, int flags);//Windows

	sock socket
	buf is the buffer address of the data to be sent
	len is the number of bytes of data to be sent
	flags are options when sending data, generally 0 or NULL

How to solve the tcp sticky package problem

We can make the information into json, the front is the basic information of the package (open, not encrypted), and the back is the content of the communication protocol to be sent, and the content of the protocol can be encrypted

Server

	#define TCP_LISTEN_PORT  9190
	#define BUF_SIZE 30

	static struct sockaddr_in serv_addr;
	static struct sockaddr_in clnt_addr;
	int tcp_socket_fd = -1;
	void TCP_Server_Socket_Init(void)
	{
		tcp_socket_fd  = socket(PF_INET, SOCK_STREAM, 0);
	    if(-1 == tcp_socket_fd )
	    {
		printf("socket() error\n");
		return;
	    }

	    memset(&serv_addr, 0, sizeof(serv_addr));

	    serv_addr.sin_family = AF_INET;
	    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	    serv_addr.sin_port = htons(TCP_LISTEN_PORT); 

		if(-1 == bind(tcp_socket_fd , (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
		{
		    printf("bind() error\n");
		return;
		}  

		if(-1 == listen(tcp_socket_fd , 5)
		{
		    printf("listen() error\n");
		return;
		}  
	}


	int main()
	{
	    int fd_ret = 0;
	    struct timeval timeout;
	    fd_set fb_sockset;

		char message[BUF_SIZE];
		int srt_len;
		int clnt_socket_fb;
		socklen_t clnt_adr_sz;

		TCP_Server_Socket_Init();
		clnt_adr_sz = sizeof(clnt_adr);
		while(1)
		{
			FD_ZERO(&fb_sockset);
			FD_SET(tcp_socket_fd ,&fb_sockset);
			timeout.tv_sec=2;
			timeout.tv_usec=0;

			fd_ret = select(tcp_socket_fd +1, &fb_sockset, NULL, NULL, &timeout);
			if(fd_ret > 0)
			{
				clnt_socket_fb= accept(tcp_socket_fd ,  (struct sockaddr*)&clnt_addr, &clnt_adr_sz );
				if(-1 == clnt_socket_fb)
				{
					printf("accept() error\n");
				}
				else
				{
					while(srt_len=recv(clnt_socket_fb, message, BUF_SIZE, 0)!=0)
					{
						send(clnt_socket_fb, message, srt_len, 0);
						printf("Message from clent: %s",message);
						close(clnt_socket_fb);
					}
				}
			}
		}
		close(tcp_socket_fd );
		return 0;
	}


Client

	#define TCP_LISTEN_PORT  9190
	#define BUF_SIZE 30

	static struct sockaddr_in serv_addr;
	static struct sockaddr_in clnt_addr;
	int tcp_socket_fd = -1;
	void TCP_Client_Socket_Init(void)
	{
		tcp_socket_fd = socket(PF_INET, SOCK_STREAM, 0);
	    if(-1 == tcp_socket_fd )
	    {
		printf("socket() error\n");
		return;
	    }

	    memset(&clnt_addr, 0, sizeof(clnt_addr));

	    clnt_addr.sin_family = AF_INET;
	    clnt_addr.sin_addr.s_addr = inet_addr("192.168.0.1");//方式1
	    clnt_addr.sin_addr.s_addr = htonl(0xC0A80001);//方式2
	    clnt_addr.sin_port = htons(TCP_LISTEN_PORT ); 

		if(-1 == connect(tcp_socket_fd, (struct sockaddr*)&clnt_addr, sizeof(clnt_addr))))
		{
			printf("connect() error\n");
		}
		else
		{
			printf("connected...............\n");
		}
	}


	int main()
	{
		char message[]=“Nice.to.meet.you!”;
		int srt_len;
		socklen_t serv_adr_sz;
		TCP_Client_Socket_Init();
		serv_adr_sz = sizeof(serv_addr);
		while(1)
		{
			send(tcp_socket_fd , message, strlen(message), 0, );
			str_lent = recv(tcp_socket_fd , message, BUF_SIZE -1, 0);
			printf("Message from server: %s",message);
		}
		close(tcp_socket_fd);
		return 0;
	}


3. UDP

3.1, read, write
Because UDP can communicate without a connection, the address information of the other party is needed to send and receive data.

ssize_t sendto(int sock, const void *buf, size_t nbytes, int flags, struct sockaddr *to, socklen_t addrlen);//Linux

ssize_t recvfrom(int sock, void *buf, size_t nbytes, int flags, struct sockaddr *to, socklen_t addrlen);//Linux

int send(SOCKET sock, const char *buf, int len, int flags);//Windows

int recv(SOCKET sock, char *buf, int len, int flags);//Windows


sock socket
	buf is the buffer address of the data to be sent
	len is the number of bytes of data to be sent
	flags are options when sending data, generally 0 or NULL

to the structure of the destination address information
length of addrlen to

Server

	#define UDP_LISTEN_PORT  9190
	#define BUF_SIZE 30

	static struct sockaddr_in serv_addr;
	static struct sockaddr_in clnt_addr;
	int udp_socket_fd = -1;
	void UDP_Server_Socket_Init(void)
	{
		udp_socket_fd = socket(PF_INET, SOCK_DGRAM, 0);
	    if(-1 == udp_socket_fd )
	    {
		printf("socket() error\n");
		return;
	    }

	    memset(&serv_addr, 0, sizeof(serv_addr));

	    serv_addr.sin_family = AF_INET;
	    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	    serv_addr.sin_port = htons(UDP_LISTEN_PORT ); 

		if(-1 == bind(udp_socket_fd , (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
		{
		    printf("bind() error\n");
		return;
		}  
	}


	int main()
	{
		char message[BUF_SIZE];
		int srt_len;
		socklen_t clnt_adr_sz;
		UDP_Server_Socket_Init();
		clnt_adr_sz = sizeof(clnt_adr);
		while(1)
		{
			str_lent = recvfrom(udp_socket_fd , message, BUF_SIZE, 0,  (struct sockaddr*)&clnt_addr, &clnt_adr_sz );
			sendto(udp_socket_fd, message, BUF_SIZE, 0,  (struct sockaddr*)&clnt_addr, clnt_adr_sz );

			printf("Message from client: %s",message);
		}
		close(udp_socket_fd);
		return 0;
	}

Client

	#define UDP_LISTEN_PORT  9190
	#define BUF_SIZE 30

	static struct sockaddr_in serv_addr;
	static struct sockaddr_in clnt_addr;
	int udp_socket_fd = -1;
	void UDP_Client_Socket_Init(void)
	{
		udp_socket_fd = socket(PF_INET, SOCK_DGRAM, 0);
	    if(-1 == udp_socket_fd )
	    {
		printf("socket() error\n");
		return;
	    }

	    memset(&clnt_addr, 0, sizeof(clnt_addr));

	    clnt_addr.sin_family = AF_INET;
	    clnt_addr.sin_addr.s_addr = inet_addr("192.168.0.1");//方式1
	    clnt_addr.sin_addr.s_addr = htonl(0xC0A80001);//方式2
	    clnt_addr.sin_port = htons(UDP_LISTEN_PORT ); 
	}


	int main()
	{
		char message[]=“Nice.to.meet.you!”;
		int srt_len;
		socklen_t serv_adr_sz;

		UDP_Client_Socket_Init();
		serv_adr_sz = sizeof(serv_addr);
		while(1)
		{
			sendto(udp_socket_fd, message, strlen(message), 0,  (struct sockaddr*)&clnt_addr, sizeof(clnt_addr) );
			str_lent = recvfrom(udp_socket_fd , message, strlen(message), 0,  (struct sockaddr*)&clnt_addr, &serv_adr_sz);
			printf("Message from server: %s",message);

		}
		close(udp_socket_fd);
		return 0;
	}

https://blog.csdn.net/u013095415/article/details/81478806?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-2.control

======================================================================================================================
# C++
order of discussion :-

- Define C++?
- What is a class in C++?
- What is an object?
- What is the difference between C and C++?
- Why is the size of an empty class not zero in C++?
  
  this is because that would make it possible for two distinct objects to have the same memory location. 
  This is the reason behind the concept that even an empty class must have a size at least 1.
- Why use access modifiers in C++?
- What are C++ access modifiers?
- What are the differences between a C++ struct and C++ class?
- What are the various OOPs concepts in C++?
- What is polymorphism in C++?
- What are the different types of polymorphism in C++?
- What is encapsulation?
- What Is Inheritance?
- What are the advantages of inheritance?
- What is an abstraction in C++? 
- What is a constructor?
- Is the default constructor exists in C++?
- Can a constructor throw an exception? How to handle the error when the constructor fails?
- What is the initializer list in C++?
- When do we use the Initializer List in C++?
-if at all there scenarios where initialization are not possible wth constructors then we can use initializers. 
- What is a copy constructor?
- When are copy constructors called in C++?
- Why copy constructor takes the parameter as a reference in C++?
- Why copy constructor argument should be const in C++?
- Can one constructor of a class call another constructor of the same class to initialize this object?
- Can a copy constructor accept an object of the same class as a parameter, in place of reference of the object? If No, why not possible?
- Are Constructors and destructors can declare as const?
- Can we make a copy constructor private?
- Can you explain the order of execution in the constructor initialization list?
- What is the difference between constructor and destructor?
- What is the conversion constructor?
- What is the difference between a copy constructor and an overloaded assignment operator?
- What is the conversion operator in C++?
- What is destructor in C++?
- When is the destructor called?
- Is it possible to overload the destructor of the class?
- Can I call the destructor explicitly?
- How destructors are different from a normal member function.
- When do we need to write a user-defined destructor?
- Why a class has only one destructor?
- Can we have a virtual destructor in C++?
- When to use virtual destructors?
- Can we have a virtual constructor in C++?
-  

--------------------------------------------------------------------------------------------------------------------------------------------------------------
# WiFI

so Wi-Fi is nothing but , it is just a market name of the standard IEEE 802.11 
so nowadays we are heading to our wireless network so the idea here it is just a lan but without wires so we

in wireless network we usually use unlicensed we use unlicensed frequency

of the ism ban and low-power, it is because to provide services in cheap and to provide service to the more people .
if we use unlicensed frequency if they are available free for free in the iSM band so it will be cheap to provide Wi-Fi services and low-power because
then we will be able to provide services with more number of people there are
various techniques and wireless network 802.11,Bluetooth and UWB and so on.
802.11 is Wi-Fi is a standard which provides standard of wireless LAN which cover two
layers physical layer and the data link layer fine .
so in this standard we have two kinds of services one is BSS basic service set ,the second is ESS extended services

what is BSS 
BSS is just a unit or a building block so we have multiple stations which can communicate with each other without any wires .so this form a basic building block these these piers these have without wires they can communicate with each other fine so this station can be mobile or stationary so this form a basic building
this station covers the range in this circle so this station can communicate wirelessly in this set so this form a basic building block or BSS in this we can have a optional centralized station also which we call as access point it is optional if we have an access point we call this architecture either Infrastructure architecture and the BSS without access point is called ad-hoc architecture 

so why do we have access point is if we have a centralized base station it became easy for us to communicate if we have a centralized Authority which can communicate with this station so it make it make us it makes easy to communicate 












so if you have access point we call it an infrastructure architecture otherwise it does up ad hoc architecture 

as it is a wireless network, the range of this device in which they can communicate is very less ,so the idea is to connect various BSS ,so that each station can communicate with a larger number of stations .

so what we do is we have the second type of services which we call an ESS extended services .it is nothing but a connection of various BSS 

but we will be able to connect these BSS only if we have an access point in that, fine so that why I was saying that if we have an access point it make us easy it make easier to communicate with a larger number of people.

so so what we do is we have multiple BSS, and all of these BSS have an access point ,and there are various stations .now my station can be a part of one or two BSS that is not a problem .now so this circle this is not one BSS and these nodes can communicate with each other violently .

but what if this node want to communicate with this node since this node cannot communicate with this node because it is outside it's strange so what we can do is all these access point are connected to each other with a wired network which we call as distributed system .

now this distributed system can be any wired line, 802.1 doesn't specify the staff the while and which we have to use here it can be Ethernet also anything which you want to use here 

so if this node want to communicate with the station which  are in this rate which are in the range of this node it can communicate them with them directly otherwise if this node want to communicate with the other station which is outside stage it then it can communicate via access point .

now the advantagenof having a wired network here is that this wired lan can be connected to any server or hub or router or anything so in this way this node can have access to the whole of the network 

based on mobility, we have three types of station or node

one is no transition nodes 
BSS transition stations and 
the ESS transition 

so if a station has the capability to move inside its BSS only then we called it that station as a no transition station 

if a node or a station has capability to move to the other gases which are a part of the same ESS then that station will be called as BSS station 

BSS transition station means it can it can move within the BSS which are a part of the single ESS 

and if the station has capability to move outside its ESS also we call it an ESS transition station 

but while station move from one basis to the other or from one ESS through the other ESS via 802.11 doesn't guarantee that the connections will remain continual during the move so during the move the the connection can be disconnected but out of the move you will be able you will be again connected 

so this standard is fine to layer physical layer and data link layer in physical layer this standard has various specification so based on the encryption and encryption scheme and coding scheme or the multiplexing scheme we have various version of a 802.11 one a 2.8 or 2.11 a a 2 2.11 be a to do dot Vinci and 

datalink earlier we have two parts I'm a medium access control layer and the logic link layer control 
in the Mac layer we have two sub layers DCF distributed coordination function and the point coordination function 

so a 802.11 provide two kinds of services contention free services and the contention based services 
so contention free services are optional 

so distributed coordination function basically provide contention based services so this is compulsory 
but if we want to to have contention free services we can have a PCF running on top of DCM fine 

 let's consider a situation a station enter a network now this station can be in the range of various access point so to which access point this station can associate so so this station can associate itself with this access point as well as scan this access point 
 
 so the process or the technique by which the station associate itself to one of the access point within its reach is called scanning 
 
 whenever a station enter a network it has to it has to do scanning to associate itself with one with one of the access point or 
 
 suppose this station is initially associate itself with this access point and after some time it became unhappy with this access point 
 
 so then also it can associate itself with the other access point so this process called scanning by this station associate itself to one of the access point so 
 
 what is some steps we have to follow to do scanning is 
 
 first this station the sand of probe frame  and all of the access point which are in the range of this station will get this Probe frame 
 
 then all the access point which are in the reach of this station will send a probe response frame 
 
 after getting  all the probe response frame this station will associate itself with one of the  AP 
 
 so this station will select one of the AP and it will send Association request to that Access point 
 
 and this access point will send Association response frame to this station and the connection is built 
 
basically this is called active scanning why active because in this the station approaches the access points first and then access point reply 

but there is other kind of scanning which we call as passive scanning so time to time all the access point will send a beacon frame [becomes frame it is an advertisement by this access point which tells the capability its capability to each of this station] 

so by that this access point will send a beacon frame which address a advertises its capability to say to this station and 

then if this this station want to associate itself with this access point it can send the associate request frame to this access point so this type of scanning is called passive scanning 

now we talk about the first sub layer of mac layer which is DCF distributed coordination function 

so this is a compulsory service and this DCF provide contention based service 

what do you mean by contention based service 

it means multiple station contend  among each other to get access of the channel ,for that it uses csma/ca [carrier sensing multiple axis collision avoidance] not collision detection. unlike in wire we use csma/cd [carrier sensing multiple axis collision detection] 

actually collision detection is a better technique because of if we can detect the collision we can do RE-transmission and other thing ,but in the wireless Network we cannot do collision detection and that's why we have to go with collision avoidance 

there are reason in that envious Network we cannot use collision detection okay so if you remember that in Ethernet when we used csma/cd how do we detect the collision in that we have a wired LAN when the station is connected to this while it is sending the data it is also listening to the channel while sending the data it is also listening to the channel and if I mean if it lessens some other frequency it detects that there is self collision so in order to detect collision my station has to be full duplex that means it is capable of sending and receiving signal at the same time 

but since as I said that in Wi-Fi we want to provide services to the more customer and we want to be it to be cheap as cheap as possible 

so Wi-Fi operate at half duplex in wifi so if we want a station to be full duplex it will be more costly and  there for Wi-Fi operate sells half duplex 

so if I station sending our data on a channel it cannot listen at the same time so it's not possible for a station to detect a collision 

second reason by which we cannot able to detect collision is that in Wi-Fi as you see that 

this node is in the okay this node range in this BSS so the range of this station is this circle only so then when we want to detect collision every station must be aware of other station where which is sending the signal 

but in Wi-Fi if a standing the data and see sending the data is unaware that see standing the data because the strength of the signal will see sending the data the signal strength is less at a so when east anglia a sending the data while it reaches to see the signal strength is very low to detect collision so C will not be able to know that is also sending a data so this is another reason why we cannot do collision detection in Wi-Fi and the third reason is that there are problem like hidden terminal problem which we'll discuss later and due to that also will not be able to do collision detection in five five so we have to go for collision avoidance so in DS here we use csma/ca carrier sensing multiple access collision avoidance so what is the process now we have a source and we have a receiver or sender or receiver so since this s Ethernet we have carrier sensing multiple axes so when this sender or this source want to send some data to this receiver it first XJ it first sends the carrier if the channel is idle then it will send the data so as we have in the Ethernet in the starting of the carrier sense multiple access technique is the same we use back of time with a persistence strategy so initially if the station will set a back of time to zero and according to its purchases strategy it may be it may be one persistent non persistent or anything according to its persistence strategy it will sells the channel if the channel is idle if the channel is idle then this station will wait for some time which we call as d ifs time D ifs will distributed interframe space then after waiting for a D RDFS of an amount of time it send a control frame to receiver which we call as RDS request to send it the sender is asking the permission to receiver whether it it can send the data to this receiver or not after receiving the RDS signal from sender this it will wait throne is FS amount of time which we called as short interframe space and then it will reply with cts signal clear to send that means receiver is saying to the sender that it is ready to receive the data after getting the cts signal the sender again we'll wait for is FS amount of time and then it will send up data after receiving the data that is z1 will wait for is a per amount of time and will send an acknowledgment so let's look at more detail what we are doing is first of all source will sense the carrier whether the sir the sir whether the carrier is idle or not and for that it uses the same backup algorithm and the persistence strategy well it's fine that the pulse it find that the channel idle it wait for di FS amount of time so as you see after getting the channel idle also we are waiting for small period of time di FS here si FS here si FS why we are waiting for this period of time because now we have to do collision avoidance we have to take care that after sensing the channel also there may be chances for the collision so we are not thetaba sending the data or any signal we are waiting for some period of time and after that we are sending this control signal so you see that for collision avoidance which we are straightaway not sending the data packet first we are there is a kind of handshaking between the source and the receiver it first request whether the receiver is ready to take the data packet or not when did this kind of handshaking is done then only the source will send data packet to the receiver so this is another way how we are doing the collision avoidance fine so now you will be able to understand the sacrament clearly in this third the source will turn the back of algorithm and according to its purchases strategy it will self whether the channel is idle or not after sensing the channel is idle it will wait for the IFS amount of time which is distributed interframe space after waiting for this period of time it sent a request to send signal to the receiver and it started timer see in this video we have it how do we know whether the idea signal is received by the receiver or not they could be a collision in between for that well it send an RTS signal to the receiver it starts a timer so if the cts signal is received before time out then if the cts signal is reached is received before time out then only will process afterward otherwise what it will what we will do will increase the if the cts signal is not received before time out we will increase the back of time algorithm back of time and after again wait for that back of time and the processor again start if the CTS is signal is received before time out it means that the receiver is ready to take the data frame then also after receiving the CTS signal we are waiting for is FS amount of time again for collision avoidance after waiting for I guess FS amount of time this send a data frame and now again because of the collision we start a timer so if we get an acknowledgment before time out then it's a success and the packet is received if they don't get the acknowledgment before time on a what we'll do we'll increase the back of time and the process will start again in the meantime if we reach after increasing the back of time if the limit is reached we can't do anything and we have to abort the process so this is the whole picture by two Khalifa collision avoidance we are waiting for short period of time and we are finally or we are doing of handshaking between the sender and receiver before sending the data packet apart from collision avoidance waiting for this period of time is important because as I said in the Wi-Fi is Wi-Fi station our station are half duplex so it may need to change its set from signing straight to the receiving state so for that some amount of time is needed so for that also the before signing of data packet or before listening we wait for some period of time and these these timings are important for priority suppose two station there are two station which sells the channel at the same time so they both will find the channel idle so if the packet which have two so we can give priority to the station fine so see this is one sender and this is one receiver it may be maybe this sender is not sending to this receiver so this is one sender and this is one receiver this receiver has to send acknowledgement packet or cts signal and this sender has to send RTS or data packet or so if they both station sells the channel at the same time they both find they both will find it idle then this station because this station suppose it want to say it want to send RT signal it will wait for the amount of time and since this receiver want to send an acknowledgment or CTS it will wait for is FS amount of time so now if they want that if both if these two stations sense the channel at the same time and we want that this receiver should send the packet first because it is sending an acknowledgment or the clear to send signal so we want to give priority do priority to the acknowledgement packet so what we can do we can make di FS bigger than as ifs which is generally the case so di FS is bigger than as ifs so if sender or another receiver is accessing the channel at the same is sensing the channel at the same time because it will wait for more more amount of time receiver will succeed and it will send the acknowledgement packet first before sender can send the RTS packet fine so these intervals are very important to give the priority to the packets for avoiding the collision and to switch between the receiving state and the sending state for collision avoidance we also want when this station is sending some data to this station we want that other station should not send data in between to avoid collision so when this station is sending some data to this station how do other station know that they they don't have to send any data so for - then for that also this handshaking helps when this station is an RTS packet to this station the all the station which are in the range of this sort will hear this RTS packet and the in this RDS packet we have a field called duration field in which it is given the time amount for which this these two stations want to occupy the channel so when so when the other station which are in the range of this source read this RTS signal they know that the this amount of time the channel is going to occupy so they start a vector called nav network a location vector so whenever the other station here RTS or CTS and in in these packets there is a field called duration field in which the amount of time this transmission is going to take place the time is there so when the other station here this ideas packet it starts it's an every time this is a timer or we call it a network or location vector so for this period of time other station they are not going to say even sense the channel they will sit idle to avoid collision so we can add one more thing here that before sensing the channel before sensing the channel the station circuits and every timer if nav timer is expired then only it sells the channel otherwise it wait for its I Navy to get expired this is also meant for collision avoidance so in Wi-Fi we have two problems one is called hidden terminal problem and that is called exposed station problem so what is hidden terminal problem let's say there are three station B a and C the range of P is this circle and the range of C if this certain fine so let's consider a case when be bound to send some data to a sc1 to send some data to a big beep on to transmit some data to a and C also bound to transmit some data to a but B and C are hidden from each other they don't know about each other so when B is transmitting some data to a C don't know that is receiving some data from B so it so the both can start sending data at the same time and there will be apparition so this is called hidden terminal problem because B and C are unaware of each other they can they can both send data at the same time which will lead to collision fine so how does our this handshaking Lam this handshaking signals help in avoiding this problem is suppose B and C sends the channel at the same time fine and they both will find it idle so B so B will first send RTS signal to a and C also send RTS signal to a fine after after listening to the audio signal from both the side a decide whichever data heave on the packet first so he will send them suppose this is called RTS B then this is our DSC it will send CTS signal to B so these two station since they want to communicate with a they first send an RTS signal to a and a will decide that the which which request it it's why it want to accept it's end and CTS signal for that but friends a sanded CTS signal-c is also in the range suppose Avon to send CTS signal to be but says see you can also listen to the CIT C can also listen to the CTS signal with a send a CTA signal to be C can also listen to that signal so C know that there there may be some hidden know which want to communicate with a so it will stop signing the data so this hidden terminal problem can be solved by RTS and CTS signals okay so the Expo second problem we have is exposed station problem this is a Revere reverse of the previous problem in this problem station is not able to shine data even when channel is idle so let's consider one example this is one receiver this is one sender this is another sender and this is another receiver okay so let's consider this case these are four station the range of this station is from this station to this station the range of s1 is from this to this range from s2 is this and likewise you know currently s1 is transmitting data to r1 and now as to want to transmit some data to r2 but but huh since s2 is in the range of s1 when s1 is sending data to are one has to assume that it cannot send the data to r2 because someone in its range is san some data but if you see there is no problem as to can send data in to r2 because the channel is there is no interference as to can easily send data to our - it will not interfere with the transition over here but actually s2 will not send because it is hearing the transmission by s1 because as to is in the range of s1 s2 is in the range of s1 so when s1 is transmitting data to R 1 s 2 is listening to that so it assumed that it cannot send data to any station but it's not the case as - it can easily send data to r2 because there is no interference so this is called exposed station problem because of this transition this station is exposed to the entire network it is not able to transmit data to r2 so how to deal with this problem so the RTS and CTS signal which I told you about briefly can solve this problem Parshin only partially so when s1 want to communicate with r1 it first sell an RDS signal to r1 s1 first send an RTS signal to Arvin and since s within the range of s1 s2 will also listen to that RDS fine but when Arvind reply to ask fun with a serious signal then s2 will lost listen to it see tears because s2 is not in the range of r1 so for this transmission as to will receive the RTA signal but it will not receive the cts signal so by this as two cans as to can detect that this is an exposed station problem so it can send data to r2 there is no problem it can send data to r2 so RTS and CTS signal can solve this problem so with the help of ideal and CTS signal as to can detect the Expo station problem means that as to can detect that s1 is communicating with an OLE which is not interfering the node it he want to communicates with so what it will do it will send an RTS signal to our - but if s1 and s2 are not synchronized if s1 and s2 are not synchronized what do you mean by synchronized means if their data rate are different or their packet sizes are different so if s1 and s2 are not synchronized then when s to send an RTI a signal to r2 and r2 send a CTS signal to s2 this cts signal will not be able to listen s2 will not be able to listen this cts signal if s1 and s2 are not synchronized because this cts signal will be collide and if their data rate are different and packet size are different then as to will not be able to listen this cts signal and as to will not be able to communicate with our two so this is this problem is called expose station problem means even if the channel is idle s2 is not able to communicate with our two okay until now we talk about DSF sub layer of mac layer which provide contention based services and it is compulsory to provide but there are some circumstances in which I want to give priority priority to some station to get access to the channel suppose I am running only D a DCF protocol so in that all of these station are running csma/ca protocol so any of these station can get access to the channel but what if this station want to send some time-sensitive frames means it is important to get to get channel by this station first but if I am running only DS here there is no mean that time I can guarantee that this station will get the channel any of these station which are competing with with it can get access to the channel so for this this kind of scenario when I want to give priority to some station to get access of the channel what we do is centralized base station which is access point it run PCF PCF protocol which provides contention free services so this access point will pull among the station to which it want to give contention free services means it will pull this this station if if access point born that this station should deliver its pac at first without any contention it will pull this station and it will tell other station to keep quiet till that period of time so they will remain idle and only in that period only this station will send the frame so how access point run this algorithm is the same way so it will first sense a carrier if the channel is idle it will send it will wait for the IFS amount of time what is p NFS PCF interframe space it will fail for that period of time after that it will send up be conferring in the beacon frame there is an information that access point bond to both this station to provide contention free services so when access point sent the beacon frame in the whole VSS the station which is pulled it will be quiet but the other station we'll start there nav vector and every timer which is network allocation vector what that does mean well until the nav vector and every timer is there all the station will not even sell such an ax they even remain idle in that way this pole station will get chance to deliver its frame without any contention so when these others say these other station listen to the beacons frame they will start there lav vector after weakens frame the AP will wait for as ifs amount of time short interframe space after dad it recenter pool frame to make ready the pole station to send its frame after receiving the pooled polled frame pool frame by access point this pole station will wait for again wait for is s ifs amount of time short interframe space time and after that it will send an acknowledgment that it here it has successfully received the pole frame pole frame and it will send the data without any contention after receiving the data after receiving the data so this station will send data to the access point and which will be delivered to this wide land to the whole network after receiving the packet from this pole station the AP will wait for is s ifs amount of time and it will send an acknowledgment after this transmission is over it has to inform other station that the contention free services it want to provide it's over so access point this kind of contention free frame to all the station and when are these other station will receive the contention free contention free frame from the access point they will or they will end their nav vector and again the contention based services will start so this is that's why we use point coordination function just I said that we want to give priority to acknowledgement packet more than the data packet for that what we did is that s ifs timer is less than D ifs timer when a station want to send a data packet it has to wait for D ifs amount of time and when a station has to send a acknowledgement packet it has to wait for sa effects amount of time if s ifs amount of time is less than the ifs amount of time so if it happens that these both the station access the channel or sensor channel at the same time acknowledgement ACK the station which which is standing acknowledgment packet will get the channel first because s ifs is less than the offense and it will send the packet first so in this way we are giving priority to the acknowledgement packet more than the data packets in the same way what if access point want to start the contention free services and at the same time this station is also trying to send the packet so access point and these other station sends the channel at the same time and they both find channel idle but after sensing the channel ap will wait for P ifs amount of time and these other station will wait for D ifs amount of time if I want to give priority to the access point so that is the contention free services will start earlier P ifs has to be smaller than D ifs if in the saw okay so if other these are the other station and access point even if this as the channel at the same time access point will get access to the channel first because pif it is more than di FS in this way with time viselli uh we choose the timing of these this is space Sifl di fnn be ifs okay so this is all about the to sub layer of Mac in the Wi-Fi in Wi-Fi fragmentation is also allowed since the channel is noisy if my data packets are very long it is her then if the it is it got corrupted I have to Sri said II transmit the whole big bracket so it is better if I send the small packet so in Wi-Fi the fragmentation is allowed so we now talk about the frame format all these things which we are going to learn now you need not to mug up you just get the beep idea and if the gain question came on this you will be able to do fine so in the frame format these are the particular fields two bytes are given for frame control then we have a D means duration then we have address 1 address to address 3 sequence control which is a sequence number address for frame body and the F here which is a checksum so in the frame control which are thought to by they are part of a Assam fields the first field is protocol version then we have type so in I per in Wi-Fi we have various type of frame for example we have management frame so if you remember in the starting I told you about that if the station enter in the network it have to associate itself with a access point for that it sent the proof frame associated request ramp request frame proof frame associated request frame all these are management frame next type of frame which we have a control frame which are RTS CTS acknowledgement frame all these are control frame and then we have a data frame so in frame control we have protocol version then we have we have to specify which type of frame is this then in the particular type also we have various subtypes so for example if the typist control frame it could be an RTS frame CTS frame or acknowledgement so we have to specify it subtypes then we have these two particular bits which means to D s and from DS D s means distributed system distributed system is nothing but the via LAN which we have in our ESS so these two bit decide what are these four address going to be there in the body of this frame fine okay so I will define it then define them later so after frame control we have duration field which is of two bytes so in case of RTS signal RTS packet or cts packet we have to specify the duration of time we want to occupy the channel so for that we have the duration field we specify that the time interval we want to occupy the channel in this field based on these two field we have these four addresses then for synchronization we have sequence number and for error detection we have checksum okay so these two bit decide what are these four address going to be there so if the bit these to beta 0 0 what do you mean by 0 0 if 2d as bit is 0 means a packet is not going to distributed system so actually the complete picture is there so these are the station and this is the ESS fine so it could be the case there's this station want to communicate with this station so when this station want to communicate with this station it can communicate it right directly because it is in the range of its BSS fine so it the the frame need not to go to the distributed system so in this case both this bit going to be 0 it means the packet or the frame is not going to distributed system and is not coming from distributed system fine so based on that we have these 4 status so these are the 4 addresses in address 1 we the address of the next destination so in data link layer the packet go hop-by-hop though we in address one in address one field we specify the address of the next destination or the next hop in address to we specify the address of previous hop or the previous destination in address three we provide the final destination address and in writers for we have original source address so in the first case when the packet is not going to distributed system and not coming from distributed system means the packet is communicating with the station directly this case in this case what is the address one means the address of next destination it is the final destination it want to communicate so in the address one we have the destination address in address to we have to write previous destination address which is the source itself in address three in this case we mentioned the bssid so if this station is communicating with this so it is in the this circle BSS so we have to specify is the bssid in this case and there is no need to specify the original source because destination address to the specifying the original soul so in this particular case I just for this nun in the second case we have to D as bit 0 and from Dias bit 1 means the packet or the frame is not going to distributed system but it is coming from distributed system so so this is the case so this is a distributed system so the packet is coming from distributed system to this station so the packet is coming or the frame is coming from access point to this to this station so in address 1 we place the destination in address two will provide the standing API address sending AP address address 3 we provide the source address and the address for is not here the third case is the packet or the frame is going to distributed system but it is not coming from distributed system means it is this case the frame is going from station to this access point fine so in address one will place the receiving access point address in address to we will place the source address in address three will place the destination address and address will be none here and the final case is the packet or the frame is going to distributed system and it is coming from distributed system so this is basically this case in the land the packet or the frame is going from one access point to the other access point so in this case the address one will have the receiving access point address address two will have sending a access point ideas at the three will have destination address and address for will have the original source address so this is what - these two bit decide what are the four addresses we are going to have and SC will be the sequence number and body will range from zero to two three one two byte and there will be Sander crc32 checksum of the four byte this is what we have to do about the frame format please don't mug up this frame these fields and all these byte etcetera you just need to get the field key there are some types of types there are two days bed from dias bed and the address are placed accordingly you need to know that part only okay now we talk about the physical layer I don't think actually this part is not important for gate perspective gate perspective so I will just give the very brief idea to just give you an idea okay so in physical layer in I w8o 2.1 we have various it specification according to the multiplexing scheme we are using and coding scheme we are using and the security standard we are using we have various specification of 8 or 2.1 months so we have a two 2.11 a in which the bandwidth feared which we are using is five point seven to five gigahertz we are using orthogonal frequency-division multiplexing as an Wireless encoding scheme we are using phase shift key as a modulation scheme that speed varies from 6 to 54 megabit per second and the range is 25 to 75 feet in 802 dot burn 1b specification the bandwidth is 2.4 gigahertz and the virus encoding scheme a scheme is DSS the modulation scheme is phase shift key the speed range from 5.5 to 11 Mbps and the range is from 100 to 200 feet in the a to 2.1 1g specification the bandwidth is 2.4 gigahertz and the speed is 54 Mbps and the encoding scheme which we are using is OFDM the important part here is just that we are using unlicensed Bandhan I am so I told why we are using a licen band so that it is available free of course to provide cheaper services cheaper so in physical layer we are using this encoding scheme FHSS frequency hopping spread spectrum and it is used in original WLAN standard ieee 802 dot 1 1 we have also D Triple S direct sequence spread spectrum which is used as an encoding scheme in a 2 2.11 B we have OFDM orthogonal frequency division multiplexing which is used as an encoding scheme in a 2 2.11 G in the wireless network security is main concern because you are using unlicensed band so it is open to all though your data is not secure so you have to go for security it's a main concern here so in turbulent security Center we have WEP which is by it equivalent privacy protocol and it is used as a security personal e it is used as security protocol in 802 dot 1 1 B and it uses rc4 as an encryption algorithm we have Wi-Fi protected access and WPA it is a tamper error a key integrity protocol and encryption the main idea here is that encryption encryption algorithm changes the key dynamically for each data transmission so the key will be changing dynamically for each data transmission this is the idea we are here and the encryption algorithm is same RT 4 we have the second wpa wpa2 in which we use instead of rc4 encryption algorithm we use advanced encryption encryption standard AES which is stronger than our c4 so this is what about the physical physical layer it was
