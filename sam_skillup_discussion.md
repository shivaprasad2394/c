# Hello sam,
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
- faster than high level languages
- system programming (access to memory /pointers).

compilation of C-code
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
    2)static----->varible with static specifier,have internal or no linkage,memory persistant,initialized once.
    3)extern----->default specifier class for global variables and function.
                 •varibles with extern class have no storage allocation for variable.
                 •indicates/informs compiler about offload declaration/definition of variable.
    4)register--->variable with register class have visibility Local to Function.
                 •informs compiler to store the variable in cpu registers.





Extra:-
=======
- **compiler** is a computer program that translates computer code written in one programming language (the source language) into another .
- **mid-level language**C is called middle-level language because it actually **binds the gap between a machine level language and high-level languages**. A user can use c language to do **System Programming** (for writing operating system) as well as **Application Programming** (menu driven customer billing system )
