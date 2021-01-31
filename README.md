C
=============================================================================================================================
c practice perpose
http://cse.unl.edu/~cbourke/searchingSorting.pdf
https://github.com/rafi007akhtar/c-algorithms/blob/master/single_pointer_doublelinkedlist.c


storage classes :- 
---------------
                   1)decide the extent(lifetime) of variable.
                   2)scope (visibility) of the variable
                   3)storage location in memory.
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

----------------------------------------------------------------------------------------------------------------------------
scope difference
----------------
    
    1)Global variable-->Extenal linkage. [i.e visible outside the program]
    2)Global static  -->Internal linkage. [i.e visibity is restricted to the program where it is defined]
    3)Local static   -->no linkage.[i.e visibility is restricted to the local function where it is defined]

----------------------------------------------------------------------------------------------------------------------------

    static default value-->0 
    note:-the start up code initializes the the data segment to 0.
    ============================================================================================

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

# Inline function in C
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
# note:if static is not used then it will give error.
    In function `main':
    undefined reference to `foo'
    To resolve this problem use “static” before inline. 
    Using static keyword forces the compiler to consider this inline function in the linker, 
    and hence the program compiles and run successfully.[for more refer the readme in inline subs]
watch it really good :https://www.youtube.com/watch?v=gINI12EMbds   &
https://www.youtube.com/watch?v=MNxNlMQ5QJ4
-----------------------------------------------------------------------------------------
const:- a qualifier ,gives direction to the compiler that the value of declaring object could not be changed.[not modifiable]
-----
    •const int a------------>a constant integer.
    •int const a------------>a constant integer.
  -------------------------------------------
  
    •const int *a ==========>a pointer to constant integer-->[value constant]
    •int const *a ==========>a constant pointer to integer-->[address constant]
  ---------------------------------------
    
    •const int* const a \==>
                          =========>constant pointer to a constant int.
    •int const* a const /==>
  
  --------------------------------------------
========================================================================================
  
pre increment 
==========
    --->increament is done *immediatly.
post increment
===========
    --->increment effect is done in *next statement.
    ex:-
    char ac[5]={'A','B','C','D','E'};
    char *pcdata = ac;
    ---------------------------------- 
    *++pcdata =====>'B' 
    <--------           
    ++*pcdata =====>'A' 
    <--------           
    *p++  =========>'A' 
    <---                
   ------------------------------------
--------------------------------------------------------

    ++*p -->take data and increment data.
    *++p -->move pointer to next and read data.
    *p++ -->read data ,then move pointer to next.
    (*p)++ >increment the data.
    [P++ + ++p] or [++P + p++] -->????

===========================================================================================

extras:-

Difference between const and Macro:-
====================================
Const-------------------->>v/s<<-----------------Macro
======================================================
    handled by compiler                          |                             handled by preprocessor
    A qualifier (modifies behavior of identifier)|                             A pre processor directive
    type checking                                |                             No typechecking
    Scoped by c block                            |                             applies for file
        
=======================================================

volatile keyword
================
    A Type qualifier that prevents object from the compiler optimization.
according to c standards:-
========================
          • A volatile object can be modified in ways unknown to the implementation.
          • the value of the object can be changed at any time without any action being taken by the code.
          • when a variable or object is declared volatile the compiler reloads the value from the memory each time it is accessed by the programm. [i.e:-it prevents from cacheing a variable into registers]
          •reading the value from memory is the only way to check the unpredictable change of the value.
          
   Example:-
   ======= 
    access the memory-mapped peripheral register or hardware status register
======================================================================

    #define COM_STATUS_BIT  0x00000006

    uint32_t const volatile * const pStatusReg = (uint32_t*)0x00020000;


    unit32_t GetRecvData()
    {
      //Code to recv data
        while (((*pStatusReg)  & COM_STATUS_BIT) == 0)
      {
            // Wait untill flag does not set
        }

        return RecvData;
    }
=======================================================================    

    • Sharing the global variables or buffers between the multiple threads.
    • Accessing the global variables in an interrupt routine or signal handler.
======================================================================= [note:-1st explain without volatile]

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
    }

=========================================================================
    
    •volatile  prevents the object from any compiler optimization and says that the value of the object can be changed by something that is beyound the control of the program and so that compiler will not make any assumptions about the object.
    volatile int a;
    • When a compiler see the above declaration ,then it avoids to make any assumptions regarding the variable/object and in every iteration read the value from the address whic is assigned to the variable.
    
======================================================================================================================   
   
[todo from here]

      What is the difference between the const and volatile qualifier in C?
            Answer:
            The const keyword is compiler-enforced and says that the program could not change the value of the object that means it makes the object nonmodifiable type.
            e.g,
            const int a = 0;
            if you will try to modify the value of “a”, you will get the compiler error because “a” is qualified with const keyword that prevents to change the value of the integer variable.

      In another side volatile prevent from any compiler optimization and says that the value of the object can be changed by something that is beyond the control of the program and so that compiler will not make any assumption about the object.
      e.g,
      volatile int a;

      When the compiler sees the above declaration then it avoids to make any assumption regarding the “a” and in every iteration read the value from the address which is assigned to the variable.

      Can a variable be both constant and volatile in C?
      Answer:
      Yes, we can use both constant and volatile together. One of the great use of volatile and const keyword together is at the time of accessing the GPIO registers. In case of GPIO, its value can be changed by the ‘external factors’ (if a switch or any output device is attached with GPIO), if it is configured as an input. In that situation, volatile plays an important role and ensures that the compiler always read the value from the GPIO address and avoid to make any assumption.
      
     After using the volatile keyword, you will get the proper value whenever you are accessing the ports but still here is one more problem because the pointer is not const type so it might be your program change the pointing address of the pointer. So we have to create a constant pointer with the volatile keyword.

      Syntax of declaration,

      int volatile * const PortRegister;

      How to read the above declaration,
      int volatile * const PortRegister;
       |     |     |   |    |
       |     |     |   |    +------> PortRegister is a
       |     |     |   +-----------> constant
       |     |     +---------------> pointer to a
       |     +---------------------> volatile
       +---------------------------> integer
       
       Consider a simple below example:

 

      #define PORTX 0x00020000 // Address of the GPIO

      uint32_t volatile * const pcPortReg = (uint32_t *) PORTX;
      The pcPortReg is a constant pointer to a volatile unsigned integer, using *pcPortReg we can access the memory-mapped register.

      *pcPortReg = value; // Write value to the port
      value = *pcPortReg; // Read value from the port
      

==============================================================================================

bit manipulation
----------------
1)SET a Bit
-----------

    •Bitwise OR Operator used to set a int data type
    •OR of two bit is always 1(SET) , if any one of them is 1.
                          
                          Number | = (1<< nth Position)    1010 1000
                                                           0100 0000
                                                            <-------nth bit
                                                           -----------
                                                           1100 1000
                                                           -----------
--------------------------------------------------------------------------------------------------------
2)Clear a Bit
-------------

    •Bitwise AND oprator used to clear.
    •AND of two bit is always 0(clear) if any of the bit is 0.
                          
                        Number &= ~ (1<< nth Position)    0100 1000
                                                          1011 1111
                                                          (~)<------nth bit
                                                           -----------
                                                           10001000
                                                           -----------
 -------------------------------------------------------------------------------------------------------
 3)Checking a Bit
-----------------

    •Bitwise AND oprator used to check wether ser or not.
    •AND of two bit is always 1(SET) if any of the bit is 1.
                          
                  Bit = Number & (1 << nth)               0100 1000
                                                          0100 0000
                                                            <------nth bit
                                                          ------------
                                                          0100 0000
                                                          ------------
-------------------------------------------------------------------------------------------------------
 3)Toggle a Bit
-----------------

    •Bitwise XOR oprator used to Toggle .
                                                      Number ^= (1<< nth Position)
                          
                                                           1010 1000
                                                           0100 0000
                                                            <-------nth bit
                                                           -----------
                                                           1110 1000
                                                           ----------- 
-----------------------------------------------------------------------------------------------------
4)Detect if two Integers have opposite Signs.
--------------------------------------------

     •EX-OR of “a” and “b” will be negative,if “a” and “b” have the opposite signs.
     •XOR less than 0.
                       bRetValue = ((a ^ b) < 0); // true if a and b have opposite signs
----------------------------------------------------------------------------------------------------
5)Reverse Bits of a Number
--------------------------

Method 1:
---------
    • check the set bits of num and run the loop through all the bits of an integer.
    • If we find the ith bits of num is set then just put 1 at the ((INT_BITS – 1) – ith ) position of tmp, where INT_BITS is the number of bits of an integer.

                  #define CHAR_BITS  8  // size of character
                  #define INT_BITS  ( sizeof(int) * CHAR_BITS)


                  //bit reversal function
                  unsigned int ReverseTheBits(unsigned int num)
                  {
                      unsigned int iLoop = 0;
                      unsigned int tmp = 0;         //  Assign num to the tmp 
                      int iNumberLopp = (INT_BITS - 1);     

                      for(; iLoop < iNumberLopp; ++iLoop)
                      {

                        if((num & (1 << iLoop))) // check set bits of num
                        {
                         tmp |= 1 << ((INT_BITS - 1) - iLoop); //putting the set bits of num in tmp
                        }    
                      }

                      return tmp;
                  }

Method 2:
---------
     • It is a simple algorithm to reverse bits of the 32-bit integer.
     • This algorithm uses the eight constant value for the reversing the bits and takes five simple steps.
     
      • Steps 1:
      num = (((num & 0xaaaaaaaa) >> 1) | ((num & 0x55555555) << 1));

  #  This expression used to swap the bits.
    Let an example, suppose num is 0100, after the above expression it will be 1000.

     • Steps 2:
      num = (((num & 0xcccccccc) >> 2) | ((num & 0x33333333) << 2));

  #  Above expression uses to swap the 2 bits of a nibble.
    Suppose num is 10 00, after the above expression, it will be 00 01.

     • Steps 3:
      num = (((num & 0xf0f0f0f0) >> 4) | ((num & 0x0f0f0f0f) << 4));

  #  An expression used to swaps the nibbles.
    like if num is 0011 0010 then after the above expression it will be 0010 0011.

     • Steps 4:
      num = (((num & 0xff00ff00) >> 8) | ((num & 0x00ff00ff) << 8));

  #  This statement uses to swap the bytes of an integer. 
    Let num is 00001000 00001100, after the above expression, it will be 00001100 00001000.

     • Steps 5:
      ((num >> 16) | (num << 16));
   #   The above expression uses to swap the half-word of an integer.
      Means that if the num is 0000000011001110 1000100100000110 
      after the above result number will be 1000100100000110 0000000011001110.
      
--------------------------------------------------------------------------------------------------------

# decimal to Binary
[todo from here]

--------------------------------------------------------------------------------------------------------
# pointers
[todo from here]

•pointers deal with address and value.

•memory address store value,address also strore other address has value.

-->**pointers** are variables which store address.
when we declare  int *p=&a;
p stores '&a' has value. 
so, **'p'** has **value** '&a' ,if not assigned it wil be (**NIL**).

there are two operators associated with pointers.
1) '*' which refers to indirection operation ('content @').
2) '&' which refers to address of the operator.

**Example**

    int i =0;                                     |
    int *q,*p=NULL;                               |
    printf("&i=%p i=%d\n",&i,*(&i));              | &i==>004(a's address)  i=0(a's value)
    printf("p=%p\n",p);                           | p=(NIL) -->p's value
    p=&i;                                         |
    printf("p=%p *p=%d &p=%p q=%p\n",p,*p,&p,q);  | p=004 (p's value)  *p=0 (contenet @ p's value)  &p=008 (address of p)  
    return 0;                                     | q=(NIL) --> Q's value(no address value stored yet). 

**Note** &(&p)  -->we cannot take address of address(i.e its a constant not a valid memory location)
-------------------------------------------------------------------------------------------------------
# memory
[todo from here]

-------------------------------------------------------------------------------------------------------
# big/little endian
[todo from here]

-------------------------------------------------------------------------------------------------------
# function pointers & typedef
[todo from here]

------------------------------------------------------------------------------------------------------
# pointers and array
[todo from here]

------------------------------------------------------------------------------------------------------
# data structure(linked list)
[todo from here]

-----------------------------------------------------------------------------------------------------
# strings
[todo from here]

-----------------------------------------------------------------------------------------------------
# alignment in structure and bit feilds
[todo from here]
https://www.youtube.com/watch?v=Tk-i7iSzCWY
------------------------------------------------------------------------------------------------------
honor mention 
https://www.youtube.com/channel/UCb9okJF6NGPDUGgAQxu3TcA/search?query=c
https://www.youtube.com/watch?v=gGTad760ogM&list=PLTQzjZn0BgA7BHHWKiuhG59bLO7TbNS41&index=48
https://www.youtube.com/user/EmbeddedSoftware/search?query=static
