C
=============================================================================================================================
storage classes :- 
---------------
                   1)decide the extent(lifetime)
                   2)scope (visibility)
                   3)storage location in memory.
there are 4 types of storage class specifier:-
--------------------------------------------

    1)auto    -->Local variables,Garbage value(default).
    2)static  -->internal or no linkage,memory persistant,initialized once.
    3)register-->no storage allocation for variable,indicates/informs compiler about offload declaration/definition of variable.
    4)extern  -->Local to Function,informs compiler to store the variable in cpu registers.

----------------------------------------------------------------------------------------------------------------------------
scope difference
----------------
    
    1)Global variable-->Extenal linkage
    2)Global static  -->Internal linkage
    3)Local static   -->no linkage

----------------------------------------------------------------------------------------------------------------------------

    static default value-->0 
    ============================================================================================

Macro-------------------->>v/s<<-----------------functions
================================================================================================                                        
    No TypeChecking                           |                             exist
    preprocessed                              |                             compiled
    codelength increases on Macro call        |                             remains same
    Speed of Execution faster                 |                             Speed of execution Slower
    useful in small code                      |                             usefull in large code
    difficult to debug                        |                             Easy
    
    =============================================================================================

typedef :-defining new names to existing types.
-------  
    Pros:-
        • to reduce complexity
        • to increase code readability and portability.
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
      

