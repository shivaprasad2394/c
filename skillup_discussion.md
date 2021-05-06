# Hello ,
Agenda
======
    1)C
    2)C++
    3)Linux system programmming
    4)Wifi
    5)Gps


# C++
order of discussion :-

- Define C++?
- What is a class in C++?
- What is an object?
- What is the difference between C and C++?
- Why is the size of an empty class not zero in C++?
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
