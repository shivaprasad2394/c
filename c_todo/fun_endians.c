#include <stdio.h> 

/* function to show bytes in memory, from location start to start+n*/
void show_mem_rep(char *start, int n) 
{ 
	int i; 
        printf(" little endian representation\n");
	for (i = 0; i < n; i++) 
		printf(" %.2x", start[i]); 
	printf("\n"); 
} 

/*Main function to call above function for 0x01234567*/
int main() 
{ 
int i = 0x01234567; 
printf("Little and big endian are two ways of storing multibyte data-types ( int, float, etc). \nIn little endian machines, 'last byte' of binary representation of the multibyte data-type is stored 'first'. \nOn the other hand, in big endian machines, 'first byte' of binary representation of the multibyte data-type is stored 'first'.\n");
show_mem_rep((char *)&i, sizeof(i)); 
getchar(); 
return 0; 
} 

