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
