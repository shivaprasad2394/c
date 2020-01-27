# auto
todo more@ below link.
https://www.cquestions.com/2009/09/return-type-of-function-in-c.html
Return type of function in c programming

return is keyword of c. When the control reaches to the return keyword it immediately terminates the execution of that function and transfer the control to the calling function.

Syntax of return statement:

Here expression is optional which has indicated by [ ].
Example:


#include<stdio.h>
void dev();
int main(){
    printf("one\n");
    dev();
    printf("two\n");
    return 0;
}
void dev(){
    printf("three\n");
    return;
    printf("four\n");
}

Output:
one
three
two


Features of return type of function in C programming



1. Default return type of function is signed int data type.

2. Function can return only one value at a time.

3. Storage classes allowed with return type are static, extern, typedef i.e. we cannot use auto and register storage class with the return type of any function.


#include<stdio.h>
auto int tcs(int);
int main(){
    int a=5;
    a=tcs(a);
    printf("%d",a);
    return 0;
}
auto int tcs(int x){
    return x++;
}

Output: Compilation error

4. Default storage class of return type of a function is extern.
5. In return type we can use modifier like short, long, signed, unsigned, extern, static, const, volatile etc.


#include<stdio.h>
long unsigned static const ddlg(){
    static const long unsigned a=0101;
    return a;
}
int main(){
    long number;
    number=ddlg();
    printf("%X",number);
    return 0;
}

Output:41

Return type of function can be:


1. Primitive data type: Primitive data types are: char, int, float, double, void 
Examples:


a. function which is returning char data type
b. function which is returning int data type
c. function which is returning float data type
d. function which is returning double data type
e. function which is returning void data type

2. Derived data type.


Derived data types are: array, function, pointer
Examples:


a. Function which is returning array
b. function which is returning function
c. function which is returning pointer


3. User defined data type.


User defined data types are: structure, union, enum
Examples:


a. Function which is returning structure
b. Function which is returning union
c. Function which is returning enum
