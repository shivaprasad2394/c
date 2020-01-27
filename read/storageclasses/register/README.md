# Register
https://www.cquestions.com/2011/02/register-storage-class-in-c.html

register storage class in c

Register storage class specifiers in c with example


A register storage class is very similar to auto storage class except one most important property. All register variable in c stores in CPU not in the memory.

Important points about register storage class

(1)In following declaration:

    register int a;

We are only requesting not forcing to compiler to store variable a in CPU. Compiler will decide where to store in the variable a.

(2)A register variable execute faster than other variables because it is stored in CPU so during the execution compiler has no extra burden to bring the variable from memory to CPU.

(3)Since a CPU have limited number of register so it is programmer responsibility which variable should declared as register variable i.e. variable which are using many times should declared as a register variable.

(4) We cannot dereference register variable since it has not any memory address. For example:
     
(a)
#include<stdio.h>
int main(){
    register int a=10;
    int *p;
    p=&a;
    printf("%u",p);
}

Output: Compilation error

(b)
#include<stdio.h>
int main(){
    register int a,b;
    scanf("%d%d",&a,&b);
    printf("%d  %d",a,b);
}

Output: Compilation error

(5) Default initial value of register variable is garbage.

(6) Scope and visibility of register variable is block.
