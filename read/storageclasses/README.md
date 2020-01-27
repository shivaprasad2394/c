# extern 

extern keyword in c
Keyword extern is used for declaring extern variables in c. This modifier is used with all data types like int, float, double, array, pointer, structure, function etc.

Important points about extern keyword:

1. It is default storage class of all global variables as well all functions. For example, Analyze following two c code and its output:

(a)
#include <stdio.h>
int i;    //By default it is extern variable
int main(){
    printf("%d",i);
    return 0;
}

Output: 0

(b)

#include <stdio.h>
extern int i;    //extern variable
int main(){
    printf("%d",i);
    return 0;
}

Output: Compilation error, undefined symbol i.

Question: In Both program variable i is extern variable. But why output is different? Read second and third points.

(c)

#include <stdio.h>
void sum(int,int) //By default it is extern.
int main(){
    int a=5,b=10;
    sum(a,b);
    return 0;
}
void sum(int a,int b){
    printf("%d”",a+b);
}

Output: 15

2. When we use extern modifier with any variables it is only declaration i.e. memory is not allocated for these variable. Hence in second case compiler is showing error unknown symbol i. To define a variable i.e. allocate the memory for extern variables it is necessary to initialize the variables. For example:

#include <stdio.h>
extern int i=10;    //extern variable
int main(){
    printf("%d",i);
    return 0;
}

Output: 10

3. If you will not use extern keyword with global variables then compiler will automatically initialize with default value to extern variable.

4. Default initial value of extern integral type variable is zero otherwise null. For example:

#include <stdio.h>
char c;
int i;
float f;
char *str;  
int main(){
    printf("%d %d %f %s",c,i,f,str);
    return 0;
}

Output: 0 0 0.000000 (null)

5. We cannot initialize extern variable locally i.e. within any block either at the time of declaration or separately. We can only initialize extern variable globally. For example:

(a)
#include <stdio.h>
int main(){
extern int i=10; //Try to initialize extern variable
                 //locally.
    printf("%d",i);
    return 0;
}
Output: Compilation error: Cannot initialize extern variable.

(b)
#include <stdio.h>
int main(){
    extern int i; //Declaration of extern variable i.
    int i=10;     //Try to locally initialization of
                  //extern variable i.
    printf("%d",i);
    return 0;
}

Output: Compilation error: Multiple declaration of variable i.

6. If we declare any variable as extern variable then it searches that variable either it has been initialized or not. If it has been initialized which may be either extern or static* then it is ok otherwise compiler will show an error. For example:

(a)
#include <stdio.h>
int main(){
    extern int i; //It will search the initialization of
                  //variable i.
    printf("%d",i);
    return 0;
}
int i=20;    //Initialization of variable i.

Output: 20

(b)
#include <stdio.h>
int main(){
extern int i; //It will search the any initialized
              //variable i which may be static or 
              //extern.
printf("%d",i);
    return 0;
}
extern int i=20; //Initialization of extern variable i.

Output: 20
(c)
#include <stdio.h>
int main(){
extern int i; //It will search the any initialized
              //variable i which may be static or 
              //extern.
    printf("%d",i);
    return 0;
}
static int i=20; //Initialization of static variable i.


Output: 20

(d)
#include <stdio.h>
int main(){
    extern int i;   //variable i has declared but not
                    //initialized
    printf("%d",i);
    return 0;
}

Output: Compilation error: Unknown symbol i.

7. A particular extern variable can be declared many times but we can initialize at only one time. For example:

(a)
extern int i; //Declaring the variable i.
int i=25;     //Initializing the variable.
extern int i; //Again declaring the variable i.
#include <stdio.h>
int main(){
    extern int i; //Again declaring the variable i.
    printf("%d",i);
    return 0;
}


Output: 25

(b)
extern int i; //Declaring the variable
int i=25;     //Initializing the variable
#include <stdio.h>
int main(){
         printf("%d",i);
    return 0;
}
int i=20; //Initializing the variable


Output: Compilation error: Multiple initialization variable i.

8. We cannot write any assignment statement globally. For example:

#include <stdio.h>
extern int i;
int i=10;   //Initialization statement
i=25;       //Assignment statement
int main(){
    printf("%d",i);
    return 0;
}

Output: Compilation error
Note: Assigning any value to the variable at the time of declaration is known as initialization while assigning any value to variable not at the time of declaration is known assignment.
(b)
#include <stdio.h>
extern int i;
int main(){
    i=25;       //Assignment statement
    printf("%d",i);
    return 0;
}
int i=10;   //Initialization statement

Output: 25

9. If declared an extern variables or function globally then its visibility will whole the program which may contain one file or many files. For example consider a c program which has written in two files named as one.c and two.c:
(a)

//one.c

#include<conio.h>
int i=25; //By default extern variable
int j=5;  //By default extern variable
/**
Above two line is initialization of variable i and j.
*/
void main(){
    clrscr();
    sum();
    getch();
}

//two.c

#include<stdio.h>
extern int i; //Declaration of variable i.
extern int j; //Declaration of variable j.
/**
Above two lines will search the initialization statement of variable i and j either in two.c (if initialized variable is static or extern) or one.c (if initialized variable is extern) 
*/
void sum(){
    int s;
    s=i+j;
    printf("%d",s);
}

Compile and execute above two file one.c and two.c at the same time:

In Turbo c compiler

Step 1: Write above two codes in the file named as one.c and two.c (You can give any name as you like) and save it.
Step 2: In Turbo c++ IDE click on Project -> Open project menu as shown in following screen dump.
