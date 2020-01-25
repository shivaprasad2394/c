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

Macro---------------------------->>v/s<<--------------------functions
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
  
