#include<stdio.h>
void main(){
int i=6;
int *p=&i;
printf("p=%u\n",p);//value/addr stored in pointer.
printf("*p=%d\n",*p);//content at that addr.
printf("&p=%u\n",&p);//addr of pointer.
printf("&i=%u\n",&i);//addr in varible/object.
}
