//wrong codedont learn:wap to init str without static len allocation.
/*#include <stdio.h>
#include<string.h>
int main() {
int l;
char *name;
printf("Enter your input plz: ");
scanf("%d",&l);
printf("input str len should be =%d\n",l+1);
printf("input:\n");
//puts("Hold it!");
//fflush(stdout);
//fflush(stdin);
setbuf(stdin,name);
fgets(name,(l+1),stdin);
printf("input is %s\n",name);
printf("strlen=%ld\n",strlen(name));
return 0;
}
*/
//wap to remove duplicate char from str.
//wap to reverse words of a str.

#include <stdio.h>
#include<string.h>
#define SIZE 30

void reverse_words(char str[]){
printf("enter");
int f,l,k=0;
printf("whole reverse:");
while(f<l){
//swap first and last chars logic:- a=a+b-(b=a).
str[f]=str[f]+str[l]-(str[l]=str[f]);
f++;
l--;
}
printf("str_revfull=%s",str);
}

int main() {
char buf[SIZE];
gets(buf);
printf("string is: %s\n", buf); 
reverse_words(buf);
return 0;
}
