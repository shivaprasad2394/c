/* 
 * explaining strtok :-https://www.youtube.com/watch?v=34DnZ2ewyZo
#include<stdio.h>
#include<stlib.h>
#include<string.h>

int main(){
char * str[]="Lets break this string into pieces";//in mem==>"Lets break this string into pieces"
char * piece = strtok(str,"");//in mem ==>str value now="Lets \000 break this string into pieces" 
printf("%s\n",piece);//in mem==>piece value ==>same memory basically poinert readng the same string"Lets"
piece = strtok(NULL,"");//no change here for str
printf ("%s\n",piece);//in mem ==>str value now="Lets \000 break \000 this string into pieces"
return 0;
}
*/
/*include<stdio.h>
#include<stlib.h>
#include<string.h>

int main(){
char * str[]="Lets break this string into pieces";//in mem==>"Lets break this string into pieces"
char * piece = strtok(str,"");//in mem ==>str value now="Lets \000 break this string into pieces"
while(piece !=NULL){
printf("%s\n",piece);//in mem==>piece value ==>same memory basically poinert readng the same string"Lets"
piece=strtok(NULL,"");
}
return 0;
}*/
//======string initialization=============
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    // Const string, will break
    // char *str = "Hello!";
    
    // String on the stack, will work
    // char str[] = "Hello!";
    
    // Dynamically allocated string on the heap, will work
    char *str = malloc(50, sizeof(char));
    strcpy(str, "Hello!");
    
    printf("%s\n", str);
    str[0] = 'h';
    printf("%s\n", str);
    
    // Only needed for dynamically allocated string
    free(str);
    return 0;
}
