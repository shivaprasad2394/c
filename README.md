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

Macro                                        v/s                              functions
================================================================================================                                        
    No TypeChecking                           |                             exist
    preprocessed                              |                             compiled
    codelength increases on Macro call        |                             remains same
    Speed of Execution faster                 |                             Speed of execution Slower
    useful in small code                      |                             usefull in large code
    difficult to debug                        |                             Easy
    
    =============================================================================================
