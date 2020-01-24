#include<stdio.h>
int add(int a,int b){
printf("add=%d",(a+b));
return (a+b);
}
int mul(int a,int b){
printf("mult=%d",(a*b));
return(a*b);
}
void* print_ops(int a,int b,void* (*op)(int,int)){
return ((void *)op(a,b));
}
void main(){
printf("funtion pointer are used to store address of a function that we want to call later on\nit is a way to assigning function to a variable using typedef to function pointers\na function pointer can be represesnted in like this for no return type\tvoid (*poi) (int)\nand for return type void* like this \tvoid *(*poi)(int *)\nwhen we are typedef ing any function poinetr of type void (*__fun_name__)()-->fun_name represent the function name ----for further refer jacobsorber\nso far typedef --> typedef void(*__alias_name__)(__parameter__)\nand then example-->alias_name <some_name>=&function\n<some_name()>--->calls function\nrun time polymorphism cab also be implemented using function pointer\n");
int result=(int *)print_ops(3,4,add);
int result1=(int *)print_ops(4,5,mul);
}
