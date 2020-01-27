C
=============================================================================================================================
storage classes :- 
---------------
                   1)decide the extent(lifetime) of variable.
                   2)scope (visibility) of the variable
                   3)storage location in memory.
there are 4 types of storage class specifier:-
--------------------------------------------

    1)auto------->a default specifier class for local variables,if variable not specifeid any storage class.
                 • Local variables are auto by default,Garbage value(default).
                 •function with auto specifier cannot have reurn type.if trier will give compilation error.
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

Macro-------------------->>v/s<<-----------------functions
================================================================================================                                        
    No TypeChecking (ex:- func parameter)     |                             exist
    preprocessed                              |                             compiled
    codelength increases on Macro call        |                             remains same
    Speed of Execution faster                 |                             Speed of execution Slower
    useful in small code                      |                             usefull in large code
    difficult to debug                        |                             Easy
    
    =============================================================================================

     • In macros, no type checking(incompatible operand, etc.) is done and thus use of micros can lead to errors/side-effects in some cases.
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
when pointers come into picture there are two things one is the address and second is the value.
addresses store value ,addresses also store other addresses as value.
map the difference, addresses cannot store address but they can store address as if their values.
now pointers is a very important concept so what is a pointer so here you see I have written star p it
is an int pointer what it means is P
will be some address and that address
will actually contain an integer the
address will be of one individual bite
but when you will dereference that is
you will try to get star p then you will
get the value of value contained at that
address which is actually contained at p
okay so it is little bit infusing yes
yes I know now there are two operators
involved one is star know there is
ampersand star is called indirection &
ampersand is called address of operator
now this over here note that star p is
equal to null when we write then it does
not mean that star p is equal to null
but what it means is p is equal to none
star p is the notation for p being a
pointer we could have equivalently
written inch star Q and Q is equal to none
now consider a plane variable I which we
have declared now if i right ampersand I
that means the address of that variable
I and if i right star of ampersand I
then that means value at that address
think that I have a ball and I have a
bag and the ball is inside the bag then
I ask myself a question hey which bag
contains this ball for example I is the
ball an ampersand is the back so you
will say okay this bag contains the ball
so you get ampersand I then I say okay
now tell me this bag contains which ball
so that is like getting the
dereferencing so you'll get that ball
again so you get the original ball that
is I now here p is initially nil that is
mala now I say okay here p now you can
store the address of I ok p is basically
storing the address of I that means you
keep a copy now here you see p
percentage p so p is a pointer because
it is keeping a copy of that and then
star p is nothing but e when we
dereference that address then we get
nothing but i but since he is keeping in
a copy of address itself is not an
address so we can take its address again
and then i have just used q so that it
does not give me the unused variable
warning but now if i want to take
address of P then it's not possible
because it's not an lvalue its address
cannot be taken okay we'll see in a
second how
so let us compile this i think i'll
compile this program already okay so
let's from this okay so we see this
output home right now as I said you
cannot take a dress off an address
samples and paste address so let's try
to compile this now lvalue required now
what is an lvalue i think i have told
this in one or two tutorials that L
value is something whose address can be
taken an expression is not an lvalue
similarly an address is not an lvalue
strings like this are not an lvalue
these are format strings something which
is stored in a variable yes a string
stored in the variable is an lvalue
these will be created at runtime and
will be destroyed actually these are
embedded into the cold in the assembly
code the entire string will be murdered
and then the variable substitution
happens but this will be received by
printf function so that's how it will
work so make sure you understand what is
a star and what is ampersand that is
critical as far as syntax is concerned
if you get messed up with ampersand and
stuff no hope and also remember you can
take address of P that is address off
the pointer pointers have an address
remember and they contain address also
but then the address of the first
address cannot be taken that if
ampersand ampersand I is not allowed you
say p of ampersand I so I said that okay
ampersand p we can do so that means i am
percent numbers and i should be allowed
know even that is not allowed no even
that is not allowed so you can even
though he is nothing but ampersand I but
then this is not actually like a link it
is making a copy of that that is why it
is making a copy so P itself will occupy
space and that will be its address that
memory address four bytes and then on
that memory ampersand I will be written
and then amples and I is something else
that is the address which will contain
the value of eyes it's like you have two
cells think like this 0x a this is the
memory and it contains ampersand I and
then you have some memory as 0 X B and
it contains ok small I then it contains
I now what is ampersand is nothing but 0
X B now you can modify this part 0 X B
but you cannot take address of 0 X a and
0 X B now if you do ampersand ampersand
I it is like you are trying to get a
dress of 0 X B and if we do ampersand
ampersand of T you are trying to get a
dress of a but if you do ampersand
ampersand of a sorry if you do ampersand
of P that is like you are trying to get
the address of 0 X B which is nothing
but 0 XA i hope this much makes things
rather clear so now we will proceed in
our next example along with the we'll
start with swap function rather i should
avoid swap will leave its up when we hit
functions we will proceed with malach
car lock and
remember related functions which involve
pointers and you see how the allocate
memory on heap and how do we deal Oh
Kate those thanks for watching the video
and for reading more about it hop on to
limit programming dot o RG in the
process of rewriting the book using c11
specification and I hope to complete
that in let's say six to eight months
given that time and health permits make
am suffering from cold so all the videos
recorded today having this problem and
make sure you read the spec and you can
read the dentistry itself for getting
the concept on this or you can read many
other books which I have shown in my
first or second video the list of books
thanks for watching the video happy
programming

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
