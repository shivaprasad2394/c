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

const:- a qualifier ,gives direction to the compiler that the value of declaring object could not be changed.[not modifiable]

	•const int a------------>a constant integer.
	•int const a------------>a constant integer.
	•const int *a ==========>a pointer to constant integer-->[value constant]
	•int const *a ==========>a constant pointer to integer-->[address constant]
	•const int* const a \==>
			      =========>constant pointer to a constant int.
	•int const* a const /==>


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

	#include <iostream>
	#include <string.h>
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

usecase for union:-
E.g.

		Connection
	     /       |       \
	  Network   USB     VirtualConnection
If you want the Connection "class" to be either one of the above, you could write something like:

	struct Connection
	{
	    int type;
	    union
	    {
		struct Network network;
		struct USB usb;
		struct Virtual virtual;
	    }
	};
Example use in libinfinity: http://git.0x539.de/?p=infinote.git;a=blob;f=libinfinity/common/inf-session.c;h=3e887f0d63bd754c6b5ec232948027cbbf4d61fc;hb=HEAD#l74


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

1)Set a bit:-num|=(1<<nth pos)	
	
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

/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

	#include<stdio.h> //word reverse code
	void swap (char * str,int first ,int last);

	int pattern_search(char *str,char *buf){
	int a=0,b=0,c=0;
	while(str[a]!='\0'){
	if((buf[b]==str[c]) && (buf[b]!='\0')){
		c++;
		b++;
	}
	else{
		if(buf[b]=='\0')
			return 1;
	a++;
	c=a;
	b=0;
	}
	}
	return -1;
	}

	void reverse_string(char *str){
	int first=0;
	int len=strlen(str);
	len--;
	while(first<len){
	//a=a+b-(b=a);
	str[first]=str[first]+str[len]-(str[len]=str[first]);
	first++;
	len--;
	}
	printf("after=%s\n",str);
	}
	void swap(char * str,int first ,int last){
		while(first<last){
			str[first]=str[first]+str[last]-(str[last]=str[first]);
			first++;
			last--;
			printf("\nafter swap=%s",str);
		}
	}
	void reverse_word(char *str){
		int f=0;	//first position
		int l=0;	//last position
		int flag=0;	//indicates to swap word characters within word range/length
		int j=0;	//f+1 position or next position of head

		l=printf("%s",str);//dont change it will affect
		l--;
		printf("\nstr len=%d\n",l);
		swap(str,f,l);

		l=f=0;					//reset and start with individual word

		while(str[l]!='\0'){	//keep swaping until end
			if(str[l]==' '){	//if last is pointing to space dont swap skip
				if(flag>0){		//probably an indication skip and move on
					f=j+1;		//skip and move to next char in word
				}
				swap(str,f,(l-1));
				flag=1;
				j=l;
			}
			l++;//update last position to end of each word
		}
		if(str[l]=='\0'){//probably i am swaping internal char of word 
		f=j+1;
		swap(str,f,(l-1));//k=l-1;
		}
		printf("after each rev=%s\n",str);
	}

	void main(){
		char str[25];//character array
		char str1[25];
		printf("enter:\n");
		gets(str);
	    printf("enter:\n");
		gets(str1);
		//reverse_string(str);
		//each_word_swapper();
		int a=pattern_search(str,str1);
		if(a==1)
		printf("pattern");
		printf("not pat");
	}
	/*void remove_duplicate(char *str){ //remove duplicate
		char dup[25];
		char new[25];
		printf("\ndupped begin");
		int l=printf("%s",str);
		l--;
		char table[255]={0};
		int i=0,j=0,k=0;
		while(str[i]!='\0'){
			dup[i++]=str[l--];
			printf("\n%d%d",i,l);
		}
		dup[i]='\0';
		printf("ops=%s",dup);
		i=0;
		while(dup[i]!='\0'){
			if(table[(dup[i])]==0){
				table[(dup[i])]=1;
				new[k]=dup[i];
				k++;
			}else{
				printf("\n skipped %c",dup[i]);
			}
			i++;
		}
		printf("\ndupped str=%s",new);
	}*/

	/*int myatoi(char *str){
		int num=48,total=0,i=0,j=1,n=0,res[25]={0};
		n=printf("%s",str);
		while(str[i]!='\0'){
			if(str[i]=='\0'){
				res[i]='\0';
				printf("\n null breaker");
				break;
			}
			else if(str[i]>=num && str[i] <=(num+10)){
				res[i]=str[i]-num;
				printf("\nr%d i%d",res[i],i);
			}else{
			//here handle non numerics
			}
			i++;
		}
		for(i=0;res[i]!='\0';i++){
			//total += res[i]*(j<<(n-i));
			total*=10;
			total+=res[i];
			printf("\n t%d",total);
		}
		printf("\nanswer=%d",total);
		return total;
	}*/	
					     
					     
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

What is Semaphore?
Semaphore is simply a variable that is non-negative and shared between threads. A semaphore is a signaling mechanism, and a thread that is waiting on a semaphore can be signaled by another thread. It uses two atomic operations, 1)wait, and 2) signal for the process synchronization.

A semaphore either allows or disallows access to the resource, which depends on how it is set up.

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


A process is a program in execution.

Each process contains everything required to run (or restart) the program:

Address space — an abstraction for all memory available to that process. Address space contains program’s code and data required to run the program (static data, heap, and stack).
One or more threads of execution (I’ll explain that term in detail later)
Set of OS resources, for example opened files or network connections

Each process contains a single or multiple threads of execution. If a process has a single thread, only one action can be performed at a time. If a process has multiple threads, it can perform multiple actions at the same time.

A thread is a sequence of instructions that can be executed independently from other code/single cpu core

Each thread contains all information necessary to execute it’s code. We need to keep track of 1) which part of the program is currently being executed and 2) what is currently stored in memory.

That’s why each thread has its own program counter (a pointer that indicates which instruction will be executed next), CPU registers, and a stack.

Threads within the same process share all other memory segments:

heap — containing dynamically allocated variables
text segment — containing program’s code
data segment — containing global or static variables

The most significant, practical difference is in how processes and threads communicate.

In a multithreaded process, threads share memory. Thus, many threads can access and modify the same memory, which may lead to bugs that are very difficult to find.

Processes don’t share memory in this way, they have to use inter-process communication instead.

Creating a process is fairly resource-intensive. It is generally more efficient to use a single multi-threaded process than to spawn multiple single-threaded processes.


What is a Deadlock?
Junior 
Top 21 Concurrency Interview Questions  Concurrency  21  
Answer
A lock occurs when multiple processes try to access the same resource at the same time. One process loses out and must wait for the other to finish.

A deadlock occurs when the waiting process is still holding on to another resource that the first needs before it can finish.


So, an example:

Resource A and resource B are used by process X and process Y

X starts to use A.
X and Y try to start using B
Y 'wins' and gets B first
now Y needs to use A
A is locked by X, which is waiting for Y
Thread 1               Thread 2

Lock1->Lock();         Lock2->Lock();
WaitForLock2();        WaitForLock1();   <-- Oops!

Deadlock ex:-
Jack and Jill share a sparse kitchen that has only one of everything. They both want to make a sandwich at the same time. Each needs a slice of bread and each needs a knife, so they both go to get the loaf of bread and the knife from the kitchen.

Jack gets the knife first, while Jill gets the loaf of bread first. Now Jack tries to find the loaf of bread and Jill tries to find the knife, but both find that what they need to finish the task is already in use. If they both decide to wait until what they need is no longer in use, they will wait for each other forever. Deadlock.


Is there any difference between a Binary Semaphore and Mutex?
Mid 
Top 21 Concurrency Interview Questions  Concurrency  21  
Answer
A mutex (or Mutual Exclusion Semaphores) is a locking mechanism used to synchronize access to a resource. Only one task (can be a thread or process based on OS abstraction) can acquire the mutex. It means there will be ownership associated with mutex, and only the owner can release the lock (mutex).

Semaphore (or Binary Semaphore) is signaling mechanism (“I am done, you can carry on” kind of signal). For example, if you are listening songs (assume it as one task) on your mobile and at the same time your friend called you, an interrupt will be triggered upon which an interrupt service routine (ISR) will signal the call processing task to wakeup. A binary semaphore is NOT protecting a resource from access. Semaphores are more suitable for some synchronization problems like producer-consumer.

Short version:

A mutex can be released only by the thread that had acquired it.
A binary semaphore can be signaled by any thread (or process).


What is a Race Condition?
Mid 
Top 21 Concurrency Interview Questions  Concurrency  21  
Answer
A race condition is a situation on concurrent programming where two concurrent threads or processes compete for a resource and the resulting final state depends on who gets the resource first.

Because the thread scheduling algorithm can swap between threads at any time, you don't know the order in which the threads will attempt to access the shared data. Therefore, the result of the change in data is dependent on the thread scheduling algorithm, i.e. both threads are "racing" to access/change the data.

Problems often occur when one thread does a "check-then-act" (e.g. "check" if the value is X, then "act" to do something that depends on the value being X) and another thread does something to the value in between the "check" and the "act". E.g:

if (x == 5) // The "Check"
{
   y = x * 2; // The "Act"

   // If another thread changed x in between "if (x == 5)" and "y = x * 2" above,
   // y will not be equal to 10.
}
The point being, y could be 10, or it could be anything, depending on whether another thread changed x in between the check and act. You have no real way of knowing.

In order to prevent race conditions from occurring, you would typically put a lock (Mutex or Semaphores) around the shared data to ensure only one thread can access the data at a time. This would mean something like this:

// Obtain lock for x
if (x == 5)
{
   y = x * 2; // Now, nothing can change x until the lock is released. 
              // Therefore y = 10
}
// release lock for x


 What is the meaning of the term “Thread-Safe”?
Mid 
Top 21 Concurrency Interview Questions  Concurrency  21  
Problem
Does it mean that two threads can't change the underlying data simultaneously? Or does it mean that the given code segment will run with predictable results when multiple threads are executing that code segment?

Answer
Thread-safe code is code that will work even if many Threads are executing it simultaneously within the same process. This often means, that internal data-structures or operations that should run uninterrupted are protected against different modifications at the same time.
Another definition may be like - a class is thread-safe if it behaves correctly when accessed from multiple threads, regardless of the scheduling or interleaving of the execution of those threads by the runtime environment, and with no additional synchronisation or other coordination on the part of the calling code.



*******************************************************************************


			#include <pthread.h>
			#include <stdio.h>
			#include <stdlib.h>
			/*
			Binary search using Pthread.
			Input :  list = 1, 5, 7, 10, 12, 14, 15, 18, 20, 22, 25, 27, 30, 64, 110, 220
				 key = 7
			Output : 7 found in list

			*/
			void *
			func (void *arg)
			{
			  // detach the current thread from the calling thread
			  pthread_detach (pthread_self ());	//pthread_self: used to get the thread id of the current thread.

			  printf ("Detached threadA detached thread does not require a thread to join on terminating.The resources of the thread are automatically released after terminating if the thread is detached.\n");

			  // exit the current thread
			  pthread_exit (NULL);
			}

			/*Mutex thread lock*/
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
			int main ()
			{
			  int num = 0;
			  printf("enter choice\n1)pthread\n2)Message Quene\n3)Fork&pipe\n4)namedpipe\n5)Shared memory\n6)pthread syncronization");
			  scanf ("%d" & num);
			  switch (num)
			    {
			    case 1:
			      {
				pthread_t ptid;
				// Creating a new thread
				pthread_create (&ptid, NULL, &func, NULL);
				printf ("This line may be printed before thread terminates\n");
				// The following line terminates the thread manually
				// pthread_cancel(ptid);

				// Compare the two threads created
				if (pthread_equal (ptid, pthread_self ())
				    printf("Threads are equal\n");
				else
				    printf ("Threads are not equal lets wait for child thread\n");

				    // Waiting for the created thread to terminate
				    pthread_join (ptid, NULL);
				    printf ("This line will be printed after thread ends\n");
				    pthread_exit (NULL);

			      }
			    case 2:
			    {
				/*
			A context switch is a procedure that a computer's CPU (central processing unit) follows to change from one task (or process) to another while ensuring that the tasks do not conflict. Effective context switching is critical if a computer is to provide user-friendly multitasking.*/

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
			    } 
			    case 3:
			    printf ("Case1: Value is: %d", num); 
			    default:
				printf ("Default: Value is: %d", num);}

			return 0;

			}

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

Wireless LAN is a network where devices are using Wireless protocol / technology to communicate with each other in a defined area.


IEEE 802.11  provides standard for wireless LAN which covers 2 layers

1. **Physical layer**.

2. **Data link layer**.

in this standard we have two kinds of services:-

1.bss(  basic service set)

2.Ess( extended service)

**BSS**:- it is a group/unit of wireless Network devices that are communicating with same AP.

**BSSID**:- is a AP's  physical / Mac address. 

It is 48 bit long hex-decimal number

**AP**:- these are devices which accept Wireless signals from multiple devices and retransmit them to  the rest of the network.

AP also known as base station
AP is a layer 2 device

**SSID**:- it is a unique character string used to identify an AP.

When a service is extended by adding more AP, this is called e s s.

It's shared network name is called essid.

**ADHOC**( without ap in bss) :- it is a decentralized type of network,  Wireless devices communicates directly to each other  rather than using a Bridge(ex:-AP).

It is peer-to-peer

**ESS**:- ESS  is a collection of multiple AP's  and their Associated client stations, all United by a single DSM

The Logical network name of the ESS  is often called  extended service set  identifier.

The terminology of essid  and ssid  are synonyms.

Promiscius mode:- also known as Wi-Fi monitor mode. Basically used for listening to the Wi-Fi   packets  over-the-air.

IEEE 802.11 standards  specify 2 layers

1. Data link layer

2. Physical layer

Data link layer is divided into two layers
1. Logical link control layer

2. Medium Access Control layer

In Mac we have two more layers
1.   **DCF**

2.   **PCF**

The first sub layer of Mac  is DCF it provides contention Based Services that is csma/ca(  carrier sensing multiple access/ Collision avoidance)

Csma/ CA  is Wireless

Csma / CD is   for  wired

Wi-Fi operate at half duplex. So it can either send or receive  at  a time. Hence csma / CD is not possible.

csma / c a  timers are maintained the check Collision

The process or a technique  by  which  a station  can associate itself with an AP it's called scanning

Whenever a Station  enters a  network it has to do scanning in order to associate with a p by doing scanning.

Steps for scanning

1. Send a  probe  Frame.

2. All AP  Within reach send   probe response frame

3. Station will send associate request frame to AP

4. AP will send  Association response frame

**Active scanning**
In active scanning station approach AP, then AP replies the station.
**Passive scanning**
In passive scanning all the AP sends Timely Beacon frame( advertising packets illustrating its capability to all stations)

There are two kinds of problems  in csma / CA
1.  **hidden terminal problem**
2. **Exposed station problem**( interference probleml)

**Hidden Terminal problem** can be  solved  by rts and cts

By this we are making  claient stations   aware  another  claint station across the AP

In **exposed station problem** station will not be able to send data even when the channel is  idle

This is because the station thinks some other station it's trying to send data to   the AP

This problem is also solved by rts and cts.
Provided Station 1 and Station 2  are synchronized

PCF ( Point coordination function)
PCF is poll based/ priority based.

**Fragmentation**:- since the channel is noisy, if  data is corrupted we need to retransmit the whole Packet so in wi-fi, fragmentation is  encouraged.

Frame format
FC d  add1   add2   add3  SC  add4  body  fcs 

FC( **frame control**)  it consists of various bits
Namely

1. Protocol version

2. Frame type

3. Sub type

4. To destination

5. From destination

**Frame type** is subdivided into

1. Management frame

2. Control frame

3. Data frame

Sub type  helps  specify  the exact type of frame.

**Management frame** is farther sub  divided in to 

1. Probe frame

2.  Association frame

3. Authentication frame

4. Beacon frame

**Control  frame** is further subdivided into

1. R t s

2. CTS

3. Acknowledgement

The duration bit specify  time interval we want to occupy the channel.

**Sequence control** SC  used for synchronization

Fsc ( **frame sequence checking**)  is used for are checking probably crc32

To DS(  a packet going to distributed system) & from DS  ( a packet coming from distributed system)
 are Wired lan address 1 to address 4

For a direct communication between station one and Station 2 there is no need of destination address so  2DS &  from DS  is 0.

	Address 1  specifies the address of next destination
	Address 2 specifies the address of previous destination
	Address 3 specifies the address of Final Destination
	Address 4 specifies the address of original  source

**Physical layer**:- based on the encryption/ multiplexing scheme we have various versions of 802.11 Such has  a,b,g,n in physical layer.

IEEE 802. 11 versions is differentiated based on  encoding, speed, range e t c

IEEE 802. 11a:- 5. 75 G hz , ofdm, psk,6- 54 Mbps
IEEE 802. 11b:- 2. 44G hz, dsss, psk,   5.5 to  11 Mbps
IEEE 802. 11g:-2.4 G hz , ofdm, 54 Mbps

Wi-Fi use unlicensed band in I s m.

**Beacon frame**:- Beacon frame contains layer 2 information including

1. ssid
2. Channel info
3. Data rates( supported & required)
4. Security
5. Qos parameters.


A **normal no encryption** connection process

1. AP send a  Beacon broadcast management frame.( basically a broadcast address is sent)

2. The client sends a probe request frame  to the AP  carrying the  specified ssid. (I.e  when clicked  connect)

3. The AP responds to the client ssid  connection request (i.e  it states. It does not except any form of frame payload encryption) or ( does not give any challenge)

4.  the client  attempts a low level authentication request to the Target AP

5. The AP response to the client  authentication request(i.e  it indicates acceptance of identity)

6. The client  sends  and Association request to the AP 

7. The AP response to the Association request

8.  the client  request disconnection from the AP.(i.e  when clicked disconnect, the  nic  card sends  a disconnect management frame to the AP. Requesting disconnect)

**Power saving mode**

During power saving mode the client station
Sends  null data  with PS poll  bit set.

The station will be Beacon  interval active

The data buffering and Tim flag notification will be done by access point

Once the station wakes up it is notified by Tim flag notification and sends  PS  poll  to get the buffered data.

**Four-way handshake**

If four-way handshake is   successful, then the client and AP are ready for encrypted data traffic.

During a four-way handshake  following frames Exchange

1.  AP generates announce  and transmit to  station.

2. The station generates pmk  using password +ssid hash, and  receive announce . Utilizing both announce and pmk  along with the help of snonce randomly generated at its end will generate PTK( Pairwise transcient key)

The station transmit  s Nounce to the AP.

3. AP generates PTK from the  s nounce. Meanwhile it generates group temporal key  and   share it with station.

4.  the station after receiving gtk sends acknowledgement to  AP.

A **normal WPA2 encryption** method

1.Mobile station transmit probe request to  AP. Probe request consist of supported data rates,  802. 11 capabilities.

2. AP checks if capabilities are matching  and sends  probe response consisting of ssid+ supported data rates+ encryption types+  capability

3. The station  select the compatible probe response and  attempt low level Authentication request

4. The AP respond by  low level Authentication response

5. At this point station is  said to be  Authenticated  but not yet associated.
Station can be authenticated to multiple AP, but associate to only one AP.
So once it chooses the right ap  for Association  it sends  Association request consisting of selected encryption type+ 802. 11 features

6. At AP  if the capability match, it create Association ID and sends  Association response consisting of status code Plus Id.

7. Now  Mobile station can transmit data  unless the encryption type selected was wpa2/wpa/wep.

8. If WPA2/ 802.1X was the selected encryption type, then four way handshake is required for  encrypted data transport.

After the STA completes the four-way handshake with the AP, the data link layer successfully establishes a connection, but in the network OSI seven-layer model, the application layer must have an IP address to access the network. DHCP is the process of obtaining IP from the AP's DHCP service. .


1.**scan** 		Scan nearby hotspots

		scan
		OK

2.**scan_results**	Get the result of the scan

		scan_results
		bssid / frequency / signal level / flags / ssid
		20:f4:1b:83:40:e4 2462 -63 [WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][ ESS] ROC
		80:89:17:a1:a8:ee 2437 -64 [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS] samuel
		80:89:17:a1:a8:e4 2437 -67 [ WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS] TV-WIFI
		80:89:17:9f:d3:ba 2412 -73 [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS] Xrr
		f4:ec:38:7b:2c:96 2437 -75 [WPA-PSK-CCMP][WPA2-PSK-CCMP][WPS][ESS] TP-LINK_7B2C96
		1c:fa:68:50:8a:76 2462 -71 [WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][WPS][ESS] RDSPEED100M
		D0:c7:c0:fd:86:64 2437 -73 [WPA-PSK-CCMP][WPA2-PSK-CCMP][ESS] yingyunguanli-huiyishi
		4e:e0:10:c2:44:57 2462 -59 [WPA2 -PSK-CCMP][ESS] hellowifi
		4e:e0:10:c2:48:5d 2462 -70 [WPA2-PSK-CCMP][ESS] ADESKTOP-93DNJ6F
		ac:e0:10:c2:63:bc 2412 -66 [WPA-PSK-CCMP+TKIP][WPA2-PSK-CCMP+TKIP][WPS][ESS] wifi
		cc:34:29:2c:7f:e8 2412 -76 [WPA-PSK-TKIP][WPA2-PSK -TKIP][ESS] dlink


3.**add_network**		Add a network

by viewing the scan results, we chose to be a wifi connection, such as hellowifi
this time, we must first add a network.

		/> add_network
		2
This 2 is a value returned by wpa_supplicant to us. It represents this network. We need to use this value in future operations.

4. Set ssid and password	Ssid is the name of the hotspot, here is hellowifi.

		/> set_network 2 ssid “hellowifi”
		OK
		/> set_network 2 psk “11223344”
		OK
		psk is the name of the wifi password in WPA2-PSK mode.If there is no encryption:
		/>set_network 2 key_mgmt NONE

if it is WEP security mode:
/>**set_network** 2 wep_key0 “your ap passwork”

5.**enable_network**		Enable wifi

		/> select_network 2
		OK

Selecting the network is optional. If you have already connected a wifi, you should reselect a network.

		/> enable_network 2
		OK

6. Switch wifi	If we currently have multiple networks, we can switch:
/> select_network 0
OK
/> enable_network 0
OK
wifi in network 0 will be connected

  How to enable a wifi connection with wpa_supplicant?
Step by step：
1> run the wpa_supplicant program;
path：/system/bin/wpa_supplicant -d -Dwext -iwlan0 -c/data/misc/wifi/wpa_supplicant.conf
among them:
-d : increase debugging information
-Dwext :wext, the driver name
-iwlan0 :wlan0, network interface name

/system/bin/wpa_supplicant :wpa_supplicant executable path
/data/misc/wifi/wpa_supplicant.conf :wpa_supplicant configuration file path
2, run the command line tool wpa_cli;
执行 ：wpa_cli -iwlan0 -p/data/system/wpa_supplicant


What is **DHCP**?

DHCP (Dynamic Host Configuration Protocol) is a network protocol for local area networks. It refers to a range of IP addresses controlled by the server, and the client can automatically obtain the IP address and subnet mask assigned by the server when logging in to the server. By default, DHCP, as a service component of Windows Server, will not be automatically installed by the system, and administrators need to install it manually and perform necessary configuration.

1. DHCP normal process


		ClientModeImpl$ObtainingIpState:
		 enter()
		  startIpClient()
		   sendNetworkChangeBroadcast(DetailedState.OBTAINING_IPADDR)
		   stopDhcpSetup()
		   mIpClient.startProvisioning(prov.build()) <= IpClientManager

		NetworkStack:
		IpClient:
		 // CHECKSTYLE:OFF IndentationCheck
			addState(mStoppedState);
			addState(mStartedState);
			    addState(mPreconnectingState, mStartedState);
			    addState(mClearingIpAddressesState, mStartedState);
			    addState(mRunningState, mStartedState);
			addState(mStoppingState);
			// CHECKSTYLE:ON IndentationCheck

			setInitialState(mStoppedState);

		IpClient.startProvisioning()
		 sendMessage(CMD_START, new android.net.shared.ProvisioningConfiguration(req))

		IpClient$StoppedState:
		 enter()
		  stopAllIP()
		  resetLinkProperties()
		 CMD_START
		  transitionTo(mClearingIpAddressesState)

		IpClient$ClearingIpAddressesState:
		 enter()
		   deferMessage(obtainMessage(CMD_ADDRESSES_CLEARED))
		   CMD_ADDRESSES_CLEARED
		    transitionTo(mRunningState)

		IpClient$RunningState:
		 enter()
		  mPacketTracker = createPacketTracker()
		  mPacketTracker.start(mConfiguration.mDisplayName)
		  startIPv6()
		  startIPv4()
		  applyInitialConfig(config)
		  startIpReachabilityMonitor()

		IpClient.startIPv4():
		 startDhcpClient() // Start DHCPv4
		  mDhcpClient = mDependencies.makeDhcpClient(mContext, IpClient.this, mInterfaceParams,mDependencies.getDhcpClientDependencies(mIpMemoryStore, mIpProvisioningMetrics))
		  mDhcpClient.registerForPreDhcpNotification()
		  mDhcpClient.sendMessage(DhcpClient.CMD_START_DHCP, new DhcpClient.Configuration(mL2Key, isUsingPreconnection()))

		DhcpClient:
			// CHECKSTYLE:OFF IndentationCheck
			addState(mStoppedState);
			addState(mDhcpState);
			    addState(mDhcpInitState, mDhcpState);
			    addState(mWaitBeforeStartState, mDhcpState);
			    addState(mWaitBeforeObtainingConfigurationState, mDhcpState);
			    addState(mDhcpPreconnectingState, mDhcpState);
			    addState(mObtainingConfigurationState, mDhcpState);
			    addState(mDhcpSelectingState, mDhcpState);
			    addState(mDhcpRequestingState, mDhcpState);
			    addState(mIpAddressConflictDetectingState, mDhcpState);
			    addState(mDhcpHaveLeaseState, mDhcpState);
				addState(mConfiguringInterfaceState, mDhcpHaveLeaseState);
				addState(mDhcpBoundState, mDhcpHaveLeaseState);
				addState(mWaitBeforeRenewalState, mDhcpHaveLeaseState);
				addState(mDhcpRenewingState, mDhcpHaveLeaseState);
				addState(mDhcpRebindingState, mDhcpHaveLeaseState);
				addState(mDhcpDecliningState, mDhcpHaveLeaseState);
			    addState(mDhcpInitRebootState, mDhcpState);
			    addState(mDhcpRebootingState, mDhcpState);
			// CHECKSTYLE:ON IndentationCheck

		DhcpClient$StoppedState:
		 CMD_START_DHCP
		  startInitRebootOrInit()
		   preDhcpTransitionTo(mWaitBeforeStartState, mDhcpInitState)
		    transitionTo(mWaitBeforeStartState)
		     DhcpState.enter()
		      clearDhcpState()
		      initInterface() && initUdpSocket()
		      mDhcpPacketHandler = new DhcpPacketHandler(getHandler())
		      mDhcpPacketHandler.start()
		       WaitBeforeOtherState.enter()
			mController.sendMessage(CMD_PRE_DHCP_ACTION)  => IpClient => ClientModeImpl$IpClientCallbacksImpl
			 transitionTo(mDhcpInitState)
			  DhcpInitState.enter()
			   PacketRetransmittingState.enter()
			    sendMessage(CMD_KICK)
			     CMD_KICK
			      DhcpInitState.sendPacket()
			       sendDiscoverPacket()
				transmitPacket(packet, "DHCPDISCOVER", DhcpPacket.ENCAP_L2, INADDR_BROADCAST)
			      scheduleKick()
			   startNewTransaction()

		mDhcpPacketHandler.transmitPacket(buf, mInterfaceBroadcastAddr)
		DhcpPacketHandler.handlePacket() <= receive packet
		 sendMessage(CMD_RECEIVED_PACKET, packet)
		  PacketRetransmittingState.CMD_RECEIVED_PACKET
		   DhcpInitState.receivePacket(packet)
		    receiveOfferOrAckPacket(packet, isDhcpRapidCommitEnabled())
		     packet instanceof DhcpOfferPacket
		      transitionTo(mDhcpRequestingState)
		       PacketRetransmittingState.enter()
			sendMessage(CMD_KICK)
			 CMD_KICK
			  DhcpRequestingState.sendPacket()
			   sendRequestPacket()
		     packet instanceof DhcpAckPacket
		      confirmDhcpLease(packet, results)
		      transitionTo(isDhcpIpConflictDetectEnabled() ? mIpAddressConflictDetectingState : mConfiguringInterfaceState)
		transitionTo(mConfiguringInterfaceState)
		 ConfiguringInterfaceState.enter()
		   notifySuccess()
		  mController.sendMessage(CMD_CONFIGURE_LINKADDRESS, mDhcpLease.ipAddress) => IpClient$RunningState
		   mInterfaceCtrl.setIPv4Address(ipAddress)
		    mDhcpClient.sendMessage(DhcpClient.EVENT_LINKADDRESS_CONFIGURED)
		     ConfiguringInterfaceState.EVENT_LINKADDRESS_CONFIGURED
		      transitionTo(mDhcpBoundState)
		       DhcpBoundState.enter()
			connectUdpSock(mDhcpLease.serverAddress)
			scheduleLeaseTimers()
			logTimeToBoundState()

		InterfaceController.setIPv4Address(ipAddress)
		 setInterfaceConfiguration(address, null)
		   mNetd.interfaceSetCfg(ifConfig)

------------------------------------------------------------------------------------------------------------------------------------------------

The ViperIII system includes Vehicle Processor and Graphics Processor. 
The Vehicle Processor will manage all real-time functions, manage communications with the vehicle system, and monitor the onboard functionality. 
The Graphics Processor will house all the user interface functions and includes a touch screen for interaction with the Human Machine Interface (HMI).

**Wi-Fi**: This module initializes and interfaces to the Wi-Fi H/W over SDIO to the OS. It must be able to manage a list of stored devices, 
must facilitate the user’s discovery of new devices, and the connection and storage of the link information of connected devices.


The so-called Netd is the abbreviation of Network Daemon, which means Network Daemon.

**Netd** is responsible for the configuration, operation, management, and query related to the network. & 

Implementation of functions, such as 

		bandwidth control (Bandwidth), 
		traffic statistics, 
		bandwidth control, 
		network address translation (NAT), 
		personal area network (pan), 
		PPP link, 
		soft-ap, 
		shared Internet access (Tether), 
		configuration routing table, 
		interface Configuration management, etc...

through netlink, virtual file system, user interface provided by linux kernel, communication kernel, or 
direct execution of system modules to manage network related parts.

Netd is the mostly deamon, which provides developers with an interface for management. It is ndc (nativedeamonconnector),
and various commands defined in CommandListener can be used directly through adb. 

NativeDeamonConnector of the similar framework layer is an interface provided for the upper layer. 
The following is a collection of commands available for ndc in 4.2:

**hostapd** is a software that sets the wireless network card to Master mode.
Simulating AP ( usually thought of as a router ) function,
The function of Hostapd is to act as an AP 's authentication server, responsible for controlling and managing the access and authentication of stations ( usually a PC with a wireless network card ) .

The wireless network card can be switched to AP/Master mode through Hostapd , and an open ( unencrypted ) , WEP , WPA or WPA2 wireless network can be established by modifying the configuration file . 
And by modifying the configuration file, you can set various parameters of the wireless network card, including frequency, signal, beacon packet time interval, whether to send beacon packets, and if responding to probe requests, etc.

When using wifi, as a station, it works in managed mode, 
and there is a background process wpa_supplicant to manage authentication.

When working in sofap, as an AP, it works in master mode, 
and the background process hostapd performs authentication processing.

in **wifi managed**,
As a station, the user starts the WIFI through the UI, loads the WIFI driver from the framework layer, 
JNI, and hardware layer, and loads the firmware. After the driver is loaded successfully, 
start wpa_supplicant, set the mad address, set it to managed mode, start scan through the ioctl command, 
start DHCPD to obtain the IP address, link to the corresponding AP, and sock communication at the same time after the connection is established 

In **softap mode**, 
the process is similar to station mode, except that wpa_supplicant is not started, 
and the background management process of hostapd is started.

Load the driver of softap from the framework layer, JNI, and hardware layer, and load the firmware. 
After the driver is loaded successfully, start hostap, set the mad address, set the master mode, set the BSSID, 
and start DHCPD to obtain the IP address. Wait for the station to connect.


**softap** (Soft Access Point)
Softap can share the mobile network used by the mobile phone for wlan access devices.
When the notebook is connected to softap, you can access the Internet through the 3g of the mobile phone.



