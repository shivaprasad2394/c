# static
https://www.cquestions.com/2011/02/static-variable-in-c.html

static variable in c
static keyword in c:

    Keyword static is used for declaring static variables in c. This modifier is used with all data types like int, float, double, array, pointer, structure, function etc.

Important points about static keyword:

1. It is not default storage class of global variables. For example, analyze the following three programs and its output.

(a)

#include<stdio.h>
int a;
int main(){
    printf("%d",a);
    return 0;
}

Output: 0

(b)
#include<stdio.h>
static int a;
int main(){
    printf("%d",a);
    return 0;
}

Output: 0

(c)
#include<stdio.h>
extern int a;
int main(){
    printf("%d",a);
    return 0;
}
Output: Compilation error

At first glance if you will observe the output of above three codes you can say default storage class of global variable is static. But it is not true. Why? Read extern storage class.

2. Default initial value of static integral type variables are zero otherwise null. For example:

#include <stdio.h>
static char c;
static int i;
static float f;
static char *str;  
int main(){
    printf("%d %d %f %s",c,i,f,str);
    return 0;
}

Output: 0 0 0.000000 (null)

3. A same static variable can be declared many times but we can initialize at only one time. For example:

(a)
#include <stdio.h>
static int i;        //Declaring the variable i.
static int i=25;     //Initializing the variable.
static int i;        //Again declaring the variable i.
int main(){
    static int i;    //Again declaring the variable i.
    printf("%d",i);
    return 0;
}

Output: 25

(b)
#include <stdio.h>
static int i;        //Declaring the variable
static int i=25;     //Initializing the variable
int main(){
         printf("%d",i);
    return 0;
}
static int i=20;     //Again initializing the variable

Output: Compilation error: Multiple initialization variable i.

 

4. We cannot write any assignment statement globally. For example:
#include <stdio.h>
static int i=10;   //Initialization statement
i=25;              //Assignment statement
int main(){
    printf("%d",i);
    return 0;
}
            
Output: Compilation error

Note: Assigning any value to the variable at the time of declaration is known as initialization while assigning any value to variable not at the time of declaration is known assignment.

(b)
#include <stdio.h>
static int i=10;
int main(){
    i=25;       //Assignment statement
    printf("%d",i);
    return 0;
}

Output: 25

(5) A static variable initializes only one time in whole program. For example:

#include <stdio.h>
static int i=10;
int main(){
    i=5;
    for(i=0;i<5;i++){
         static int a=10; //This statement will execute
                          //only time.
         printf("%d",a++);//This statement will execute
                          //five times.
    }  
    return 0;
}

Output: 10 11 12 13 14

(6)If we declared static variable locally then its visibility will within a block where it has declared. For example:

#include<stdio.h>
int main(){
    {                       
         static int a=5;     
         printf("%d",a);
    }                       
    //printf("%d",a);   variable a is not visible here.
    return 0;   
}

Output: 5

7. If declared a static variable or function globally then its visibility will only the file in which it has declared not in the other files. For example:

(a)
#include<stdio.h>
static float a=144.0f; //global to all function
int main(){
    {                        
         printf("%d",a); //variable a is visible here.
       //printf("%d",b); variable b is not visible here.
    }                       
    printf("%d",a);   //variable a is visible here.
    //printf("%d",b);    variable b is not visible here.
    return 0;
}
static int b=5;    //Global to only calculation function
void calculation(){
    printf("%d",a);   //variable a is visible here.
    printf("%d",b);   //variable b is visible here.
}
   
(b) Consider a c program which has written in two files named as one.c and two.c:

//one.c

#include<conio.h>
static int i=25;
static int j=5; 

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
extern void sum(){
    int s;
    s=i+j;
    printf("%d",s);
}

