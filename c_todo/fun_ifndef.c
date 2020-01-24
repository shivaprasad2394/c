#include<stdio.h>
int main() 
{
printf("Preprocessors also support if-else directives which are typically used for conditional compilation\nA header file may be included more than one time directly or indirectly, this leads to problems of redeclaration of same variables/functions\nTo avoid this problem, directives like defined, ifdef and ifndef are used.\n"); 
#if VERBOSE >= 2 
  printf("Trace Message"); 
#endif 
}

