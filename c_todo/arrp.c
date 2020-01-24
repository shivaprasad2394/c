#include<stdio.h>
#define SIZE 10
 
int main()
{
    int *arrop[3];
    int a[2] = {10,20,30} ;int b[2] = {40,50,60}; int c[2] = {70,80,90};
    int i;
 
    arrop[0] = a;
    arrop[1] = b;
    arrop[2] = c;
 
    for(i = 0; i < 3; i++)
    {
        printf("Value = %d\n",  *(arrop[i]+1));
    }
 
    return 0;
}
